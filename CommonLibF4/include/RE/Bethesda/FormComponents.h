#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTList.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTTuple.h"
#include "RE/Bethesda/MemoryManager.h"
#include "RE/NetImmerse/NiRefObject.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class BaseFormComponent;
	class TESTexture;
	class TESIcon;
	class BGSAttachParentArray;
	class BGSAttackDataForm;
	class BGSBipedObjectForm;
	class BGSBlockBashData;
	class BGSCraftingUseSound;
	class BGSDestructibleObjectForm;
	class BGSEquipType;
	class BGSFeaturedItemMessage;
	class BGSForcedLocRefType;
	class BGSIdleCollection;
	class BGSInstanceNamingRulesForm;
	class BGSKeywordForm;
	class BGSMenuDisplayObject;
	class BGSMessageIcon;
	class BGSNativeTerminalForm;
	class BGSOverridePackCollection;
	class BGSPerkRankArray;
	class BGSPickupPutdownSounds;
	class BGSPreloadable;
	class BGSPreviewTransform;
	class BGSPropertySheet;
	class BGSSkinForm;
	class BGSSoundTagComponent;
	class TESContainer;
	class TESDescription;
	class TESEnchantableForm;
	class TESFullName;
	class TESModel;
	class BGSBehaviorGraphModel;
	class BGSModelMaterialSwap;
	class BGSTextureModel;
	class TESModelRDT;
	class TESActorBaseData;
	class TESAIForm;
	class TESBipedModelForm;
	class TESImageSpaceModifiableForm;
	class TESLeveledList;
	class TESModelTri;
	class TESProduceForm;
	class TESRaceForm;
	class TESReactionForm;
	class TESSpellList;
	class TESTexture1024;
	class TESValueForm;
	class TESWeightForm;

	namespace BGSMod
	{
		namespace Template
		{
			class Item;
			class Items;
		}
	}

	enum class ACTOR_VALUE_MODIFIER;
	enum class ENUM_FORM_ID;
	enum class IO_TASK_PRIORITY;

	class ActorValueInfo;
	class ActorValueOwner;
	class BGSDebris;
	class BGSEquipSlot;
	class BGSExplosion;
	class BGSImpactDataSet;
	class BGSInstanceNamingRules;
	class BGSKeyword;
	class BGSListForm;
	class BGSLocationRefType;
	class BGSMaterialSwap;
	class BGSMaterialType;
	class BGSMessage;
	class BGSPerk;
	class BGSSoundDescriptorForm;
	class BGSTerminal;
	class BGSTransform;
	class BGSVoiceType;
	class EnchantmentItem;
	class NavMesh;
	class NiAVObject;
	class QueuedFile;
	class SpellItem;
	class TBO_InstanceData;
	class TESActorBase;
	class TESBoundObject;
	class TESFaction;
	class TESForm;
	class TESGlobal;
	class TESIdleForm;
	class TESImageSpaceModifier;
	class TESLevItem;
	class TESLevSpell;
	class TESObjectARMO;
	class TESObjectCELL;
	class TESObjectREFR;
	class TESPackage;
	class TESRace;
	class TESShout;

	namespace BSResource
	{
		struct ID;
	}

	namespace MagicSystem
	{
		enum class CastingType;
	}

	namespace BGSTypedFormValuePair
	{
		union SharedVal
		{
			std::uint32_t i;
			float f;
		};
		static_assert(sizeof(SharedVal) == 0x4);
	}

	class ActorValueOwner
	{
	public:
		static constexpr auto RTTI{ RTTI_ActorValueOwner };

		virtual ~ActorValueOwner() = default;  // 00

		// add
		virtual float GetActorValue([[maybe_unused]] const ActorValueInfo& a_info) const { return 0.0F; }																		 // 01
		virtual float GetPermanentActorValue([[maybe_unused]] const ActorValueInfo& a_info) const { return 0.0F; }																 // 02
		virtual float GetBaseActorValue([[maybe_unused]] const ActorValueInfo& a_info) const { return 0.0F; }																	 // 03
		virtual void SetBaseActorValue([[maybe_unused]] const ActorValueInfo& a_info, [[maybe_unused]] float a_value) { return; }												 // 04
		virtual void ModBaseActorValue([[maybe_unused]] const ActorValueInfo& a_info, [[maybe_unused]] float a_delta) { return; }												 // 05
		virtual void ModActorValue([[maybe_unused]] ACTOR_VALUE_MODIFIER a_modifier, [[maybe_unused]] const ActorValueInfo& a_info, [[maybe_unused]] float a_delta) { return; }	 // 06
		virtual float GetModifier([[maybe_unused]] ACTOR_VALUE_MODIFIER a_modifier, [[maybe_unused]] const ActorValueInfo& a_info) const { return 0.0F; }						 // 07
		virtual void RestoreActorValue([[maybe_unused]] const ActorValueInfo& a_info, [[maybe_unused]] float a_amount) { return; }												 // 08
		virtual void SetActorValue(const ActorValueInfo& a_info, float a_value) { SetBaseActorValue(a_info, a_value); }															 // 09
		virtual bool GetIsPlayerOwner() const { return false; }																													 // 0A
	};
	static_assert(sizeof(ActorValueOwner) == 0x8);

	class BGSNavmeshableObject
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSNavmeshableObject };

		// members
		BSTSmartPointer<NavMesh> embeddedNavmesh;  // 0
	};
	static_assert(sizeof(BGSNavmeshableObject) == 0x8);

	class BGSOpenCloseForm
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSOpenCloseForm };

		virtual ~BGSOpenCloseForm() = default;	// 00

		// add
		virtual void HandleOpenStart(TESObjectREFR*, TESObjectREFR*, bool) { return; }	 // 01
		virtual void HandleCloseStart(TESObjectREFR*, TESObjectREFR*, bool) { return; }	 // 02
		virtual void HandleOpenFinish(TESObjectREFR*, TESObjectREFR*) { return; }		 // 03
		virtual void HandleCloseFinish(TESObjectREFR*, TESObjectREFR*) { return; }		 // 04
	};
	static_assert(sizeof(BGSOpenCloseForm) == 0x8);

	struct TESChildCell
	{
	public:
		static constexpr auto RTTI{ RTTI_TESChildCell };

		virtual ~TESChildCell() = default;	// 00

		// add
		virtual TESObjectCELL* GetSaveParentCell() const = 0;  // 01
	};
	static_assert(sizeof(TESChildCell) == 0x8);

	class TESMagicCasterForm
	{
	public:
		static constexpr auto RTTI{ RTTI_TESMagicCasterForm };
	};
	static_assert(std::is_empty_v<TESMagicCasterForm>);

	class TESMagicTargetForm
	{
	public:
		static constexpr auto RTTI{ RTTI_TESMagicTargetForm };
	};
	static_assert(std::is_empty_v<TESMagicTargetForm>);

	class TBO_InstanceData :
		public BSIntrusiveRefCounted  // 08
	{
	public:
		static constexpr auto RTTI{ RTTI_TBO_InstanceData };

		virtual ~TBO_InstanceData() = default;	// 00

		// add
		virtual BGSKeywordForm* GetKeywordData() const { return nullptr; }							// 01
		virtual void DeleteKeywordData() { return; }												// 02
		virtual void CreateKeywordData() { return; }												// 03
		virtual BGSBlockBashData* GetBlockBashData() const { return nullptr; }						// 04
		virtual void DeleteBlockBashData() { return; }												// 05
		virtual void CreateBlockBashData() { return; }												// 06
		virtual BSTArray<EnchantmentItem*>* GetEnchantmentArray() const { return nullptr; }			// 07
		virtual void DeleteEnchantmentArray() { return; }											// 08
		virtual void CreateEnchantmentArray() { return; }											// 09
		virtual BSTArray<BGSMaterialSwap*>* GetMaterialSwapArray() const { return nullptr; }		// 0A
		virtual void DeleteMaterialSwapArray() { return; }											// 0B
		virtual void CreateMaterialSwapArray() { return; }											// 0C
		virtual float GetWeight() const { return -1.0F; }											// 0D
		virtual std::int32_t GetValue() const { return -1; }										// 0E
		virtual std::uint32_t GetHealth() const { return 0; }										// 0F
		virtual float GetColorRemappingIndex() const { return std::numeric_limits<float>::max(); }	// 10
		virtual void PostAttach3D(NiAVObject* a_obj3D, TESObjectREFR* a_ref) const;					// 11
		virtual void PostApplyMods(const TESBoundObject*) { return; }								// 12
	};
	static_assert(sizeof(TBO_InstanceData) == 0x10);

	class BaseFormComponent
	{
	public:
		static constexpr auto RTTI{ RTTI_BaseFormComponent };

		virtual ~BaseFormComponent() = default;	 // 00

		F4_HEAP_REDEFINE_NEW(BaseFormComponent);

		// add
		virtual std::uint32_t GetFormComponentType() const { return 0; }													   // 01
		virtual void InitializeDataComponent() = 0;																			   // 02
		virtual void ClearDataComponent() = 0;																				   // 03
		virtual void InitComponent() { return; }																			   // 04
		virtual void CopyComponent([[maybe_unused]] BaseFormComponent* a_copy) { return; }									   // 06
		virtual void CopyComponent([[maybe_unused]] BaseFormComponent* a_copy, [[maybe_unused]] TESForm* a_owner) { return; }  // 05
	};
	static_assert(sizeof(BaseFormComponent) == 0x8);

	class TESTexture :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESTexture };

		// override (BaseFormComponent)
		void InitializeDataComponent() override;		  // 02
		void ClearDataComponent() override { return; }	  // 03
		void CopyComponent(BaseFormComponent*) override;  // 06

		// add
		virtual std::uint32_t GetMaxAllowedSize() { return 0; }						// 07
		virtual const char* GetAsNormalFile(BSStringT<char>& a_outFilename) const;	// 08
		virtual const char* GetDefaultPath() const { return "Textures\\"; }			// 09

		// members
		BSFixedString textureName;	// 08
	};
	static_assert(sizeof(TESTexture) == 0x10);

	class TESIcon :
		public TESTexture  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESIcon };
	};
	static_assert(sizeof(TESIcon) == 0x10);

	template <std::uint32_t N>
	class BGSTypedKeywordValue
	{
	public:
		// members
		std::uint16_t keywordIndex;	 // 0
	};

	template <std::uint32_t N>
	class BGSTypedKeywordValueArray
	{
	public:
		// members
		BGSTypedKeywordValue<N>* array;	 // 00
		std::uint32_t size;				 // 08
	};

	class BGSAttachParentArray :
		public BaseFormComponent,			 // 00
		public BGSTypedKeywordValueArray<2>	 // 08
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSAttachParentArray };

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override { return 'APPA'; }	// 01
		void InitializeDataComponent() override { return; }						// 02
		void ClearDataComponent() override;										// 03
		void CopyComponent(BaseFormComponent*) override { return; }				// 06
		void CopyComponent(BaseFormComponent*, TESForm*) override;				// 05
	};
	static_assert(sizeof(BGSAttachParentArray) == 0x18);

	struct AttackData
	{
	public:
		// members
		float damageMult;			 // 00
		float attackChance;			 // 04
		SpellItem* attackSpell;		 // 08
		std::uint32_t flags;		 // 10
		float attackAngle;			 // 14
		float strikeAngle;			 // 18
		std::int32_t staggerOffset;	 // 1C
		BGSKeyword* attackType;		 // 20
		float knockdown;			 // 28
		float recoveryTime;			 // 2C
		float actionPointsMult;		 // 30
	};
	static_assert(sizeof(AttackData) == 0x38);

	class BGSAttackData :
		public NiRefObject	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSAttackData };

		// members
		BSFixedString event;			  // 10
		AttackData data;				  // 18
		BGSEquipSlot* weaponEquipSlot;	  // 50
		BGSEquipSlot* requiredEquipSlot;  // 58
	};
	static_assert(sizeof(BGSAttackData) == 0x60);

	class BGSAttackDataMap :
		public NiRefObject	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSAttackDataMap };

		// members
		BSTHashMap<BSFixedString, NiPointer<BGSAttackData>> attackDataMap;	// 10
		TESRace* defaultDataRace;											// 40
	};
	static_assert(sizeof(BGSAttackDataMap) == 0x48);

	class BGSAttackDataForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSAttackDataForm };

		// members
		NiPointer<BGSAttackDataMap> attackDataMap;	// 08
	};
	static_assert(sizeof(BGSAttackDataForm) == 0x10);

	struct BIPED_MODEL
	{
	public:
		// members
		std::uint32_t bipedObjectSlots;	 // 0
	};
	static_assert(sizeof(BIPED_MODEL) == 0x4);

	class BGSBipedObjectForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSBipedObjectForm };

		// members
		BIPED_MODEL bipedModelData;	 // 08
	};
	static_assert(sizeof(BGSBipedObjectForm) == 0x10);

	class BGSBlockBashData :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSBlockBashData };

		// members
		BGSImpactDataSet* blockBashImpactDataSet;  // 08
		BGSMaterialType* altBlockMaterialType;	   // 10
	};
	static_assert(sizeof(BGSBlockBashData) == 0x18);

	class BGSCraftingUseSound :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSCraftingUseSound };

		// members
		BGSSoundDescriptorForm* craftingUseSound;  // 08
	};
	static_assert(sizeof(BGSCraftingUseSound) == 0x10);

	class DestructibleObjectStage
	{
	public:
		// members
		std::int8_t modelDamageStage;			 // 00
		std::int8_t healthPercentage;			 // 01
		std::int8_t flags;						 // 02
		std::uint32_t selfDamagePerSecond;		 // 04
		BGSExplosion* explosion;				 // 08
		BGSDebris* debris;						 // 10
		std::uint32_t debrisCount;				 // 18
		BGSModelMaterialSwap* replacementModel;	 // 20
		BSFixedString sequenceName;				 // 28
	};
	static_assert(sizeof(DestructibleObjectStage) == 0x30);

	struct DestructibleObjectData
	{
	public:
		// members
		std::uint32_t health;														  // 00
		std::int8_t numStages;														  // 04
		std::int8_t flags;															  // 05
		DestructibleObjectStage** stagesArray;										  // 08
		BSTArray<BSTTuple<TESForm*, BGSTypedFormValuePair::SharedVal>>* damageTypes;  // 10
		volatile std::int32_t replacementModelRefCount;								  // 18
		NiPointer<QueuedFile> preloadedReplacementModels;							  // 20
	};
	static_assert(sizeof(DestructibleObjectData) == 0x28);

	class BGSDestructibleObjectForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSDestructibleObjectForm };

		// members
		DestructibleObjectData* data;  // 08
	};
	static_assert(sizeof(BGSDestructibleObjectForm) == 0x10);

	class BGSEquipType :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSEquipType };

		// members
		BGSEquipSlot* equipSlot;  // 08
	};
	static_assert(sizeof(BGSEquipType) == 0x10);

	class BGSFeaturedItemMessage :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSFeaturedItemMessage };

		// members
		BGSMessage* featuredItemMessage;  // 08
	};
	static_assert(sizeof(BGSFeaturedItemMessage) == 0x10);

	class BGSForcedLocRefType :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSForcedLocRefType };

		// members
		BGSLocationRefType* forcedType;	 // 08
	};
	static_assert(sizeof(BGSForcedLocRefType) == 0x10);

	class BGSIdleCollection :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSIdleCollection };

		// members
		std::int8_t idleFlags;	  // 08
		std::int8_t idleCount;	  // 09
		TESIdleForm** idleArray;  // 10
		float timerCheckForIdle;  // 18
	};
	static_assert(sizeof(BGSIdleCollection) == 0x20);

	class BGSInstanceNamingRulesForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSInstanceNamingRulesForm };

		// members
		BGSInstanceNamingRules* instanceNamingRules;  // 08
	};
	static_assert(sizeof(BGSInstanceNamingRulesForm) == 0x10);

	class IKeywordFormBase
	{
	public:
		static constexpr auto RTTI{ RTTI_IKeywordFormBase };

		virtual ~IKeywordFormBase() = default;	// 00

		// add
		virtual bool HasKeyword(const BGSKeyword* a_keyword, const TBO_InstanceData* a_data) const = 0;								// 01
		virtual void CollectAllKeywords(BSScrapArray<const BGSKeyword*>& a_outKeywords, const TBO_InstanceData* a_data) const = 0;	// 02
	};
	static_assert(sizeof(IKeywordFormBase) == 0x8);

	class BGSKeywordForm :
		public BaseFormComponent,  // 00
		public IKeywordFormBase	   // 08
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSKeywordForm };

		// add
		virtual BGSKeyword* GetDefaultKeyword() const { return nullptr; }  // 07

		// members
		BGSKeyword** keywords;		// 10
		std::uint32_t numKeywords;	// 18
	};
	static_assert(sizeof(BGSKeywordForm) == 0x20);

	class BGSMenuDisplayObject :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSMenuDisplayObject };

		// members
		TESBoundObject* menuDispObject;	 // 08
	};
	static_assert(sizeof(BGSMenuDisplayObject) == 0x10);

	class BGSMessageIcon :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSMessageIcon };

		// override (BaseFormComponent)
		void InitializeDataComponent() override;		  // 02
		void ClearDataComponent() override;				  // 03
		void CopyComponent(BaseFormComponent*) override;  // 06

		// members
		TESIcon icon;  // 08
	};
	static_assert(sizeof(BGSMessageIcon) == 0x18);

	class BGSNativeTerminalForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSNativeTerminalForm };

		// members
		BGSTerminal* terminal;	// 08
	};
	static_assert(sizeof(BGSNativeTerminalForm) == 0x10);

	class BGSOverridePackCollection :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSOverridePackCollection };

		// members
		BGSListForm* spectatorOverRidePackList;		 // 08
		BGSListForm* observeCorpseOverRidePackList;	 // 10
		BGSListForm* guardWarnOverRidePackList;		 // 18
		BGSListForm* enterCombatOverRidePackList;	 // 20
		BGSListForm* followerCommandPackList;		 // 28
		BGSListForm* elevatorOverRidePackList;		 // 30
	};
	static_assert(sizeof(BGSOverridePackCollection) == 0x38);

	struct PerkRankData
	{
	public:
		// members
		BGSPerk* perk;			  // 00
		std::int8_t currentRank;  // 08
	};
	static_assert(sizeof(PerkRankData) == 0x10);

	class BGSPerkRankArray :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSPerkRankArray };

		// members
		PerkRankData* perks;	  // 08
		std::uint32_t perkCount;  // 10
	};
	static_assert(sizeof(BGSPerkRankArray) == 0x18);

	class BGSPickupPutdownSounds :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSPickupPutdownSounds };

		// members
		BGSSoundDescriptorForm* pickupSound;   // 08
		BGSSoundDescriptorForm* putdownSound;  // 10
	};
	static_assert(sizeof(BGSPickupPutdownSounds) == 0x18);

	class BGSPreloadable :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSPreloadable };

		// add
		virtual void QueueModelsImpl(void* a_queued, IO_TASK_PRIORITY, QueuedFile*, const TBO_InstanceData*) = 0;  // 07 - todo
	};
	static_assert(sizeof(BGSPreloadable) == 0x8);

	class BGSPreviewTransform :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSPreviewTransform };

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override { return 'NRTP'; }	// 01
		void InitializeDataComponent() override { transform = nullptr; }		// 02
		void ClearDataComponent() override { return; }							// 03
		void InitComponent() override;											// 04
		void CopyComponent(BaseFormComponent*) override { return; }				// 06
		void CopyComponent(BaseFormComponent*, TESForm*) override;				// 05

		// members
		BGSTransform* transform;  // 08
	};
	static_assert(sizeof(BGSPreviewTransform) == 0x10);

	class BGSPropertySheet :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSPropertySheet };

		// members
		BSTArray<BSTTuple<TESForm*, BGSTypedFormValuePair::SharedVal>>* properties;	 // 08
	};
	static_assert(sizeof(BGSPropertySheet) == 0x10);

	class BGSSkinForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSSkinForm };

		// members
		TESObjectARMO* formSkin;  // 08
	};
	static_assert(sizeof(BGSSkinForm) == 0x10);

	class BGSSoundTagComponent :
		public BaseFormComponent  // 0
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSSoundTagComponent };

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override { return 'CTAC'; }	// 01
		void InitializeDataComponent() override { return; }						// 02
		void ClearDataComponent() override;										// 03
		void InitComponent() override;											// 04
		void CopyComponent(BaseFormComponent*) override { return; }				// 06
		void CopyComponent(BaseFormComponent*, TESForm*) override;				// 05
	};
	static_assert(sizeof(BGSSoundTagComponent) == 0x8);

	class ContainerItemExtra
	{
	public:
		// members
		TESForm* ownerForm;	 // 00
		union
		{
			TESGlobal* ownerGlobal;
			std::int32_t ownerRank;
			void* u;
		};				   // 08
		float healthMult;  // 10
	};
	static_assert(sizeof(ContainerItemExtra) == 0x18);

	class ContainerObject
	{
	public:
		// members
		std::int32_t count;				// 00
		TESBoundObject* obj;			// 08
		ContainerItemExtra* itemExtra;	// 10
	};
	static_assert(sizeof(ContainerObject) == 0x18);

	class TESContainer :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESContainer };

		// members
		ContainerObject** containerObjects;	 // 08
		std::uint32_t numContainerObjects;	 // 10
	};
	static_assert(sizeof(TESContainer) == 0x18);

	struct BGSLocalizedStringDL
	{
	public:
		// members
		std::uint32_t id;  // 0
	};
	static_assert(sizeof(BGSLocalizedStringDL) == 0x4);

	class TESDescription :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESDescription };

		// override (BaseFormComponent)
		void InitializeDataComponent() override	 // 02
		{
			fileOffset = 0;
			chunkOffset = 0;
		}

		void ClearDataComponent() override { return; }	  // 03
		void CopyComponent(BaseFormComponent*) override;  // 06

		// members
		std::uint32_t fileOffset;			   // 08
		std::uint32_t chunkOffset;			   // 0C
		BGSLocalizedStringDL descriptionText;  // 10
	};
	static_assert(sizeof(TESDescription) == 0x18);

	class TESEnchantableForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESEnchantableForm };

		virtual MagicSystem::CastingType GetCastingType() const { return *castingType; }  // 07

		// members
		EnchantmentItem* formEnchanting;										// 08
		stl::enumeration<MagicSystem::CastingType, std::uint16_t> castingType;	// 10
		std::uint16_t amountofEnchantment;										// 12
	};
	static_assert(sizeof(TESEnchantableForm) == 0x18);

	class TESFullName :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESFullName };

		// add
		virtual std::uint32_t GetFullNameLength() const { return fullName.length(); }  // 07
		virtual const char* GetFullName() const { return fullName.c_str(); }		   // 08

		[[nodiscard]] static const char* GetFullName(const TESForm* a_obj);

		// members
		BGSLocalizedString fullName;  // 08
	};
	static_assert(sizeof(TESFullName) == 0x10);

	class TESModel :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESModel };

		// override (BaseFormComponent)
		void InitializeDataComponent() override;		  // 02
		void ClearDataComponent() override;				  // 03
		void CopyComponent(BaseFormComponent*) override;  // 06

		// add
		virtual const char* GetModel() { return model.c_str(); }					// 07
		virtual void SetModel(const char* a_model) { model = a_model; }				// 08
		virtual BGSModelMaterialSwap* GetAsModelMaterialSwap() { return nullptr; }	// 09

		// members
		BSFixedString model;		  // 08
		BSResource::ID* textures;	  // 10
		BSResource::ID* materials;	  // 18
		std::uint32_t* addons;		  // 20
		std::int8_t numTextures;	  // 28
		std::int8_t numTexturesSRGB;  // 29
		std::int8_t numAddons;		  // 2A
		std::int8_t numMaterials;	  // 2B
		std::int8_t flags;			  // 2C
	};
	static_assert(sizeof(TESModel) == 0x30);

	class BGSBehaviorGraphModel :
		public TESModel	 // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSBehaviorGraphModel };
	};
	static_assert(sizeof(BGSBehaviorGraphModel) == 0x30);

	class BGSModelMaterialSwap :
		public TESModel	 // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSModelMaterialSwap };

		// members
		BGSMaterialSwap* swapForm;	// 30
		float colorRemappingIndex;	// 38
	};
	static_assert(sizeof(BGSModelMaterialSwap) == 0x40);

	class BGSTextureModel :
		public TESModel	 // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSTextureModel };
	};
	static_assert(sizeof(BGSTextureModel) == 0x30);

	class TESModelRDT :
		public TESModel	 // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESModelRDT };
	};
	static_assert(sizeof(TESModelRDT) == 0x30);

	struct ACTOR_BASE_DATA
	{
	public:
		// members
		std::uint32_t actorBaseFlags;	 // 00
		std::int16_t xpValueOffset;		 // 04
		std::uint16_t level;			 // 06
		std::uint16_t calcLevelMin;		 // 08
		std::uint16_t calcLevelMax;		 // 0A
		std::uint16_t baseDisposition;	 // 0C
		std::uint16_t templateUseFlags;	 // 0E
		std::int16_t bleedoutOverride;	 // 10
	};
	static_assert(sizeof(ACTOR_BASE_DATA) == 0x14);

	struct FACTION_RANK
	{
	public:
		// members
		TESFaction* faction;  // 00
		std::int8_t rank;	  // 08
	};
	static_assert(sizeof(FACTION_RANK) == 0x10);

	class TESActorBaseData :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESActorBaseData };

		// add
		virtual void CopyFromTemplateForms([[maybe_unused]] TESActorBase** a_forceTemplates) { return; }  // 07
		virtual bool GetIsGhost() const;																  // 08
		virtual bool GetInvulnerable() const;															  // 09

		// members
		ACTOR_BASE_DATA actorData;		  // 08
		std::int32_t changeFlags;		  // 1C
		TESLevItem* deathItem;			  // 20
		BGSVoiceType* voiceType;		  // 28
		TESForm* baseTemplateForm;		  // 30
		TESForm** templateForms;		  // 38
		TESGlobal* legendChance;		  // 40
		TESForm* legendTemplate;		  // 48
		BSTArray<FACTION_RANK> factions;  // 50
	};
	static_assert(sizeof(TESActorBaseData) == 0x68);

	struct AIDATA_GAME
	{
	public:
		// members
		std::uint32_t aggression : 2;	   // 00:00
		std::uint32_t confidence : 3;	   // 00:02
		std::uint32_t energy : 8;		   // 00:05
		std::uint32_t morality : 2;		   // 00:13
		std::uint32_t unused : 3;		   // 00:15
		std::uint32_t assistance : 2;	   // 00:18
		std::uint32_t useAggroRadius : 1;  // 00:20
		std::uint16_t aggroRadius[3];	   // 04
		std::uint32_t noSlowApproach : 1;  // 0A:00
	};
	static_assert(sizeof(AIDATA_GAME) == 0x10);

	class PackageList
	{
	public:
		// members
		BSSimpleList<TESPackage*> listPackages;
	};
	static_assert(sizeof(PackageList) == 0x10);

	class TESAIForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESAIForm };

		// members
		AIDATA_GAME aiData;		 // 08
		PackageList aiPackList;	 // 18
	};
	static_assert(sizeof(TESAIForm) == 0x28);

	class TESBipedModelForm :
		public BaseFormComponent  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI_TESBipedModelForm };

		// members
		BGSModelMaterialSwap worldModel[2];	 // 008
		TESIcon inventoryIcon[2];			 // 088
		BGSMessageIcon messageIcon[2];		 // 0A8
		TESModelRDT constraintTemplate;		 // 0D8
	};
	static_assert(sizeof(TESBipedModelForm) == 0x108);

	class TESImageSpaceModifiableForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESImageSpaceModifiableForm };

		// members
		TESImageSpaceModifier* formImageSpaceModifying;	 // 08
	};
	static_assert(sizeof(TESImageSpaceModifiableForm) == 0x10);

	struct LEVELED_OBJECT
	{
	public:
		// members
		TESForm* form;					// 00
		ContainerItemExtra* itemExtra;	// 08
		std::uint16_t count;			// 10
		std::uint16_t level;			// 12
		std::int8_t chanceNone;			// 14
	};
	static_assert(sizeof(LEVELED_OBJECT) == 0x18);

	class TESLeveledList :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESLeveledList };

		// add
		virtual std::int8_t GetChanceNone();								   // 07
		virtual bool GetMultCalc();											   // 08
		virtual std::int32_t GetMaxLevelDifference() { return 0; }			   // 09
		virtual const char* GetOverrideName() { return nullptr; }			   // 0A
		virtual bool GetCanContainFormsOfType(ENUM_FORM_ID a_type) const = 0;  // 0B

		// members
		TESGlobal* chanceGlobal;														 // 08
		BSTArray<BSTTuple<TESForm*, BGSTypedFormValuePair::SharedVal>>* keywordChances;	 // 10
		LEVELED_OBJECT* leveledLists;													 // 18
		LEVELED_OBJECT** scriptAddedLists;												 // 20
		std::int8_t scriptListCount;													 // 28
		std::int8_t baseListCount;														 // 29
		std::int8_t chanceNone;															 // 2A
		std::int8_t llFlags;															 // 2B
		std::int8_t maxUseAllCount;														 // 2C
	};
	static_assert(sizeof(TESLeveledList) == 0x30);

	class TESModelTri :
		public TESModel	 // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESModelTri };
	};
	static_assert(sizeof(TESModelTri) == 0x30);

	class TESProduceForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESProduceForm };

		// members
		BGSSoundDescriptorForm* harvestSound;  // 08
		TESBoundObject* produceItem;		   // 10
		std::int8_t produceChance[4];		   // 18
	};
	static_assert(sizeof(TESProduceForm) == 0x20);

	class TESRaceForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESRaceForm };

		// add
		virtual bool SwitchRace(TESRace* a_race)  // 07
		{
			formRace = a_race;
			return true;
		}

		// members
		TESRace* formRace;	// 08
	};
	static_assert(sizeof(TESRaceForm) == 0x10);

	struct GROUP_REACTION
	{
	public:
		// members
		TESForm* form;				 // 00
		std::int32_t reaction;		 // 08
		std::int32_t fightReaction;	 // 0C
	};
	static_assert(sizeof(GROUP_REACTION) == 0x10);

	class TESReactionForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESReactionForm };

		// members
		BSSimpleList<GROUP_REACTION*> reactionList;	 // 08
		std::int8_t groupFormType;					 // 18
	};
	static_assert(sizeof(TESReactionForm) == 0x20);

	class TESSpellList :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESSpellList };

		struct SpellData
		{
		public:
			// members
			SpellItem** spells;			 // 00
			TESLevSpell** levSpells;	 // 08
			TESShout** shouts;			 // 10
			std::uint32_t numSpells;	 // 18
			std::uint32_t numLevSpells;	 // 1C
			std::uint32_t numShouts;	 // 20
		};
		static_assert(sizeof(SpellData) == 0x28);

		// members
		SpellData* spellData;  // 08
	};
	static_assert(sizeof(TESSpellList) == 0x10);

	class TESTexture1024 :
		public TESTexture  // 10
	{
	public:
		static constexpr auto RTTI{ RTTI_TESTexture1024 };

		// override (TESTexture)
		std::uint32_t GetMaxAllowedSize() override { return 1024; }	 // 07
	};
	static_assert(sizeof(TESTexture1024) == 0x10);

	class TESValueForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESValueForm };

		// members
		std::int32_t value;	 // 08
	};
	static_assert(sizeof(TESValueForm) == 0x10);

	class TESWeightForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESWeightForm };

		// members
		float weight;  // 08
	};
	static_assert(sizeof(TESWeightForm) == 0x10);

	namespace BGSMod
	{
		struct Container :
			public BSTDataBuffer<2, BSDataBufferHeapAllocator>	// 00
		{
		public:
			static constexpr auto RTTI{ RTTI_BGSMod__Container };
		};
		static_assert(sizeof(Container) == 0x10);

		namespace Template
		{
			class Item :
				public TESFullName,		  // 00
				public BGSMod::Container  // 10
			{
			public:
				static constexpr auto RTTI{ RTTI_BGSMod__Template__Item };

				// members
				BGSMod::Template::Items* parentTemplate;  // 20
				BGSKeyword** nameKeywordA;				  // 28
				std::uint16_t parent;					  // 30
				std::int8_t levelMin;					  // 32
				std::int8_t levelMax;					  // 33
				std::int8_t keywords;					  // 34
				std::int8_t tierStartLevel;				  // 35
				std::int8_t altLevelsPerTier;			  // 36
				bool isDefault : 1;						  // 37:1
				bool fullNameEditorOnly : 1;			  // 37:2
			};
			static_assert(sizeof(Item) == 0x38);

			class Items :
				public BaseFormComponent  // 00
			{
			public:
				static constexpr auto RTTI{ RTTI_BGSMod__Template__Items };

				// override (BaseFormComponent)
				std::uint32_t GetFormComponentType() const override { return 'TJBO'; }	// 01
				void InitializeDataComponent() override { return; }						// 02
				void ClearDataComponent() override;										// 03
				void InitComponent() override;											// 04
				void CopyComponent(BaseFormComponent*) override { return; }				// 06
				void CopyComponent(BaseFormComponent*, TESForm*) override;				// 05

				// members
				BSTArray<Item*> items;	// 08
			};
			static_assert(sizeof(Items) == 0x20);
		}
	}
}
