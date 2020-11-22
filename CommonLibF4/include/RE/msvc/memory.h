#pragma once

#include <cassert>
#include <cstdint>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>

namespace RE::msvc
{
	template <class T>
	struct default_delete;

	template <class T, class Deleter = default_delete<T>>
	class unique_ptr;

	namespace detail
	{
		// std::_Get_deleter_pointer_type
		template <class T, class Deleter, class = void>
		struct _deleter_pointer_type
		{
			using type = std::add_pointer_t<std::remove_extent_t<T>>;
		};

		template <class T, class Deleter>
		struct _deleter_pointer_type<
			T,
			Deleter,
			std::void_t<
				typename Deleter::pointer>>
		{
			using type = typename Deleter::pointer;
		};

		template <class T, class Deleter>
		using deleter_pointer_type = _deleter_pointer_type<
			T,
			std::remove_reference_t<
				Deleter>>;

		template <class T, class Deleter>
		using deleter_pointer_type_t = typename deleter_pointer_type<T, Deleter>::type;

		template <class T>
		struct is_bounded_array :
			std::false_type
		{};

		template <class T, std::size_t N>
		struct is_bounded_array<T[N]> :
			std::true_type
		{};

		template <class T>
		inline constexpr bool is_bounded_array_v = is_bounded_array<T>::value;

		template <class T>
		struct is_unbounded_array :
			std::false_type
		{};

		template <class T>
		struct is_unbounded_array<T[]> :
			std::true_type
		{};

		template <class T>
		inline constexpr bool is_unbounded_array_v = is_unbounded_array<T>::value;

		// std::_Unique_ptr_base

		// default template
		template <class T, class Deleter, class = void>
		class unique_ptr
		{
		public:
			using pointer = deleter_pointer_type_t<T, Deleter>;
			using deleter_type = Deleter;

			template <
				class... Args,
				std::enable_if_t<
					std::is_nothrow_constructible_v<
						deleter_type,
						Args...>,
					int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
			unique_ptr(pointer a_ptr, Args... a_args) noexcept :
				_pointer{ a_ptr },
				_deleter{ std::forward<Args>(a_args)... }
			{}

			template <
				class D = deleter_type,
				std::enable_if_t<
					std::is_nothrow_move_constructible_v<
						D>,
					int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
			unique_ptr(unique_ptr&& a_rhs) noexcept :
				_pointer{ std::move(a_rhs._pointer) },
				_deleter{ std::move(a_rhs._deleter) }
			{
				a_rhs._pointer = pointer{};
			}

			// copy reference
			template <
				class U,
				class E,
				std::enable_if_t<
					std::conjunction_v<
						std::is_reference<
							E>,
						std::is_nothrow_constructible<
							deleter_type,
							const E&>>,
					int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
			unique_ptr(unique_ptr<U, E>&& a_rhs) noexcept :
				_pointer{ std::move(a_rhs._pointer) },
				_deleter{ a_rhs._deleter }
			{
				a_rhs._pointer = typename unique_ptr<U, E>::pointer{};
			}

			// move non-reference
			template <
				class U,
				class E,
				std::enable_if_t<
					std::conjunction_v<
						std::negation<
							std::is_reference<
								E>>,
						std::is_nothrow_constructible<
							deleter_type,
							E&&>>,
					int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
			unique_ptr(unique_ptr<U, E>&& a_rhs) noexcept :
				_pointer{ std::move(a_rhs._pointer) },
				_deleter{ std::move(a_rhs._deleter) }
			{
				a_rhs._pointer = typename unique_ptr<U, E>::pointer{};
			}

			[[nodiscard]] deleter_type& get_deleter() noexcept
			{
				return _deleter;
			}

			[[nodiscard]] const deleter_type& get_deleter() const noexcept
			{
				return _deleter;
			}

		protected:
			// members
			pointer _pointer;

		private:
			template <class, class, class>
			friend class unique_ptr;

			// members
			deleter_type _deleter;
		};

