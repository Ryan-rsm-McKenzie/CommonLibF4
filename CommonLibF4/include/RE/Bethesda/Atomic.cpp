#include "RE/Bethesda/Atomic.h"

namespace RE
{
	template class BSTAtomicValue<std::int32_t>;
	static_assert(sizeof(BSTAtomicValue<std::int32_t>) == 0x4);

	template class BSTAtomicValue<std::uint32_t>;
	static_assert(sizeof(BSTAtomicValue<std::uint32_t>) == 0x4);

	template class BSTAtomicValue<std::int64_t>;
	static_assert(sizeof(BSTAtomicValue<std::int64_t>) == 0x8);

	template class BSTAtomicValue<std::uint64_t>;
	static_assert(sizeof(BSTAtomicValue<std::uint64_t>) == 0x8);
}
