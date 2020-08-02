#include "RE/Bethesda/BSLock.h"

namespace RE
{
	template struct BSAutoLockDefaultPolicy<BSSpinLock>;
	static_assert(std::is_empty_v<BSAutoLockDefaultPolicy<BSSpinLock>>);

	template class BSAutoLock<BSSpinLock>;
	static_assert(sizeof(BSAutoLock<BSSpinLock>) == 0x8);
}
