#pragma once

#include "F4SE/Logger.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSScript.h"
#include "RE/Bethesda/GameScript.h"
#include "RE/Bethesda/TESForms.h"

namespace RE::BSScript
{
	namespace detail
	{
		// clang-format off
		template <class F, class R, class... Args>
		concept invocable_r = requires(F&& a_func, Args&&... a_args)
		{
			{ std::invoke(std::forward<F>(a_func), std::forward<Args>(a_args)...) } -> std::same_as<R>;
		};
		// clang-format on

		template <class T>
		concept static_tag = std::same_as<T, std::monostate>;

		// clang-format off
		template <class T>
		concept object =
			std::is_pointer_v<T> &&
			std::derived_from<std::remove_pointer_t<T>, TESForm> &&
			requires { T::FORM_ID; };
		// clang-format on

		// clang-format off
		template <class T>
		concept string =
			std::convertible_to<T, std::string_view> &&
			std::constructible_from<T, std::string_view>;
		// clang-format on

		template <class T>
		concept integral =
			(std::integral<T> && !std::same_as<std::remove_cv_t<T>, bool>) ||
			std::is_enum_v<T>;

		template <class T>
		concept signed_integral =
			(std::signed_integral<T> && !std::same_as<std::remove_cv_t<T>, bool>) ||
			(std::is_enum_v<T> && std::signed_integral<std::underlying_type_t<T>>);

		template <class T>
		concept unsigned_integral =
			(std::unsigned_integral<T> && !std::same_as<std::remove_cv_t<T>, bool>) ||
			(std::is_enum_v<T> && std::unsigned_integral<std::underlying_type_t<T>>);

		template <class T>
		concept floating_point = std::floating_point<T>;

		template <class T>
		concept boolean = std::same_as<std::remove_cv_t<T>, bool>;

		template <class T>
		concept valid_self =
			static_tag<T> ||
			object<T>;

		template <class T>
		concept valid_parameter =
			object<T> ||
			string<T> ||
			integral<T> ||
			floating_point<T> ||
			boolean<T>;

		template <class T>
		concept valid_return =
			valid_parameter<T> ||
			std::same_as<T, void>;
	}

	template <class T>
	[[nodiscard]] constexpr std::uint32_t GetVMTypeID() noexcept
		requires std::same_as<T, void>
	{
		return static_cast<std::uint32_t>(TypeInfo::RawType::kNone);
	}

	template <detail::static_tag T>
	[[nodiscard]] constexpr std::uint32_t GetVMTypeID() noexcept
	{
		return static_cast<std::uint32_t>(TypeInfo::RawType::kNone);
	}

	template <detail::object T>
	[[nodiscard]] constexpr std::uint32_t GetVMTypeID() noexcept
	{
		return static_cast<std::uint32_t>(T::FORM_ID);
	}

	template <detail::string T>
	[[nodiscard]] constexpr std::uint32_t GetVMTypeID() noexcept
	{
		return static_cast<std::uint32_t>(TypeInfo::RawType::kString);
	}

	template <detail::integral T>
	[[nodiscard]] constexpr std::uint32_t GetVMTypeID() noexcept
	{
		return static_cast<std::uint32_t>(TypeInfo::RawType::kInt);
	}

	template <detail::floating_point T>
	[[nodiscard]] constexpr std::uint32_t GetVMTypeID() noexcept
	{
		return static_cast<std::uint32_t>(TypeInfo::RawType::kFloat);
	}

	template <detail::boolean T>
	[[nodiscard]] constexpr std::uint32_t GetVMTypeID() noexcept
	{
		return static_cast<std::uint32_t>(TypeInfo::RawType::kBool);
	}

	template <detail::object T>
	void PackVariable(Variable& a_var, const T* a_val)
	{
		const auto success = [&]() {
			const auto game = GameVM::GetSingleton();
			const auto vm = game ? game->GetVM() : nullptr;
			BSTSmartPointer<ObjectTypeInfo> typeInfo;
			if (!vm || !vm->GetScriptObjectType(GetVMTypeID<T>(), typeInfo) || !typeInfo) {
				return false;
			}

			const auto& handles = vm->GetObjectHandlePolicy();
			const auto handle = handles.GetHandleForObject(
				GetVMTypeID<T>(),
				const_cast<const void*>(
					static_cast<const volatile void*>(a_val)));
			if (handle == handles.EmptyHandle()) {
				return false;
			}

			BSTSmartPointer<Object> object;
			if (!vm->FindBoundObject(handle, typeInfo->name.c_str(), false, object, false) &&
				vm->CreateObject(typeInfo->name, object) &&
				object) {
				auto& binding = vm->GetObjectBindPolicy();
				binding.BindObject(object, handle);
			}

			if (!object) {
				return false;
			}

			a_var = std::move(object);
			return true;
		}();

		if (!success) {
			assert(false);
			F4SE::log::error("failed to pack variable"sv);
			a_var = nullptr;
		}
	}

