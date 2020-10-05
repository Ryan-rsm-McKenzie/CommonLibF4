#pragma once

#include "RE/Bethesda/BSExtraData.h"
#include "RE/Bethesda/BSTArray.h"

namespace RE
{
	namespace PowerUtils
	{
		class PowerGrid;
	}

	struct Workshop
	{
	public:
		struct DeletedItemInfo
		{
		public:
			~DeletedItemInfo() noexcept {}	// intentional

			// members
			std::uint32_t formID;  // 0
			std::uint32_t count;   // 4
		};
		static_assert(sizeof(DeletedItemInfo) == 0x8);

		class __declspec(novtable) ExtraData :
			public BSExtraData	// 00
		{
		public:
			static constexpr auto RTTI{ RTTI::Workshop__ExtraData };
			static constexpr auto VTABLE{ VTABLE::Workshop__ExtraData };
			static constexpr auto TYPE{ EXTRA_DATA_TYPE::kWorkshop };

			// members
			PowerUtils::PowerGrid* currentPowerGrid;			// 18
			BSTArray<PowerUtils::PowerGrid*> powerGrid;			// 20
			BSTArray<Workshop::DeletedItemInfo*> deletedItems;	// 38
			std::int32_t powerRating;							// 50
			bool offGridItems;									// 54
		};
		static_assert(sizeof(ExtraData) == 0x58);
	};
	static_assert(std::is_empty_v<Workshop>);
}
