#pragma once

#include "RE/Bethesda/BSPointerHandle.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTSingleton.h"

namespace RE
{
	class BGSInventoryItem;

	namespace InventoryInterface
	{
		struct CountChangedEvent
		{
		public:
			// members
			std::uint32_t inventoryOwnerID;  // 00
			std::uint32_t itemID;            // 04
			std::int32_t newCount;           // 08
			std::int32_t oldCount;           // 0C
		};
		static_assert(sizeof(CountChangedEvent) == 0x10);

		struct FavoriteChangedEvent
		{
		public:
			~FavoriteChangedEvent() noexcept {}  // intentional

			// members
			BGSInventoryItem* itemAffected;  // 0
		};
		static_assert(sizeof(FavoriteChangedEvent) == 0x8);

		struct Handle
		{
		public:
			~Handle() noexcept {}  // intentional

			// members
			std::uint32_t id;  // 0
		};
		static_assert(sizeof(Handle) == 0x4);
	}

	class BGSInventoryInterface :
		BSTSingletonSDM<BGSInventoryInterface>,                   // 00
		BSTEventSource<InventoryInterface::CountChangedEvent>,    // 08
		BSTEventSource<InventoryInterface::FavoriteChangedEvent>  // 60
	{
	public:
		struct Agent
		{
		public:
			// members
			std::uint32_t handleID;     // 0
			ObjectRefHandle itemOwner;  // 4
			std::uint16_t listIndex;    // 8
			std::uint16_t refCount;     // A
		};
		static_assert(sizeof(Agent) == 0xC);

		[[nodiscard]] static BGSInventoryInterface* GetSingleton()
		{
			REL::Relocation<BGSInventoryInterface**> singleton{ REL::ID(501899) };
			return *singleton;
		}

		[[nodiscard]] const BGSInventoryItem* RequestInventoryItem(const std::uint32_t& a_handleID) const
		{
			using func_t = decltype(&BGSInventoryInterface::RequestInventoryItem);
			REL::Relocation<func_t> func{ REL::ID(1200959) };
			return func(this, a_handleID);
		}

		// members
		BSTArray<Agent> agentArray;  // B8
	};
	static_assert(sizeof(BGSInventoryInterface) == 0xD0);
}
