#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSScript.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/GameScript.h"
#include "RE/Bethesda/TESForms.h"

#include "F4SE/Logger.h"

namespace RE::BSScript
{
	namespace detail
	{
		struct wrapper_accessor;

		template <class T>
		void PackVariable(Variable& a_var, T&& a_val);

		template <class T>
		[[nodiscard]] T UnpackVariable(const Variable& a_var);

		template <class CharT, std::size_t N1, std::size_t N2>
		[[nodiscard]] consteval auto make_structure_tag(
			stl::nttp::string<CharT, N1> a_lhs,
			stl::nttp::string<CharT, N2> a_rhs) noexcept
			-> stl::nttp::string<CharT, N1 + 1 + N2>
		{
			char buf[a_lhs.length() + 1 + a_rhs.length() + 1]{ '\0' };
			std::copy_n(a_lhs.data(), a_lhs.length(), buf);
			buf[a_lhs.length()] = '#';
			std::copy_n(a_rhs.data(), a_rhs.length(), buf + a_lhs.length() + 1);
			return { static_cast<const char(&)[N1 + 1 + N2 + 1]>(buf) };
		}
	}

	template <
		stl::nttp::string O,
		stl::nttp::string S>
	class structure_wrapper
	{
	private:
		static constexpr stl::nttp::string _full = detail::make_structure_tag(O, S);

	public:
		static constexpr std::string_view name{ _full.data(), _full.length() };

		structure_wrapper()
		{
			if (!_proxy) {
				const auto game = GameVM::GetSingleton();
				const auto vm = game ? game->GetVM() : nullptr;
				if (!vm ||
					!vm->CreateStruct(name, _proxy) ||
					!_proxy) {
					F4SE::log::error(
						FMT_STRING("failed to create structure of type \"{}\""),
						name);
					assert(false);
				}
			}
		}

		template <class T>
		bool insert(std::string_view a_name, T&& a_val)
		{
			if (_proxy && _proxy->type) {
				auto& mappings = _proxy->type->varNameIndexMap;
				const auto it = mappings.find(a_name);
				if (it != mappings.end()) {
					auto& var = _proxy->variables[it->second];
					detail::PackVariable(var, std::forward<T>(a_val));
					return true;
				}
			}

			F4SE::log::warn(
				FMT_STRING("failed to pack var \"{}\" on structure \"{}\""),
				a_name,
				name);
			return false;
		}

		[[nodiscard]] bool is_none() const noexcept { return _proxy == nullptr; }

		template <class T>
		std::optional<T> find(std::string_view a_name) const
		{
			if (_proxy && _proxy->type) {
				const auto& mappings = _proxy->type->varNameIndexMap;
				const auto it = mappings.find(a_name);
				if (it != mappings.end()) {
					const auto& var = _proxy->variables[it->second];
					return detail::UnpackVariable<T>(var);
				}
			}

			return std::nullopt;
		}

	protected:
		friend struct detail::wrapper_accessor;

		explicit structure_wrapper(BSTSmartPointer<Struct> a_proxy) noexcept :
			_proxy(std::move(a_proxy))
		{
			assert(_proxy != nullptr);
		}

		[[nodiscard]] BSTSmartPointer<Struct> get_proxy() const& { return _proxy; }
		[[nodiscard]] BSTSmartPointer<Struct> get_proxy() && { return std::move(_proxy); }

	private:
		BSTSmartPointer<Struct> _proxy;
	};

	template <class>
	struct script_traits final
	{
		using is_array = std::false_type;
		using is_string = std::false_type;
		using is_nullable = std::false_type;
	};

	template <
		class T,
		class Allocator>
	struct script_traits<
		std::vector<T, Allocator>>
		final
	{
		using is_array = std::true_type;
	};

	template <class Traits>
	struct script_traits<
		std::basic_string_view<char, Traits>>
		final
	{
		using is_string = std::true_type;
	};

	template <
		class Traits,
		class Allocator>
	struct script_traits<
		std::basic_string<char, Traits, Allocator>>
		final
	{
		using is_string = std::true_type;
	};