		// empty deleter
		template <class T, class Deleter>
		class unique_ptr<
			T,
			Deleter,
			std::enable_if_t<
				std::disjunction_v<
					std::is_empty<
						Deleter>,
					std::is_same<
						default_delete<T>,
						Deleter>>>> :
			public Deleter
		{
		private:
			using super = Deleter;

		public:
			using pointer = deleter_pointer_type_t<T, Deleter>;
			using deleter_type = Deleter;

			template <
				class... Args,
				std::enable_if_t<
					std::is_nothrow_constructible_v<
						deleter_type,
						Args...>,
					int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
			unique_ptr(pointer a_ptr, Args... a_args) noexcept :
				super{ std::forward<Args>(a_args)... },
				_pointer{ a_ptr }
			{}

			template <
				class D = deleter_type,
				std::enable_if_t<
					std::is_nothrow_move_constructible_v<
						D>,
					int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
			unique_ptr(unique_ptr&& a_rhs) noexcept :
				super{ std::move(a_rhs) },
				_pointer{ std::move(a_rhs._pointer) }
			{
				a_rhs._pointer = pointer{};
			}

			// copy reference
			template <
				class U,
				class E,
				std::enable_if_t<
					std::conjunction_v<
						std::is_reference<
							E>,
						std::is_nothrow_constructible<
							deleter_type,
							const E&>>,
					int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
			unique_ptr(unique_ptr<U, E>&& a_rhs) noexcept :
				super{ a_rhs },
				_pointer{ std::move(a_rhs._pointer) }
			{
				a_rhs._pointer = typename unique_ptr<U, E>::pointer{};
			}

			// move non-reference
			template <
				class U,
				class E,
				std::enable_if_t<
					std::conjunction_v<
						std::negation<
							std::is_reference<
								E>>,
						std::is_nothrow_constructible<
							deleter_type,
							E&&>>,
					int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
			unique_ptr(unique_ptr<U, E>&& a_rhs) noexcept :
				super{ std::move(a_rhs) },
				_pointer{ std::move(a_rhs._pointer) }
			{
				a_rhs._pointer = typename unique_ptr<U, E>::pointer{};
			}

			[[nodiscard]] deleter_type& get_deleter() noexcept
			{
				return *this;
			}

			[[nodiscard]] const deleter_type& get_deleter() const noexcept
			{
				return *this;
			}

		protected:
			// members
			pointer _pointer;

		private:
			template <class, class, class>
			friend class unique_ptr;
		};
	}

	// scalar
	template <class T>
	struct default_delete
	{
	public:
		constexpr default_delete() noexcept = default;

		template <
			class U,
			std::enable_if_t<
				std::is_convertible_v<
					U*,
					T*>,
				int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
		default_delete(const default_delete<U>&) noexcept
		{}

		void operator()(T* a_ptr) const
		{
			delete a_ptr;
		}
	};

	// array
	template <class T>
	struct default_delete<T[]>
	{
	public:
		constexpr default_delete() noexcept = default;

		template <
			class U,
			std::enable_if_t<
				std::is_convertible_v<
					U (*)[],
					T (*)[]>,
				int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
		default_delete(const default_delete<U[]>&) noexcept
		{}

		template <
			class U,
			std::enable_if_t<
				std::is_convertible_v<
					U (*)[],
					T (*)[]>,
				int> = 0>
		void operator()(U* a_ptr) const
		{
			delete[] a_ptr;
		}
	};