	template <detail::string T>
	void PackVariable(Variable& a_var, T&& a_val)
	{
		a_var = BSFixedString(std::forward<T>(a_val));
	}

	template <detail::signed_integral T>
	void PackVariable(Variable& a_var, T&& a_val)
	{
		a_var = static_cast<std::int32_t>(a_val);
	}

	template <detail::unsigned_integral T>
	void PackVariable(Variable& a_var, T&& a_val)
	{
		a_var = static_cast<std::uint32_t>(a_val);
	}

	template <detail::floating_point T>
	void PackVariable(Variable& a_var, T&& a_val)
	{
		a_var = static_cast<float>(a_val);
	}

	template <detail::boolean T>
	void PackVariable(Variable& a_var, T&& a_val)
	{
		a_var = static_cast<bool>(a_val);
	}

	template <detail::static_tag T>
	[[nodiscard]] std::monostate UnpackVariable([[maybe_unused]] const Variable& a_var)
	{
		assert(a_var.is<std::nullptr_t>());
		return {};
	}

	template <detail::object T>
	[[nodiscard]] T* UnpackVariable(const Variable& a_var)
	{
		const auto result = [&]() -> void* {
			const auto game = GameVM::GetSingleton();
			const auto vm = game ? game->GetVM() : nullptr;
			const auto object = get<Object>(a_var);
			if (!vm || !object) {
				return nullptr;
			}

			const auto& handles = vm->GetObjectHandlePolicy();
			const auto handle = object->GetHandle();
			if (!handles.IsHandleLoaded(handle)) {
				return nullptr;
			}

			return handles.GetObjectForHandle(GetVMTypeID<T>(), handle);
		}();

		if (!result) {
			assert(false);
			F4SE::log::error("failed to get object from variable"sv);
		}

		return static_cast<T*>(result);
	}

	template <detail::string T>
	[[nodiscard]] T UnpackVariable(const Variable& a_var)
	{
		return T(static_cast<std::string_view>(get<BSFixedString>(a_var)));
	}

	template <detail::signed_integral T>
	[[nodiscard]] T UnpackVariable(const Variable& a_var)
	{
		return static_cast<T>(get<std::int32_t>(a_var));
	}

	template <detail::unsigned_integral T>
	[[nodiscard]] T UnpackVariable(const Variable& a_var)
	{
		return static_cast<T>(get<std::uint32_t>(a_var));
	}

	template <detail::floating_point T>
	[[nodiscard]] T UnpackVariable(const Variable& a_var)
	{
		return static_cast<T>(get<float>(a_var));
	}

	template <detail::boolean T>
	[[nodiscard]] T UnpackVariable(const Variable& a_var)
	{
		return static_cast<T>(get<bool>(a_var));
	}

	template <class>
	class NativeFunction;

	template <
		detail::valid_return R,
		detail::valid_self S,
		detail::valid_parameter... Args>
	class NativeFunction<R(S, Args...)> :
		public NF_util::NativeFunctionBase
	{
	private:
		using super = NF_util::NativeFunctionBase;

	public:
		// clang-format off
		template <class F>
			requires detail::invocable_r<F, R, S, Args...>
		NativeFunction(std::string_view a_object, std::string_view a_function, F a_func) :
			super(a_object, a_function, sizeof...(Args), detail::static_tag<S>),
			_stub(std::move(a_func))
		// clang-format on
		{
			assert(super::descTable.paramCount == sizeof...(Args));
			std::size_t i = 0;
			((super::descTable.entries[i++].second = GetVMTypeID<Args>()), ...);
			super::retType = GetVMTypeID<R>();
		}

		// override (NF_util::NativeFunctionBase)
		bool HasStub() const override { return static_cast<bool>(_stub); }  // 15

		bool MarshallAndDispatch(Variable& a_self, Internal::VirtualMachine&, std::uint32_t, Variable& a_retVal, const StackFrame& a_stackFrame) const override  // 16
		{
			a_retVal = nullptr;

			const auto stack = a_stackFrame.parent;
			if (!stack) {
				assert(false);
				F4SE::log::error("native function called without relevant stack"sv);
				return false;
			}

			const auto invoke = [&]() {
				const auto pframe = std::addressof(a_stackFrame);
				const auto page = stack->GetPageForFrame(pframe);
				std::uint32_t i = 0;
				return _stub(
					UnpackVariable<S>(a_self),
					(UnpackVariable<Args>(stack->GetStackFrameVariable(pframe, i++, page)), ...));
			};

			if constexpr (!std::same_as<R, void>) {
				PackVariable(a_retVal, invoke());
			} else {
				invoke();
			}

			return true;
		}

	private:
		std::function<R(S, Args...)> _stub;
	};

	template <
		detail::valid_return R,
		detail::valid_self S,
		detail::valid_parameter... Args>
	NativeFunction(std::string_view, std::string_view, R (*)(S, Args...)) -> NativeFunction<R(S, Args...)>;
}
