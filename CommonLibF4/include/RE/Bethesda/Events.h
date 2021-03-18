#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSPointerHandle.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/UserEvents.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class BGSMessage;
	class TESObjectCELL;
	class TESObjectREFR;

	struct BSThreadEvent
	{
	public:
		enum class Event
		{
			kOnStartup,
			kOnShutdown
		};

		static void InitSDM()
		{
			using func_t = decltype(&BSThreadEvent::InitSDM);
			REL::Relocation<func_t> func{ REL::ID(1425097) };
			return func();
		}
	};
	static_assert(std::is_empty_v<BSThreadEvent>);

	enum class QuickContainerMode : std::int32_t
	{
		kLoot,
		kTeammate,
		kPowerArmor,
		kTurret,
		kWorkshop,
		kCrafting,
		kStealing,
		kStealingPowerArmor
	};

	struct CellAttachDetachEvent
	{
	public:
		enum class EVENT_TYPE
		{
			kPreAttach,
			kPostAttach,
			kPreDetach,
			kPostDetach
		};

		// members
		TESObjectCELL* cell;                              // 00
		stl::enumeration<EVENT_TYPE, std::int32_t> type;  // 08
	};
	static_assert(sizeof(CellAttachDetachEvent) == 0x10);

	struct InventoryItemDisplayData
	{
	public:
		// members
		BSFixedStringCS itemName;       // 00
		std::uint32_t itemCount;        // 08
		std::uint32_t equipState;       // 0C
		std::uint32_t filterFlag;       // 10
		bool isLegendary;               // 14
		bool isFavorite;                // 15
		bool isTaggedForSearch;         // 16
		bool isBetterThanEquippedItem;  // 17
	};
	static_assert(sizeof(InventoryItemDisplayData) == 0x18);

	class MenuModeChangeEvent
	{
	public:
		// members
		BSFixedString menuName;  // 00
		bool enteringMenuMode;   // 08
	};
	static_assert(sizeof(MenuModeChangeEvent) == 0x10);

	class MenuModeCounterChangedEvent
	{
	public:
		// members
		BSFixedString menuName;  // 00
		bool incrementing;       // 08
	};
	static_assert(sizeof(MenuModeCounterChangedEvent) == 0x10);

	class MenuOpenCloseEvent
	{
	public:
		// members
		BSFixedString menuName;  // 00
		bool opening;            // 08
	};
	static_assert(sizeof(MenuOpenCloseEvent) == 0x10);

	struct QuickContainerStateData
	{
	public:
		// members
		BSTSmallArray<InventoryItemDisplayData, 5> itemData;      // 00
		ObjectRefHandle containerRef;                             // 88
		ObjectRefHandle inventoryRef;                             // 8C
		BSFixedStringCS aButtonText;                              // 90
		BSFixedString containerName;                              // 98
		BSFixedStringCS perkButtonText;                           // A0
		std::int32_t selectedClipIndex;                           // A8
		stl::enumeration<QuickContainerMode, std::int32_t> mode;  // AC
		bool perkButtonEnabled;                                   // B0
		bool isNewContainer;                                      // B1
		bool addedDroppedItems;                                   // B2
		bool isLocked;                                            // B3
		bool buttonAEnabled;                                      // B4
		bool buttonXEnabled;                                      // B5
		bool refreshContainerSize;                                // B6
		bool containerActivated;                                  // B7
	};
	static_assert(sizeof(QuickContainerStateData) == 0xB8);

	class QuickContainerStateEvent :
		public BSTValueEvent<QuickContainerStateData>  // 00
	{
	public:
	};
	static_assert(sizeof(QuickContainerStateEvent) == 0xC0);

	struct TESFurnitureEvent
	{
	public:
		enum class FurnitureEventType : std::int32_t
		{
			kEnter,
			kExit
		};

		// members
		NiPointer<TESObjectREFR> actor;                           // 00
		NiPointer<TESObjectREFR> targetFurniture;                 // 08
		stl::enumeration<FurnitureEventType, std::int32_t> type;  // 10
	};
	static_assert(sizeof(TESFurnitureEvent) == 0x18);

	struct TESMagicEffectApplyEvent
	{
	public:
		// members
		NiPointer<TESObjectREFR> target;  // 00
		NiPointer<TESObjectREFR> caster;  // 08
		std::uint32_t magicEffectFormID;  // 10
	};
	static_assert(sizeof(TESMagicEffectApplyEvent) == 0x18);

	class TutorialEvent
	{
	public:
		// members
		BSFixedString eventName;     // 00
		const BGSMessage* assocMsg;  // 08
	};
	static_assert(sizeof(TutorialEvent) == 0x10);

	class UserEventEnabledEvent
	{
	public:
		// members
		stl::enumeration<UserEvents::USER_EVENT_FLAG, std::int32_t> newUserEventFlag;  // 0
		stl::enumeration<UserEvents::USER_EVENT_FLAG, std::int32_t> oldUserEventFlag;  // 4
		stl::enumeration<UserEvents::SENDER_ID, std::int32_t> senderID;                // 8
	};
	static_assert(sizeof(UserEventEnabledEvent) == 0xC);

	namespace CellAttachDetachEventSource
	{
		struct CellAttachDetachEventSourceSingleton :
			public BSTSingletonImplicit<CellAttachDetachEventSourceSingleton>
		{
		public:
			[[nodiscard]] static CellAttachDetachEventSourceSingleton& GetSingleton()
			{
				using func_t = decltype(&CellAttachDetachEventSourceSingleton::GetSingleton);
				REL::Relocation<func_t> func{ REL::ID(862142) };
				return func();
			}

			// members
			BSTEventSource<CellAttachDetachEvent> source;  // 00
		};
		static_assert(sizeof(CellAttachDetachEventSourceSingleton) == 0x58);
	}
}
