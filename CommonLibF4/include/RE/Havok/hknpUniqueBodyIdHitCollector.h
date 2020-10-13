#pragma once

#include "RE/Havok/hkRefPtr.h"
#include "RE/Havok/hknpAllHitsCollector.h"

namespace RE
{
	class hknpBSWorld;

	class __declspec(novtable) hknpUniqueBodyIdHitCollector :
		public hknpAllHitsCollector  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpUniqueBodyIdHitCollector };
		static constexpr auto VTABLE{ VTABLE::hknpUniqueBodyIdHitCollector };

		// members
		hkRefPtr<hknpBSWorld> latentWorld;  // 3F0
	};
	static_assert(sizeof(hknpUniqueBodyIdHitCollector) == 0x400);
}