	// scalar
	template <class T, class Deleter>
	class unique_ptr :
		public detail::unique_ptr<T, Deleter>
	{
	private:
		using super = detail::unique_ptr<T, Deleter>;

		using super::_pointer;

	public:
		// member types
		using pointer = typename super::pointer;
		using element_type = T;
		using deleter_type = typename super::deleter_type;

		// constructors

		unique_ptr(const unique_ptr&) = delete;

		// 1a
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::conjunction_v<
					std::is_nothrow_default_constructible<
						D>,
					std::negation<
						std::is_pointer<
							D>>>,
				int> = 0>
		constexpr unique_ptr() noexcept :
			super(pointer{})
		{}

		// 1b
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::conjunction_v<
					std::is_nothrow_default_constructible<
						D>,
					std::negation<
						std::is_pointer<
							D>>>,
				int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
		constexpr unique_ptr(std::nullptr_t) noexcept :
			super(pointer{})
		{}

		// 2
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::conjunction_v<
					std::is_nothrow_default_constructible<
						D>,
					std::negation<
						std::is_pointer<
							D>>>,
				int> = 0>
		explicit unique_ptr(pointer a_ptr) noexcept :
			super(a_ptr)
		{}

		// 3a
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::conjunction_v<
					std::negation<
						std::is_reference<
							D>>,
					std::is_nothrow_copy_constructible<
						D>>,
				int> = 0>
		unique_ptr(pointer a_ptr, const deleter_type& a_dtor) noexcept :
			super(a_ptr, a_dtor)
		{}

		// 4a
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::conjunction_v<
					std::negation<
						std::is_reference<
							D>>,
					std::is_nothrow_move_constructible<
						D>>,
				int> = 0>
		unique_ptr(pointer a_ptr, deleter_type&& a_dtor) noexcept :
			super(a_ptr, std::move(a_dtor))
		{}

		// 3b
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::conjunction_v<
					std::is_lvalue_reference<
						D>,
					std::negation<
						std::is_const<
							D>>>,
				int> = 0>
		unique_ptr(pointer a_ptr, deleter_type& a_dtor) noexcept :
			super(a_ptr, a_dtor)
		{}

		// 4b
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::conjunction_v<
					std::is_lvalue_reference<
						D>,
					std::negation<
						std::is_const<
							D>>>,
				int> = 0>
		unique_ptr(pointer, deleter_type&& a4b) = delete;

		// 3c
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::conjunction_v<
					std::is_lvalue_reference<
						D>,
					std::is_const<
						D>>,
				int> = 0>
		unique_ptr(pointer a_ptr, const deleter_type& a_dtor) noexcept :
			super(a_ptr, a_dtor)
		{}

		// 4c
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::conjunction_v<
					std::is_lvalue_reference<
						D>,
					std::is_const<
						D>>,
				int> = 0>
		unique_ptr(pointer, const deleter_type&& a4c) = delete;

		// 5
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::is_nothrow_move_constructible_v<
					D>,
				int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
		unique_ptr(unique_ptr&& a_rhs) noexcept :
			super(std::move(a_rhs))
		{}

		// 6
		template <
			class U,
			class E,
			std::enable_if_t<
				std::conjunction_v<
					std::is_convertible<
						typename unique_ptr<U, E>::pointer,
						pointer>,
					std::negation<
						std::is_array<U>>,
					std::conditional_t<
						std::is_reference_v<
							deleter_type>,
						std::conjunction<
							std::is_same<
								E,
								deleter_type>,
							std::is_nothrow_constructible<
								deleter_type,
								const E&>>,
						std::conjunction<
							std::is_convertible<
								E,
								deleter_type>,
							std::is_nothrow_constructible<
								deleter_type,
								E&&>>>>,
				int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
		unique_ptr(unique_ptr<U, E>&& a_rhs) noexcept :
			super(std::move(a_rhs))
		{}

		// destructor

		~unique_ptr() noexcept
		{
			if (_pointer) {
				get_deleter()(_pointer);
			}
		}

		// assignment

		unique_ptr& operator=(const unique_ptr&) = delete;

		// 1a
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::conjunction_v<
					std::conditional_t<
						std::is_reference_v<
							D>,
						std::is_nothrow_copy_assignable<
							std::remove_reference_t<D>>,
						std::is_nothrow_move_assignable<
							D>>,
					std::is_move_assignable<
						D>>,
				int> = 0>
		unique_ptr& operator=(unique_ptr&& a_rhs) noexcept
		{
			if (this != std::addressof(a_rhs)) {
				reset(a_rhs.release());
				get_deleter() = std::forward<deleter_type>(a_rhs.get_deleter());
			}
			return *this;
		}

		// 1b
		template <
			class U,
			class E,
			std::enable_if_t<
				std::conjunction_v<
					std::conditional_t<
						std::is_reference_v<
							deleter_type>,
						std::is_nothrow_copy_assignable<
							std::remove_reference_t<deleter_type>>,
						std::is_nothrow_move_assignable<
							deleter_type>>,
					std::negation<
						std::is_array<
							U>>,
					std::is_convertible<
						typename unique_ptr<U, E>::pointer,
						pointer>,
					std::is_assignable<
						deleter_type&,
						E&&>>,
				int> = 0>
		unique_ptr& operator=(unique_ptr<U, E>&& a_rhs) noexcept
		{
			reset(a_rhs.release());
			get_deleter() = std::forward<E>(a_rhs.get_deleter());
			return *this;
		}

		// 2
		unique_ptr& operator=(std::nullptr_t) noexcept
		{
			reset();
			return *this;
		}

		// modifiers

		pointer release() noexcept
		{
			auto old = _pointer;
			_pointer = pointer{};
			return old;
		}

		void reset(pointer a_ptr = pointer{}) noexcept
		{
			auto old = _pointer;
			_pointer = a_ptr;
			if (old) {
				get_deleter()(old);
			}
		}

		void swap(unique_ptr& a_other) noexcept
		{
			using std::swap;
			swap(_pointer, a_other._pointer);
			swap(get_deleter(), a_other.get_deleter());
		}

		// observers

		[[nodiscard]] pointer get() const noexcept
		{
			return _pointer;
		}

		using super::get_deleter;

		[[nodiscard]] explicit operator bool() const noexcept
		{
			return good();
		}

		[[nodiscard]] auto operator*() const
			-> std::add_lvalue_reference_t<T>
		{
			assert(good());
			return *get();
		}

		[[nodiscard]] pointer operator->() const noexcept
		{
			assert(good());
			return get();
		}

	private:
		[[nodiscard]] constexpr bool good() const noexcept
		{
			return get() != pointer{};
		}
	};

