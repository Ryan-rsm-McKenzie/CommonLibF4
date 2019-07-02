#include "RE/Scaleform/Lock.h"


namespace RE
{
	namespace Scaleform
	{
		Lock::Locker::Locker(Lock& a_lock)
		{
			_lock = &a_lock;
			_lock->lock();
		}


		Lock::Locker::~Locker()
		{
			_lock->unlock();
		}


		void Lock::lock()
		{
			EnterCriticalSection(&cs);
		}


		void Lock::unlock()
		{
			LeaveCriticalSection(&cs);
		}
	}
}
