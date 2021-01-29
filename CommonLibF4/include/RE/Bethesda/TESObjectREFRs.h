#pragma once

#include "RE/Bethesda/BGSInventoryItem.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSSoundHandle.h"
#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/MemoryManager.h"
#include "RE/Bethesda/TESForms.h"
#include "RE/Havok/hknpBodyId.h"
#include "RE/Havok/hknpClosestUniqueBodyIdHitCollector.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiRefObject.h"

namespace RE
{
	enum class BIPED_OBJECT;
	enum class IO_TASK_PRIORITY;
	enum class ITEM_REMOVE_REASON;

	namespace MagicSystem
	{
		enum class CastingSource;
	}

	namespace BGSBodyPartDefs
	{
		enum class LIMB_ENUM;
	}

	class ActorCause;
	class BGSAnimationSequencer;
	class BGSDecalGroup;
	class BGSInventoryList;
	class BGSObjectInstance;
	class BGSObjectInstanceExtra;
	class BSAnimationGraphChannel;
	class BSAnimationGraphManager;
	class BSFaceGenNiNode;
	class BShkbAnimationGraph;
	class DialogueResponse;
	class hkVector4f;
	class MagicCaster;
	class MagicTarget;
	class ModelReferenceEffect;
	class NiAVObject;
	class NiLight;
	class NiNode;
	class NiTransform;
	class NonActorMagicCaster;
	class TargetEntry;
	class TBO_InstanceData;
	class TrapData;
	class TrapEntry;
	class WeaponAnimationGraphManagerHolder;

	struct BSActiveGraphIfInactiveEvent;
	struct BSAnimationGraphEvent;
	struct BSAnimationUpdateData;
	struct LOADED_REF_DATA;

	namespace ActorValueEvents
	{
		struct ActorValueChangedEvent;
	}

	namespace BGSInventoryListEvent
	{
		enum class Type
		{
			kAddStack,
			kChangedStack,
			kAddNewItem,
			kRemoveItem,
			kClear,
			UpdateWeight
		};

		struct Event
		{
		public:
			// members
			stl::enumeration<Type, std::uint16_t> changeType;  // 00
			ObjectRefHandle owner;                             // 04
			TESBoundObject* objAffected;                       // 08
			std::uint32_t count;                               // 10
			std::uint32_t stackID;                             // 14
		};
		static_assert(sizeof(Event) == 0x18);
	}

	enum class RESET_3D_FLAGS
	{
		kModel = 1u << 0,
		kSkin = 1u << 1,
		kHead = 1u << 2,
		kFace = 1u << 3,
		kScale = 1u << 4,
		kSkeleton = 1u << 5,
		kInitDefault = 1u << 6,
		kSkyCellSkin = 1u << 7,
		kHavok = 1u << 8,
		kDontAddOutfit = 1u << 9,
		kKeepHead = 1u << 10,
		kDismemberment = 1u << 11
	};

