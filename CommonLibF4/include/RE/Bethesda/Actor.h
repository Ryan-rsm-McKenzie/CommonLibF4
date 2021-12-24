#pragma once

#include "RE/Bethesda/AITimeStamp.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSPointerHandle.h"
#include "RE/Bethesda/BSSoundHandle.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTSingleton.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTTuple.h"
#include "RE/Bethesda/IMovementInterface.h"
#include "RE/Bethesda/TESObjectREFRs.h"
#include "RE/NetImmerse/NiFlags.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	enum class ACTOR_CRITICAL_STAGE;
	enum class ACTOR_LIFE_STATE;
	enum class ACTOR_LOS_LOCATION;
	enum class ATTACK_STATE_ENUM;
	enum class PACKAGE_OBJECT_TYPE;
	enum class POWER_ATTACK_TYPE;
	enum class PTYPE;
	enum class RESET_3D_FLAGS;
	enum class SIT_SLEEP_STATE;

	template <class>
	class AnimationStanceFireLocationData;

	template <class>
	class BSPointerHandleSmartPointer;

	template <class, class, class, template <class> class>
	class BSResponse;

	template <class>
	class DoNothingUnhandledPolicy;

	class ActiveEffect;
	class ActorMagicCaster;
	class ActorMover;
	class ActorPackageLoadFormBuffer;
	class AimModel;
	class AIProcess;
	class BGSSaveFormBuffer;
	class bhkCharacterController;
	class bhkCharacterMoveFinishEvent;
	class bhkCharacterStateChangeEvent;
	class bhkNonSupportContactEvent;
	class bhkNPCollisionObject;
	class bhkRagdollPenetrationUtil;
	class BipedAnim;
	class BSCloneReserver;
	class BSClothExtraData;
	class BSFaceGenAnimationData;
	class BSLightingShaderProperty;
	class BSPathingRequest;
	class BSTransformDeltaEvent;
	class CombatController;
	class CombatGroup;
	class EffectItem;
	class EquippedItem;
	class EquippedItemData;
	class HitData;
	class IAnimationStanceData;
	class IProcedureTreeExecState;
	class MovementControllerNPC;
	class MovementMessageActorCollision;
	class MovementMessageNewPath;
	class MovementMessageUpdateRequestImmediate;
	class MuzzleFlash;
	class PackageLocation;
	class PerkEntryVisitor;
	class QueuedFile;
	class QueuedItem;

	struct ActorCPMEvent;
	struct ActorInventoryEvent;
	struct ActorMotionFeedbackData;
	struct ActorMotionFeedbackOutput;
	struct AIPerkData;
	struct BSAnimationGraphVariableCache;
	struct BSMovementDataChangedEvent;
	struct BSSubGraphActivationUpdate;
	struct CastPowerItem;
	struct DeferredHideLimb;
	struct HighProcessData;
	struct ObjectstoAcquire;
	struct Perks;

	namespace ActorEquipManagerEvent
	{
		struct Event;
	}

	namespace MagicSystem
	{
		enum class CannotCastReason;
		enum class WardState;
	}

	namespace PerkValueEvents
	{
		struct PerkValueChangedEvent;
		struct PerkEntryUpdatedEvent;
	}

	enum class INTERACTING_STATE : std::uint32_t
	{
		kNotInteracting,
		kWaitingToInteract,
		kInteracting,
		kWaitingToStopInteracting
	};

	struct MiddleLowProcessData
	{
	public:
		// members
		std::int32_t hourPackageEvaluated;  // 0
	};
	static_assert(sizeof(MiddleLowProcessData) == 0x4);

	class __declspec(novtable) ActorPackageData
	{
	public:
		static constexpr auto RTTI{ RTTI::ActorPackageData };
		static constexpr auto VTABLE{ VTABLE::ActorPackageData };

		virtual ~ActorPackageData();  // 00

		// add
		virtual PTYPE GetPackageType() = 0;                                                                             // 01
		virtual IProcedureTreeExecState* GetProcedureExecState() { return nullptr; }                                    // 02
		virtual void SetProcedureExecState([[maybe_unused]] IProcedureTreeExecState& a_procedureExecState) { return; }  // 03
		virtual void ClearProcedureExecState() { return; }                                                              // 04
		virtual void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer) = 0;                                                 // 05
		virtual void LoadGame(ActorPackageLoadFormBuffer* a_loadGameBuffer) = 0;                                        // 06
		virtual void InitLoadGame([[maybe_unused]] ActorPackageLoadFormBuffer* a_loadGameBuffer) { return; }            // 07
		virtual void ResetPackData([[maybe_unused]] TESPackage* a_pack) { return; }                                     // 08
	};
	static_assert(sizeof(ActorPackageData) == 0x8);

	class ActorPackage
	{
	public:
		// members
		BSSpinLock packageLock;               // 00
		TESPackage* package;                  // 08
		ActorPackageData* data;               // 10
		ObjectRefHandle target;               // 18
		std::int32_t currentProcedureIndex;   // 1C
		float packageStartTime;               // 20
		std::uint32_t modifiedPackageFlag;    // 24
		std::uint16_t modifiedInterruptFlag;  // 28
		std::int8_t actorPackageFlags;        // 2A
		std::int8_t preferredSpeed;           // 2B
	};
	static_assert(sizeof(ActorPackage) == 0x30);

	struct CommandedActorData
	{
	public:
		// members
		ActorHandle commandedActor;  // 00
		ActiveEffect* activeEffect;  // 08
	};
	static_assert(sizeof(CommandedActorData) == 0x10);

	class ActiveEffectList
	{
	public:
		// members
		BSTArray<BSTSmartPointer<ActiveEffect>> data;  // 00
		std::int8_t iterating;                         // 18
	};
	static_assert(sizeof(ActiveEffectList) == 0x20);

	struct SubGraphIdleRootData
	{
	public:
		// members
		SubgraphIdentifier subGraphID;  // 00
		BSFixedString idleRootName;     // 08
		std::int8_t count;              // 10
		std::int8_t activeCount;        // 11
		bool forFirstPerson;            // 12
	};
	static_assert(sizeof(SubGraphIdleRootData) == 0x18);

	class __declspec(novtable) EquippedItemData :
		public NiRefObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::EquippedItemData };
		static constexpr auto VTABLE{ VTABLE::EquippedItemData };

		// add
		virtual void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer, const EquippedItem& a_equippedItem) const = 0;  // 02
		virtual void LoadGame(BGSLoadFormBuffer* a_loadGameBuffer, const EquippedItem& a_equippedItem) = 0;        // 03
		virtual std::uint32_t GetObjectType() const = 0;                                                           // 04
	};
	static_assert(sizeof(EquippedItemData) == 0x10);

	class __declspec(novtable) EquippedWeaponData :
		public EquippedItemData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::EquippedWeaponData };
		static constexpr auto VTABLE{ VTABLE::EquippedWeaponData };

		// members
		TESAmmo* ammo;                                                                               // 10
		std::uint32_t ammoCount;                                                                     // 18
		AimModel* aimModel;                                                                          // 20
		MuzzleFlash* muzzleFlash;                                                                    // 28
		NiAVObject* fireNode;                                                                        // 30
		ATTACK_STATE_ENUM attackState;                                                               // 38
		BSTArray<BSTTuple<std::uint32_t, AnimationStanceFireLocationData<NiPoint3>>> fireLocations;  // 40
		NiPointer<QueuedFile> weaponPreload;                                                         // 58
		NiPointer<QueuedFile> projectilePreload;                                                     // 60
		NiPointer<BSCloneReserver> reserveProjectileClones;                                          // 68
		BSSoundHandle idleSound;                                                                     // 70
		BSSoundHandle attackSound;                                                                   // 78
		BSSoundHandle reverbSound;                                                                   // 80
		BSSoundHandle prevAttack;                                                                    // 88
		BSSoundHandle prevReverb;                                                                    // 90
		const BGSSoundKeywordMapping* attackSoundData;                                               // 98
		bool reverbSoundIsTail;                                                                      // A0
	};
	static_assert(sizeof(EquippedWeaponData) == 0xA8);

	class EquippedItem
	{
	public:
		// members
		BGSObjectInstance item;            // 00
		const BGSEquipSlot* equipSlot;     // 10
		BGSEquipIndex equipIndex;          // 18
		NiPointer<EquippedItemData> data;  // 20
	};
	static_assert(sizeof(EquippedItem) == 0x28);

	struct SubgraphHandle
	{
	public:
		// members
		std::uint64_t handle;  // 0
	};
	static_assert(sizeof(SubgraphHandle) == 0x8);

	template <class T>
	class AnimationStanceNodeLocationData
	{
	public:
		// members
		T nodeLocationArray[3];  // 00
	};

	struct MiddleHighProcessData
	{
	public:
		// members
		BSTEventSource<ActorInventoryEvent> inventoryEventSource;                                                 // 000
		NiPointer<bhkNPCollisionObject> poseBound;                                                                // 058
		ActorPackage runOncePackage;                                                                              // 060
		BSTArray<ActorHandle> deadDetectList;                                                                     // 090
		BSSimpleList<TESObjectREFR*> refListChairBed;                                                             // 0A8
		NiPoint3 rotation;                                                                                        // 0B8
		NiPoint3 rotationSpeed;                                                                                   // 0C4
		NiPoint3 actorMountPosition;                                                                              // 0D0
		NiPoint3 furniturePathPoint;                                                                              // 0DC
		NiPoint3 lastSeenPosition;                                                                                // 0E8
		ActorHandle bleedoutAttacker;                                                                             // 0F4
		stl::enumeration<MagicSystem::WardState, std::int32_t> wardState;                                         // 0F8
		BSTSmartPointer<BSResponse<BSFixedString, Actor, BSFixedString, DoNothingUnhandledPolicy>> animResponse;  // 100
		BSTArray<CommandedActorData> commandedActors;                                                             // 108
		NiNode* damageRootNode[26];                                                                               // 120
		NiNode* weaponBone;                                                                                       // 1F0
		NiAVObject* headNode;                                                                                     // 1F8
		NiAVObject* torsoNode;                                                                                    // 200
		NiAVObject* faceTargetSourceNode;                                                                         // 208
		BSFaceGenNiNode* faceNodeSkinned;                                                                         // 210
		NiPointer<BSLightingShaderProperty> lightingProperty;                                                     // 218
		QueuedItem* listItemstoEquipUnequip;                                                                      // 220
		HitData* lastHitData;                                                                                     // 228
		DeferredHideLimb* headDeferredHideLimb;                                                                   // 230
		ActiveEffectList activeEffects;                                                                           // 238
		BSTSmartPointer<BSAnimationGraphManager> animationGraphManager;                                           // 258
		BSAnimationGraphVariableCache* animationVariableCache;                                                    // 260
		BSTArray<SubGraphIdleRootData> subGraphIdleManagerRoots;                                                  // 268
		BSSpinLock equippedItemsLock;                                                                             // 280
		BSTArray<EquippedItem> equippedItems;                                                                     // 288
		BSTArray<BSClothExtraData*> clothExtraDataCache;                                                          // 2A0
		BSTArray<BSTSmallArray<SubgraphHandle, 2>> subGraphHandles;                                               // 2B8
		BSTSmallArray<SubgraphIdentifier, 2> currentDefaultSubGraphID;                                            // 2D0
		BSTSmallArray<SubgraphIdentifier, 2> requestedDefaultSubGraphID;                                          // 2F0
		BSTSmallArray<SubgraphIdentifier, 2> currentWeaponSubGraphID;                                             // 310
		BSTSmallArray<SubgraphIdentifier, 2> requestedWeaponSubGraphID;                                           // 330
		BSTSmartPointer<IAnimationStanceData> stanceData;                                                         // 350
		BSTArray<BSTTuple<std::uint32_t, AnimationStanceNodeLocationData<NiPoint3>>> nodeLocationArray;           // 358
		float stanceHeightArray[6][2];                                                                            // 370
		float headHeightOffset;                                                                                   // 3A0
		ObjectRefHandle currentFurniture;                                                                         // 3A4
		ObjectRefHandle occupiedFurniture;                                                                        // 3A8
		TESIdleForm* currentIdle;                                                                                 // 3B0
		ActorHandle commandingActor;                                                                              // 3B8
		const TESIdleForm* furnitureIdle;                                                                         // 3C0
		BSFaceGenAnimationData* faceAnimationData;                                                                // 3C8
		MagicItem* currentPackageSpell;                                                                           // 3D0
		TESObjectWEAP* lastBoundWeapon;                                                                           // 3D8
		NiPointer<bhkCharacterController> charController;                                                         // 3E0
		BSTSmartPointer<bhkRagdollPenetrationUtil> penetrationDetectUtil;                                         // 3E8
		NiPointer<QueuedFile> bodyPartPreload;                                                                    // 3F0
		TESIdleForm* lastIdlePlayed;                                                                              // 3F8
		AIPerkData* perkData;                                                                                     // 400
		NiPoint3 lookAtLocation;                                                                                  // 408
		float pursueTimer;                                                                                        // 414
		float furnitureAngle;                                                                                     // 418
		float furnitureEntryFootstepDeltaTarget;                                                                  // 41C
		float packageIdleTimer;                                                                                   // 420
		float equippedWeight;                                                                                     // 424
		float desiredSpeed;                                                                                       // 428
		float animationSpeed;                                                                                     // 42C
		float bleedoutTimer;                                                                                      // 430
		float bleedoutRate;                                                                                       // 434
		float bleedoutMaxHealth;                                                                                  // 438
		float maxWardPower;                                                                                       // 43C
		float animGraphEventTimeout;                                                                              // 440
		float torchEvalTimer;                                                                                     // 444
		float alphaMult;                                                                                          // 448
		float scriptRefractPower;                                                                                 // 44C
		float sleepingTimer;                                                                                      // 450
		float deferredKillTimer;                                                                                  // 454
		float killMoveTimer;                                                                                      // 458
		float staggerTimer;                                                                                       // 45C
		float mountDismountSafetyTimer;                                                                           // 460
		AITimeStamp rangeWaypointIdleTimer;                                                                       // 464
		std::int32_t packageIdleNumber;                                                                           // 468
		std::int32_t reservationSlot;                                                                             // 46C
		SubgraphIdentifier currentFurnitureSubgraphID;                                                            // 470
		std::uint32_t currentFurnitureMarkerID;                                                                   // 478
		std::uint32_t occupiedFurnitureMarkerID;                                                                  // 47C
		std::uint64_t nextExtraArrow3DUpdate;                                                                     // 480
		std::uint32_t deferredKill;                                                                               // 488
		std::uint32_t flareFlags;                                                                                 // 48C
		stl::enumeration<PACKAGE_OBJECT_TYPE, std::int32_t> useItem;                                              // 490
		std::int16_t animActionSuccess;                                                                           // 494
		std::uint16_t update3DModel;                                                                              // 496
		std::int8_t weaponCullCounter;                                                                            // 498
		std::int8_t archetypeChangeType;                                                                          // 499
		bool animWeaponCull;                                                                                      // 49A
		bool aimingTarget;                                                                                        // 49B
		bool doneClothesChange;                                                                                   // 49C
		bool pickPackIdle;                                                                                        // 49D
		bool doneOnce;                                                                                            // 49E
		bool refreshFlareFlags;                                                                                   // 49F
		bool pickPocketed;                                                                                        // 4A0
		bool summonedCreature;                                                                                    // 4A1
		bool forceNextUpdate;                                                                                     // 4A2
		bool playedBeginIdles;                                                                                    // 4A3
		bool playedEndIdles;                                                                                      // 4A4
		bool quickPlacement;                                                                                      // 4A5
		bool beenAttacked;                                                                                        // 4A6
		bool alwaysHit;                                                                                           // 4A7
		bool doNoDamage;                                                                                          // 4A8
		bool soulTrapped;                                                                                         // 4A9
		bool lookAt;                                                                                              // 4AA
		bool eating;                                                                                              // 4AB
		bool calcLight;                                                                                           // 4AC
		bool preventCombat;                                                                                       // 4AD
		bool dyingFromBleedout;                                                                                   // 4AE
		bool fleeing;                                                                                             // 4AF
		bool instantGetOut;                                                                                       // 4B0
		bool hostileGuard;                                                                                        // 4B1
		bool stopIdleFailed;                                                                                      // 4B2
		bool killQueued;                                                                                          // 4B3
		bool ragdollInstant;                                                                                      // 4B4
		bool scriptDeferredKill;                                                                                  // 4B5
		bool furnitureEntryLeftFootFirst;                                                                         // 4B6
		bool furnitureAnimationPlayed;                                                                            // 4B7
		bool queuedInstantInteractionAnimation;                                                                   // 4B8
		bool queuedModifyInitialAnimationPose;                                                                    // 4B9
		bool avoidPlayer;                                                                                         // 4BA
		bool usingPathingFaceTargetWhileTrackingOutOfRange;                                                       // 4BB
	};
	static_assert(sizeof(MiddleHighProcessData) == 0x4C0);

	class CachedValueData
	{
	public:
		// members
		float value;  // 0
		bool dirty;   // 4
	};
	static_assert(sizeof(CachedValueData) == 0x8);

	class CachedValues
	{
	public:
		// members
		float cachedRadius;                                  // 00
		float cachedWidth;                                   // 04
		float cachedLength;                                  // 08
		float cachedForwardLength;                           // 0C
		float cachedDPS;                                     // 10
		float cachedEyeLevel;                                // 14
		float cachedWalkSpeed;                               // 18
		float cachedRunSpeed;                                // 1C
		float cachedJogSpeed;                                // 20
		float cachedFastWalkSpeed;                           // 24
		std::uint32_t booleanValues;                         // 28
		std::uint32_t flags;                                 // 2C
		BSTArray<CachedValueData> actorValueCache;           // 30
		BSTArray<CachedValueData> permanentActorValueCache;  // 48
	};
	static_assert(sizeof(CachedValues) == 0x60);

	class AITimer
	{
	public:
		float startTime;   // 0
		float targetTime;  // 4
	};
	static_assert(sizeof(AITimer) == 0x8);

	class AIProcess
	{
	public:
		[[nodiscard]] TESAmmo* GetCurrentAmmo(BGSEquipIndex a_equipIndex) const
		{
			using func_t = decltype(&AIProcess::GetCurrentAmmo);
			REL::Relocation<func_t> func{ REL::ID(1154936) };
			return func(this, a_equipIndex);
		}

		void SetCurrentAmmo(BGSEquipIndex a_equipIndex, TESAmmo* a_ammo)
		{
			using func_t = decltype(&AIProcess::SetCurrentAmmo);
			REL::Relocation<func_t> func{ REL::ID(795983) };
			return func(this, a_equipIndex, a_ammo);
		}

		// members
		MiddleLowProcessData* middleLow;                    // 00
		MiddleHighProcessData* middleHigh;                  // 08
		HighProcessData* high;                              // 10
		ActorPackage currentPackage;                        // 18
		float hourLastProcessed;                            // 48
		float timeAdjustmentsMade;                          // 4C
		std::uint32_t dateLastProcessed;                    // 50
		CachedValues* cachedValues;                         // 58
		std::int32_t numberItemsActivate;                   // 60
		BSSimpleList<ObjectstoAcquire*> objectList;         // 68
		BSSimpleList<TESObjectREFR*> genericLocationsList;  // 78
		ObjectstoAcquire* acquireObject;                    // 88
		ObjectstoAcquire* savedAcquireObject;               // 90
		float essentialDownTimer;                           // 98
		float deathTime;                                    // 9C
		float trackedDamage;                                // A0
		TESBoundObject* itemBeingUsed;                      // A8
		AITimer combatDelayTimer;                           // B0
		ObjectRefHandle followTarget;                       // B8
		ObjectRefHandle target;                             // BC
		ObjectRefHandle genericLocation;                    // C0
		ObjectRefHandle genericSecondLocation;              // C4
		BGSListForm* targetFormList;                        // C8
		std::uint32_t currentSpeakingTopicID;               // D0
		ObjectRefHandle patrolLocation;                     // D4
		ObjectRefHandle idleTarget;                         // D8
		std::int16_t formListNumb;                          // DC
		char lowProcessFlags;                               // DE
		char processLevel;                                  // DF
		bool skippedTimeStampForPathing;                    // E0
		bool ignoringCombat;                                // E1
		bool endAlarmOnActor;                               // E2
		bool escortingPlayer;                               // E3
		bool updateEditorDeadModel;                         // E4
		bool editorDeadActive;                              // E5
		bool initializingPosition;                          // E6
	};
	static_assert(sizeof(AIProcess) == 0xE8);

	class __declspec(novtable) MagicTarget
	{
	public:
		static constexpr auto RTTI{ RTTI::MagicTarget };
		static constexpr auto VTABLE{ VTABLE::MagicTarget };

		struct AddTargetData;
		struct SpellDispelData;

		// members
		virtual ~MagicTarget();  // 00

		// add
		virtual bool AddTarget(AddTargetData& a_data);                                                                                                                               // 01
		virtual TESObjectREFR* GetTargetStatsObject() { return nullptr; }                                                                                                            // 02
		virtual bool MagicTargetIsActor() { return false; }                                                                                                                          // 03
		virtual bool IsInvulnerable() const { return false; }                                                                                                                        // 04
		virtual void InvalidateCommandedActorEffect([[maybe_unused]] ActiveEffect* a_effect) { return; }                                                                             // 05
		virtual bool CanAddActiveEffect() const = 0;                                                                                                                                 // 06
		virtual ActiveEffectList* GetActiveEffectList() = 0;                                                                                                                         // 07
		virtual float CheckResistance([[maybe_unused]] MagicItem* a_spell, [[maybe_unused]] EffectItem* a_effect, [[maybe_unused]] TESBoundObject* a_source) const { return 1.0F; }  // 08
		virtual void EffectAdded([[maybe_unused]] ActiveEffect* a_effect) { return; }                                                                                                // 09
		virtual void EffectRemoved([[maybe_unused]] ActiveEffect* a_effect) { return; }                                                                                              // 0A
		virtual void EffectActiveStatusChanged([[maybe_unused]] ActiveEffect* a_effect) { return; }                                                                                  // 0B
		virtual bool CheckAbsorb([[maybe_unused]] Actor* a_caster, [[maybe_unused]] MagicItem* a_spell, [[maybe_unused]] const EffectItem* a_effectItem) { return false; }           // 0C

		// members
		SpellDispelData* postUpdateDispelList;  // 08
		std::int8_t flags;                      // 10
	};
	static_assert(sizeof(MagicTarget) == 0x18);

	enum class WEAPON_STATE : std::uint32_t
	{
		kSheathed,
		kWantToDraw,
		kDrawing,
		kDrawn,
		kWantToSheathe,
		kSheathing
	};

	class __declspec(novtable) ActorState :
		public IMovementState  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ActorState };
		static constexpr auto VTABLE{ VTABLE::ActorState };

		// add
		virtual bool SetWeaponMagicDrawn(bool a_drawn);                // 21
		virtual bool SetWeaponState(WEAPON_STATE a_state);             // 22
		virtual bool DoSetSitSleepState(SIT_SLEEP_STATE a_state) = 0;  // 23
		virtual SIT_SLEEP_STATE DoGetSitSleepState() const = 0;        // 24
		virtual bool SetInIronSightsImpl(bool a_sighted) = 0;          // 25
		virtual void SetReloadingImpl(bool a_reloading);               // 26

		[[nodiscard]] bool GetWeaponMagicDrawn() const noexcept { return weaponState >= WEAPON_STATE::kDrawn; }

		// members
		std::uint32_t moveMode: 14;             // 08:00
		std::uint32_t flyState: 3;              // 08:14
		std::uint32_t lifeState: 4;             // 08:17
		std::uint32_t knockState: 4;            // 08:21
		std::uint32_t meleeAttackState: 3;      // 08:25
		std::uint32_t talkingToPlayer: 1;       // 08:28
		std::uint32_t forceRun: 1;              // 08:29
		std::uint32_t forceSneak: 1;            // 08:30
		std::uint32_t headTracking: 1;          // 08:31
		std::uint32_t reanimating: 1;           // 0C:00
		WEAPON_STATE weaponState: 3;            // 0C:01
		std::uint32_t wantBlocking: 1;          // 0C:04
		std::uint32_t flightBlocked: 1;         // 0C:05
		std::uint32_t recoil: 2;                // 0C:06
		std::uint32_t allowFlying: 1;           // 0C:08
		std::uint32_t staggered: 1;             // 0C:09
		std::uint32_t inWrongProcessLevel: 1;   // 0C:10
		std::uint32_t stance: 3;                // 0C:11
		std::uint32_t gunState: 4;              // 0C:14
		INTERACTING_STATE interactingState: 2;  // 0C:18
		std::uint32_t headTrackRotation: 1;     // 0C:20
		std::uint32_t inSyncAnim: 1;            // 0C:21
	};
	static_assert(sizeof(ActorState) == 0x10);

	class __declspec(novtable) IPostAnimationChannelUpdateFunctor
	{
	public:
		static constexpr auto RTTI{ RTTI::IPostAnimationChannelUpdateFunctor };
		static constexpr auto VTABLE{ VTABLE::IPostAnimationChannelUpdateFunctor };

		virtual ~IPostAnimationChannelUpdateFunctor() = default;  // 00

		// add
		virtual void DoPostAnimationChannelUpdate() = 0;  // 01
	};
	static_assert(sizeof(IPostAnimationChannelUpdateFunctor) == 0x8);

	struct Modifiers
	{
	public:
		// members
		float modifiers[3];  // 0
	};
	static_assert(sizeof(Modifiers) == 0xC);

	class ActorValueStorage
	{
	public:
		// members
		BSTArray<BSTTuple<std::uint32_t, float>> baseValues;     // 00
		BSTArray<BSTTuple<std::uint32_t, Modifiers>> modifiers;  // 18
		BSReadWriteLock avLock;                                  // 30
	};
	static_assert(sizeof(ActorValueStorage) == 0x38);

	class __declspec(novtable) Actor :
		public TESObjectREFR,                                           // 000
		public MagicTarget,                                             // 110
		public ActorState,                                              // 128
		public BSTEventSink<BSMovementDataChangedEvent>,                // 138
		public BSTEventSink<BSTransformDeltaEvent>,                     // 140
		public BSTEventSink<BSSubGraphActivationUpdate>,                // 148
		public BSTEventSink<bhkCharacterMoveFinishEvent>,               // 150
		public BSTEventSink<bhkNonSupportContactEvent>,                 // 158
		public BSTEventSink<bhkCharacterStateChangeEvent>,              // 160
		public IPostAnimationChannelUpdateFunctor,                      // 168
		public BSTEventSource<MovementMessageUpdateRequestImmediate>,   // 170
		public BSTEventSource<PerkValueEvents::PerkValueChangedEvent>,  // 1C8
		public BSTEventSource<PerkValueEvents::PerkEntryUpdatedEvent>,  // 220
		public BSTEventSource<ActorCPMEvent>                            // 278
	{
	public:
		static constexpr auto RTTI{ RTTI::Actor };
		static constexpr auto VTABLE{ VTABLE::Actor };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kACHR };

		// add
		virtual void PlayPickUpSound(TESBoundObject* a_boundObj, bool a_pickUp, bool a_use);                                                                                                             // 0C6
		virtual float GetHeading() const { return data.angle.z; }                                                                                                                                        // 0C7
		virtual void SetAvoidanceDisabled([[maybe_unused]] bool a_tf) { return; }                                                                                                                        // 0C8
		virtual void DrawWeaponMagicHands(bool a_draw);                                                                                                                                                  // 0C9
		virtual void SetPosition(const NiPoint3& a_pos, bool a_updateCharController);                                                                                                                    // 0CA
		virtual void KillDying();                                                                                                                                                                        // 0CB
		virtual void Resurrect(bool a_resetInventory, bool a_attach3D);                                                                                                                                  // 0CC
		virtual bool PutActorInChairBedQuick(TESObjectREFR* a_furniture, std::uint32_t a_index);                                                                                                         // 0CD
		virtual bool PutActorOnMountQuick();                                                                                                                                                             // 0CE
		virtual void Update(float a_delta);                                                                                                                                                              // 0CF
		virtual void UpdateNoAI(float);                                                                                                                                                                  // 0D0
		virtual void UpdateMotionDrivenState();                                                                                                                                                          // 0D1
		virtual void UpdateCharacterControllerSimulationSettings(bhkCharacterController& a_charController);                                                                                              // 0D2
		virtual void PotentiallyFixRagdollState();                                                                                                                                                       // 0D3
		virtual void UpdateNonRenderSafe(float);                                                                                                                                                         // 0D4
		virtual bool ShouldHandleEquipNow() const;                                                                                                                                                       // 0D5
		virtual void SetCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::uint32_t a_value);                                                                                                    // 0D6
		virtual std::uint32_t ModCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::int32_t a_value);                                                                                            // 0D7
		virtual void RemoveCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::int32_t a_value);                                                                                                  // 0D8
		virtual std::uint32_t GetCrimeGoldValue(const TESFaction* a_faction) const;                                                                                                                      // 0D9
		virtual void GoToPrison([[maybe_unused]] TESFaction* a_faction, [[maybe_unused]] bool a_removeItems, [[maybe_unused]] bool a_realJail) { return; }                                               // 0DA
		virtual void ServePrisonTime() { return; }                                                                                                                                                       // 0DB
		virtual void PayFine([[maybe_unused]] TESFaction* a_faction, [[maybe_unused]] bool a_movetoMarker, [[maybe_unused]] bool a_removeStolenItems) { return; }                                        // 0DC
		virtual float GetCurrentEyeLevel() const;                                                                                                                                                        // 0DD
		virtual void SetInDialoguewithPlayer(bool a_flag);                                                                                                                                               // 0DE
		virtual bool GetCannibal() { return false; }                                                                                                                                                     // 0DF
		virtual void SetCannibal(bool) { return; }                                                                                                                                                       // 0E0
		virtual bool GetVampireFeed() { return false; }                                                                                                                                                  // 0E1
		virtual void SetVampireFeed(bool) { return; }                                                                                                                                                    // 0E2
		virtual void InitiateVampireFeedPackage(Actor* a_target, TESObjectREFR* a_furniture);                                                                                                            // 0E3
		virtual void InitiateCannibalPackage(Actor* a_target);                                                                                                                                           // 0E4
		virtual float GetEyeHeading() const;                                                                                                                                                             // 0E5
		virtual void GetEyeAngles(float& a_eyeHeading, float& a_eyeLooking) const;                                                                                                                       // 0E6
		virtual void GetEyeVector(NiPoint3& a_origin, NiPoint3& a_direction, bool a_includeCameraOffset) const;                                                                                          // 0E7
		virtual void SetRefraction(bool a_enable, float a_refractionPower);                                                                                                                              // 0E8
		virtual float GetAcrobatics() const { return 1.0F; }                                                                                                                                             // 0E9
		virtual bool Get3DUpdateFlag(RESET_3D_FLAGS a_flag) const;                                                                                                                                       // 0EA
		virtual ObjectRefHandle DropObject(const BGSObjectInstance& a_object, BSTSmallArray<std::uint32_t, 4>* a_stackData, std::int32_t a_number, const NiPoint3* a_point, const NiPoint3* a_rotate);   // 0EB
		virtual void PickUpObject(TESObjectREFR* a_objREFR, std::int32_t a_count, bool a_playPickUpSounds);                                                                                              // 0EC
		virtual void AttachArrow(const BSTSmartPointer<BipedAnim>& a_biped, BGSEquipIndex a_equipIndex);                                                                                                 // 0ED
		virtual void DetachArrow(const BSTSmartPointer<BipedAnim>& a_biped, BGSEquipIndex a_equipIndex);                                                                                                 // 0EE
		virtual bool ReloadWeapon(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, BGSEquipIndex a_equipIndex);                                                                                        // 0EF
		virtual std::uint32_t UseAmmo(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, BGSEquipIndex a_equipIndex, std::uint32_t a_shotCount);                                                         // 0F0
		virtual bool CalculateCachedOwnerIsInCombatantFaction() const;                                                                                                                                   // 0F1
		virtual CombatGroup* GetCombatGroup() const;                                                                                                                                                     // 0F2
		virtual void SetCombatGroup(CombatGroup* a_group);                                                                                                                                               // 0F3
		virtual bool CheckValidTarget(TESObjectREFR& a_ref) const;                                                                                                                                       // 0F4
		virtual bool InitiateDialogue(Actor* a_target, PackageLocation* a_packLoc, PackageLocation* a_packSecondLoc);                                                                                    // 0F5
		virtual void EndDialogue();                                                                                                                                                                      // 0F6
		virtual Actor* SetUpTalkingActivatorActor(Actor* a_target, Actor*& a_talkingactivator);                                                                                                          // 0F7
		virtual void InitiateFlee(TESObjectREFR* a_fleeRef, bool a_runonce, bool a_knows, bool a_combatMode, TESObjectCELL* a_cell, TESObjectREFR* a_ref, float a_fleeFromDist, float a_fleeToDist);     // 0F8
		virtual void InitiateGetUpPackage();                                                                                                                                                             // 0F9
		virtual void PutCreatedPackage(TESPackage* a_pack, bool a_tempPack, bool a_isACreatedPackage, bool a_allowFromFurniture);                                                                        // 0FA
		virtual void UpdateAlpha();                                                                                                                                                                      // 0FB
		virtual void SetAlpha(float a_newAlpha);                                                                                                                                                         // 0FC
		virtual float GetAlpha();                                                                                                                                                                        // 0FD
		virtual bool IsInCombat() const;                                                                                                                                                                 // 0FE
		virtual void UpdateCombat();                                                                                                                                                                     // 0FF
		virtual void StopCombat();                                                                                                                                                                       // 100
		virtual bool GetUsesAttackPercents() { return false; }                                                                                                                                           // 101
		virtual std::uint8_t GetPowerAttackPercent(POWER_ATTACK_TYPE) { return 0; }                                                                                                                      // 102
		virtual void WeaponSwingCallBack(BGSEquipIndex a_equipIndex);                                                                                                                                    // 103
		virtual void SetActorStartingPosition();                                                                                                                                                         // 104
		virtual void SetLifeState(ACTOR_LIFE_STATE a_lifeState);                                                                                                                                         // 105
		virtual bool HasBeenAttacked();                                                                                                                                                                  // 106
		virtual void SetBeenAttacked(bool a_flag);                                                                                                                                                       // 107
		virtual void UseSkill(ActorValueInfo*, float, TESForm*) { return; }                                                                                                                              // 108
		virtual bool IsAtPoint(const NiPoint3& a_point, float a_radius, bool a_expandRadius, bool a_alwaysTestHeight);                                                                                   // 109
		virtual bool IsInFaction(const TESFaction* a_faction) const;                                                                                                                                     // 10A
		virtual bool HasPerkEntries(std::uint8_t a_entryPoint) const;                                                                                                                                    // 10B
		virtual void ForEachPerkEntry(std::uint8_t a_entryPoint, PerkEntryVisitor& a_visitor) const;                                                                                                     // 10C
		virtual void ApplyPerksFromBase();                                                                                                                                                               // 10D
		virtual void StartPowerAttackCoolDown() { return; }                                                                                                                                              // 10E
		virtual bool IsPowerAttackCoolingDown() const { return false; }                                                                                                                                  // 10F
		virtual void HandleHealthDamage(Actor* a_attacker, float a_damage);                                                                                                                              // 110
		virtual bool QSpeakingDone() const;                                                                                                                                                              // 111
		virtual void SetSpeakingDone(bool a_done);                                                                                                                                                       // 112
		virtual NiPoint3 CalculateLOSLocation(ACTOR_LOS_LOCATION a_location) const;                                                                                                                      // 113
		virtual void CreateMovementController();                                                                                                                                                         // 114
		virtual bool ShouldPivotToFaceCamera() const { return false; }                                                                                                                                   // 115
		virtual BGSKeyword* GetSpeakingAnimArchType() { return speakingAnimArchType; }                                                                                                                   // 116
		virtual void KillImpl(Actor* a_attacker, float a_damage, bool a_sendEvent, bool a_ragdollInstant);                                                                                               // 117
		virtual void DoReparentWeapon(const TESObjectWEAP* a_weapon, BGSEquipIndex a_equipIndex, bool a_weaponDrawn);                                                                                    // 118
		virtual bool DrinkPotion(AlchemyItem* a_potion, std::uint32_t a_stackID);                                                                                                                        // 119
		virtual bool CheckCast(MagicItem* a_spell, bool a_dualCast, MagicSystem::CannotCastReason* a_reason);                                                                                            // 11A
		virtual void CheckTempModifiers() { return; }                                                                                                                                                    // 11B
		virtual void SetLastRiddenMount(ActorHandle a_mount) { return; }                                                                                                                                 // 11C
		virtual ActorHandle QLastRiddenMount() const;                                                                                                                                                    // 11D
		virtual bool CalculateCachedOwnerIsUndead() const;                                                                                                                                               // 11E
		virtual bool CalculateCachedOwnerIsNPC() const;                                                                                                                                                  // 11F
		virtual bool SetSneaking(bool a_sneaking);                                                                                                                                                       // 120
		virtual void ResetHavokPhysics();                                                                                                                                                                // 121
		virtual bool ShouldDoCharacterUpdate() const { return true; }                                                                                                                                    // 122
		virtual bool GetAnimationCanBeInterpolated() const;                                                                                                                                              // 123
		virtual const BSFixedString& GetResponseString() const;                                                                                                                                          // 124
		virtual void ModifyMovementData(float a_delta, NiPoint3& a_moveDelta, NiPoint3& a_angleDelta);                                                                                                   // 125
		virtual void UpdateCombatControllerSettings();                                                                                                                                                   // 126
		virtual void UpdateFadeSettings(bhkCharacterController* a_charController);                                                                                                                       // 127
		virtual bool ComputeMotionFeedbackSpeedAndDirection(const ActorMotionFeedbackData& a_data, float a_delta, ActorMotionFeedbackOutput& a_retData);                                                 // 128
		virtual bool UpdateFeedbackGraphSpeedAndDirection(const ActorMotionFeedbackOutput& a_data);                                                                                                      // 129
		virtual void UpdateActor3DPosition();                                                                                                                                                            // 12A
		virtual void PrecacheData();                                                                                                                                                                     // 12B
		virtual void WornArmorChanged(const BGSObjectInstance& a_object);                                                                                                                                // 12C
		virtual void ProcessTracking(float a_delta, NiAVObject* a_ob3D);                                                                                                                                 // 12D
		virtual void CreateActorMover();                                                                                                                                                                 // 12E
		virtual void DestroyActorMover();                                                                                                                                                                // 12F
		virtual bool ShouldRespondToActorCollision(const MovementMessageActorCollision&, const BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<Actor, HandleManager>>& a_otherActor) const;  // 130
		virtual float CheckClampDamageModifier(ActorValueInfo& a_info, float a_delta);                                                                                                                   // 131
		virtual void ValidateNewPath([[maybe_unused]] const MovementMessageNewPath& a_newPathMessage) { return; }                                                                                        // 132

		[[nodiscard]] TESAmmo* GetCurrentAmmo(BGSEquipIndex a_equipIndex) const
		{
			return currentProcess ? currentProcess->GetCurrentAmmo(a_equipIndex) : nullptr;
		}

		[[nodiscard]] bool GetHostileToActor(Actor* a_actor)
		{
			using func_t = decltype(&Actor::GetHostileToActor);
			REL::Relocation<func_t> func{ REL::ID(1148686) };
			return func(this, a_actor);
		}

		[[nodiscard]] TESNPC* GetNPC() const noexcept;

		void Reset3D(bool a_reloadAll, std::uint32_t a_additionalFlags, bool a_queueReset, std::uint32_t a_excludeFlags)
		{
			using func_t = decltype(&Actor::Reset3D);
			REL::Relocation<func_t> func{ REL::ID(302888) };
			return func(this, a_reloadAll, a_additionalFlags, a_queueReset, a_excludeFlags);
		}

		void SetCurrentAmmo(BGSEquipIndex a_equipIndex, TESAmmo* a_ammo)
		{
			if (currentProcess) {
				currentProcess->SetCurrentAmmo(a_equipIndex, a_ammo);
			}
		}

		// members
		NiTFlags<std::uint32_t, Actor> niFlags;                              // 2D0
		float updateTargetTimer;                                             // 2D4
		NiPoint3 editorLocCoord;                                             // 2D8
		NiPoint3 editorLocRot;                                               // 2E4
		TESForm* editorLocForm;                                              // 2F0
		BGSLocation* editorLocation;                                         // 2F8
		AIProcess* currentProcess;                                           // 300
		ActorMover* actorMover;                                              // 308
		BGSKeyword* speakingAnimArchType;                                    // 310
		BSTSmartPointer<MovementControllerNPC> movementController;           // 318
		TESPackage* initialPackage;                                          // 320
		CombatController* combatController;                                  // 328
		TESFaction* vendorFaction;                                           // 330
		ActorValueStorage avStorage;                                         // 338
		BGSDialogueBranch* exclusiveBranch;                                  // 370
		stl::enumeration<ACTOR_CRITICAL_STAGE, std::int32_t> criticalStage;  // 378
		ObjectRefHandle dialogueItemTarget;                                  // 37C
		ActorHandle currentCombatTarget;                                     // 380
		ActorHandle myKiller;                                                // 384
		float checkMyDeadBodyTimer;                                          // 388
		float voiceTimer;                                                    // 38C
		float voiceLengthTotal;                                              // 390
		float underWaterTimer;                                               // 394
		std::int32_t thiefCrimeStamp;                                        // 398
		std::int32_t actionValue;                                            // 39C
		float timeronAction;                                                 // 3A0
		AITimeStamp calculateVendorFactionTimer;                             // 3A4
		std::uint32_t intimidateBribeDayStamp;                               // 3A8
		float equippedWeight;                                                // 3AC
		BSTSmallArray<SpellItem*> addedSpells;                               // 3B0
		ActorMagicCaster* magicCasters[4];                                   // 3C8
		MagicItem* selectedSpell[4];                                         // 3E8
		CastPowerItem* castPowerItems;                                       // 408
		TESForm* selectedPower;                                              // 410
		TESRace* race;                                                       // 418
		Perks* perks;                                                        // 420
		BSTSmartPointer<BipedAnim> biped;                                    // 428
		BSNonReentrantSpinLock addingToOrRemovingFromScene;                  // 430
		BSReadWriteLock perkArrayLock;                                       // 434
		std::uint32_t flags;                                                 // 43C
		std::uint32_t moreFlags;                                             // 440
		Modifiers healthModifiers;                                           // 444
		Modifiers actionPointsModifiers;                                     // 450
		Modifiers staminaModifiers;                                          // 45C
		Modifiers radsModifiers;                                             // 468
		float lastUpdate;                                                    // 474
		std::uint32_t lastSeenTime;                                          // 478
		float armorRating;                                                   // 47C
		float armorBaseFactorSum;                                            // 480
		std::uint32_t visFlags: 4;                                           // 484:00
		std::int8_t raceSwitchPending: 1;                                    // 488:0
		std::int8_t soundCallBackSet;                                        // 489
		bool trespassing;                                                    // 48A
	};
	static_assert(sizeof(Actor) == 0x490);

	class ActorEquipManager :
		public BSTSingletonSDM<ActorEquipManager>,            // 00
		public BSTEventSource<ActorEquipManagerEvent::Event>  // 08
	{
	public:
		[[nodiscard]] static ActorEquipManager* GetSingleton()
		{
			REL::Relocation<ActorEquipManager**> singleton{ REL::ID(1174340) };
			return *singleton;
		}

		bool EquipObject(
			Actor* a_actor,
			const BGSObjectInstance& a_object,
			std::uint32_t a_stackID,
			std::uint32_t a_number,
			const BGSEquipSlot* a_slot,
			bool a_queueEquip,
			bool a_forceEquip,
			bool a_playSounds,
			bool a_applyNow,
			bool a_locked)
		{
			using func_t = decltype(&ActorEquipManager::EquipObject);
			REL::Relocation<func_t> func{ REL::ID(988029) };
			return func(this, a_actor, a_object, a_stackID, a_number, a_slot, a_queueEquip, a_forceEquip, a_playSounds, a_applyNow, a_locked);
		}

		bool UnequipObject(
			Actor* a_actor,
			const BGSObjectInstance* a_object,
			std::uint32_t a_number,
			const BGSEquipSlot* a_slot,
			std::uint32_t a_stackID,
			bool a_queueEquip,
			bool a_forceEquip,
			bool a_playSounds,
			bool a_applyNow,
			const BGSEquipSlot* a_slotBeingReplaced)
		{
			using func_t = decltype(&ActorEquipManager::UnequipObject);
			REL::Relocation<func_t> func{ REL::ID(1292493) };
			return func(this, a_actor, a_object, a_number, a_slot, a_stackID, a_queueEquip, a_forceEquip, a_playSounds, a_applyNow, a_slotBeingReplaced);
		}
	};
	static_assert(sizeof(ActorEquipManager) == 0x60);
}