	// array
	template <class T, class Deleter>
	class unique_ptr<T[], Deleter> :
		public detail::unique_ptr<T[], Deleter>
	{
	private:
		using super = detail::unique_ptr<T[], Deleter>;

		using super::_pointer;

	public:
		// member types
		using pointer = typename super::pointer;
		using element_type = T;
		using deleter_type = typename super::deleter_type;

	private:
		template <class U>
		using is_argument_convertible =
			std::disjunction<
				std::is_same<
					U,
					pointer>,
				std::is_same<
					U,
					std::nullptr_t>,
				std::conjunction<
					std::is_same<
						pointer,
						element_type*>,
					std::is_pointer<U>,
					std::is_same<
						std::remove_pointer_t<U> (*)[],
						element_type (*)[]>>>;

	public:
		// constructors

		unique_ptr(const unique_ptr&) = delete;

		// 1a
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::conjunction_v<
					std::is_nothrow_default_constructible<
						D>,
					std::negation<
						std::is_pointer<
							D>>>,
				int> = 0>
		constexpr unique_ptr() noexcept :
			super(pointer{})
		{}

		// 1b
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::conjunction_v<
					std::is_nothrow_default_constructible<
						D>,
					std::negation<
						std::is_pointer<
							D>>>,
				int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
		constexpr unique_ptr(std::nullptr_t) noexcept :
			super(pointer{})
		{}

		// 2
		template <
			class U,
			std::enable_if_t<
				std::conjunction_v<
					std::is_nothrow_default_constructible<
						deleter_type>,
					std::negation<
						std::is_pointer<
							deleter_type>>,
					is_argument_convertible<U>>,
				int> = 0>
		explicit unique_ptr(U a_ptr) noexcept :
			super(a_ptr)
		{}

		// 3a
		template <
			class U,
			std::enable_if_t<
				std::conjunction_v<
					std::negation<
						std::is_reference<
							deleter_type>>,
					std::is_nothrow_copy_constructible<
						deleter_type>,
					is_argument_convertible<U>>,
				int> = 0>
		unique_ptr(U a_ptr, const deleter_type& a_dtor) noexcept :
			super(a_ptr, a_dtor)
		{}

		// 4a
		template <
			class U,
			std::enable_if_t<
				std::conjunction_v<
					std::negation<
						std::is_reference<
							deleter_type>>,
					std::is_nothrow_move_constructible<
						deleter_type>,
					is_argument_convertible<U>>,
				int> = 0>
		unique_ptr(U a_ptr, deleter_type&& a_dtor) noexcept :
			super(a_ptr, std::move(a_dtor))
		{}

		// 3b
		template <
			class U,
			std::enable_if_t<
				std::conjunction_v<
					std::is_lvalue_reference<
						deleter_type>,
					std::negation<
						std::is_const<
							deleter_type>>,
					is_argument_convertible<U>>,
				int> = 0>
		unique_ptr(U a_ptr, deleter_type& a_dtor) noexcept :
			super(a_ptr, a_dtor)
		{}

		// 4b
		template <
			class U,
			std::enable_if_t<
				std::conjunction_v<
					std::is_lvalue_reference<
						deleter_type>,
					std::negation<
						std::is_const<
							deleter_type>>,
					is_argument_convertible<U>>,
				int> = 0>
		unique_ptr(U, deleter_type&&) noexcept = delete;

		// 3c
		template <
			class U,
			std::enable_if_t<
				std::conjunction_v<
					std::is_lvalue_reference<
						deleter_type>,
					std::is_const<
						deleter_type>,
					is_argument_convertible<U>>,
				int> = 0>
		unique_ptr(U a_ptr, const deleter_type& a_dtor) noexcept :
			super(a_ptr, a_dtor)
		{}

		// 4c
		template <
			class U,
			std::enable_if_t<
				std::conjunction_v<
					std::is_lvalue_reference<
						deleter_type>,
					std::is_const<
						deleter_type>,
					is_argument_convertible<U>>,
				int> = 0>
		unique_ptr(U, const deleter_type&&) noexcept = delete;

		// 5
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::is_nothrow_move_constructible_v<
					D>,
				int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
		unique_ptr(unique_ptr&& a_rhs) noexcept :
			super(std::move(a_rhs))
		{}

		// 6
		template <
			class U,
			class E,
			std::enable_if_t<
				std::conjunction_v<
					std::is_array<
						U>,
					std::is_same<
						pointer,
						element_type*>,
					std::is_same<
						typename unique_ptr<U, E>::pointer,
						typename unique_ptr<U, E>::element_type*>,
					std::is_convertible<
						typename unique_ptr<U, E>::element_type (*)[],
						element_type (*)[]>,
					std::conditional_t<
						std::is_reference_v<
							deleter_type>,
						std::conjunction<
							std::is_same<
								E,
								deleter_type>,
							std::is_nothrow_constructible<
								deleter_type,
								const E&>>,
						std::conjunction<
							std::is_convertible<
								E,
								deleter_type>,
							std::is_nothrow_constructible<
								deleter_type,
								E&&>>>>,
				int> = 0>  // NOLINTNEXTLINE(google-explicit-constructor)
		unique_ptr(unique_ptr<U, E>&& a_rhs) noexcept :
			super(std::move(a_rhs))
		{}

		// destructor

		~unique_ptr() noexcept
		{
			if (_pointer) {
				get_deleter()(_pointer);
			}
		}

		// assignment

		unique_ptr& operator=(const unique_ptr&) = delete;

		// 1a
		template <
			class D = deleter_type,
			std::enable_if_t<
				std::conjunction_v<
					std::conditional_t<
						std::is_reference_v<
							D>,
						std::is_nothrow_copy_assignable<
							std::remove_reference_t<D>>,
						std::is_nothrow_move_assignable<
							D>>,
					std::is_move_assignable<
						D>>,
				int> = 0>
		unique_ptr& operator=(unique_ptr&& a_rhs) noexcept
		{
			if (this != std::addressof(a_rhs)) {
				reset(a_rhs.release());
				get_deleter() = std::forward<deleter_type>(a_rhs.get_deleter());
			}
			return *this;
		}

		// 1b
		template <
			class U,
			class E,
			std::enable_if_t<
				std::conjunction_v<
					std::is_array<U>,
					std::is_same<
						pointer,
						element_type*>,
					std::is_same<
						typename unique_ptr<U, E>::pointer,
						typename unique_ptr<U, E>::element_type*>,
					std::is_convertible<
						typename unique_ptr<U, E>::element_type (*)[],
						element_type (*)[]>,
					std::is_assignable<
						deleter_type&,
						E&&>>,
				int> = 0>
		unique_ptr& operator=(unique_ptr<U, E>&& a_rhs) noexcept
		{
			if (this != std::addressof(a_rhs)) {
				reset(a_rhs.release());
				get_deleter() = std::forward<E>(a_rhs.get_deleter());
			}
			return *this;
		}

		// 2
		unique_ptr& operator=(std::nullptr_t) noexcept
		{
			reset();
			return *this;
		}

		// modifiers

		pointer release() noexcept
		{
			auto old = _pointer;
			_pointer = pointer{};
			return old;
		}

		// 3
		template <
			class U,
			std::enable_if_t<
				is_argument_convertible<
					U>::value,
				int> = 0>
		void reset(U a_ptr) noexcept
		{
			auto old = _pointer;
			_pointer = a_ptr;
			if (old) {
				get_deleter()(old);
			}
		}

		// 4
		void reset(std::nullptr_t = nullptr) noexcept
		{
			reset(pointer{});
		}

		void swap(unique_ptr& a_other) noexcept
		{
			using std::swap;
			swap(_pointer, a_other._pointer);
			swap(get_deleter(), a_other.get_deleter());
		}

		// observers

		[[nodiscard]] pointer get() const noexcept
		{
			return _pointer;
		}

		using super::get_deleter;

		[[nodiscard]] explicit operator bool() const noexcept
		{
			return good();
		}

		[[nodiscard]] element_type& operator[](std::size_t a_idx) const
		{
			assert(good());
			return get()[a_idx];
		}

	private:
		[[nodiscard]] constexpr bool good() const noexcept
		{
			return get() != pointer{};
		}
	};

