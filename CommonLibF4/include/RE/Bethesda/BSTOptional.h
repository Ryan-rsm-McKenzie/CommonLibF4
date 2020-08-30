#pragma once

namespace RE
{
	template <class T>
	class BSTOptional
	{
	public:
		using value_type = T;

		// 1a)
		constexpr BSTOptional() noexcept = default;

		// 1b)
		constexpr BSTOptional(std::nullopt_t) noexcept {}

		// 2)
		template <
			class U = value_type,
			std::enable_if_t<
				std::is_copy_constructible_v<U>,
				int> = 0>
		constexpr BSTOptional(const BSTOptional& a_rhs) noexcept(
			std::is_nothrow_copy_constructible_v<value_type>)
		{
			if (a_rhs.has_value()) {
				stl::construct_at(std::addressof(_value), a_rhs.value());
				_hasValue = true;
			}
		}

		// 3)
		template <
			class U = value_type,
			std::enable_if_t<
				std::is_move_constructible_v<U>,
				int> = 0>
		constexpr BSTOptional(BSTOptional&& a_rhs) noexcept(
			std::is_nothrow_move_constructible_v<value_type>)
		{
			if (a_rhs.has_value()) {
				stl::construct_at(std::addressof(_value), std::move(a_rhs).value());
				_hasValue = true;
			}
		}

		// 4)
		template <
			class U,
			std::enable_if_t<
				std::conjunction_v<
					std::is_constructible<value_type, const U&>,
					std::negation<
						std::disjunction<
							std::is_constructible<value_type, BSTOptional<U>&>,
							std::is_constructible<value_type, const BSTOptional<U>&>,
							std::is_constructible<value_type, BSTOptional<U>&&>,
							std::is_constructible<value_type, const BSTOptional<U>&&>,
							std::is_convertible<BSTOptional<U>&, value_type>,
							std::is_convertible<const BSTOptional<U>&, value_type>,
							std::is_convertible<BSTOptional<U>&&, value_type>,
							std::is_convertible<const BSTOptional<U>&&, value_type>>>>,
				int> = 0>
		BSTOptional(const BSTOptional<U>& a_rhs) noexcept(
			std::is_nothrow_constructible_v<value_type, const U&>)
		{
			if (a_rhs.has_value()) {
				stl::construct_at(std::addressof(_value), a_rhs.value());
				_hasValue = true;
			}
		}

		// 5)
		template <
			class U,
			std::enable_if_t<
				std::conjunction_v<
					std::is_constructible<value_type, U&&>,
					std::negation<
						std::disjunction<
							std::is_constructible<value_type, BSTOptional<U>&>,
							std::is_constructible<value_type, const BSTOptional<U>&>,
							std::is_constructible<value_type, BSTOptional<U>&&>,
							std::is_constructible<value_type, const BSTOptional<U>&&>,
							std::is_convertible<BSTOptional<U>&, value_type>,
							std::is_convertible<const BSTOptional<U>&, value_type>,
							std::is_convertible<BSTOptional<U>&&, value_type>,
							std::is_convertible<const BSTOptional<U>&&, value_type>>>>,
				int> = 0>
		BSTOptional(BSTOptional<U>&& a_rhs) noexcept(
			std::is_nothrow_constructible_v<value_type, U&&>)
		{
			if (a_rhs.has_value()) {
				stl::construct_at(std::addressof(_value), std::move(a_rhs).value());
				_hasValue = true;
			}
		}

		// 6)
		template <
			class... Args,
			std::enable_if_t<
				std::is_constructible_v<value_type, Args...>,
				int> = 0>
		constexpr explicit BSTOptional(std::in_place_t, Args&&... a_args) noexcept(
			std::is_nothrow_constructible_v<value_type, Args...>)
		{
			stl::construct_at(std::addressof(_value), std::forward<Args>(a_args)...);
			_hasValue = true;
		}

		// 7)
		template <
			class U,
			class... Args,
			std::enable_if_t<
				std::is_constructible_v<T, std::initializer_list<U>&, Args&&...>,
				int> = 0>
		constexpr explicit BSTOptional(std::in_place_t, std::initializer_list<U> a_ilist, Args&&... a_args) noexcept(
			std::is_nothrow_constructible_v<value_type, std::initializer_list<U>&, Args&&...>)
		{
			stl::construct_at(std::addressof(_value), a_ilist, std::forward<Args>(a_args)...);
			_hasValue = true;
		}

		// 8)
		template <
			class U = value_type,
			std::enable_if_t<
				std::conjunction_v<
					std::is_constructible<value_type, U&&>,
					std::negation<
						std::disjunction<
							std::is_same<stl::remove_cvref_t<U>, std::in_place_t>,
							std::is_same<stl::remove_cvref_t<U>, BSTOptional<value_type>>>>>,
				int> = 0>
		constexpr BSTOptional(U&& a_value) noexcept(
			std::is_nothrow_constructible_v<value_type, U&&>)
		{
			stl::construct_at(std::addressof(_value), std::forward<U>(a_value));
			_hasValue = true;
		}

		~BSTOptional() noexcept(
			std::is_nothrow_destructible_v<value_type>)
		{
			reset();
		}

		// 1)
		BSTOptional& operator=(std::nullopt_t) noexcept(
			std::is_nothrow_destructible_v<value_type>)
		{
			reset();
			return *this;
		}

