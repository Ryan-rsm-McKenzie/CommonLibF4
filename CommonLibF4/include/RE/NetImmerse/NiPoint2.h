#pragma once

namespace RE
{
	class NiPoint2
	{
	public:
		// members
		float x;
		float y;
	};
	static_assert(sizeof(NiPoint2) == 0x8);
}