	// 1
	template <
		class T,
		class... Args,
		std::enable_if_t<
			std::negation_v<
				std::is_array<
					T>>,
			int> = 0>
	[[nodiscard]] unique_ptr<T> make_unique(Args&&... a_args)
	{
		return unique_ptr<T>(new T(std::forward<Args>(a_args)...));
	}

	// 2
	template <
		class T,
		std::enable_if_t<
			detail::is_unbounded_array_v<
				T>,
			int> = 0>
	[[nodiscard]] unique_ptr<T> make_unique(std::size_t a_size)
	{
		return unique_ptr<T>(new std::remove_extent_t<T>[a_size]());
	}

	// 3
	template <
		class T,
		class... Args,
		std::enable_if_t<
			detail::is_bounded_array_v<
				T>,
			int> = 0>
	void make_unique(Args&&...) = delete;

	// 4
	template <
		class T,
		class... Args,
		std::enable_if_t<
			std::negation_v<
				std::is_array<
					T>>,
			int> = 0>
	[[nodiscard]] unique_ptr<T> make_unique_for_overwrite()
	{
		return unique_ptr<T>(new T);
	}

	// 5
	template <
		class T,
		std::enable_if_t<
			detail::is_unbounded_array_v<
				T>,
			int> = 0>
	[[nodiscard]] unique_ptr<T> make_unique_for_overwrite(std::size_t a_size)
	{
		return unique_ptr<T>(new std::remove_extent_t<T>[a_size]);
	}

