#pragma once

namespace RE
{
	template <class Integral, class>
	class NiTFlags
	{
	public:
		using integral_type = Integral;

		static_assert(std::is_integral_v<integral_type>);

		constexpr NiTFlags() noexcept {}  // NOLINT(moderinize-use-equals-default)

		// members
		integral_type flags{ 0 };  // 00
	};
}
