#pragma once

namespace RE
{
	template <class Integral, Integral N, class Discriminant>
	struct hkHandle
	{
	public:
		~hkHandle() noexcept {}  // intentional

		// members
		Integral value;  // 0
	};
}