		// 2)
		constexpr BSTOptional& operator=(const BSTOptional& a_rhs) noexcept(
			std::conjunction_v<
				std::is_nothrow_destructible<value_type>,
				std::is_nothrow_copy_constructible<value_type>>)
		{
			if (this != std::addressof(a_rhs)) {
				reset();
				if (a_rhs.has_value()) {
					stl::construct_at(std::addressof(_value), a_rhs.value());
					_hasValue = true;
				}
			}
			return *this;
		}

		// 3)
		constexpr BSTOptional& operator=(BSTOptional&& a_rhs) noexcept(
			std::conjunction_v<
				std::is_nothrow_destructible<value_type>,
				std::is_nothrow_move_constructible<value_type>>)
		{
			if (this != std::addressof(a_rhs)) {
				reset();
				if (a_rhs.has_value()) {
					stl::construct_at(std::addressof(_value), std::move(a_rhs).value());
					_hasValue = true;
				}
			}
			return *this;
		}

		// 4)
		template <
			class U = value_type,
			std::enable_if_t<
				std::conjunction_v<
					std::is_constructible<value_type, U&&>,
					std::negation<
						std::is_same<stl::remove_cvref_t<U>, std::in_place_t>>>,
				int> = 0>
		BSTOptional& operator=(U&& a_value) noexcept(
			std::conjunction_v<
				std::is_nothrow_destructible<value_type>,
				std::is_nothrow_constructible<value_type, U&&>>)
		{
			reset();
			stl::construct_at(std::addressof(_value), std::forward<U>(a_value));
			_hasValue = true;
			return *this;
		}

		// 5)
		template <
			class U,
			std::enable_if_t<
				std::conjunction_v<
					std::is_constructible<value_type, const U&>,
					std::negation<
						std::disjunction<
							std::is_constructible<value_type, BSTOptional<U>&>,
							std::is_constructible<value_type, const BSTOptional<U>&>,
							std::is_constructible<value_type, BSTOptional<U>&&>,
							std::is_constructible<value_type, const BSTOptional<U>&&>,
							std::is_convertible<BSTOptional<U>&, value_type>,
							std::is_convertible<const BSTOptional<U>&, value_type>,
							std::is_convertible<BSTOptional<U>&&, value_type>,
							std::is_convertible<const BSTOptional<U>&&, value_type>>>>,
				int> = 0>
		BSTOptional& operator=(const BSTOptional<U>& a_rhs) noexcept(
			std::conjunction_v<
				std::is_nothrow_destructible<value_type>,
				std::is_nothrow_constructible<value_type, const U&>>)
		{
			reset();
			if (a_rhs.has_value()) {
				stl::construct_at(std::addressof(_value), a_rhs.value());
				_hasValue = true;
			}
			return *this;
		}

		// 6)
		template <
			class U,
			std::enable_if_t<
				std::conjunction_v<
					std::is_constructible<value_type, U&&>,
					std::negation<
						std::disjunction<
							std::is_constructible<value_type, BSTOptional<U>&>,
							std::is_constructible<value_type, const BSTOptional<U>&>,
							std::is_constructible<value_type, BSTOptional<U>&&>,
							std::is_constructible<value_type, const BSTOptional<U>&&>,
							std::is_convertible<BSTOptional<U>&, value_type>,
							std::is_convertible<const BSTOptional<U>&, value_type>,
							std::is_convertible<BSTOptional<U>&&, value_type>,
							std::is_convertible<const BSTOptional<U>&&, value_type>>>>,
				int> = 0>
		BSTOptional& operator=(BSTOptional<U>&& a_rhs) noexcept(
			std::conjunction_v<
				std::is_nothrow_destructible<value_type>,
				std::is_nothrow_constructible<value_type, U&&>>)
		{
			reset();
			if (a_rhs.has_value()) {
				stl::construct_at(std::addressof(_value), std::move(a_rhs).value());
				_hasValue = true;
			}
			return *this;
		}

		constexpr const value_type* operator->() const noexcept { return std::addressof(value()); }
		constexpr value_type* operator->() noexcept { return std::addressof(value()); }
		constexpr const value_type& operator*() const& noexcept { return value(); }
		constexpr value_type& operator*() & noexcept { return value(); }
		constexpr const value_type&& operator*() const&& noexcept { return std::move(*this).value(); }
		constexpr value_type&& operator*() && noexcept { return std::move(*this).value(); }

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return has_value(); }
		[[nodiscard]] constexpr bool has_value() const noexcept { return _hasValue; }

		[[nodiscard]] constexpr value_type& value() & noexcept
		{
			assert(has_value());
			return _value;
		}

		constexpr const value_type& value() const& noexcept
		{
			assert(has_value());
			return _value;
		}

		constexpr value_type&& value() && noexcept
		{
			assert(has_value());
			return std::move(_value);
		}

		constexpr const value_type&& value() const&& noexcept
		{
			assert(has_value());
			return std::move(_value);
		}

		void reset() noexcept(
			std::is_nothrow_destructible_v<value_type>)
		{
			if (has_value()) {
				if constexpr (!std::is_trivially_destructible_v<value_type>) {
					stl::destroy_at(std::addressof(_value));
				}
				_hasValue = false;
			}
		}

	private:
		// members
		union
		{
			std::remove_const_t<value_type> _value;
			std::byte _buffer[sizeof(value_type)]{};
		};						  // 00
		bool _hasValue{ false };  // ??
	};

	template <class T>
	BSTOptional(T) -> BSTOptional<T>;
}
