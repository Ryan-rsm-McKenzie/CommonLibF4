#pragma once

#include "RE/NetImmerse/NiTDefaultAllocator.h"
#include "RE/NetImmerse/NiTPointerListBase.h"

namespace RE
{
	template <class T>
	class NiTList :
		public NiTPointerListBase<NiTDefaultAllocator<T>, T>  // 00
	{
	public:
	};
}
