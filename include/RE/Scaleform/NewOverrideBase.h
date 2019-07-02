#pragma once

#include "RE/Scaleform/Memory.h"
#include "RE/Scaleform/Stats.h"


namespace RE
{
	namespace Scaleform
	{
		template <UInt32 STAT>
		class NewOverrideBase
		{
		public:
			enum { kStatType = STAT };

			SF_MEMORY_REDEFINE_NEW(NewOverrideBase, STAT);
		};
		STATIC_ASSERT(sizeof(NewOverrideBase<0>) == 0x1);
	}
}
