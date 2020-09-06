#pragma once

#include "RE/NetImmerse/NiMatrix3.h"
#include "RE/NetImmerse/NiPoint3.h"

namespace RE
{
	class NiTransform
	{
	public:
		// members
		NiMatrix3 rotate;	 // 00
		NiPoint3 translate;	 // 30
		float scale;		 // 3C
	};
	static_assert(sizeof(NiTransform) == 0x40);
}
