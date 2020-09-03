#pragma once

#include "RE/Havok/hkRefPtr.h"
#include "RE/Havok/hknpAllHitsCollector.h"

namespace RE
{
	class hknpBSWorld;

	class hknpUniqueBodyIdHitCollector :
		public hknpAllHitsCollector	 // 000
	{
	public:
		static constexpr auto RTTI{ RTTI_hknpUniqueBodyIdHitCollector };

		// members
		hkRefPtr<hknpBSWorld> latentWorld;	// 3F0
	};
	static_assert(sizeof(hknpUniqueBodyIdHitCollector) == 0x400);
}
