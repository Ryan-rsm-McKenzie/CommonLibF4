#pragma once

#include "RE/Bethesda/BSExtraData.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/MemoryManager.h"
#include "RE/NetImmerse/NiPoint3.h"

namespace RE
{
	template <class, class>
	class BSPointerHandleManagerInterface;

	template <class>
	class BSPointerHandleSmartPointer;

	class BGSConstructibleObject;
	class BGSKeyword;
	class TESBoundObject;
	class TESForm;
	class TESObjectCELL;
	class TESWorldSpace;

	template <class, class>
	struct BSTTuple;

	namespace PowerUtils
	{
		class PowerGrid;
	}

	namespace Workshop
	{
		struct BuildableAreaEvent;
		struct PlacementStatusEvent;

		struct ContextData
		{
		public:
			// members
			NiPoint3 lookPos;           // 00
			NiPoint3 lookDir;           // 0C
			float zAngle;               // 18
			TESObjectCELL* parentCell;  // 20
			TESWorldSpace* worldSpace;  // 28
		};
		static_assert(sizeof(ContextData) == 0x30);

		struct DeletedItemInfo
		{
		public:
			~DeletedItemInfo() noexcept {}  // NOLINT(modernize-use-equals-default)

			// members
			std::uint32_t formID;  // 0
			std::uint32_t count;   // 4
		};
		static_assert(sizeof(DeletedItemInfo) == 0x8);

		class __declspec(novtable) ExtraData :
			public BSExtraData  // 00
		{
		public:
			static constexpr auto RTTI{ RTTI::Workshop__ExtraData };
			static constexpr auto VTABLE{ VTABLE::Workshop__ExtraData };
			static constexpr auto TYPE{ EXTRA_DATA_TYPE::kWorkshop };

			// members
			PowerUtils::PowerGrid* currentPowerGrid;            // 18
			BSTArray<PowerUtils::PowerGrid*> powerGrid;         // 20
			BSTArray<Workshop::DeletedItemInfo*> deletedItems;  // 38
			std::int32_t powerRating;                           // 50
			bool offGridItems;                                  // 54
		};
		static_assert(sizeof(ExtraData) == 0x58);

		class WorkshopMenuNode
		{
		public:
			~WorkshopMenuNode() { Clear(); }

			void Clear()
			{
				filterKeyword = nullptr;
				parent = nullptr;
				recipe = nullptr;
				row = 0;
				column = 0;
				selected = false;
				children.clear();
			}

			bool FindAndSetSelectedNode(std::uint16_t a_row, std::uint32_t a_crc, std::uint16_t& a_outRow)
			{
				using func_t = decltype(&WorkshopMenuNode::FindAndSetSelectedNode);
				REL::Relocation<func_t> func{ REL::ID(1309368) };
				return func(this, a_row, a_crc, a_outRow);
			}

			F4_HEAP_REDEFINE_NEW(WorkshopMenuNode);

			// members
			BGSKeyword* filterKeyword{ nullptr };                      // 00
			WorkshopMenuNode* parent{ nullptr };                       // 08
			BSTArray<msvc::unique_ptr<WorkshopMenuNode>> children;     // 10
			BGSConstructibleObject* recipe{ nullptr };                 // 28
			BGSConstructibleObject* sourceFormListRecipe{ nullptr };   // 30
			TESForm* form{ nullptr };                                  // 38
			std::uint32_t uniqueID{ static_cast<std::uint32_t>(-1) };  // 40
			std::uint16_t row{ 0 };                                    // 44
			std::uint16_t column{ 0 };                                 // 46
			bool selected{ false };                                    // 48
		};
		static_assert(sizeof(WorkshopMenuNode) == 0x50);

		[[nodiscard]] inline WorkshopMenuNode* GetSelectedWorkshopMenuNode(std::uint32_t a_row, std::uint32_t& a_column)
		{
			using func_t = decltype(&Workshop::GetSelectedWorkshopMenuNode);
			REL::Relocation<func_t> func{ REL::ID(763948) };
			return func(a_row, a_column);
		}

		inline void ScrapReference(const ContextData& a_context, BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<TESObjectREFR, HandleManager>>& a_scrapRef, BSTArray<BSTTuple<TESBoundObject*, std::uint32_t>>* a_rewards)
		{
			using func_t = decltype(&Workshop::ScrapReference);
			REL::Relocation<func_t> func{ REL::ID(636327) };
			return func(a_context, a_scrapRef, a_rewards);
		}

		[[nodiscard]] inline bool WorkshopCanShowRecipe(BGSConstructibleObject* a_recipe, BGSKeyword* a_filter)
		{
			using func_t = decltype(&Workshop::WorkshopCanShowRecipe);
			REL::Relocation<func_t> func{ REL::ID(239190) };
			return func(a_recipe, a_filter);
		}
	}
}
