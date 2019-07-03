#pragma once

#include "RE/Scaleform/MemoryHeap.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			struct MemoryParams
			{
				MemoryParams(UPInt a_memoryArena = 0);


				// members
				MemoryHeap::HeapDesc	desc;						// 00
				float					heapLimitMultiplier;		// 40
				UInt32					maxCollectionRoots;			// 44
				UInt32					framesBetweenCollections;	// 48
				UInt32					initialDynamicLimit;		// 4C
			};
			STATIC_ASSERT(sizeof(MemoryParams) == 0x50);
		}
	}
}
