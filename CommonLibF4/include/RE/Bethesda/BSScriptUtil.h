#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSScript.h"
#include "RE/Bethesda/GameScript.h"
#include "RE/Bethesda/TESForms.h"

#include "F4SE/Logger.h"

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
			std::derived_from<T, TESForm> &&
			requires { T::FORM_ID; };
		// clang-format on

		template <class T>
		concept string =
			std::convertible_to<T, std::string_view> &&
			std::constructible_from<T, std::string_view>;

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

		// clang-format off
		template <class T>
		concept boolean = std::same_as<std::remove_cv_t<T>, bool>;
		// clang-format on

		template <class T>
		concept valid_self =
			static_tag<T> ||
			(std::is_reference_v<T>&& object<std::remove_reference_t<T>>);

		template <class T>
		concept valid_parameter =
			(std::is_pointer_v<T> && object<std::remove_pointer_t<T>>) ||
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
	[[nodiscard]] constexpr TypeInfo::RawType GetVMTypeID() noexcept
		requires(std::same_as<T, void>)
	{
		return TypeInfo::RawType::kNone;
	}

	template <detail::static_tag T>
	[[nodiscard]] constexpr TypeInfo::RawType GetVMTypeID() noexcept
	{
		return TypeInfo::RawType::kNone;
	}

	template <detail::object T>
	[[nodiscard]] constexpr TypeInfo::RawType GetVMTypeID() noexcept
	{
		return static_cast<TypeInfo::RawType>(T::FORM_ID);
	}

	template <detail::string T>
	[[nodiscard]] constexpr TypeInfo::RawType GetVMTypeID() noexcept
	{
		return TypeInfo::RawType::kString;
	}

	template <detail::integral T>
	[[nodiscard]] constexpr TypeInfo::RawType GetVMTypeID() noexcept
	{
		return TypeInfo::RawType::kInt;
	}

	template <detail::floating_point T>
	[[nodiscard]] constexpr TypeInfo::RawType GetVMTypeID() noexcept
	{
		return TypeInfo::RawType::kFloat;
	}

	template <detail::boolean T>
	[[nodiscard]] constexpr TypeInfo::RawType GetVMTypeID() noexcept
	{
		return TypeInfo::RawType::kBool;
	}

	template <detail::object T>
	void PackVariable(Variable& a_var, const T* a_val)
	{
		const auto success = [&]() {
			const auto game = GameVM::GetSingleton();
			const auto vm = game ? game->GetVM() : nullptr;
			BSTSmartPointer<ObjectTypeInfo> typeInfo;
			if (!vm ||
				!vm->GetScriptObjectType(
					static_cast<std::uint32_t>(GetVMTypeID<T>()),
					typeInfo) ||
				!typeInfo) {
				return false;
			}

			const auto& handles = vm->GetObjectHandlePolicy();
			const auto handle = handles.GetHandleForObject(
				static_cast<std::uint32_t>(GetVMTypeID<T>()),
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

			return handles.GetObjectForHandle(static_cast<std::uint32_t>(GetVMTypeID<T>()), handle);
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

	template <
		class F,
		bool LONG,
		detail::valid_return R,
		detail::valid_self S,
		detail::valid_parameter... Args>
	class NativeFunction :
		public NF_util::NativeFunctionBase
	{
	private:
		using super = NF_util::NativeFunctionBase;

	public:
		template <class Fn>
		NativeFunction(std::string_view a_object, std::string_view a_function, Fn a_func)  //
			requires(detail::invocable_r<Fn, R, S, Args...> ||
					 detail::invocable_r<Fn, R, IVirtualMachine&, std::uint32_t, S, Args...>) :
			super(a_object, a_function, sizeof...(Args), detail::static_tag<S>),
			_stub(std::move(a_func))
		{
			assert(super::descTable.paramCount == sizeof...(Args));
			std::size_t i = 0;
			((super::descTable.entries[i++].second = GetVMTypeID<Args>()), ...);
			super::retType = GetVMTypeID<R>();
		}

		// override (NF_util::NativeFunctionBase)
		bool HasStub() const override { return static_cast<bool>(_stub); }  // 15

		bool MarshallAndDispatch(Variable& a_self, Internal::VirtualMachine& a_vm, std::uint32_t a_stackID, Variable& a_retVal, const StackFrame& a_stackFrame) const override  // 16
		{
			a_retVal = nullptr;

			const auto stack = a_stackFrame.parent;
			if (!stack) {
				assert(false);
				F4SE::log::error("native function called without relevant stack"sv);
				return false;
			}

			const auto invoke = [&]() {
				return [&]<std::size_t... I>(std::index_sequence<I...>)
				{
					const auto self = [&]() -> S {
						if constexpr (detail::static_tag<S>) {
							return std::monostate{};
						} else {
							auto* const ret = UnpackVariable<std::remove_reference_t<S>>(a_self);
							assert(ret != nullptr);  // super::Call should guarantee this
							return *ret;
						}
					};

					const auto pframe = std::addressof(a_stackFrame);
					const auto page = stack->GetPageForFrame(pframe);
					const auto args = [&]<class T>(std::in_place_type_t<T>, std::size_t a_index) {
						return UnpackVariable<std::remove_pointer_t<T>>(stack->GetStackFrameVariable(pframe, a_index, page));
					};

					if constexpr (LONG) {
						return _stub(
							reinterpret_cast<IVirtualMachine&>(a_vm),  // TODO: static_cast
							a_stackID,
							self(),
							args(std::in_place_type_t<Args>{}, I)...);
					} else {
						return _stub(
							self(),
							args(std::in_place_type_t<Args>{}, I)...);
					}
				}
				(std::index_sequence_for<Args...>{});
			};

			if constexpr (!std::same_as<R, void>) {
				PackVariable(a_retVal, invoke());
			} else {
				invoke();
			}

			return true;
		}

	private:
		std::function<F> _stub;
	};

	template <
		detail::valid_return R,
		detail::valid_self S,
		detail::valid_parameter... Args>
	NativeFunction(std::string_view, std::string_view, R (*)(S, Args...))
		-> NativeFunction<
			R(S, Args...),
			false,
			R,
			S,
			Args...>;

	template <
		detail::valid_return R,
		detail::valid_self S,
		detail::valid_parameter... Args>
	NativeFunction(std::string_view, std::string_view, R (*)(IVirtualMachine&, std::uint32_t, S, Args...))
		-> NativeFunction<
			R(IVirtualMachine&, std::uint32_t, S, Args...),
			true,
			R,
			S,
			Args...>;

	template <class F>
	void IVirtualMachine::BindNativeMethod(stl::zstring a_object, stl::zstring a_function, F a_func, std::optional<bool> a_taskletCallable)
	{
		const auto success = BindNativeMethod(new NativeFunction(a_object, a_function, std::move(a_func)));
		if (!success) {
			F4SE::log::warn("failed to register method \"{}\" on object \"{}\""sv, a_function, a_object);
		}

		if (success && a_taskletCallable) {
			SetCallableFromTasklets(a_object.data(), a_function.data(), *a_taskletCallable);
		}
	}
}
