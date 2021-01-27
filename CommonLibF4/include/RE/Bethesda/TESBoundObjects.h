#pragma once

#include "RE/Bethesda/BGSMod.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTList.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTTuple.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/TESCondition.h"
#include "RE/Bethesda/TESForms.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	enum class CHUNK_ID;
	enum class SOUND_LEVEL;
	enum class STAGGER_MAGNITUDE;
	enum class WEAPON_RUMBLE_PATTERN;
	enum class WEAPONHITBEHAVIOR;

	class BGSObjectInstanceExtra;
	class NiAVObject;

	struct BaseTreeData;

	class __declspec(novtable) TESObject :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObject };
		static constexpr auto VTABLE{ VTABLE::TESObject };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNONE };

		// add
		virtual bool IsBoundAnimObject() { return false; }                              // 4A
		virtual TESWaterForm* GetWaterType() const { return nullptr; }                  // 4B
		virtual bool IsAutoCalc() const { return false; }                               // 4C
		virtual void SetAutoCalc(bool) { return; }                                      // 4D
		virtual void Clone3D(TESObjectREFR*, NiPointer<NiAVObject>&, bool) { return; }  // 4E
		virtual void UnClone3D(TESObjectREFR* a_requester);                             // 4F
		virtual bool IsMarker();                                                        // 50
		virtual bool IsOcclusionMarker();                                               // 51
		virtual bool ReplaceModel();                                                    // 52
		virtual std::uint32_t IncRef() { return 0; }                                    // 53
		virtual std::uint32_t DecRef() { return 0; }                                    // 54
		virtual NiAVObject* LoadGraphics(TESObjectREFR* a_ref);                         // 55
	};
	static_assert(sizeof(TESObject) == 0x20);

	struct NiNPShortPoint3
	{
	public:
		// members
		std::int16_t x;  // 0
		std::int16_t y;  // 2
		std::int16_t z;  // 4
	};
	static_assert(sizeof(NiNPShortPoint3) == 0x6);

	class __declspec(novtable) TESBoundObject :
		public TESObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESBoundObject };
		static constexpr auto VTABLE{ VTABLE::TESBoundObject };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNONE };

		struct BOUND_DATA
		{
		public:
			// members
			NiNPShortPoint3 boundMin;  // 00
			NiNPShortPoint3 boundMax;  // 06
		};
		static_assert(sizeof(BOUND_DATA) == 0xC);

		// add
		virtual TBO_InstanceData* CreateInstanceData(const TBO_InstanceData*) const { return nullptr; }                                        // 56
		virtual const TBO_InstanceData* GetBaseInstanceData() const { return nullptr; }                                                        // 57
		virtual bool GetAttachedMarkersVisible(NiAVObject*) const { return false; }                                                            // 58
		virtual void SetAttachedMarkersVisible(NiAVObject*, bool) const { return; }                                                            // 59
		virtual bool QSupportsCountPerInstance() const { return false; }                                                                       // 5A
		virtual void SetObjectVoiceType(BGSVoiceType*) { return; }                                                                             // 5B
		virtual BGSVoiceType* GetObjectVoiceType() const { return nullptr; }                                                                   // 5C
		virtual BGSSoundDescriptorForm* GetSoundForTag(const BSFixedString& a_tag) const;                                                      // 5D
		virtual void Clone3D(TESObjectREFR* a_requester, NiPointer<NiAVObject>& a_obj3D) { TESObject::Clone3D(a_requester, a_obj3D, false); }  // 5E
		virtual bool ReplaceModel(const char* a_filename);                                                                                     // 5F
		virtual bool GetActivateText(TESObjectREFR* a_itemActivated, BSStringT<char>& a_resultString);                                         // 60
		virtual COMMAND_REFUSAL_TYPE CalculateDoFavor(Actor* a_actor, bool a_owned, TESObjectREFR*, float a_moralityMult) const;               // 61
		virtual void HandleRemoveItemFromContainer(TESObjectREFR*) { return; }                                                                 // 62
		virtual void OnRemove3D(NiAVObject*) { return; }                                                                                       // 63
		virtual void OnCheckModels() { return; }                                                                                               // 64
		virtual void OnCopyReference() { return; }                                                                                             // 65
		virtual void OnFinishScale() { return; }                                                                                               // 66

		void ApplyMods(BSTSmartPointer<TBO_InstanceData>& a_dest, const BGSObjectInstanceExtra* a_extra) const
		{
			using func_t = decltype(&TESBoundObject::ApplyMods);
			REL::Relocation<func_t> func{ REL::ID(113585) };
			return func(this, a_dest, a_extra);
		}

		// members
		BOUND_DATA boundData;                    // 20
		BGSMod::Template::Items objectTemplate;  // 30
		BGSPreviewTransform previewTransform;    // 50
		BGSSoundTagComponent soundTagComponent;  // 60
	};
	static_assert(sizeof(TESBoundObject) == 0x68);

	class __declspec(novtable) BGSComponent :
		public TESBoundObject,      // 00
		public TESFullName,         // 68
		public TESValueForm,        // 78
		public BGSCraftingUseSound  // 88
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSComponent };
		static constexpr auto VTABLE{ VTABLE::BGSComponent };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCMPO };

		// members
		TESObjectMISC* scrapItem;   // 98
		TESGlobal* modScrapScalar;  // 90
	};
	static_assert(sizeof(BGSComponent) == 0xA8);

	class __declspec(novtable) BGSAcousticSpace :
		public TESBoundObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSAcousticSpace };
		static constexpr auto VTABLE{ VTABLE::BGSAcousticSpace };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kASPC };

		// members
		BGSSoundDescriptorForm* loopingSound;  // 68
		TESRegion* soundRegion;                // 70
		BGSReverbParameters* reverbType;       // 78
		std::uint16_t weatherAttenMillibels;   // 80
		bool isInterior;                       // 82
	};
	static_assert(sizeof(BGSAcousticSpace) == 0x88);

	class __declspec(novtable) TESObjectARMO :
		public TESBoundObject,             // 000
		public TESFullName,                // 068
		public TESRaceForm,                // 078
		public TESEnchantableForm,         // 088
		public BGSDestructibleObjectForm,  // 0A0
		public BGSPickupPutdownSounds,     // 0B0
		public TESBipedModelForm,          // 0C8
		public BGSEquipType,               // 1D0
		public BGSBipedObjectForm,         // 1E0
		public BGSBlockBashData,           // 1F0
		public BGSKeywordForm,             // 208
		public TESDescription,             // 228
		public BGSInstanceNamingRulesForm  // 240
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectARMO };
		static constexpr auto VTABLE{ VTABLE::TESObjectARMO };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kARMO };

		struct __declspec(novtable) InstanceData :
			public TBO_InstanceData  // 00
		{
		public:
			static constexpr auto RTTI{ RTTI::TESObjectARMO__InstanceData };
			static constexpr auto VTABLE{ VTABLE::TESObjectARMO__InstanceData };

			// members
			BSTArray<EnchantmentItem*>* enchantments;                                     // 10
			BSTArray<BGSMaterialSwap*>* materialSwaps;                                    // 18
			BGSBlockBashData* blockBashData;                                              // 20
			BGSKeywordForm* keywords;                                                     // 28
			BSTArray<BSTTuple<TESForm*, BGSTypedFormValuePair::SharedVal>>* damageTypes;  // 30
			BSTArray<BSTTuple<TESForm*, BGSTypedFormValuePair::SharedVal>>* actorValues;  // 38
			float weight;                                                                 // 40
			float colorRemappingIndex;                                                    // 44
			std::uint32_t value;                                                          // 48
			std::uint32_t health;                                                         // 4C
			stl::enumeration<STAGGER_MAGNITUDE, std::int32_t> staggerRating;              // 50
			std::uint16_t rating;                                                         // 54
			std::uint16_t index;                                                          // 56
		};
		static_assert(sizeof(InstanceData) == 0x58);

		class ArmorAddon
		{
		public:
			// members
			std::uint16_t index;        // 00
			TESObjectARMA* armorAddon;  // 08
		};
		static_assert(sizeof(ArmorAddon) == 0x10);

		// members
		InstanceData data;                   // 250
		BSTArray<ArmorAddon> modelArray;     // 2A8
		TESObjectARMO* armorTemplate;        // 2C0
		BGSAttachParentArray attachParents;  // 2C8
	};
	static_assert(sizeof(TESObjectARMO) == 0x2E0);

	struct OBJ_BOOK
	{
	public:
		union Teaches
		{
			ActorValueInfo* actorValueToAdvance;
			SpellItem* spell;
			BGSPerk* perk;
		};
		static_assert(sizeof(Teaches) == 0x8);

		// members
		std::int8_t flags;          // 00
		Teaches teaches;            // 08
		std::uint32_t textOffsetX;  // 10
		std::uint32_t textOffsetY;  // 14
	};
	static_assert(sizeof(OBJ_BOOK) == 0x18);

	class __declspec(novtable) TESObjectBOOK :
		public TESBoundObject,             // 000
		public TESFullName,                // 068
		public BGSModelMaterialSwap,       // 078
		public TESIcon,                    // 0B8
		public TESValueForm,               // 0C8
		public TESWeightForm,              // 0D8
		public TESDescription,             // 0E8
		public BGSDestructibleObjectForm,  // 100
		public BGSMessageIcon,             // 110
		public BGSPickupPutdownSounds,     // 128
		public BGSKeywordForm,             // 140
		public BGSFeaturedItemMessage      // 160
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectBOOK };
		static constexpr auto VTABLE{ VTABLE::TESObjectBOOK };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kBOOK };

		// members
		OBJ_BOOK data;                       // 170
		TESObjectSTAT* inventoryModel;       // 188
		TESDescription itemCardDescription;  // 190
	};
	static_assert(sizeof(TESObjectBOOK) == 0x1A8);

	class __declspec(novtable) TESObjectMISC :
		public TESBoundObject,             // 000
		public TESFullName,                // 068
		public BGSModelMaterialSwap,       // 078
		public TESIcon,                    // 0B8
		public TESValueForm,               // 0C8
		public TESWeightForm,              // 0D8
		public BGSDestructibleObjectForm,  // 0E8
		public BGSMessageIcon,             // 0F8
		public BGSPickupPutdownSounds,     // 110
		public BGSKeywordForm,             // 128
		public BGSFeaturedItemMessage      // 148
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectMISC };
		static constexpr auto VTABLE{ VTABLE::TESObjectMISC };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kMISC };

		// add
		virtual void SaveImpl() { return; }                    // 67
		virtual void LoadImpl(TESFile*, CHUNK_ID) { return; }  // 68

		// members
		BSTArray<BSTTuple<TESForm*, BGSTypedFormValuePair::SharedVal>>* componentData;  // 158
		std::int8_t* displayIndices;                                                    // 160
	};
	static_assert(sizeof(TESObjectMISC) == 0x168);

	struct TESObjectSTATData
	{
	public:
		// members
		BGSMaterialObject* materialObj;  // 00
		float materialThresholdAngle;    // 08
		float leafAmplitude;             // 0C
		float leafFrequency;             // 10
	};
	static_assert(sizeof(TESObjectSTATData) == 0x18);

	class __declspec(novtable) TESObjectSTAT :
		public TESBoundObject,        // 00
		public BGSModelMaterialSwap,  // 68
		public BGSPropertySheet,      // A8
		public BGSForcedLocRefType,   // B8
		public BGSNavmeshableObject   // C8
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectSTAT };
		static constexpr auto VTABLE{ VTABLE::TESObjectSTAT };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSTAT };

		// members
		TESObjectSTATData data;  // D0
	};
	static_assert(sizeof(TESObjectSTAT) == 0xE8);

	class __declspec(novtable) BGSStaticCollection :
		public TESBoundObject,       // 00
		public BGSModelMaterialSwap  // 68
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSStaticCollection };
		static constexpr auto VTABLE{ VTABLE::BGSStaticCollection };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSCOL };

		struct REF_COL_DATA
		{
		public:
			// members
			NiPoint3 location;  // 00
			NiPoint3 angle;     // 0C
			float scale;        // 18
		};
		static_assert(sizeof(REF_COL_DATA) == 0x1C);

		// members
		BSTHashMap<TESBoundObject*, BSSimpleList<BGSStaticCollection::REF_COL_DATA>*>* dataMap;  // A8
	};
	static_assert(sizeof(BGSStaticCollection) == 0xB0);

	struct MOVABLE_STATIC_DATA
	{
	public:
		// members
		std::int8_t flags;  // 0
	};
	static_assert(sizeof(MOVABLE_STATIC_DATA) == 0x1);

	class __declspec(novtable) BGSMovableStatic :
		public TESObjectSTAT,              // 000
		public BGSDestructibleObjectForm,  // 0E8
		public BGSKeywordForm              // 0F8
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSMovableStatic };
		static constexpr auto VTABLE{ VTABLE::BGSMovableStatic };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kMSTT };

		// members
		BGSSoundDescriptorForm* soundLoop;  // 118
		MOVABLE_STATIC_DATA data;           // 120
	};
	static_assert(sizeof(BGSMovableStatic) == 0x128);

	class __declspec(novtable) TESGrass :
		public TESBoundObject,  // 00
		public TESModel         // 68
	{
	public:
		static constexpr auto RTTI{ RTTI::TESGrass };
		static constexpr auto VTABLE{ VTABLE::TESGrass };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kGRAS };

		enum class GRASS_WATER_STATE;

		struct GRASS_DATA
		{
		public:
			// members
			std::int8_t density;                                           // 00
			std::int8_t minSlopeDegrees;                                   // 01
			std::int8_t maxSlopeDegrees;                                   // 02
			std::uint16_t distanceFromWaterLevel;                          // 04
			stl::enumeration<GRASS_WATER_STATE, std::int32_t> underwater;  // 08
			float positionRange;                                           // 0C
			float heightRange;                                             // 10
			float colorRange;                                              // 14
			float wavePeriod;                                              // 18
			std::int8_t flags;                                             // 1C
		};
		static_assert(sizeof(GRASS_DATA) == 0x20);

		// add
		virtual std::int8_t GetDensity() const { return data.density; }                                                                                   // 67
		virtual bool SetDensity(std::int8_t a_density);                                                                                                   // 68
		virtual std::int8_t GetMinSlopeDegrees() const { return data.minSlopeDegrees; }                                                                   // 69
		virtual bool SetMinSlopeDegrees(std::int8_t a_minSlopeDegrees);                                                                                   // 6A
		virtual std::int8_t GetMaxSlopeDegrees() const { return data.maxSlopeDegrees; }                                                                   // 6B
		virtual bool SetMaxSlopeDegrees(std::int8_t a_maxSlopeDegrees);                                                                                   // 6C
		virtual float GetMinSlope() const;                                                                                                                // 6D
		virtual float GetMaxSlope() const;                                                                                                                // 6E
		virtual std::uint16_t GetDistanceFromWaterLevel() const { return data.distanceFromWaterLevel; }                                                   // 6F
		virtual void SetDistanceFromWaterLevel(const std::uint16_t a_distanceFromWaterLevel) { data.distanceFromWaterLevel = a_distanceFromWaterLevel; }  // 70
		virtual GRASS_WATER_STATE GetUnderwaterState() const { return *data.underwater; }                                                                 // 71
		virtual void SetUnderwaterState(const GRASS_WATER_STATE a_underwater) { data.underwater = a_underwater; }                                         // 72
		virtual float GetPositionRange() const { return data.positionRange; }                                                                             // 73
		virtual bool SetPositionRange(float a_range);                                                                                                     // 74
		virtual float GetHeightRange() const { return data.heightRange; }                                                                                 // 75
		virtual bool SetHeightRange(float a_range);                                                                                                       // 76
		virtual float GetColorRange() const { return data.colorRange; }                                                                                   // 77
		virtual bool SetColorRange(float a_range);                                                                                                        // 78
		virtual float GetWavePeriod() const { return data.wavePeriod; }                                                                                   // 79
		virtual bool SetWavePeriod(float a_period);                                                                                                       // 7A
		virtual bool GetVertexLighting() const;                                                                                                           // 7B
		virtual void SetVertexLighting(bool a_flag);                                                                                                      // 7C
		virtual bool GetUniformScaling() const;                                                                                                           // 7D
		virtual void SetUniformScaling(bool a_flag);                                                                                                      // 7E
		virtual bool GetFitToSlope() const;                                                                                                               // 7F
		virtual void SetFitToSlope(bool a_flag) const;                                                                                                    // 80

		// members
		GRASS_DATA data;  // 98
	};
	static_assert(sizeof(TESGrass) == 0xB8);

	struct OBJ_TREE
	{
	public:
		// members
		float trunkFlexibility;   // 00
		float branchFlexibility;  // 04
		float trunkAmplitude;     // 08
		float frontAmplitude;     // 0C
		float backAmplitude;      // 10
		float sideAmplitude;      // 14
		float frontFrequency;     // 18
		float backFrequency;      // 1C
		float sideFrequency;      // 20
		float leafFlexibility;    // 24
		float leafAmplitude;      // 28
		float leafFrequency;      // 2C
	};
	static_assert(sizeof(OBJ_TREE) == 0x30);

	class __declspec(novtable) TESObjectTREE :
		public TESBoundObject,        // 000
		public BGSModelMaterialSwap,  // 068
		public TESFullName,           // 0A8
		public TESProduceForm         // 0B8
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectTREE };
		static constexpr auto VTABLE{ VTABLE::TESObjectTREE };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kTREE };

		enum class etTreeType;

		// members
		OBJ_TREE data;                                    // 0D8
		BaseTreeData* baseData;                           // 108
		stl::enumeration<etTreeType, std::int32_t> type;  // 110
	};
	static_assert(sizeof(TESObjectTREE) == 0x118);

	class __declspec(novtable) TESObjectWEAP :
		public TESBoundObject,             // 000
		public TESFullName,                // 068
		public BGSModelMaterialSwap,       // 078
		public TESIcon,                    // 0B8
		public TESEnchantableForm,         // 0C8
		public BGSDestructibleObjectForm,  // 0E0
		public BGSEquipType,               // 0F0
		public BGSPreloadable,             // 100
		public BGSMessageIcon,             // 108
		public BGSPickupPutdownSounds,     // 120
		public BGSBlockBashData,           // 138
		public BGSKeywordForm,             // 150
		public TESDescription,             // 170
		public BGSInstanceNamingRulesForm  // 188
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectWEAP };
		static constexpr auto VTABLE{ VTABLE::TESObjectWEAP };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kWEAP };

		struct RangedData
		{
		public:
			// members
			BGSProjectile* overrideProjectile;                                    // 00
			float fireSeconds;                                                    // 08
			float firingRumbleLeftMotorStrength;                                  // 0C
			float firingRumbleRightMotorStrength;                                 // 10
			float firingRumbleDuration;                                           // 14
			float reloadSeconds;                                                  // 18
			float boltChargeSeconds;                                              // 1C
			float sightedTransitionSeconds;                                       // 20
			std::uint32_t rumblePeriod;                                           // 24
			stl::enumeration<WEAPON_RUMBLE_PATTERN, std::int32_t> rumblePattern;  // 28
			std::int8_t numProjectiles;                                           // 2C
		};
		static_assert(sizeof(RangedData) == 0x30);

		struct __declspec(novtable) InstanceData :
			public TBO_InstanceData  // 000
		{
		public:
			static constexpr auto RTTI{ RTTI::TESObjectWEAP__InstanceData };
			static constexpr auto VTABLE{ VTABLE::TESObjectWEAP__InstanceData };

			// members
			BGSSoundDescriptorForm* attackSound;                                          // 010
			BGSSoundDescriptorForm* attackSound2D;                                        // 018
			BGSSoundDescriptorForm* attackLoop;                                           // 020
			BGSSoundDescriptorForm* attackFailSound;                                      // 028
			BGSSoundDescriptorForm* idleSound;                                            // 030
			BGSSoundDescriptorForm* equipSound;                                           // 038
			BGSSoundDescriptorForm* unEquipSound;                                         // 040
			BGSSoundDescriptorForm* fastEquipSound;                                       // 048
			BGSBlockBashData* blockBashData;                                              // 050
			BGSImpactDataSet* impactDataSet;                                              // 058
			TESLevItem* npcAddAmmoList;                                                   // 060
			TESAmmo* ammo;                                                                // 068
			BGSEquipSlot* equipSlot;                                                      // 070
			SpellItem* effect;                                                            // 078
			BGSKeywordForm* keywords;                                                     // 080
			BGSAimModel* aimModel;                                                        // 088
			BGSZoomData* zoomData;                                                        // 090
			RangedData* rangedData;                                                       // 098
			BSTArray<EnchantmentItem*>* enchantments;                                     // 0A0
			BSTArray<BGSMaterialSwap*>* materialSwaps;                                    // 0A8
			BSTArray<BSTTuple<TESForm*, BGSTypedFormValuePair::SharedVal>>* damageTypes;  // 0B0
			BSTArray<BSTTuple<TESForm*, BGSTypedFormValuePair::SharedVal>>* actorValues;  // 0B8
			float attackSeconds;                                                          // 0C0
			float reloadSpeed;                                                            // 0C4
			float speed;                                                                  // 0C8
			float reach;                                                                  // 0CC
			float minRange;                                                               // 0D0
			float maxRange;                                                               // 0D4
			float attackDelaySec;                                                         // 0D8
			float damageToWeaponMult;                                                     // 0DC
			float outOfRangeDamageMult;                                                   // 0E0
			float secondaryDamage;                                                        // 0E4
			float criticalChargeBonus;                                                    // 0E8
			float weight;                                                                 // 0EC
			float soundLevelMult;                                                         // 0F0
			float attackActionPointCost;                                                  // 0F4
			float fullPowerSeconds;                                                       // 0F8
			float minPowerPerShot;                                                        // 0FC
			float colorRemappingIndex;                                                    // 100
			float criticalDamageMult;                                                     // 104
			stl::enumeration<STAGGER_MAGNITUDE, std::int32_t> staggerValue;               // 108
			std::uint32_t value;                                                          // 10C
			std::uint32_t flags;                                                          // 110
			stl::enumeration<SOUND_LEVEL, std::int32_t> soundLevel;                       // 114
			stl::enumeration<WEAPONHITBEHAVIOR, std::int32_t> hitBehavior;                // 118
			ActorValueInfo* skill;                                                        // 120
			ActorValueInfo* resistance;                                                   // 128
			std::uint16_t ammoCapacity;                                                   // 130
			std::uint16_t attackDamage;                                                   // 132
			std::uint16_t rank;                                                           // 134
			std::int8_t accuracyBonus;                                                    // 136
			std::int8_t type;                                                             // 137
		};
		static_assert(sizeof(InstanceData) == 0x138);

		struct __declspec(novtable) Data :
			public InstanceData  // 000
		{
		public:
			static constexpr auto RTTI{ RTTI::TESObjectWEAP__Data };
			static constexpr auto VTABLE{ VTABLE::TESObjectWEAP__Data };
		};
		static_assert(sizeof(Data) == 0x138);

		// members
		TESObjectWEAP::Data weaponData;              // 198
		BGSModelMaterialSwap* firstPersonModel;      // 2D0
		TESObjectWEAP* weaponTemplate;               // 2D8
		BGSMod::Attachment::Mod* embeddedWeaponMod;  // 2E0
		BGSAttachParentArray attachParents;          // 2E8
	};
	static_assert(sizeof(TESObjectWEAP) == 0x300);

	struct AMMO_DATA
	{
	public:
		// members
		BGSProjectile* projectile;  // 00
		std::uint32_t health;       // 08
		std::int8_t flags;          // 0C
		float damage;               // 10
	};
	static_assert(sizeof(AMMO_DATA) == 0x18);

	class __declspec(novtable) TESAmmo :
		public TESBoundObject,             // 000
		public TESFullName,                // 068
		public BGSModelMaterialSwap,       // 078
		public TESIcon,                    // 0B8
		public BGSMessageIcon,             // 0C8
		public TESValueForm,               // 0E0
		public BGSDestructibleObjectForm,  // 0F0
		public BGSPickupPutdownSounds,     // 100
		public TESDescription,             // 118
		public BGSKeywordForm,             // 130
		public TESWeightForm               // 150
	{
	public:
		static constexpr auto RTTI{ RTTI::TESAmmo };
		static constexpr auto VTABLE{ VTABLE::TESAmmo };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kAMMO };

		// members
		AMMO_DATA data;                // 160
		BGSLocalizedString shortDesc;  // 178
		TESModel shellCasing;          // 180
	};
	static_assert(sizeof(TESAmmo) == 0x1B0);

	class __declspec(novtable) TESKey :
		public TESObjectMISC  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::TESKey };
		static constexpr auto VTABLE{ VTABLE::TESKey };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kKEYM };
	};
	static_assert(sizeof(TESKey) == 0x168);

	class __declspec(novtable) BGSIdleMarker :
		public TESBoundObject,    // 00
		public BGSKeywordForm,    // 68
		public TESModel,          // 88
		public BGSIdleCollection  // B8
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSIdleMarker };
		static constexpr auto VTABLE{ VTABLE::BGSIdleMarker };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kIDLM };

		// members
		BGSKeyword* animArchType;  // D8
		BGSKeyword* flavorAnim;    // E0
	};
	static_assert(sizeof(BGSIdleMarker) == 0xE8);

	class __declspec(novtable) BGSNote :
		public TESBoundObject,         // 000
		public TESWeightForm,          // 068
		public TESValueForm,           // 078
		public TESModel,               // 088
		public TESFullName,            // 0B8
		public TESIcon,                // 0C8
		public BGSPickupPutdownSounds  // 0D8
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSNote };
		static constexpr auto VTABLE{ VTABLE::BGSNote };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNOTE };

		// members
		BSFixedString programFile;  // 0F0
		union
		{
			BGSSoundDescriptorForm* noteSound;
			std::size_t noteFormID;
		};                 // 0F8
		std::int8_t type;  // 100
		bool hasBeenRead;  // 101
	};
	static_assert(sizeof(BGSNote) == 0x108);

	struct BGSProjectileData
	{
	public:
		// members
		std::uint32_t flags;                      // 00
		float gravity;                            // 04
		float speed;                              // 08
		float range;                              // 0C
		TESObjectLIGH* light;                     // 10
		TESObjectLIGH* muzzleFlashLight;          // 18
		float explosionProximity;                 // 20
		float explosionTimer;                     // 24
		BGSExplosion* explosionType;              // 28
		BGSSoundDescriptorForm* activeSoundLoop;  // 30
		float muzzleFlashDuration;                // 38
		float fadeOutTime;                        // 3C
		float force;                              // 40
		BGSSoundDescriptorForm* countdownSound;   // 48
		BGSSoundDescriptorForm* deactivateSound;  // 50
		TESObjectWEAP* defaultWeaponSource;       // 58
		float coneSpread;                         // 60
		float collisionRadius;                    // 64
		float lifetime;                           // 68
		float relaunchInterval;                   // 6C
		BGSTextureSet* decalData;                 // 70
		BGSCollisionLayer* collisionLayer;        // 78
		BGSProjectile* vatsProjectile;            // 80
		std::int8_t tracerFrequency;              // 88
	};
	static_assert(sizeof(BGSProjectileData) == 0x90);

	class __declspec(novtable) BGSProjectile :
		public TESBoundObject,            // 000
		public TESFullName,               // 068
		public TESModel,                  // 078
		public BGSPreloadable,            // 0A8
		public BGSDestructibleObjectForm  // 0B0
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSProjectile };
		static constexpr auto VTABLE{ VTABLE::BGSProjectile };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kPROJ };

		// members
		BGSProjectileData data;                                  // 0C0
		TESModel muzzleFlashModel;                               // 150
		stl::enumeration<SOUND_LEVEL, std::int32_t> soundLevel;  // 180
	};
	static_assert(sizeof(BGSProjectile) == 0x188);

	struct BGSHazardData
	{
	public:
		// members
		std::uint32_t limit;              // 00
		float radius;                     // 04
		float lifetime;                   // 08
		float imageSpaceRadius;           // 0C
		float targetInterval;             // 10
		std::uint32_t flags;              // 14
		MagicItem* spell;                 // 18
		TESObjectLIGH* light;             // 20
		BGSImpactDataSet* impactDataSet;  // 28
		BGSSoundDescriptorForm* sound;    // 30
		float fullEffectRadius;           // 38
		float taperWeight;                // 3C
		float taperCurve;                 // 40
	};
	static_assert(sizeof(BGSHazardData) == 0x48);

	class __declspec(novtable) BGSHazard :
		public TESBoundObject,              // 000
		public TESFullName,                 // 068
		public TESModel,                    // 078
		public BGSPreloadable,              // 0A8
		public TESImageSpaceModifiableForm  // 0B0
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSHazard };
		static constexpr auto VTABLE{ VTABLE::BGSHazard };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kHAZD };

		// members
		BGSHazardData data;  // 0C0
	};
	static_assert(sizeof(BGSHazard) == 0x108);

	class __declspec(novtable) BGSBendableSpline :
		public TESBoundObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSBendableSpline };
		static constexpr auto VTABLE{ VTABLE::BGSBendableSpline };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kBNDS };

		struct SplineData_Untilv130
		{
		public:
			// members
			float numTiles;           // 00
			std::uint16_t numSlices;  // 04
			std::uint16_t flags;      // 06
			NiColor color;            // 08
		};
		static_assert(sizeof(SplineData_Untilv130) == 0x14);

		struct SplineData :
			public SplineData_Untilv130  // 00
		{
		public:
			// members
			float windSensibility;  // 14
			float flexibility;      // 18
		};
		static_assert(sizeof(SplineData) == 0x1C);

		// members
		SplineData data;            // 68
		BGSTextureSet* textureSet;  // 88
	};
	static_assert(sizeof(BGSBendableSpline) == 0x90);

	class __declspec(novtable) TESSoulGem :
		public TESObjectMISC  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::TESSoulGem };
		static constexpr auto VTABLE{ VTABLE::TESSoulGem };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSLGM };

		// members
		TESSoulGem* linkedSoulGem;  // 168
		std::int8_t currentSoul;    // 170
		std::int8_t soulCapacity;   // 171
	};
	static_assert(sizeof(TESSoulGem) == 0x178);

	class __declspec(novtable) TESLevItem :
		public TESBoundObject,  // 00
		public TESLeveledList   // 68
	{
	public:
		static constexpr auto RTTI{ RTTI::TESLevItem };
		static constexpr auto VTABLE{ VTABLE::TESLevItem };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLVLI };
	};
	static_assert(sizeof(TESLevItem) == 0x98);

	class __declspec(novtable) TESLevSpell :
		public TESBoundObject,  // 00
		public TESLeveledList   // 68
	{
	public:
		static constexpr auto RTTI{ RTTI::TESLevSpell };
		static constexpr auto VTABLE{ VTABLE::TESLevSpell };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLVSP };
	};
	static_assert(sizeof(TESLevSpell) == 0x98);

	struct BGSExplosionData
	{
	public:
		// members
		TESObjectLIGH* light;                                                // 00
		BGSSoundDescriptorForm* sound1;                                      // 08
		BGSSoundDescriptorForm* sound2;                                      // 10
		BGSImpactDataSet* impactDataSet;                                     // 18
		TESBoundObject* impactPlacedObject;                                  // 20
		BGSProjectile* spawnProjectile;                                      // 28
		NiPoint3 projectileVector;                                           // 30
		float projectileSpread;                                              // 3C
		std::uint32_t projectileCount;                                       // 40
		float force;                                                         // 44
		float damage;                                                        // 48
		float innerRadius;                                                   // 4C
		float outerRadius;                                                   // 50
		float imageSpaceRadius;                                              // 54
		float verticalOffsetMult;                                            // 58
		std::uint32_t flags;                                                 // 5C
		stl::enumeration<SOUND_LEVEL, std::int32_t> soundLevel;              // 60
		float placedObjectFadeDelay;                                         // 64
		stl::enumeration<STAGGER_MAGNITUDE, std::int32_t> staggerMagnitude;  // 68
	};
	static_assert(sizeof(BGSExplosionData) == 0x70);

	class __declspec(novtable) BGSExplosion :
		public TESBoundObject,              // 000
		public TESFullName,                 // 068
		public TESModel,                    // 078
		public TESEnchantableForm,          // 0A8
		public BGSPreloadable,              // 0C0
		public TESImageSpaceModifiableForm  // 0C8
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSExplosion };
		static constexpr auto VTABLE{ VTABLE::BGSExplosion };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kEXPL };

		// members
		BGSExplosionData data;  // 0D8
	};
	static_assert(sizeof(BGSExplosion) == 0x148);

	struct ADDON_DATA
	{
	public:
		// members
		std::uint16_t masterParticleCap;  // 0
		std::int8_t flags;                // 2
	};
	static_assert(sizeof(ADDON_DATA) == 0x4);

	class __declspec(novtable) BGSAddonNode :
		public TESBoundObject,       // 00
		public BGSModelMaterialSwap  // 68
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSAddonNode };
		static constexpr auto VTABLE{ VTABLE::BGSAddonNode };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kADDN };

		// members
		std::uint32_t index;                        // A8
		BGSSoundDescriptorForm* sound;              // B0
		TESObjectLIGH* light;                       // B8
		ADDON_DATA data;                            // C0
		BSNonReentrantSpinLock masterParticleLock;  // C4
	};
	static_assert(sizeof(BGSAddonNode) == 0xC8);

	struct OBJ_ARMA
	{
	public:
		// members
		std::int8_t priorities[2];  // 0
		std::int8_t modelRange[2];  // 2
		std::int8_t unused[2];      // 4
		std::int8_t soundValue;     // 6
		float weaponAdjust;         // 8
	};
	static_assert(sizeof(OBJ_ARMA) == 0xC);

	class __declspec(novtable) TESObjectARMA :
		public TESObject,          // 000
		public TESRaceForm,        // 020
		public BGSBipedObjectForm  // 030
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectARMA };
		static constexpr auto VTABLE{ VTABLE::TESObjectARMA };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kARMA };

		// members
		OBJ_ARMA data;                                           // 040
		BGSModelMaterialSwap bipedModel[2];                      // 050
		BGSModelMaterialSwap bipedModelFacebones[2];             // 0D0
		BGSModelMaterialSwap bipedModel1stPerson[2];             // 150
		BGSTextureSet* skinTextures[2];                          // 1D0
		BGSListForm* skinTextureSwapLists[2];                    // 1E0
		BSTArray<TESRace*> additionalRaces;                      // 1F0
		BGSFootstepSet* footstepSet;                             // 208
		BGSArtObject* artObject;                                 // 210
		BSTHashMap<BSFixedString, NiPoint3>* scaleModifiers[2];  // 218
	};
	static_assert(sizeof(TESObjectARMA) == 0x228);

	class __declspec(novtable) BGSArtObject :
		public TESBoundObject,       // 00
		public BGSKeywordForm,       // 68
		public BGSModelMaterialSwap  // 88
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSArtObject };
		static constexpr auto VTABLE{ VTABLE::BGSArtObject };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kARTO };

		enum class ArtType;

		struct Data
		{
		public:
			// members
			stl::enumeration<ArtType, std::int32_t> artType;  // 0
		};
		static_assert(sizeof(Data) == 0x4);

		// members
		Data data;  // C8
	};
	static_assert(sizeof(BGSArtObject) == 0xD0);

	struct BGSDualCastDataDEF
	{
	public:
		// members
		BGSProjectile* projectile;        // 00
		BGSExplosion* explosion;          // 08
		TESEffectShader* effectShader;    // 10
		BGSArtObject* hitEffectArt;       // 18
		BGSImpactDataSet* impactDataSet;  // 20
		std::uint32_t flags;              // 28
	};
	static_assert(sizeof(BGSDualCastDataDEF) == 0x30);

	class __declspec(novtable) BGSDualCastData :
		public TESBoundObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSDualCastData };
		static constexpr auto VTABLE{ VTABLE::BGSDualCastData };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kDUAL };

		// members
		BGSDualCastDataDEF data;  // 68
	};
	static_assert(sizeof(BGSDualCastData) == 0x98);
}
