#include "RE/Scaleform/RefCountImplCore.h"


namespace RE
{
	namespace Scaleform
	{
		RefCountImplCore::RefCountImplCore() :
			_refCount(1),
			_pad0C(0)
		{}


		SInt32 RefCountImplCore::GetRefCount() const
		{
			return _refCount;
		}


		void RefCountImplCore::operator=(const RefCountImplCore&)
		{
			return;
		}
	}
}
