#pragma once

namespace RE
{
	class NiPoint3
	{
	public:
		// members
		float x;  // 0
		float y;  // 4
		float z;  // 8
	};
	static_assert(sizeof(NiPoint3) == 0xC);

	class alignas(0x10) NiPoint3A :
		public NiPoint3
	{
	public:
	};
	static_assert(sizeof(NiPoint3A) == 0x10);
}
