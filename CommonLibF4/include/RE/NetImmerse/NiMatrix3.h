#pragma once

#include "RE/NetImmerse/NiPoint4.h"

namespace RE
{
	class alignas(0x10) NiMatrix3
	{
	public:
		// members
		NiPoint4 entry[3];	// 00
	};
	static_assert(sizeof(NiMatrix3) == 0x30);
}
