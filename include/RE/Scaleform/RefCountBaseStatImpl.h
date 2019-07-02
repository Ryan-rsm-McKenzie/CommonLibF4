#pragma once

#include "RE/Scaleform/Memory.h"
#include "RE/Scaleform/Stats.h"

#define SF_REFCOUNTALLOC_CHECK_DELETE(class_name, p)


namespace RE
{
	namespace Scaleform
	{
		template <class Base, UInt32 STAT>
		class RefCountBaseStatImpl : public Base
		{
		public:
			RefCountBaseStatImpl() = default;

			SF_MEMORY_REDEFINE_NEW_IMPL(Base, SF_REFCOUNTALLOC_CHECK_DELETE, STAT)
		};
		// size == sizeof(Base)
	}
}