	template <class T>
	struct script_traits<
		std::optional<T>>
		final
	{
		using is_nullable = std::true_type;
	};

	namespace detail
	{
		template <class>
		struct _is_structure_wrapper :
			std::false_type
		{};

		template <stl::nttp::string O, stl::nttp::string S>
		struct _is_structure_wrapper<structure_wrapper<O, S>> :
			std::true_type
		{};

		template <class T>
		using is_structure_wrapper = _is_structure_wrapper<std::decay_t<T>>;

		template <class T>
		inline constexpr bool is_structure_wrapper_v = is_structure_wrapper<T>::value;

		template <class T>
		using decay_t =
			std::conditional_t<
				std::is_pointer_v<T>,
				std::remove_cv_t<std::remove_pointer_t<T>>,
				std::decay_t<T>>;

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
		concept _string =
			std::same_as<
				typename script_traits<T>::is_string,
				std::true_type> &&
			std::convertible_to<T, std::string_view> &&
			std::constructible_from<T, std::string_view>;

		template <class T>
		concept string = _string<std::decay_t<T>>;

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

		// clang-format off
		template <class T>
		concept _array =
			std::same_as<
				typename script_traits<T>::is_array,
				std::true_type> &&
			std::is_default_constructible_v<T> &&
			requires(T a_array, typename T::value_type a_value)
		{
			{ a_array.begin() } -> std::same_as<typename T::iterator>;
			{ a_array.end() } -> std::same_as<typename T::iterator>;
			{ a_array.size() } -> std::same_as<typename T::size_type>;
			a_array.push_back(std::move(a_value));
		};
		// clang-format on

		template <class T>
		concept array = _array<std::decay_t<T>>;

		template <class T>
		concept wrapper = is_structure_wrapper_v<T>;

		template <class T>
		concept _nullable =
			std::same_as<
				typename script_traits<T>::is_nullable,
				std::true_type> &&
			(array<typename T::value_type> ||
				wrapper<typename T::value_type>);

		template <class T>
		concept nullable = _nullable<std::decay_t<T>>;

		template <class T>
		concept valid_self =
			static_tag<T> ||
			(std::is_reference_v<T>&& object<decay_t<T>>);

		template <class T>
		concept valid_parameter =
			(std::is_pointer_v<T> && object<decay_t<T>>) ||
			(!std::is_reference_v<T> &&
				(string<T> ||
					integral<T> ||
					floating_point<T> ||
					boolean<T> ||
					array<T> ||
					wrapper<T> ||
					nullable<T>));

		template <class T>
		concept valid_return =
			valid_parameter<T> ||
			std::same_as<T, void>;

		struct wrapper_accessor
		{
			template <class T>
			[[nodiscard]] static T construct(const Variable& a_var)  //
				requires(is_structure_wrapper_v<T>)
			{
				return T(get<Struct>(a_var));
			}

			template <wrapper T>
			[[nodiscard]] static auto get_proxy(T&& a_wrapper)
			{
				return std::forward<T>(a_wrapper).get_proxy();
			}
		};
	}

	template <detail::object T>
	[[nodiscard]] constexpr std::uint32_t GetVMTypeID() noexcept
	{
		return static_cast<std::uint32_t>(T::FORM_ID);
	}

	template <class T>
	[[nodiscard]] std::optional<TypeInfo> GetTypeInfo()  //
		requires(std::same_as<T, void>)
	{
		return TypeInfo::RawType::kNone;
	}

	template <detail::static_tag T>
	[[nodiscard]] std::optional<TypeInfo> GetTypeInfo()
	{
		return TypeInfo::RawType::kNone;
	}

	template <detail::object T>
	[[nodiscard]] std::optional<TypeInfo> GetTypeInfo()
	{
		const auto game = GameVM::GetSingleton();
		const auto vm = game ? game->GetVM() : nullptr;
		BSTSmartPointer<ObjectTypeInfo> typeInfo;
		if (!vm ||
			!vm->GetScriptObjectType(GetVMTypeID<T>(), typeInfo) ||
			!typeInfo) {
			assert(false);
			F4SE::log::error("failed to get type info for object"sv);
			return std::nullopt;
		} else {
			return typeInfo.get();
		}
	}

