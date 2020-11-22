#pragma once

#include "RE/Bethesda/BSFixedString.h"

namespace RE::BGSBodyPartDefs
{
	struct HitReactionData
	{
	public:
		// members
		BSFixedString chainStart;  // 00
		BSFixedString chainEnd;    // 08
		BSFixedString variableX;   // 10
		BSFixedString variableY;   // 18
		BSFixedString variableZ;   // 20
	};
	static_assert(sizeof(HitReactionData) == 0x28);
}
