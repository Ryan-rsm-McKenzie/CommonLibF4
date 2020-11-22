#pragma once

#include "RE/Bethesda/BSFixedString.h"

namespace RE::Movement
{
	struct MaxSpeeds
	{
	public:
		// members
		float speeds[7][4];  // 00
	};
	static_assert(sizeof(MaxSpeeds) == 0x70);

	struct TypeData
	{
	public:
		// members
		BSFixedString typeName;  // 00
		MaxSpeeds defaultData;   // 08
		float floatHeight;       // 78
		float flightAngleGain;   // 7C
	};
	static_assert(sizeof(TypeData) == 0x80);
}