	template <detail::string T>
	[[nodiscard]] std::optional<TypeInfo> GetTypeInfo()
	{
		return TypeInfo::RawType::kString;
	}

	template <detail::integral T>
	[[nodiscard]] std::optional<TypeInfo> GetTypeInfo()
	{
		return TypeInfo::RawType::kInt;
	}

	template <detail::floating_point T>
	[[nodiscard]] std::optional<TypeInfo> GetTypeInfo()
	{
		return TypeInfo::RawType::kFloat;
	}

	template <detail::boolean T>
	[[nodiscard]] std::optional<TypeInfo> GetTypeInfo()
	{
		return TypeInfo::RawType::kBool;
	}

	template <detail::array T>
	[[nodiscard]] std::optional<TypeInfo> GetTypeInfo()
	{
		using value_type = detail::decay_t<typename std::decay_t<T>::value_type>;

		auto typeInfo = GetTypeInfo<value_type>();
		if (typeInfo) {
			typeInfo->SetArray(true);
		}

		return typeInfo;
	}

	template <detail::wrapper T>
	[[nodiscard]] std::optional<TypeInfo> GetTypeInfo()
	{
		const auto game = GameVM::GetSingleton();
		const auto vm = game ? game->GetVM() : nullptr;
		if constexpr (detail::is_structure_wrapper_v<T>) {
			BSTSmartPointer<StructTypeInfo> typeInfo;
			if (!vm ||
				!vm->GetScriptStructType(T::name, typeInfo) ||
				!typeInfo) {
				assert(false);
				F4SE::log::error("failed to get type info for structure"sv);
				return std::nullopt;
			} else {
				return typeInfo.get();
			}
		} else {
			static_assert(false && sizeof(T));
		}
	}

	template <detail::nullable T>
	[[nodiscard]] std::optional<TypeInfo> GetTypeInfo()
	{
		using value_type = typename std::decay_t<T>::value_type;
		return GetTypeInfo<value_type>();
	}

