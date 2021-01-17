#pragma once

#include "RE/Bethesda/BGSCharacterMorph.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/TESBoundObjects.h"
#include "RE/Bethesda/TESCondition.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiPoint3.h"

namespace RE
{
	enum class CREATURE_SOUND;

	class MenuOpenCloseEvent;

	namespace BGSCharacterTint
	{
		class Entries;
	}

	class __declspec(novtable) TESBoundAnimObject :
		public TESBoundObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESBoundAnimObject };
		static constexpr auto VTABLE{ VTABLE::TESBoundAnimObject };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNONE };
	};
	static_assert(sizeof(TESBoundAnimObject) == 0x68);

	namespace TESSoundDefs
	{
		struct RepeaterData
		{
		public:
			// members
			float minDelay;  // 0
			float maxDelay;  // 4
			bool stackable;  // 8
		};
		static_assert(sizeof(RepeaterData) == 0xC);
	}

	class __declspec(novtable) TESSound :
		public TESBoundAnimObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESSound };
		static constexpr auto VTABLE{ VTABLE::TESSound };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSOUN };

		// members
		BGSSoundDescriptorForm* descriptor;     // 68
		TESSoundDefs::RepeaterData repeatData;  // 70
	};
	static_assert(sizeof(TESEyes) == 0x48);

	class __declspec(novtable) TESObjectACTI :
		public TESBoundAnimObject,         // 000
		public TESFullName,                // 068
		public BGSModelMaterialSwap,       // 078
		public TESMagicTargetForm,         // 120
		public BGSDestructibleObjectForm,  // 0B8
		public BGSOpenCloseForm,           // 0C8
		public BGSKeywordForm,             // 0D0
		public BGSPropertySheet,           // 0F0
		public BGSForcedLocRefType,        // 100
		public BGSNativeTerminalForm,      // 110
		public BGSNavmeshableObject        // 120
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectACTI };
		static constexpr auto VTABLE{ VTABLE::TESObjectACTI };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kACTI };

		// members
		BGSSoundDescriptorForm* soundLoop;      // 128
		BGSSoundDescriptorForm* soundActivate;  // 130
		TESWaterForm* waterForm;                // 138
		std::uint16_t flags;                    // 140
	};
	static_assert(sizeof(TESObjectACTI) == 0x148);

	class __declspec(novtable) BGSTalkingActivator :
		public TESObjectACTI  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSTalkingActivator };
		static constexpr auto VTABLE{ VTABLE::BGSTalkingActivator };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kTACT };

		// add
		virtual bool GetReflectedByAutoWater() { return false; }  // 67

		// members
		TESObjectREFR* tempRef;   // 148
		BGSVoiceType* voiceType;  // 150
	};
	static_assert(sizeof(BGSTalkingActivator) == 0x158);

	struct CONT_DATA
	{
	public:
		// members
		std::int8_t contFlags;  // 0
	};
	static_assert(sizeof(CONT_DATA) == 0x1);

	class __declspec(novtable) TESObjectCONT :
		public TESBoundAnimObject,         // 000
		public TESContainer,               // 068
		public TESFullName,                // 080
		public BGSModelMaterialSwap,       // 090
		public TESWeightForm,              // 0D0
		public TESMagicCasterForm,         // 148
		public TESMagicTargetForm,         // 148
		public BGSDestructibleObjectForm,  // 0E0
		public BGSOpenCloseForm,           // 0F0
		public BGSKeywordForm,             // 0F8
		public BGSForcedLocRefType,        // 118
		public BGSPropertySheet,           // 128
		public BGSNativeTerminalForm       // 138
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectCONT };
		static constexpr auto VTABLE{ VTABLE::TESObjectCONT };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCONT };

		// members
		CONT_DATA data;                        // 149
		BGSSoundDescriptorForm* openSound;     // 150
		BGSSoundDescriptorForm* closeSound;    // 158
		BGSSoundDescriptorForm* takeAllSound;  // 160
		BGSListForm* containsOnlyList;         // 168
	};
	static_assert(sizeof(TESObjectCONT) == 0x170);

	class __declspec(novtable) TESObjectDOOR :
		public TESBoundAnimObject,         // 000
		public TESFullName,                // 068
		public BGSModelMaterialSwap,       // 078
		public TESMagicCasterForm,         // 100
		public TESMagicTargetForm,         // 100
		public BGSDestructibleObjectForm,  // 0B8
		public BGSOpenCloseForm,           // 0C8
		public BGSKeywordForm,             // 0D0
		public BGSNativeTerminalForm       // 0F0
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectDOOR };
		static constexpr auto VTABLE{ VTABLE::TESObjectDOOR };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kDOOR };

		// members
		BGSLocalizedString altOpenText;      // 108
		BGSLocalizedString altCloseText;     // 110
		BGSSoundDescriptorForm* openSound;   // 118
		BGSSoundDescriptorForm* closeSound;  // 120
		BGSSoundDescriptorForm* loopSound;   // 128
		std::int8_t flags;                   // 130
		BSTArray<TESForm*> randomTeleports;  // 138
	};
	static_assert(sizeof(TESObjectDOOR) == 0x150);

	struct OBJ_LIGH
	{
	public:
		// members
		std::int32_t time;                // 00
		std::uint32_t radius;             // 04
		std::uint32_t color;              // 08
		std::uint32_t flags;              // 0C
		float fallOffExponent;            // 10
		float fov;                        // 14
		float nearDistance;               // 18
		float flickerPeriodRecip;         // 1C
		float flickerIntensityAmplitude;  // 20
		float flickerMovementAmplitude;   // 24
		float attenConstant;              // 28
		float attenScalar;                // 2C
		float attenExponent;              // 30
		float godrayNearClipDistance;     // 34
	};
	static_assert(sizeof(OBJ_LIGH) == 0x38);

	class __declspec(novtable) TESObjectLIGH :
		public TESBoundAnimObject,         // 000
		public BGSModelMaterialSwap,       // 068
		public TESIcon,                    // 0A8
		public BGSMessageIcon,             // 0B8
		public TESWeightForm,              // 0D0
		public TESValueForm,               // 0E0
		public BGSDestructibleObjectForm,  // 0F0
		public BGSEquipType,               // 100
		public BGSPropertySheet,           // 110
		public BGSOpenCloseForm,           // 120
		public BGSKeywordForm              // 128
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectLIGH };
		static constexpr auto VTABLE{ VTABLE::TESObjectLIGH };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLIGH };

		// members
		OBJ_LIGH data;                  // 148
		float fade;                     // 180
		BGSSoundDescriptorForm* sound;  // 188
		TESTexture goboTexture;         // 190
		NiColor emittanceColor;         // 1A0
		BGSLensFlare* lensFlare;        // 1B0
		BGSGodRays* godRays;            // 1B8
	};
	static_assert(sizeof(TESObjectLIGH) == 0x1C0);

	class __declspec(novtable) TESFlora :
		public TESObjectACTI,  // 000
		public TESProduceForm  // 148
	{
	public:
		static constexpr auto RTTI{ RTTI::TESFlora };
		static constexpr auto VTABLE{ VTABLE::TESFlora };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kFLOR };
	};
	static_assert(sizeof(TESFlora) == 0x168);

	struct WorkbenchData
	{
	public:
		enum class Type;

		// members
		stl::enumeration<Type, std::int8_t> type;  // 0
	};
	static_assert(sizeof(WorkbenchData) == 0x1);

	class BSFurnitureMarker
	{
	public:
		// members
		NiPoint3 position;                 // 00
		BGSKeyword* actorMustHaveKeyword;  // 10
		float heading;                     // 18
		std::uint32_t allowedAnimations;   // 1C
	};
	static_assert(sizeof(BSFurnitureMarker) == 0x20);

	class __declspec(novtable) TESFurniture :
		public TESObjectACTI  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::TESFurniture };
		static constexpr auto VTABLE{ VTABLE::TESFurniture };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kFURN };

		struct EntryPointData
		{
		public:
			// members
			std::uint32_t entryPoint;  // 0
			std::uint32_t flags;       // 4
		};
		static_assert(sizeof(EntryPointData) == 0x8);

		// members
		BSTArray<EntryPointData> entryPointDataArray;  // 148
		BGSAttachParentArray attachParents;            // 160
		WorkbenchData wbData;                          // 178
		std::uint32_t furnFlags;                       // 17C
		TESForm* associatedForm;                       // 180
		BSTArray<BSFurnitureMarker> markersArray;      // 188
	};
	static_assert(sizeof(TESFurniture) == 0x1A0);

	class __declspec(novtable) TESActorBase :
		public TESBoundAnimObject,         // 000
		public TESActorBaseData,           // 068
		public TESContainer,               // 0D0
		public TESSpellList,               // 0E8
		public TESAIForm,                  // 0F8
		public TESFullName,                // 120
		public ActorValueOwner,            // 130
		public BGSDestructibleObjectForm,  // 138
		public BGSSkinForm,                // 148
		public BGSKeywordForm,             // 158
		public BGSAttackDataForm,          // 178
		public BGSPerkRankArray,           // 188
		public BGSPropertySheet            // 1A0
	{
	public:
		static constexpr auto RTTI{ RTTI::TESActorBase };
		static constexpr auto VTABLE{ VTABLE::TESActorBase };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNONE };

		// add
		virtual bool GetHasPLSpecTex() const { return false; }        // 67
		virtual TESCombatStyle* GetCombatStyle() { return nullptr; }  // 68
		virtual void SetCombatStyle(TESCombatStyle*) { return; }      // 69
		virtual TESForm* GetAsForm() { return nullptr; }              // 6A
	};
	static_assert(sizeof(TESActorBase) == 0x1B0);

	struct NPC_DATA
	{
	public:
		// members
		std::int16_t autoCalcHealth;        // 0
		std::int16_t autoCalcActionPoints;  // 2
		std::uint16_t farDistance;          // 4
		std::int8_t gearedUpWeapons;        // 6
	};
	static_assert(sizeof(NPC_DATA) == 0x8);

	class CreatureSounds
	{
	public:
		// members
		BSTArray<CREATURE_SOUND> consciousLoops;  // 00
		bool stopLoopWhenUnconscious;             // 18
	};
	static_assert(sizeof(CreatureSounds) == 0x20);

	class __declspec(novtable) TESNPC :
		public TESActorBase,                     // 000
		public TESRaceForm,                      // 1B0
		public BGSOverridePackCollection,        // 1C0
		public BGSForcedLocRefType,              // 1F8
		public BGSNativeTerminalForm,            // 208
		public BSTEventSink<MenuOpenCloseEvent>  // 218
	{
	public:
		static constexpr auto RTTI{ RTTI::TESActorBase };
		static constexpr auto VTABLE{ VTABLE::TESActorBase };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNPC_ };

		struct HeadRelatedData
		{
		public:
			// members
			BGSColorForm* hairColor;        // 00
			BGSColorForm* facialHairColor;  // 08
			BGSTextureSet* faceDetails;     // 10
		};
		static_assert(sizeof(HeadRelatedData) == 0x18);

		[[nodiscard]] static BSTHashMap<const TESNPC*, BSTArray<BGSHeadPart*>>& GetAlternateHeadPartListMap()
		{
			REL::Relocation<BSTHashMap<const TESNPC*, BSTArray<BGSHeadPart*>>*> map{ REL::ID(1306546), -0x8 };
			return *map;
		}

		[[nodiscard]] std::span<BGSHeadPart*> GetHeadParts(bool a_alternate = true) const
		{
			if (a_alternate && UsingAlternateHeadPartList()) {
				auto& map = GetAlternateHeadPartListMap();
				const auto it = map.find(this);
				if (it != map.end()) {
					return { it->second.data(), it->second.size() };
				} else {
					return {};
				}
			} else {
				return { headParts, static_cast<std::size_t>(numHeadParts) };
			}
		}

		[[nodiscard]] TESNPC* GetRootFaceNPC() noexcept
		{
			return const_cast<TESNPC*>(static_cast<const TESNPC*>(this)->GetRootFaceNPC());
		}

		[[nodiscard]] const TESNPC* GetRootFaceNPC() const noexcept
		{
			auto root = this;
			while (root->faceNPC) {
				root = root->faceNPC;
			}
			return root;
		}

		[[nodiscard]] bool UsingAlternateHeadPartList() const;

		// members
		BGSAttachParentArray attachParents;  // 220
		NPC_DATA data;                       // 238
		TESClass* cl;                        // 240
		HeadRelatedData* headRelatedData;    // 248
		BGSListForm* giftFilter;             // 250
		TESCombatStyle* combatStyle;         // 258
		std::uint32_t fileOffset;            // 260
		TESRace* originalRace;               // 268
		TESNPC* faceNPC;                     // 270
		NiPoint3 morphWeight;                // 278
		float height;                        // 284
		float heightMax;                     // 288
		union
		{
			TESNPC* soundCreature;
			CreatureSounds* creatureSounds;
		};                                                                                      // 290
		BGSLocalizedString shortName;                                                           // 298
		TESObjectARMO* farSkin;                                                                 // 2A0
		TESFurniture* powerArmorFurn;                                                           // 2A8
		BGSOutfit* defOutfit;                                                                   // 2B0
		BGSOutfit* sleepOutfit;                                                                 // 2B8
		BGSListForm* defaultPackList;                                                           // 2C0
		TESFaction* crimeFaction;                                                               // 2C8
		BGSHeadPart** headParts;                                                                // 2D0
		BSTArray<float>* morphRegionSliderValues;                                               // 2D8
		BSTHashMap<std::uint32_t, BGSCharacterMorph::Transform>* facialBoneRegionSliderValues;  // 2E0
		std::int8_t numHeadParts;                                                               // 2E8
		std::int8_t soundLevel;                                                                 // 2E9
		std::int8_t bodyTintColorR;                                                             // 2EA
		std::int8_t bodyTintColorG;                                                             // 2EN
		std::int8_t bodyTintColorB;                                                             // 2EC
		std::int8_t bodyTintColorA;                                                             // 2ED
		BSTArray<BGSRelationship*>* relationships;                                              // 2F0
		BSTHashMap<std::uint32_t, float>* morphSliderValues;                                    // 2F8
		BGSCharacterTint::Entries* tintingData;                                                 // 300
	};
	static_assert(sizeof(TESNPC) == 0x308);

	class __declspec(novtable) TESLevCharacter :
		public TESBoundAnimObject,   // 00
		public TESLeveledList,       // 68
		public BGSModelMaterialSwap  // 98
	{
	public:
		static constexpr auto RTTI{ RTTI::TESLevCharacter };
		static constexpr auto VTABLE{ VTABLE::TESLevCharacter };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLVLN };
	};
	static_assert(sizeof(TESLevCharacter) == 0xD8);

	class __declspec(novtable) BGSTerminal :
		public TESFurniture  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSTerminal };
		static constexpr auto VTABLE{ VTABLE::BGSTerminal };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kTERM };

		class BodyTextItem
		{
		public:
			// members
			BGSLocalizedString itemText;  // 00
			TESCondition conditions;      // 08
		};
		static_assert(sizeof(BodyTextItem) == 0x10);

		class MenuItem
		{
		public:
			union USelectionResult
			{
				BGSTerminal* subMenu;
				BGSLocalizedString* displayText;
				TESTexture* displayImage;
				BGSNote* holotape;
			};
			static_assert(sizeof(USelectionResult) == 0x8);

			// members
			BGSLocalizedString itemText;       // 00
			BGSLocalizedString responseText;   // 08
			USelectionResult selectionResult;  // 10
			TESCondition conditions;           // 18
			std::uint16_t id;                  // 20
			std::int8_t flags;                 // 22
		};
		static_assert(sizeof(MenuItem) == 0x28);

		// members
		BSTArray<BodyTextItem> bodyTextItems;   // 1A0
		BSTArray<MenuItem> menuItems;           // 1B8
		BGSLocalizedString headerTextOverride;  // 1D0
		BGSLocalizedString welcomeText;         // 1D8
	};
	static_assert(sizeof(BGSTerminal) == 0x1E0);
}
