#pragma once

#include "RE/Bethesda/BGSCharacterMorph.h"
#include "RE/Bethesda/BGSCharacterTint.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/Movement.h"
#include "RE/Bethesda/TESCondition.h"
#include "RE/Bethesda/TESForms.h"
#include "RE/NetImmerse/NiPoint3.h"

namespace RE
{
	enum class BIPED_OBJECT;

	class BGSHeadPart;

	enum class RACE_SIZE
	{
		kSmall,
		kMedium,
		kLarge,
		kExtraLarge
	};

	struct RACE_DATA
	{
	public:
		// members
		float height[2];                                            // 000
		NiPoint3 weight[2];                                         // 008
		std::int32_t flags;                                         // 020
		float accelerate;                                           // 024
		float decelerate;                                           // 028
		stl::enumeration<RACE_SIZE, std::int32_t> raceSize;         // 02C
		stl::enumeration<BIPED_OBJECT, std::int32_t> headObject;    // 030
		stl::enumeration<BIPED_OBJECT, std::int32_t> hairObject;    // 034
		stl::enumeration<BIPED_OBJECT, std::int32_t> beardObject;   // 038
		float injuredHealthPercent;                                 // 03C
		stl::enumeration<BIPED_OBJECT, std::int32_t> shieldObject;  // 040
		stl::enumeration<BIPED_OBJECT, std::int32_t> bodyObject;    // 044
		float aimAngleTolerance;                                    // 048
		float flightRadius;                                         // 04C
		float angleAccelerate;                                      // 050
		float angleTolerance;                                       // 054
		std::uint32_t flags2;                                       // 058
		NiPoint3 mountOffset;                                       // 05C
		NiPoint3 dismountOffset;                                    // 068
		NiPoint3 mountCameraOffset;                                 // 074
		stl::enumeration<BIPED_OBJECT, std::int32_t> pipboyObject;  // 080
		std::int16_t xpValue;                                       // 084
		BGSExplosion* onCrippleExplosion;                           // 088
		BGSDebris* onCrippleGenericDebris;                          // 090
		BGSImpactDataSet* onCrippleImpactDataSet;                   // 098
		float onCrippleGenericDebrisScale;                          // 0A0
		std::int8_t onCrippleGenericDebrisCount;                    // 0A4
		std::int8_t onCrippleDecalCount;                            // 0A5
		BGSExplosion* dismemberExplosion;                           // 0A8
		BGSDebris* dismemberGenericDebris;                          // 0B0
		BGSImpactDataSet* dismemberImpactDataSet;                   // 0B8
		float dismemberGenericDebrisScale;                          // 0C0
		std::int8_t dismemberGenericDebrisCount;                    // 0C4
		std::int8_t dismemberDecalCount;                            // 0C5
		BGSExplosion* explosion;                                    // 0C8
		BGSDebris* explosionGenericDebris;                          // 0D0
		BGSImpactDataSet* explosionImpactDataSet;                   // 0D8
		float explosionGenericDebrisScale;                          // 0E0
		std::int8_t explosionGenericDebrisCount;                    // 0E4
		std::int8_t explosionDecalCount;                            // 0E5
		BGSExplosion* subsegmentExplosion;                          // 0E8
		float maxPitch;                                             // 0F0
		float maxRoll;                                              // 0F4
		float defaultHeadHeight;                                    // 0F8
	};
	static_assert(sizeof(RACE_DATA) == 0x100);

	struct EquipSlotData
	{
	public:
		// members
		BGSEquipSlot* equipSlot;      // 00
		BSFixedString equipSlotNode;  // 08
	};
	static_assert(sizeof(EquipSlotData) == 0x10);

	class __declspec(novtable) TESRace :
		public TESForm,             // 000
		public TESFullName,         // 020
		public TESDescription,      // 030
		public TESSpellList,        // 048
		public BGSSkinForm,         // 058
		public BGSBipedObjectForm,  // 068
		public BGSKeywordForm,      // 078
		public BGSAttackDataForm,   // 098
		public BGSPropertySheet,    // 0A8
		public BGSPreloadable       // 0B8
	{
	public:
		static constexpr auto RTTI{ RTTI::TESRace };
		static constexpr auto VTABLE{ VTABLE::TESRace };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kRACE };

