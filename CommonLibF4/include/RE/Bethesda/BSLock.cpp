#include "RE/Bethesda/BSLock.h"

namespace RE
{
	template struct BSAutoLockDefaultPolicy<BSSpinLock>;
	static_assert(std::is_empty_v<BSAutoLockDefaultPolicy<BSSpinLock>>);

	template struct BSAutoLockReadLockPolicy<BSReadWriteLock>;
	static_assert(std::is_empty_v<BSAutoLockReadLockPolicy<BSReadWriteLock>>);

	template struct BSAutoLockWriteLockPolicy<BSReadWriteLock>;
	static_assert(std::is_empty_v<BSAutoLockWriteLockPolicy<BSReadWriteLock>>);

	template class BSAutoLock<BSSpinLock, BSAutoLockDefaultPolicy>;
	static_assert(sizeof(BSAutoLock<BSSpinLock, BSAutoLockDefaultPolicy>) == 0x8);

	template class BSAutoLock<BSReadWriteLock, BSAutoLockReadLockPolicy>;
	static_assert(sizeof(BSAutoLock<BSReadWriteLock, BSAutoLockReadLockPolicy>) == 0x8);

	template class BSAutoLock<BSReadWriteLock, BSAutoLockWriteLockPolicy>;
	static_assert(sizeof(BSAutoLock<BSReadWriteLock, BSAutoLockWriteLockPolicy>) == 0x8);
}