	// 6
	template <
		class T,
		class... Args,
		std::enable_if_t<
			detail::is_bounded_array_v<
				T>,
			int> = 0>
	void make_unique_for_overwrite(Args&&...) = delete;

	// 1
	template <class T1, class D1, class T2, class D2>
	[[nodiscard]] bool operator==(const unique_ptr<T1, D1>& a_lhs, const unique_ptr<T2, D2>& a_rhs)
	{
		return a_lhs.get() == a_rhs.get();
	}

	// 2
	template <class T1, class D1, class T2, class D2>
	[[nodiscard]] bool operator!=(const unique_ptr<T1, D1>& a_lhs, const unique_ptr<T2, D2>& a_rhs)
	{
		return a_lhs.get() != a_rhs.get();
	}

	// 3
	template <class T1, class D1, class T2, class D2>
	[[nodiscard]] bool operator<(const unique_ptr<T1, D1>& a_lhs, const unique_ptr<T2, D2>& a_rhs)
	{
		using common_t = std::common_type_t<
			typename unique_ptr<T1, D1>::pointer,
			typename unique_ptr<T2, D2>::pointer>;
		return std::less<common_t>()(a_lhs.get(), a_rhs.get());
	}

	// 4
	template <class T1, class D1, class T2, class D2>
	[[nodiscard]] bool operator<=(const unique_ptr<T1, D1>& a_lhs, const unique_ptr<T2, D2>& a_rhs)
	{
		return !(a_rhs < a_lhs);
	}

