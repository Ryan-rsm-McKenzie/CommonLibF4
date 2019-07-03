#include "RE/Scaleform/GFx/MemoryParams.h"

#include <limits>


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			MemoryParams::MemoryParams(UPInt a_memoryArena) :
				desc(),
				heapLimitMultiplier(0.25),
				maxCollectionRoots(std::numeric_limits<UInt32>::max()),
				framesBetweenCollections(std::numeric_limits<UInt32>::max()),
				initialDynamicLimit(std::numeric_limits<UInt32>::max())
			{}
		}
	}
}
