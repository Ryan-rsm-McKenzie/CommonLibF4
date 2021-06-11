#pragma once

#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTList.h"
#include "RE/Bethesda/BSTSingleton.h"
#include "RE/Bethesda/TESForms.h"
#include "RE/NetImmerse/NiTArray.h"
#include "RE/NetImmerse/NiTList.h"

namespace RE
{
	class TESFile;
	class TESRegionDataManager;

	struct BGSHotloadCompletedEvent;
	struct TESObjectList;
	struct TESRegionList;

	struct TESFileCollection
	{
	public:
		// members
		BSTArray<TESFile*> files;       // 00
		BSTArray<TESFile*> smallFiles;  // 18
	};
	static_assert(sizeof(TESFileCollection) == 0x30);

	class TESDataHandler :
		public BSTEventSource<BGSHotloadCompletedEvent>,  // 0000
		public BSTSingletonSDM<TESDataHandler>            // 0058
	{
	public:
		[[nodiscard]] static TESDataHandler* GetSingleton()
		{
			REL::Relocation<TESDataHandler**> singleton{ REL::ID(711558) };
			return *singleton;
		}

		[[nodiscard]] bool CheckModsLoaded(bool a_everModded)
		{
			using func_t = decltype(&TESDataHandler::CheckModsLoaded);
			REL::Relocation<func_t> func{ REL::ID(1432894) };
			return func(this, a_everModded);
		}

		template <class T>
		[[nodiscard]] BSTArray<T*>& GetFormArray() noexcept  //
			requires(std::derived_from<T, TESForm> &&
					 !std::is_pointer_v<T> &&
					 !std::is_reference_v<T>)
		{
			assert(T::FORM_ID < ENUM_FORM_ID::kTotal);
			return reinterpret_cast<BSTArray<T*>&>(formArrays[stl::to_underlying(T::FORM_ID)]);
		}

		// members
		TESObjectList* objectList;                                                // 0060
		BSTArray<TESForm*> formArrays[stl::to_underlying(ENUM_FORM_ID::kTotal)];  // 0068
		TESRegionList* regionList;                                                // 0F50
		NiTPrimitiveArray<TESObjectCELL*> interiorCells;                          // 0F58
		NiTPrimitiveArray<BGSAddonNode*> addonNodes;                              // 0F70
		NiTList<TESForm*> badForms;                                               // 0F88
		std::uint32_t nextID;                                                     // 0FA0
		TESFile* activeFile;                                                      // 0FA8
		BSSimpleList<TESFile*> files;                                             // 0FB0
		TESFileCollection compiledFileCollection;                                 // 0FC0
		BSTArray<std::uint32_t> releasedFormIDArray;                              // 0FF0
		bool masterSave;                                                          // 1008
		bool blockSave;                                                           // 1009
		bool saveLoadGame;                                                        // 100A
		bool autoSaving;                                                          // 100B
		bool exportingPlugin;                                                     // 100C
		bool clearingData;                                                        // 100D
		bool hasDesiredFiles;                                                     // 100E
		bool checkingModels;                                                      // 100F
		bool loadingFiles;                                                        // 1010
		bool dontRemoveIDs;                                                       // 1011
		char gameSettingsLoadState;                                               // 1012
		TESRegionDataManager* regionDataManager;                                  // 1018
	};
	static_assert(sizeof(TESDataHandler) == 0x1020);
}