	class __declspec(novtable) BSHandleRefObject :
		public NiRefObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSHandleRefObject };
		static constexpr auto VTABLE{ VTABLE::BSHandleRefObject };

		std::uint32_t DecRefCount()
		{
			stl::atomic_ref myRefCount{ refCount };
			const auto newRefCount = --myRefCount & 0x3FF;
			if (newRefCount == 0) {
				DeleteThis();
			}
			return newRefCount;
		}

		void IncRefCount()
		{
			stl::atomic_ref myRefCount{ refCount };
			++myRefCount;
		}

		[[nodiscard]] std::uint32_t QRefCount() const noexcept { return refCount & 0x3FF; }
	};
	static_assert(sizeof(BSHandleRefObject) == 0x10);

	class __declspec(novtable) IAnimationGraphManagerHolder
	{
	public:
		static constexpr auto RTTI{ RTTI::IAnimationGraphManagerHolder };
		static constexpr auto VTABLE{ VTABLE::IAnimationGraphManagerHolder };

		virtual ~IAnimationGraphManagerHolder() = default;  // 00

		// add
		virtual bool NotifyAnimationGraphImpl(const BSFixedString& a_eventName);                                                                                                                                                     // 01
		virtual void EventSuccessfullyProcessed() { return; }                                                                                                                                                                        // 02
		virtual void ModifyInitialAnimationStateImpl(const bool) { return; }                                                                                                                                                         // 03
		virtual bool GetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) const = 0;                                                                                                               // 04
		virtual bool SetAnimationGraphManagerImpl(const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) = 0;                                                                                                               // 05
		virtual bool PopulateGraphNodesToTarget([[maybe_unused]] BSScrapArray<NiAVObject*>& a_nodesToAnimate) const { return false; }                                                                                                // 06
		virtual bool ConstructAnimationGraph(BSTSmartPointer<BShkbAnimationGraph>& a_animGraph) = 0;                                                                                                                                 // 07
		virtual bool InitializeAnimationGraphVariables([[maybe_unused]] const BSTSmartPointer<BShkbAnimationGraph>& a_newGraph) const { return true; }                                                                               // 08
		virtual bool SetupAnimEventSinks([[maybe_unused]] const BSTSmartPointer<BShkbAnimationGraph>& a_newGraph) { return true; }                                                                                                   // 09
		virtual void DoFailedToLoadGraph() const { return; }                                                                                                                                                                         // 0A
		virtual bool CreateAnimationChannels([[maybe_unused]] BSScrapArray<BSTSmartPointer<BSAnimationGraphChannel>>& a_channels) { return false; }                                                                                  // 0B
		virtual void PostCreateAnimationGraphManager([[maybe_unused]] BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) { return; }                                                                                          // 0C
		virtual void PostChangeAnimationManager([[maybe_unused]] const BSTSmartPointer<BSAnimationGraphManager>& a_newAnimGraphMgr, [[maybe_unused]] const BSTSmartPointer<BSAnimationGraphManager>& a_oldAnimGraphMgr) { return; }  // 0D
		virtual bool ShouldUpdateAnimation() { return true; }                                                                                                                                                                        // 0E
		virtual std::uint32_t GetGraphVariableCacheSize() const { return 0; }                                                                                                                                                        // 0F
		virtual bool GetGraphVariableImpl([[maybe_unused]] std::uint32_t a_graphVarID, [[maybe_unused]] float& a_out) const { return false; }                                                                                        // 10
		virtual bool GetGraphVariableImpl([[maybe_unused]] std::uint32_t a_graphVarID, [[maybe_unused]] bool& a_out) const { return false; }                                                                                         // 11
		virtual bool GetGraphVariableImpl([[maybe_unused]] std::uint32_t a_graphVarID, [[maybe_unused]] std::int32_t& a_out) const { return false; }                                                                                 // 12
		virtual bool GetGraphVariableImpl(const BSFixedString& a_variable, float& a_out) const;                                                                                                                                      // 13
		virtual bool GetGraphVariableImpl(const BSFixedString& a_variable, std::int32_t& a_out) const;                                                                                                                               // 14
		virtual bool GetGraphVariableImpl(const BSFixedString& a_variable, bool& a_out) const;                                                                                                                                       // 15
		virtual void PreUpdateAnimationGraphManager([[maybe_unused]] const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) const { return; }                                                                               // 16
		virtual void PostUpdateAnimationGraphManager([[maybe_unused]] const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) const { return; }                                                                              // 17
		virtual void PreLoadAnimationGraphManager([[maybe_unused]] const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) { return; }                                                                                       // 18
		virtual void PostLoadAnimationGraphManager([[maybe_unused]] const BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr) { return; }                                                                                      // 19
	};
	static_assert(sizeof(IAnimationGraphManagerHolder) == 0x8);

	class BGSEquipIndex
	{
	public:
		~BGSEquipIndex() noexcept {}  // NOLINT(modernize-use-equals-default)

		// members
		std::uint32_t index;  // 0
	};
	static_assert(sizeof(BGSEquipIndex) == 0x4);

	struct SubgraphIdentifier
	{
	public:
		// members
		std::size_t identifier;  // 0
	};
	static_assert(sizeof(SubgraphIdentifier) == 0x8);

	struct BGSBehaviorRootData
	{
	public:
		// members
		BSFixedString idleManagerRootToUse;  // 00
		BSFixedString behaviorRootFilename;  // 08
		SubgraphIdentifier identifier;       // 10
		bool firstPerson;                    // 18
	};
	static_assert(sizeof(BGSBehaviorRootData) == 0x20);

	class BGSObjectInstance
	{
	public:
		// members
		TESForm* object{ nullptr };                      // 00
		BSTSmartPointer<TBO_InstanceData> instanceData;  // 08
	};
	static_assert(sizeof(BGSObjectInstance) == 0x10);

	template <class T>
	class BGSObjectInstanceT :
		public BGSObjectInstance
	{
	public:
	};

	struct OBJ_REFR
	{
	public:
		// members
		NiPoint3A angle;                  // 00
		NiPoint3A location;               // 10
		TESBoundObject* objectReference;  // 20
	};
	static_assert(sizeof(OBJ_REFR) == 0x30);

	class BGSInventoryList :
		public BSTEventSource<BGSInventoryListEvent::Event>  // 00
	{
	public:
		[[nodiscard]] static bool StandardObjectCompareCallbackFn(TESBoundObject* a_lhs, TESBoundObject* a_rhs)
		{
			return a_lhs == a_rhs;
		}

		void FindAndWriteStackDataForItem(
			TESBoundObject* a_object,
			BGSInventoryItem::StackDataCompareFunctor& a_compareFunc,
			BGSInventoryItem::StackDataWriteFunctor& a_writeFunc,
			bool (*a_objCompFn)(TESBoundObject*, TESBoundObject*) = StandardObjectCompareCallbackFn,
			bool a_alwaysContinue = false)
		{
			using func_t = decltype(&BGSInventoryList::FindAndWriteStackDataForItem);
			REL::Relocation<func_t> func{ REL::ID(1354005) };
			return func(this, a_object, a_compareFunc, a_writeFunc, a_objCompFn, a_alwaysContinue);
		}

		// DOES NOT LOCK
		void ForEachStack(
			std::function<bool(BGSInventoryItem&)> a_filter,                             // return true to iterate stacks
			std::function<bool(BGSInventoryItem&, BGSInventoryItem::Stack&)> a_continue  // return false to return control from function
		)
		{
			for (auto& elem : data) {
				if (a_filter(elem)) {
					for (auto stack = elem.stackData.get(); stack; stack = stack->nextStack.get()) {
						if (!a_continue(elem, *stack)) {
							return;
						}
					}
				}
			}
		}

		// members
		BSTArray<BGSInventoryItem> data;  // 58
		float cachedWeight;               // 70
		ObjectRefHandle owner;            // 74
		BSReadWriteLock rwLock;           // 78
	};
	static_assert(sizeof(BGSInventoryList) == 0x80);

	enum class BIPED_OBJECT
	{
		kNone = static_cast<std::underlying_type_t<BIPED_OBJECT>>(-1),

		kEditorCount = 32,

		kWeaponHand = kEditorCount,
		kWeaponSword,
		kWeaponDagger,
		kWeaponAxe,
		kWeaponMace,
		kWeaponTwoHandMelee,
		kWeaponBow,
		kWeaponStaff,
		kQuiver,
		kWeaponGun,
		kWeaponGrenade,
		kWeaponMine,

		kTotal
	};

	struct BIPOBJECT
	{
	public:
		~BIPOBJECT();

		// members
		BGSObjectInstance parent;          // 00
		BGSObjectInstanceExtra* modExtra;  // 10
		TESObjectARMA* armorAddon;         // 18
		TESModel* part;                    // 20
		BGSTextureSet* skinTexture;        // 28
		NiPointer<NiAVObject> partClone;   // 30
		void* handleList;                  // 38 - TODO: BSModelDB::HandleListHead
		union
		{
			std::byte spare40;
			BSTSmartPointer<WeaponAnimationGraphManagerHolder> objectGraphManager;
		};  // 40 - TODO
		union
		{
			std::byte spare48;
			NiPointer<ModelReferenceEffect> hitEffect;
		};             // 48 - TODO
		bool skinned;  // 50

	private:
		void Dtor()
		{
			using func_t = decltype(&BIPOBJECT::Dtor);
			REL::Relocation<func_t> func{ REL::ID(765242) };
			return func(this);
		}
	};
	static_assert(sizeof(BIPOBJECT) == 0x58);

	class BipedAnim :
		public BSIntrusiveRefCounted  // 0000
	{
	public:
		// members
		NiNode* root;                                                         // 0008
		BIPOBJECT object[stl::to_underlying(BIPED_OBJECT::kTotal)];           // 0010
		BIPOBJECT bufferedObjects[stl::to_underlying(BIPED_OBJECT::kTotal)];  // 0F30
		ObjectRefHandle actorRef;                                             // 1E50
	};
	static_assert(sizeof(BipedAnim) == 0x1E58);

	class __declspec(novtable) TESObjectREFR :
		public TESForm,                                                  // 000
		public BSHandleRefObject,                                        // 020
		public BSTEventSink<BSActiveGraphIfInactiveEvent>,               // 030
		public BSTEventSink<BSAnimationGraphEvent>,                      // 038
		public BSTEventSink<BGSInventoryListEvent::Event>,               // 040
		public IAnimationGraphManagerHolder,                             // 048
		public IKeywordFormBase,                                         // 050
		public ActorValueOwner,                                          // 058
		public BSTEventSource<ActorValueEvents::ActorValueChangedEvent>  // 060
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectREFR };
		static constexpr auto VTABLE{ VTABLE::TESObjectREFR };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kREFR };

		struct RemoveItemData;

		F4_HEAP_REDEFINE_NEW(TESObjectREFR);

		// add
		virtual void Predestroy();                                                                                                                                                                                                                    // 4A
		virtual void PreModelLoaderQueueing() { return; }                                                                                                                                                                                             // 4B
		virtual BGSLocation* GetEditorLocation() const;                                                                                                                                                                                               // 4C
		virtual bool GetEditorLocation(NiPoint3& a_originalLocation, NiPoint3& a_originalAngle, TESForm*& a_locationFormOut, TESForm* a_locationForm);                                                                                                // 4D
		virtual bool IsTalking() const;                                                                                                                                                                                                               // 4E
		virtual void ForceEditorLocation(BGSLocation* a_location);                                                                                                                                                                                    // 4F
		virtual void Update3DPosition(bool a_warp);                                                                                                                                                                                                   // 50
		virtual void UpdateSoundCallBack(bool a_endSceneAction);                                                                                                                                                                                      // 51
		virtual bool SetDialoguewithPlayer(bool a_flag, bool a_forceGreet, TESTopicInfo* a_topicInfo);                                                                                                                                                // 52
		virtual void AddDynamicIdleCRC([[maybe_unused]] std::uint32_t a_crc) { return; }                                                                                                                                                              // 53
		virtual void GetPreviousDynamicIdleCRCS(std::uint32_t* a_crcs, std::uint32_t a_requestSize) const;                                                                                                                                            // 54
		virtual bool GetFullLODRef() const;                                                                                                                                                                                                           // 55
		virtual void SetFullLODRef(bool a_val);                                                                                                                                                                                                       // 56
		virtual BGSAnimationSequencer* GetSequencer() const;                                                                                                                                                                                          // 57
		virtual bool QCanUpdateSync() const { return true; }                                                                                                                                                                                          // 58
		virtual bool GetAllowPromoteToPersistent() const { return true; }                                                                                                                                                                             // 59
		virtual bool DoesFloat() const { return false; }                                                                                                                                                                                              // 5A
		virtual TESPackage* CheckForCurrentAliasPackage() { return nullptr; }                                                                                                                                                                         // 5B
		virtual BGSScene* GetCurrentScene() const;                                                                                                                                                                                                    // 5C
		virtual void SetCurrentScene(BGSScene* a_scene);                                                                                                                                                                                              // 5D
		virtual bool UpdateInDialogue(DialogueResponse* a_response, bool);                                                                                                                                                                            // 5E
		virtual BGSDialogueBranch* GetExclusiveBranch() const;                                                                                                                                                                                        // 5F
		virtual void SetExclusiveBranch(BGSDialogueBranch* a_exclusiveBranch);                                                                                                                                                                        // 60
		virtual void StopCurrentDialogue(bool a_force);                                                                                                                                                                                               // 61
		virtual void FadeCurrentDialogue();                                                                                                                                                                                                           // 62
		virtual void PauseCurrentDialogue();                                                                                                                                                                                                          // 63
		virtual void ResumeCurrentDialogue();                                                                                                                                                                                                         // 64
		virtual void SetActorCause(ActorCause* a_actorCause);                                                                                                                                                                                         // 65
		virtual ActorCause* GetActorCause() const;                                                                                                                                                                                                    // 66
		virtual float GetActorWidthOrRefDiameter() const;                                                                                                                                                                                             // 67
		virtual float GetActorHeightOrRefBound() const;                                                                                                                                                                                               // 68
		virtual NiPoint3 GetStartingAngle();                                                                                                                                                                                                          // 69
		virtual NiPoint3 GetStartingLocation();                                                                                                                                                                                                       // 6A
		virtual void SetStartingPosition(const NiPoint3& a_position);                                                                                                                                                                                 // 6B
		virtual void UpdateRefLight(float a_delta);                                                                                                                                                                                                   // 6C
		virtual ObjectRefHandle RemoveItem(RemoveItemData& a_data);                                                                                                                                                                                   // 6D
		virtual void AddWornOutfitImpl([[maybe_unused]] BGSOutfit* a_outfit, [[maybe_unused]] bool a_queueItem) { return; }                                                                                                                           // 6E
		virtual bool AddWornItem(TESBoundObject* a_object, BSTSmartPointer<ExtraDataList> a_extra, std::int32_t a_number, bool a_forceEquip, BGSEquipIndex a_equipIndex);                                                                             // 6F
		virtual void DoTrap([[maybe_unused]] TrapEntry* a_trap, [[maybe_unused]] TargetEntry* a_target) { return; }                                                                                                                                   // 71
		virtual void DoTrap([[maybe_unused]] TrapData& a_trapData) { return; }                                                                                                                                                                        // 70
		virtual void SetEquipStateLocked(TESBoundObject* a_object, bool a_lock);                                                                                                                                                                      // 72
		virtual void SendContainerChangedEvent(const TESObjectREFR* a_oldContainer, const TESObjectREFR* apNewContainer, const TESBoundObject* a_baseObject, std::int32_t a_count, std::uint32_t a_referenceFormID, std::uint16_t a_uniqueID) const;  // 73
		virtual void UnequipArmorFromSlot([[maybe_unused]] BIPED_OBJECT a_bipedObject, [[maybe_unused]] bool a_markAsReequippable) { return; }                                                                                                        // 74
		virtual void RemoveAllObjectsWorn();                                                                                                                                                                                                          // 75
		virtual void PostRemoveWornObject(const BGSObjectInstance& a_object, const BGSEquipSlot* a_equipSlot);                                                                                                                                        // 76
		virtual void Set3DUpdateFlag([[maybe_unused]] RESET_3D_FLAGS a_flag) { return; }                                                                                                                                                              // 77
		virtual void ClearAll3DUpdateFlags() { return; }                                                                                                                                                                                              // 78
		virtual float AdjustItemWeight([[maybe_unused]] TESBoundObject& a_object, [[maybe_unused]] const BGSInventoryItem::Stack& a_stack, float a_weight, [[maybe_unused]] bool* a_shouldModifyWholeStackOut) { return a_weight; }                   // 79
		virtual void AddObjectToContainer(TESBoundObject* a_obj, BSTSmartPointer<ExtraDataList> a_extra, std::int32_t a_count, TESObjectREFR* a_oldContainer, ITEM_REMOVE_REASON a_reason);                                                           // 7A
		virtual NiPoint3 GetLookingAtLocation() const;                                                                                                                                                                                                // 7B
		virtual MagicCaster* GetMagicCaster(MagicSystem::CastingSource a_source);                                                                                                                                                                     // 7C
		virtual MagicTarget* GetMagicTarget();                                                                                                                                                                                                        // 7D
		virtual bool IsChild() const { return false; }                                                                                                                                                                                                // 7E
		virtual TESActorBase* GetTemplateActorBase() { return nullptr; }                                                                                                                                                                              // 7F
		virtual void SetTemplateActorBase(TESActorBase*) { return; }                                                                                                                                                                                  // 80
		virtual BSFaceGenNiNode* GetFaceNodeSkinned() { return nullptr; }                                                                                                                                                                             // 81
		virtual BSFaceGenNiNode* GetFaceNode() { return GetFaceNodeSkinned(); }                                                                                                                                                                       // 82
		virtual bool ClampToGround();                                                                                                                                                                                                                 // 83
		virtual bool DetachHavok(NiAVObject* a_obj3D);                                                                                                                                                                                                // 84
		virtual void InitHavok();                                                                                                                                                                                                                     // 85
		virtual NiAVObject* Load3D(bool a_backgroundLoading);                                                                                                                                                                                         // 86
		virtual void Release3DRelatedData();                                                                                                                                                                                                          // 87
		virtual void Set3D(NiAVObject* a_object, bool a_queue3DTasks);                                                                                                                                                                                // 88
		virtual bool ShouldBackgroundClone() const;                                                                                                                                                                                                   // 89
		virtual bool IsReadyForAttach([[maybe_unused]] const IO_TASK_PRIORITY& a_priority) const { return true; }                                                                                                                                     // 8A
		virtual NiAVObject* Get3D() const;                                                                                                                                                                                                            // 8C
		virtual NiAVObject* Get3D([[maybe_unused]] bool a_firstPerson) const { return Get3D(); }                                                                                                                                                      // 8B
		virtual NiAVObject* GetFullyLoaded3D() const;                                                                                                                                                                                                 // 8D
		virtual bool Is3rdPersonVisible() const { return true; }                                                                                                                                                                                      // 8E
		virtual bool PopulateGraphProjectsToLoad(const NiAVObject* a_obj3D, BSScrapArray<BSStaticStringT<260>>& a_projectFilenames) const;                                                                                                            // 8F
		virtual TESModel* GetTESModel() const;                                                                                                                                                                                                        // 90
		virtual TESRace* GetVisualsRace() const;                                                                                                                                                                                                      // 91
		virtual void GetPhysicsTransform(NiTransform& a_outTransform) const;                                                                                                                                                                          // 92
		virtual NiPoint3 GetBoundMin() const;                                                                                                                                                                                                         // 93
		virtual NiPoint3 GetBoundMax() const;                                                                                                                                                                                                         // 94
		virtual bool GetBehaviorRootNameOverrides([[maybe_unused]] BSScrapArray<BSFixedString>& a_behaviorRoots) const { return false; }                                                                                                              // 95
		virtual bool GetBehaviorRootNameReplacement([[maybe_unused]] BSFixedString& a_rootNameReplacement) const { return false; }                                                                                                                    // 96
		virtual bool GetBehaviorRootData(bool a_onlyCollectActiveRoots, BSScrapArray<BGSBehaviorRootData>& a_behaviorRoots) const;                                                                                                                    // 97
		virtual void OnHeadInitialized() { return; }                                                                                                                                                                                                  // 98
		virtual bool InitNonNPCAnimation(NiNode& a_nodeForAnim);                                                                                                                                                                                      // 99
		virtual bool CheckAndFixSkinAndBoneOrder(NiNode& a_nodeToTest);                                                                                                                                                                               // 9A
		virtual void ModifyAnimationUpdateData([[maybe_unused]] BSAnimationUpdateData& a_updateData) { return; }                                                                                                                                      // 9B
		virtual bool ShouldSaveAnimationOnUnloading() const;                                                                                                                                                                                          // 9C
		virtual bool ShouldSaveAnimationOnSaving() const;                                                                                                                                                                                             // 9D
		virtual bool ShouldPerformRevert() const { return true; }                                                                                                                                                                                     // 9E
		virtual void UpdateAnimation(float a_delta);                                                                                                                                                                                                  // 9F
		virtual void CollectPickNodes() { return; }                                                                                                                                                                                                   // A0
		virtual const BSTSmartPointer<BipedAnim>& GetBiped() const;                                                                                                                                                                                   // A2
		virtual const BSTSmartPointer<BipedAnim>& GetBiped(bool a_firstPerson) const;                                                                                                                                                                 // A1
		virtual const BSTSmartPointer<BipedAnim>& GetCurrentBiped() const { return GetBiped(); }                                                                                                                                                      // A3
		virtual void SetBiped([[maybe_unused]] const BSTSmartPointer<BipedAnim>& a_biped) { return; }                                                                                                                                                 // A4
		virtual void AttachWeapon(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, BGSEquipIndex a_equipIndex);                                                                                                                                     // A5
		virtual void RemoveWeapon([[maybe_unused]] const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, [[maybe_unused]] BGSEquipIndex a_equipIndex, [[maybe_unused]] bool a_queue3DTasks) { return; }                                                  // A6
		virtual void CreateInventoryList(const TESContainer* a_container);                                                                                                                                                                            // A7
		virtual void DestroyInventoryList();                                                                                                                                                                                                          // A8
		virtual void SetRunsInLow(bool) { return; }                                                                                                                                                                                                   // A9
		virtual void SetObjectReference(TESBoundObject* a_object);                                                                                                                                                                                    // AA
		virtual void MoveHavok(bool a_forceRec);                                                                                                                                                                                                      // AB
		virtual void GetLinearVelocity(NiPoint3& a_velocity) const;                                                                                                                                                                                   // AC
		virtual void ApplyMovementDelta(float a_timeDelta, const NiPoint3A& a_delta, const NiPoint3& a_angleDelta);                                                                                                                                   // AD
		virtual void SetActionComplete([[maybe_unused]] bool a_value) { return; }                                                                                                                                                                     // AE
		virtual void SetMovementComplete(bool) { return; }                                                                                                                                                                                            // AF
		virtual void Disable();                                                                                                                                                                                                                       // B0
		virtual void ResetInventory(bool a_leveledOnly);                                                                                                                                                                                              // B1
		virtual NiAVObject* GetCurrent3D() const { return Get3D(); }                                                                                                                                                                                  // B2
		virtual Explosion* IsExplosion() { return nullptr; }                                                                                                                                                                                          // B4
		virtual const Explosion* IsExplosion() const { return nullptr; }                                                                                                                                                                              // B3
		virtual Projectile* IsProjectile() { return nullptr; }                                                                                                                                                                                        // B6
		virtual const Projectile* IsProjectile() const { return nullptr; }                                                                                                                                                                            // B5
		virtual bool OnAddCellPerformQueueReference([[maybe_unused]] TESObjectCELL& a_cell) const { return true; }                                                                                                                                    // B7
		virtual void DoMoveToHigh() { return; }                                                                                                                                                                                                       // B8
		virtual void TryMoveToMiddleLow() { return; }                                                                                                                                                                                                 // B9
		virtual bool TryChangeSkyCellActorsProcessLevel() { return false; }                                                                                                                                                                           // BA
		virtual void SetDisplayGeometry(bool) { return; }                                                                                                                                                                                             // BB
		virtual void TryUpdateActorLastSeenTime() { return; }                                                                                                                                                                                         // BC
		virtual void SaveGameTest();                                                                                                                                                                                                                  // BD
		virtual TESObjectCELL* GetSaveParentCell() const;                                                                                                                                                                                             // BE
		virtual void SetParentCell(TESObjectCELL* a_cell);                                                                                                                                                                                            // BF
		virtual bool IsDead(bool a_notEssential) const;                                                                                                                                                                                               // C0
		virtual bool ProcessInWater(hknpBodyId a_bodyID, float a_waterHeight, float a_deltaTime);                                                                                                                                                     // C1
		virtual bool ApplyCurrent([[maybe_unused]] float a_deltaTime, [[maybe_unused]] const hkVector4f& a_linVel, const hkVector4f&) { return false; }                                                                                               // C2
		virtual BGSDecalGroup* GetDecalGroup() const;                                                                                                                                                                                                 // C3
		virtual void InitDefaultWornImpl(bool a_weapon, bool a_allowChanges);                                                                                                                                                                         // C4
		virtual bool HasKeywordHelper(const BGSKeyword* a_keyword, const TBO_InstanceData* a_data) const;                                                                                                                                             // C5

		void FindAndWriteStackDataForInventoryItem(
			TESBoundObject* a_object,
			BGSInventoryItem::StackDataCompareFunctor& a_compareFunc,
			BGSInventoryItem::StackDataWriteFunctor& a_writeFunc,
			bool (*a_objCompFn)(TESBoundObject*, TESBoundObject*) = BGSInventoryList::StandardObjectCompareCallbackFn,
			bool a_alwaysContinue = false)
		{
			if (inventoryList) {
				inventoryList->FindAndWriteStackDataForItem(a_object, a_compareFunc, a_writeFunc, a_objCompFn, a_alwaysContinue);
			}
		}

		[[nodiscard]] TESBoundObject* GetObjectReference() const noexcept { return data.objectReference; }
		[[nodiscard]] TESObjectCELL* GetParentCell() const noexcept { return parentCell; }

		[[nodiscard]] float GetWeightInContainer()
		{
			using func_t = decltype(&TESObjectREFR::GetWeightInContainer);
			REL::Relocation<func_t> func{ REL::ID(1377567) };
			return func(this);
		}

		// members
		TESObjectCELL* parentCell;                 // 0B8
		OBJ_REFR data;                             // 0C0
		LOADED_REF_DATA* loadedData;               // 0F0
		BGSInventoryList* inventoryList;           // 0F8
		BSTSmartPointer<ExtraDataList> extraList;  // 100
		std::uint16_t refScale;                    // 018
		std::int8_t modelState;                    // 10A
		bool predestroyed;                         // 10B
	};
	static_assert(sizeof(TESObjectREFR) == 0x110);

	class __declspec(novtable) Explosion :
		public TESObjectREFR  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::Explosion };
		static constexpr auto VTABLE{ VTABLE::Explosion };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kREFR };

		struct ExplodedLimb
		{
		public:
			// members
			stl::enumeration<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> limb;  // 00
			ActorValueInfo* limbCondition;                                    // 08
			float distance;                                                   // 10
		};
		static_assert(sizeof(ExplodedLimb) == 0x18);

		class ExplosionTarget
		{
		public:
			// members
			ObjectRefHandle ref;               // 00
			std::uint32_t flags;               // 04
			float hitFromExplosionSqrLen;      // 08
			BSTArray<ExplodedLimb> limbArray;  // 10
		};
		static_assert(sizeof(ExplosionTarget) == 0x28);

		// add
		virtual void Initialize();           // C6
		virtual void Update(float a_delta);  // C7
		virtual void FindTargets();          // C8

		// members
		hknpClosestUniqueBodyIdHitCollector collector;   // 110
		void* explosionDBHandle;                         // 520 - TODO
		float age;                                       // 528
		float obj3Dlifetime;                             // 52C
		float audioLifetime;                             // 530
		float buildTime;                                 // 534
		float innerRadius;                               // 538
		float outerRadius;                               // 53C
		float imageSpaceRadius;                          // 540
		float damageMult;                                // 544
		BSSimpleList<ExplosionTarget*> targetList;       // 548
		BSTSmallArray<BSSoundHandle, 4> soundHandles;    // 558
		NiPointer<NiLight> light;                        // 588
		ObjectRefHandle owner;                           // 590
		ObjectRefHandle explodedRef;                     // 594
		ObjectRefHandle createdRef;                      // 598
		BSTSmartPointer<ActorCause> actorCause;          // 5A0
		NonActorMagicCaster* caster;                     // 5A8
		BGSObjectInstanceT<TESObjectWEAP> weaponSource;  // 5B0
		std::int32_t frameCount;                         // 5C0
		NiPoint3A closestPoint;                          // 5D0
		NiPoint3A closestPointNormal;                    // 5E0
		float calculatedDamage;                          // 5F0
		float scale;                                     // 5F4
		std::uint32_t flags;                             // 5F8
	};
	static_assert(sizeof(Explosion) == 0x600);

	class __declspec(novtable) Hazard :
		public TESObjectREFR  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::Hazard };
		static constexpr auto VTABLE{ VTABLE::Hazard };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kPHZD };

		// members
		void* hazardDBHandle;      // 110 - TODO
		ActorHandle ownerActor;    // 118
		float age;                 // 11C
		float lifetime;            // 120
		float targetTimer;         // 124
		float radius;              // 128
		float magnitude;           // 12C
		BGSHazard* hazard;         // 130
		NiPointer<NiLight> light;  // 138
		BSSoundHandle sound;       // 140
		std::uint32_t flags;       // 148
	};
	static_assert(sizeof(Hazard) == 0x150);
}
