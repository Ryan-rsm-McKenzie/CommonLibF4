#pragma once

#include "RE/Bethesda/BSInputEventSingleUser.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTSingleton.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class BGSConstructibleObject;
	class QueuedFile;
	class QuickContainerStateEvent;
	class TESBoundObject;

	namespace BGSInventoryListEvent
	{
		struct Event;
	}

	namespace FavoriteMgr_Events
	{
		struct ComponentFavoriteEvent;
	}

	namespace InventoryInterface
	{
		struct FavoriteChangedEvent;
	}

	class __declspec(novtable) FavoritesManager :
		public BSInputEventSingleUser,                                     // 000
		public BSTEventSink<BGSInventoryListEvent::Event>,                 // 020
		public BSTEventSink<InventoryInterface::FavoriteChangedEvent>,     // 028
		public BSTSingletonSDM<FavoritesManager>,                          // 030
		public BSTEventSource<FavoriteMgr_Events::ComponentFavoriteEvent>  // 038
	{
	public:
		static constexpr auto RTTI{ RTTI::FavoritesManager };
		static constexpr auto VTABLE{ VTABLE::FavoritesManager };

		// members
		TESBoundObject* storedFavTypes[12];                                    // 090
		NiPointer<QueuedFile> bufferedFavGeometries[12];                       // 0F0
		BSTSet<const BGSConstructibleObject*> favoriteMods;                    // 150
		BSTHashMap<const TESBoundObject*, std::uint32_t> favoritedComponents;  // 180
		BSTSmallArray<std::int32_t, 12> weaponLoadedAmmo;                      // 1B0
		BSTValueEventSink<QuickContainerStateEvent> quickContainerMode;        // 1F0
		bool allowStimpakUse;                                                  // 2C8
	};
	static_assert(sizeof(FavoritesManager) == 0x2D0);
}
