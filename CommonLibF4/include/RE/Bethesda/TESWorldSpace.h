#pragma once

#include "RE/Bethesda/BSPointerHandle.h"
#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/TESForms.h"
#include "RE/NetImmerse/NiPoint2.h"
#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/NetImmerse/NiTMap.h"

namespace RE
{
	class BGSTerrainManager;
	class BSMultiBoundNode;
	class BSPortalGraph;
	class NiNode;
	class QueuedPromoteLargeReferencesTask;

	struct WORLD_MAP_DATA
	{
	public:
		// members
		std::uint32_t usableWidth;   // 00
		std::uint32_t usableHeight;  // 04
		std::int16_t nwCellX;        // 08
		std::int16_t nwCellY;        // 0A
		std::int16_t seCellX;        // 0C
		std::int16_t seCellY;        // 0E
	};
	static_assert(sizeof(WORLD_MAP_DATA) == 0x10);

	struct WORLD_MAP_OFFSET_DATA
	{
	public:
		// members
		float mapScale;    // 00
		float mapOffsetX;  // 04
		float mapOffsetY;  // 08
		float mapOffsetZ;  // 0C
	};
	static_assert(sizeof(WORLD_MAP_OFFSET_DATA) == 0x10);

	class BGSLargeRefData
	{
	public:
		struct REF_CELL_DATA
		{
		public:
			// members
			std::uint32_t refID;          // 0
			std::uint32_t parentCellKey;  // 4
		};
		static_assert(sizeof(REF_CELL_DATA) == 0x8);

		// members
		BSTHashMap<std::uint32_t, BSTArray<REF_CELL_DATA>*> cellOverlappingRefMap;                  // 00
		BSTHashMap<std::uint32_t, NiPointer<QueuedPromoteLargeReferencesTask>> cellPromoteTaskMap;  // 30
	};
	static_assert(sizeof(BGSLargeRefData) == 0x60);

	class __declspec(novtable) TESWorldSpace :
		public TESForm,      // 000
		public TESFullName,  // 020
		public TESTexture    // 030
	{
	public:
		static constexpr auto RTTI{ RTTI::TESWorldSpace };
		static constexpr auto VTABLE{ VTABLE::TESWorldSpace };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kWRLD };

		enum class PARENT_USE_FLAG
		{
			kLand = 1u << 0,
			kLOD = 1u << 1,
			kMap = 1u << 2,
			kWater = 1u << 3,
			kClimate = 1u << 4,

			kSkyCell = 1u << 6
		};

		struct ShortPoint
		{
		public:
			// members
			std::int16_t x;  // 0
			std::int16_t y;  // 2
		};
		static_assert(sizeof(ShortPoint) == 0x4);

		struct OFFSET_DATA
		{
		public:
			// members
			std::uint32_t* cellFileOffsets;  // 00
			std::uint32_t* cellFileSizes;    // 08
			NiPoint2 offsetMinCoords;        // 10
			NiPoint2 offsetMaxCoords;        // 18
			std::uint32_t fileOffset;        // 20
		};
		static_assert(sizeof(OFFSET_DATA) == 0x28);

		[[nodiscard]] TESWorldSpace* GetParentWorld(PARENT_USE_FLAG a_flags) const noexcept
		{
			return parentUseFlags.all(a_flags) ? parentWorld : nullptr;
		}

		[[nodiscard]] TESWaterForm* GetWaterType() const noexcept
		{
			auto root = this;
			for (auto iter = root; iter; iter = iter->GetParentWorld(PARENT_USE_FLAG::kWater)) {
				root = iter;
			}

			if (root->worldWater) {
				return root->worldWater;
			} else {
				REL::Relocation<TESWaterForm**> defaultWater{ REL::ID(289864) };
				return *defaultWater;
			}
		}

		// members
		BSTHashMap<std::int32_t, TESObjectCELL*> cellMap;                                      // 040
		TESObjectCELL* persistentCell;                                                         // 070
		BGSTerrainManager* terrainManager;                                                     // 078
		TESClimate* climate;                                                                   // 080
		std::int8_t flags;                                                                     // 088
		stl::enumeration<PARENT_USE_FLAG, std::uint16_t> parentUseFlags;                       // 08A
		std::int8_t worldFlags;                                                                // 08C
		ShortPoint fixedCenter;                                                                // 08E
		BSTHashMap<std::uint32_t, BSTArray<NiPointer<TESObjectREFR>>*> fixedPersistentRefMap;  // 098
		BSTArray<NiPointer<TESObjectREFR>> mobilePersistentRefs;                               // 0C8
		BSTHashMap<std::uint32_t, BSSimpleList<TESObjectREFR*>*> overlappedMultiboundMap;      // 0E0
		TESObjectCELL* skyCell;                                                                // 110
		BSTHashMap<std::uint32_t, BGSLocation*> locationMap;                                   // 118
		BSTArray<TESObjectREFR*> teleportDoorCache;                                            // 148
		NiPointer<BSPortalGraph> portalGraph;                                                  // 160
		BSTHashMap<ObjectRefHandle, NiPointer<BSMultiBoundNode>>* multiboundRefMap;            // 168
		BSTHashMap<BSMultiBoundNode*, ObjectRefHandle>* refMultiboundMap;                      // 170
		NiPointer<NiNode> multiboundNode;                                                      // 178
		NiPointer<NiNode> portalSharedNode;                                                    // 180
		TESWorldSpace* parentWorld;                                                            // 188
		BGSLightingTemplate* lightingTemplate;                                                 // 190
		TESWaterForm* worldWater;                                                              // 198
		TESWaterForm* lodWater;                                                                // 1A0
		float lodWaterHeight;                                                                  // 1A8
		WORLD_MAP_DATA worldMapData;                                                           // 1AC
		WORLD_MAP_OFFSET_DATA worldMapOffsetData;                                              // 1BC
		BGSMusicType* musicType;                                                               // 1D0
		NiPoint2 minimumCoords;                                                                // 1D8
		NiPoint2 maximumCoords;                                                                // 1E0
		NiTMap<TESFile*, TESWorldSpace::OFFSET_DATA*> offsetDataMap;                           // 1E8
		BSStringT<char> editorID;                                                              // 208
		float defaultLandHeight;                                                               // 218
		float defaultWaterHeight;                                                              // 21C
		float distantLODMult;                                                                  // 220
		BGSEncounterZone* encounterZone;                                                       // 228
		BGSLocation* location;                                                                 // 230
		TESTexture canopyShadowTexture;                                                        // 238
		TESTexture waterEnvMap;                                                                // 248
		BGSLargeRefData largeRefData;                                                          // 258
		float northRotation;                                                                   // 2B8
		std::int8_t lvlDataCellStartX;                                                         // 2BC
		std::int8_t lvlDataCellStartY;                                                         // 2BD
		std::int8_t lvlDataCellWidthX;                                                         // 2BE
		std::int8_t lvlDataCellWidthY;                                                         // 2BF
		std::int8_t* lvlDataCellA;                                                             // 2C0
		std::int8_t* maxHeightData;                                                            // 2C8
	};
	static_assert(sizeof(TESWorldSpace) == 0x2D0);
}
