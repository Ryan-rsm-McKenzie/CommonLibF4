#pragma once

namespace RE
{
	template <class T>
	class BSTAtomicValue
	{
	public:
		static_assert(std::is_integral_v<T>);

		using value_type = T;

		constexpr BSTAtomicValue() noexcept = default;

		constexpr BSTAtomicValue(T a_rhs) noexcept :
			_value(a_rhs)
		{}

		inline T operator++() { return InterlockedIncrement(std::addressof(_value)); }

		[[nodiscard]] inline T operator++(int)
		{
			const auto old = _value;
			++(*this);
			return old;
		}

		inline T operator--() { return InterlockedDecrement(std::addressof(_value)); }

		[[nodiscard]] inline T operator--(int)
		{
			const auto old = _value;
			--(*this);
			return old;
		}

		// members
		std::add_volatile_t<T> _value{};  // 0
	};

	extern template class BSTAtomicValue<std::int32_t>;
	extern template class BSTAtomicValue<std::uint32_t>;
	extern template class BSTAtomicValue<std::int64_t>;
	extern template class BSTAtomicValue<std::uint64_t>;
}
