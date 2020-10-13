#pragma once

#include "RE/Havok/hkArray.h"
#include "RE/Havok/hknpCollisionQueryCollector.h"
#include "RE/Havok/hknpCollisionResult.h"

namespace RE
{
	class __declspec(novtable) hknpAllHitsCollector :
		public hknpCollisionQueryCollector  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpAllHitsCollector };
		static constexpr auto VTABLE{ VTABLE::hknpAllHitsCollector };

		// override (hknpCollisionQueryCollector)
		void Reset() override;                                // 01
		void AddHit(const hknpCollisionResult&) override;     // 02
		bool HasHit() const override;                         // 03
		std::int32_t GetNumHits() const override;             // 04
		const hknpCollisionResult* GetHits() const override;  // 05

		// members
		hkInplaceArray<hknpCollisionResult, 10> hits;  // 020
	};
	static_assert(sizeof(hknpAllHitsCollector) == 0x3F0);
}