	// 5
	template <class T1, class D1, class T2, class D2>
	[[nodiscard]] bool operator>(const unique_ptr<T1, D1>& a_lhs, const unique_ptr<T2, D2>& a_rhs)
	{
		return a_rhs < a_lhs;
	}

	// 6
	template <class T1, class D1, class T2, class D2>
	[[nodiscard]] bool operator>=(const unique_ptr<T1, D1>& a_lhs, const unique_ptr<T2, D2>& a_rhs)
	{
		return !(a_lhs < a_rhs);
	}

	// 8
	template <class T, class D>
	[[nodiscard]] bool operator==(const unique_ptr<T, D>& a_lhs, std::nullptr_t) noexcept
	{
		return !a_lhs;
	}

	// 9
	template <class T, class D>
	[[nodiscard]] bool operator==(std::nullptr_t, const unique_ptr<T, D>& a_rhs) noexcept
	{
		return !a_rhs;
	}

	// 10
	template <class T, class D>
	[[nodiscard]] bool operator!=(const unique_ptr<T, D>& a_lhs, std::nullptr_t) noexcept
	{
		return static_cast<bool>(a_lhs);
	}

	// 11
	template <class T, class D>
	[[nodiscard]] bool operator!=(std::nullptr_t, const unique_ptr<T, D>& a_rhs) noexcept
	{
		return static_cast<bool>(a_rhs);
	}

	// 12
	template <class T, class D>
	[[nodiscard]] bool operator<(const unique_ptr<T, D>& a_lhs, std::nullptr_t)
	{
		using pointer = typename unique_ptr<T, D>::pointer;
		return std::less<pointer>()(a_lhs.get(), nullptr);
	}

	// 13
	template <class T, class D>
	[[nodiscard]] bool operator<(std::nullptr_t, const unique_ptr<T, D>& a_rhs)
	{
		using pointer = typename unique_ptr<T, D>::pointer;
		return std::less<pointer>()(nullptr, a_rhs.get());
	}

	// 14
	template <class T, class D>
	[[nodiscard]] bool operator<=(const unique_ptr<T, D>& a_lhs, std::nullptr_t)
	{
		return !(nullptr < a_lhs);
	}

	// 15
	template <class T, class D>
	[[nodiscard]] bool operator<=(std::nullptr_t, const unique_ptr<T, D>& a_rhs)
	{
		return !(a_rhs < nullptr);
	}

	// 16
	template <class T, class D>
	[[nodiscard]] bool operator>(const unique_ptr<T, D>& a_lhs, std::nullptr_t)
	{
		return nullptr < a_lhs;
	}

	// 17
	template <class T, class D>
	[[nodiscard]] bool operator>(std::nullptr_t, const unique_ptr<T, D>& a_rhs)
	{
		return a_rhs < nullptr;
	}

	// 18
	template <class T, class D>
	[[nodiscard]] bool operator>=(const unique_ptr<T, D>& a_lhs, std::nullptr_t)
	{
		return !(a_lhs < nullptr);
	}

	// 19
	template <class T, class D>
	[[nodiscard]] bool operator>=(std::nullptr_t, const unique_ptr<T, D>& a_rhs)
	{
		return !(nullptr < a_rhs);
	}

	template <class T, class Deleter>
	void swap(unique_ptr<T, Deleter>& a_lhs, unique_ptr<T, Deleter>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}
