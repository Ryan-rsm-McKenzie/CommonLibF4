#pragma once

#include "RE/Scaleform/Stats.h"


namespace RE
{
	namespace Scaleform
	{
		class StatBag
		{
		public:
			enum
			{
				kMemGranularity = 8,
				kPageShift = 4,
				kPageSize = 1 << kPageShift,
				kPageTableSize = kStat_MaxID / kPageSize,
				kEndID = kStat_MaxID,
				kIDUnused = static_cast<UInt16>(-1)
			};


			// members
			UInt8*	mem;							// 00
			UInt32	memSize;						// 08
			UInt32	pad0C;							// 0C
			UPInt	memAllocOffset;					// 10
			UInt16	idPageTable[kPageTableSize];	// 18
		};
		STATIC_ASSERT(sizeof(StatBag) == 0x218);
	}
}
