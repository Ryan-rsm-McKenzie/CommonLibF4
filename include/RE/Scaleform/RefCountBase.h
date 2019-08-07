#pragma once

#include "RE/Scaleform/RefCountBaseStatImpl.h"
#include "RE/Scaleform/RefCountImpl.h"


namespace RE
{
	namespace Scaleform
	{
		template <class T, UInt32 STAT>
		class RefCountBase : public RefCountBaseStatImpl<RefCountImpl, STAT>
		{
		public:
			enum { kStatType = STAT };

			RefCountBase() = default;
		};
		STATIC_ASSERT(sizeof(RefCountBase<void, 0>) == 0x10);
	}
}