	template <detail::object T>
	void PackVariable(Variable& a_var, const T* a_val)
	{
		if (!a_val) {
			a_var = nullptr;
			return;
		}

		const auto success = [&]() {
			const auto game = GameVM::GetSingleton();
			const auto vm = game ? game->GetVM() : nullptr;
			BSTSmartPointer<ObjectTypeInfo> typeInfo;
			if (!vm ||
				!vm->GetScriptObjectType(GetVMTypeID<T>(), typeInfo) ||
				!typeInfo) {
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
	void PackVariable(Variable& a_var, T a_val)
	{
		a_var = static_cast<std::int32_t>(a_val);
	}

	template <detail::unsigned_integral T>
	void PackVariable(Variable& a_var, T a_val)
	{
		a_var = static_cast<std::uint32_t>(a_val);
	}

	template <detail::floating_point T>
	void PackVariable(Variable& a_var, T a_val)
	{
		a_var = static_cast<float>(a_val);
	}

	template <detail::boolean T>
	void PackVariable(Variable& a_var, T a_val)
	{
		a_var = static_cast<bool>(a_val);
	}

	template <detail::array T>
	void PackVariable(Variable& a_var, T&& a_val)
	{
		using size_type = typename detail::decay_t<T>::size_type;
		using value_type = detail::decay_t<typename std::decay_t<T>::value_type>;

		const auto success = [&]() {
			const auto game = GameVM::GetSingleton();
			const auto vm = game ? game->GetVM() : nullptr;
			const auto typeInfo = GetTypeInfo<T>();
			const auto size = a_val.size();
			BSTSmartPointer<Array> out;
			if (!typeInfo ||
				!vm ||
				!vm->CreateArray(*typeInfo, static_cast<std::uint32_t>(size), out) ||
				!out) {
				return false;
			}

			size_type i = 0;
			for (auto&& elem : std::forward<T>(a_val)) {
				PackVariable(out->elements[i++], std::forward<decltype(elem)>(elem));
			}

			a_var = std::move(out);
			return true;
		}();

		if (!success) {
			assert(false);
			F4SE::log::error("failed to pack array"sv);
			a_var = nullptr;
		}
	}

	template <detail::wrapper T>
	void PackVariable(Variable& a_var, T&& a_val)
	{
		a_var = detail::wrapper_accessor::get_proxy(std::forward<T>(a_val));
	}

	template <detail::nullable T>
	void PackVariable(Variable& a_var, T&& a_val)
	{
		if (a_val.has_value()) {
			PackVariable(a_var, std::forward<T>(a_val).value());
		} else {
			a_var = nullptr;
		}
	}

	namespace detail
	{
		template <class T>
		__forceinline void PackVariable(Variable& a_var, T&& a_val)
		{
			BSScript::PackVariable(a_var, std::forward<T>(a_val));
		}
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

	template <detail::array T>
	[[nodiscard]] T UnpackVariable(const Variable& a_var)
	{
		using value_type = detail::decay_t<typename T::value_type>;

		T out;
		const auto in = get<Array>(a_var);
		for (const auto& var : in) {
			out.push_back(UnpackVariable<value_type>(var));
		}

		return out;
	}

	template <detail::wrapper T>
	[[nodiscard]] T UnpackVariable(const Variable& a_var)
	{
		return detail::wrapper_accessor::construct<T>(a_var);
	}

	template <detail::nullable T>
	[[nodiscard]] T UnpackVariable(const Variable& a_var)
	{
		if (a_var.is<std::nullptr_t>()) {
			return {};
		} else {
			using value_type = typename std::decay_t<T>::value_type;
			return UnpackVariable<value_type>(a_var);
		}
	}

	namespace detail
	{
		template <class T>
		[[nodiscard]] __forceinline T UnpackVariable(const Variable& a_var)
		{
			return BSScript::UnpackVariable<T>(a_var);
		}

		template <
			bool LONG,
			valid_self S,
			valid_parameter... Args,
			class F,
			std::size_t... I>
		decltype(auto) DispatchHelper(
			Variable& a_self,
			Internal::VirtualMachine& a_vm,
			std::uint32_t a_stackID,
			const StackFrame& a_stackFrame,
			Stack& a_stack,
			const std::function<F>& a_callback,
			std::index_sequence<I...>)
		{
			const auto self = [&]() -> S {
				if constexpr (detail::static_tag<S>) {
					return std::monostate{};
				} else {
					auto* const ptr = UnpackVariable<std::decay_t<S>>(a_self);
					assert(ptr != nullptr);  // super::Call should guarantee this
					return *ptr;
				}
			};

			const auto pframe = std::addressof(a_stackFrame);
			const auto page = a_stack.GetPageForFrame(pframe);
			const auto args = [&]<class T>(std::in_place_type_t<T>, std::size_t a_index) {
				return UnpackVariable<detail::decay_t<T>>(a_stack.GetStackFrameVariable(pframe, a_index, page));
			};

			if constexpr (LONG) {
				return a_callback(
					reinterpret_cast<IVirtualMachine&>(a_vm),  // TODO: static_cast
					a_stackID,
					self(),
					args(std::in_place_type_t<Args>{}, I)...);
			} else {
				return a_callback(
					self(),
					args(std::in_place_type_t<Args>{}, I)...);
			}
		}
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
			((super::descTable.entries[i++].second = GetTypeInfo<detail::decay_t<Args>>().value_or(nullptr)), ...);
			super::retType = GetTypeInfo<detail::decay_t<R>>().value_or(nullptr);
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
				return detail::DispatchHelper<LONG, S, Args...>(
					a_self,
					a_vm,
					a_stackID,
					a_stackFrame,
					*stack,
					_stub,
					std::index_sequence_for<Args...>{});
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
			F4SE::log::warn(
				FMT_STRING("failed to register method \"{}\" on object \"{}\""),
				a_function,
				a_object);
		}

		if (success && a_taskletCallable) {
			SetCallableFromTasklets(a_object.data(), a_function.data(), *a_taskletCallable);
		}
	}
}