		struct MOVEMENT_SPEED_OVERRIDE
		{
		public:
			// members
			BGSMovementType* moveType;         // 00
			Movement::MaxSpeeds overrideData;  // 08
		};
		static_assert(sizeof(MOVEMENT_SPEED_OVERRIDE) == 0x78);

		struct FaceRelatedData
		{
		public:
			// members
			BGSCharacterTint::Template::Groups* tintingTemplate;                //
			BSTArray<BGSTextureSet*>* faceDetailsTextureSets;                   //
			BGSTextureSet* defaultFaceDetailsTextureSet;                        //
			BSTArray<TESNPC*>* presetNPCs;                                      //
			BSTArray<BGSColorForm*>* availableHairColors;                       //
			BGSColorForm* defaultHairColor;                                     //
			BSTArray<BGSHeadPart*>* headParts;                                  //
			BSTArray<BGSCharacterMorph::Group*>* morphGroups;                   //
			BSTArray<BGSCharacterMorph::FacialBoneRegion*>* facialBoneRegions;  //
			BGSCharacterMorph::FacialBoneRegion* neckFatFacialBoneRegion;       //
			NiPoint3 neckFatAdjustmentScales;                                   //
			BSFixedString wrinkleMapPath;                                       //
		};
		static_assert(sizeof(FaceRelatedData) == 0x68);

		struct BodyMorphData
		{
		public:
			// members
			BSTHashMap<BSFixedString, BGSCharacterMorph::BoneBaseScales*> boneBaseScales;        // 00
			BSTHashMap<BSFixedString, BGSCharacterMorph::BONE_MODIFIER_MIN_MAX*> boneModifiers;  // 30
		};
		static_assert(sizeof(BodyMorphData) == 0x60);

		// members
		TESModel skeletonModel[2];                                           // 0C0
		TESModel skeletonChargenModel[2];                                    // 120
		RACE_DATA data;                                                      // 180
		float clampFaceGeoValue;                                             // 280
		float clampFaceGeoValue2;                                            // 284
		BGSTextureModel bodyTextureModels[2];                                // 288
		BGSBehaviorGraphModel behaviorGraph[2];                              // 2E8
		BSFixedString rootBehaviorGraphName[2];                              // 348
		BSFixedString behaviorGraphProjectName[2];                           // 358
		BGSVoiceType* defaultVoiceType[2];                                   // 368
		BGSBodyPartData* bodyPartData;                                       // 378
		BGSSoundTagComponent soundTagComponent;                              // 380
		BGSAttachParentArray attachParents;                                  // 388
		BSFixedString formEditorID;                                          // 3A0
		BGSMaterialType* bloodImpactMaterial;                                // 3A8
		BGSArtObject* dismemberBlood;                                        // 3B0
		BGSTextureSet* meatCapTextureSet;                                    // 3B8
		BGSTextureSet* meatCollarTextureSet;                                 // 3C0
		BGSSoundDescriptorForm* corpseOpenSound;                             // 3C8
		BGSSoundDescriptorForm* corpseCloseSound;                            // 3D0
		BSFixedString bipedObjectNames[32];                                  // 3D8
		ActorValueInfo* bipedObjectConditions[32];                           // 4D8
		BSTArray<EquipSlotData> equipSlotArray;                              // 5D8
		std::uint32_t validEquipTypes;                                       // 5F0
		TESObjectWEAP* unarmedWeapon;                                        // 5F8
		TESRace* morphRace;                                                  // 600
		TESRace* armorParentRace;                                            // 608
		TESQuest* dialogueQuest;                                             // 610
		BSTArray<MOVEMENT_SPEED_OVERRIDE> speedOverrides;                    // 618
		BSTArray<BSFixedString> phonemeTargets;                              // 630
		BSTHashMap<std::uint32_t, BGSCharacterMorph::Slider*> morphSliders;  // 648
		BGSMovementType* baseMoveTypes[4];                                   // 678
		FaceRelatedData* faceRelatedData[2];                                 // 698
		TESRace::BodyMorphData* bodyMorphData[2];                            // 6A8
		TESTexture hairColorLookupTexture;                                   // 6B8
		TESTexture hairColorLookupTextureExt;                                // 6C8
	};
	static_assert(sizeof(TESRace) == 0x6D8);
}
