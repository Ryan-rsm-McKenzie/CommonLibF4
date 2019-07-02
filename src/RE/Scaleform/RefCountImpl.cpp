#include "RE/Scaleform/RefCountImpl.h"


namespace RE
{
	namespace Scaleform
	{
		void RefCountImpl::AddRef()
		{
			InterlockedIncrement(&_refCount);
		}


		void RefCountImpl::Release()
		{
			if (InterlockedDecrement(&_refCount) == 0) {
				delete this;
			}
		}
	}
}
