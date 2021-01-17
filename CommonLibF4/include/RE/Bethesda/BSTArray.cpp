#include "RE/Bethesda/BSTArray.h"

namespace RE
{
	template class BSTAlignedHeapArrayAllocator<0x10>::Allocator;
	static_assert(sizeof(BSTAlignedHeapArrayAllocator<0x10>::Allocator) == 0x10);

	template class BSTDataBuffer<1>;
	static_assert(sizeof(BSTDataBuffer<1>) == 0x10);

	template class BSTDataBuffer<2>;
	static_assert(sizeof(BSTDataBuffer<2>) == 0x10);
}
