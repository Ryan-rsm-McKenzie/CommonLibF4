#include "RE/BSSpinLock.h"


namespace RE
{
	BSSpinLock::BSSpinLock() :
		_threadID(0),
		_lockValue(0)
	{}
}
