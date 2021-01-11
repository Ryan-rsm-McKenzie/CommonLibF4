#pragma once

#include "RE/Bethesda/AITimeStamp.h"
#include "RE/Bethesda/Actor.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSPointerHandle.h"
#include "RE/Bethesda/BSSoundHandle.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTList.h"
#include "RE/Bethesda/BSTOptional.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTTuple.h"
#include "RE/Bethesda/IMovementInterface.h"
#include "RE/Havok/hkRefPtr.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/NetImmerse/NiTMap.h"

namespace RE
{
	enum class COMMAND_TYPE;
	enum class DEFAULT_OBJECT;
	enum class PLAYER_ACTION;
	enum class QUEST_OBJECTIVE_STATE;
	enum class SCENE_ACTION_PLAYER_RESPONSE_TYPE;

	class BGSQuestObjective;
	class BipedAnim;
	class BSLight;
	class BSPathingSolution;
	class Crime;
	class DialoguePackage;
	class DoorTeleportData;
	class EffectSetting;
	class hknpBSMouseSpringAction;
	class ImageSpaceModifierInstanceDOF;
	class ImageSpaceModifierInstanceForm;
	class MenuModeChangeEvent;
	class MenuOpenCloseEvent;
	class NiAVObject;
	class NiLight;
	class NiNode;
	class OtherEventEnabledEvent;
	class QuestTargetArray;
	class TeleportPath;
	class TESHitEvent;
	class TESQuestStageItem;
	class UserEventEnabledEvent;

	struct BGSActorCellEvent;
	struct BGSActorDeathEvent;
	struct ItemChange;
	struct PickRefUpdateEvent;
	struct PositionPlayerEvent;

	namespace BGSCharacterTint
	{
		class Entries;
	}

	namespace PerkValueEvents
	{
		struct PerkEntryUpdatedEvent;
	}

	struct CrimeGoldStruct
	{
	public:
		// members
		std::uint32_t violent;                     // 00
		std::uint32_t nonViolent;                  // 04
		std::uint32_t totalNonViolentAccumulated;  // 08
		std::uint32_t totalViolentAccumulated;     // 0C
	};
	static_assert(sizeof(CrimeGoldStruct) == 0x10);

	struct StolenItemValueStruct
	{
	public:
		// members
		std::uint32_t stolenItemValueNoCrime;  // 0
		std::uint32_t istolenItemValueCrime;   // 4
	};
	static_assert(sizeof(StolenItemValueStruct) == 0x8);

	struct PlayerCoverData
	{
	public:
		enum class PEEK_STATE;

		// members
		NiPoint3 coverLocation;                                // 00
		NiPoint3 peekLocation;                                 // 0C
		float peekTimer;                                       // 18
		float updateTimer;                                     // 2C
		float blockedTimer;                                    // 20
		stl::enumeration<PEEK_STATE, std::int32_t> peekState;  // 24
		bool gunBlocked;                                       // 28
	};
	static_assert(sizeof(PlayerCoverData) == 0x2C);

	struct FriendshipFactionsStruct
	{
	public:
		// members
		std::uint16_t friendCounts[4];  // 0
	};
	static_assert(sizeof(FriendshipFactionsStruct) == 0x8);

	class BGSInstancedQuestObjective
	{
	public:
		// members
		BGSQuestObjective* objective;                                         // 00
		std::uint32_t instanceID;                                             // 08
		stl::enumeration<QUEST_OBJECTIVE_STATE, std::int32_t> enstanceState;  // 0C
	};
	static_assert(sizeof(BGSInstancedQuestObjective) == 0x10);

	struct SayOnceTimeStampStruct
	{
	public:
		// members
		std::uint32_t date;  // 0
		float hour;          // 4
	};
	static_assert(sizeof(SayOnceTimeStampStruct) == 0x8);

	struct PLAYER_TARGET_LOC
	{
	public:
		using ArrivalFunc_t = void(void*);

		// members
		TESWorldSpace* world;              // 00
		TESObjectCELL* interior;           // 08
		DoorTeleportData* transitionTel;   // 10
		NiPoint3 location;                 // 18
		NiPoint3 angle;                    // 24
		TESObjectREFR* walkThroughDoor;    // 30
		ArrivalFunc_t* arrivalFunc;        // 38
		void* arrivalFuncData;             // 40
		ObjectRefHandle furnitureRef;      // 48
		ObjectRefHandle fastTravelMarker;  // 4C
		float fastTravelDist;              // 50
		bool resetWeather;                 // 54
		bool allowAutoSave;                // 55
		bool preventLoadMenu;              // 56
		bool skyTransition;                // 57
		bool isValid;                      // 58
	};
	static_assert(sizeof(PLAYER_TARGET_LOC) == 0x60);

	class PlayerCommandTypeEvent :
		public BSTValueEvent<COMMAND_TYPE>  // 0
	{
	public:
	};
	static_assert(sizeof(PlayerCommandTypeEvent) == 0x8);

	class PlayerAutoAimActorEvent :
		public BSTValueEvent<ActorHandle>  // 0
	{
	public:
	};
	static_assert(sizeof(PlayerAutoAimActorEvent) == 0x8);

	struct XPChangeData
	{
	public:
		// members
		std::uint32_t playerLevel;      // 00
		float initialExperiencePoints;  // 04
		float experiencePointsAdded;    // 08
		bool syncedXP;                  // 0C
	};
	static_assert(sizeof(XPChangeData) == 0x10);

	class __declspec(novtable) PlayerCharacter :
		public Actor,                                                 // 000
		public BSTEventSource<BGSActorCellEvent>,                     // 4C8
		public BSTEventSource<BGSActorDeathEvent>,                    // 520
		public BSTEventSource<PositionPlayerEvent>,                   // 578
		public BSTEventSource<PickRefUpdateEvent>,                    // 5D0
		public BSTEventSink<MenuOpenCloseEvent>,                      // 490
		public BSTEventSink<MenuModeChangeEvent>,                     // 498
		public BSTEventSink<UserEventEnabledEvent>,                   // 4A0
		public BSTEventSink<OtherEventEnabledEvent>,                  // 4A8
		public BSTEventSink<TESHitEvent>,                             // 4B0
		public BSTEventSink<PerkValueEvents::PerkEntryUpdatedEvent>,  // 4B8
		public IMovementPlayerControlsFilter                          // 4C0
	{
	public:
		static constexpr auto RTTI{ RTTI::PlayerCharacter };
		static constexpr auto VTABLE{ VTABLE::PlayerCharacter };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kACHR };

		enum class GrabbingType;

		struct PlayerActionObject
		{
		public:
			// members
			float timer;                                         // 0
			ObjectRefHandle refObj;                              // 4
			stl::enumeration<PLAYER_ACTION, std::int32_t> next;  // 8
		};
		static_assert(sizeof(PlayerActionObject) == 0xC);

		// add
		virtual void InitiateSpectator(Actor*) { return; }                               // 133
		virtual std::uint32_t GetViolentCrimeGoldValue(const TESFaction* a_faction);     // 134
		virtual std::uint32_t GetNonViolentCrimeGoldValue(const TESFaction* a_faction);  // 135
		virtual void ClearAllCrimeGold(TESFaction* a_faction);                           // 136

		[[nodiscard]] static PlayerCharacter* GetSingleton()
		{
			REL::Relocation<NiPointer<PlayerCharacter>*> singleton{ REL::ID(303410) };
			return singleton->get();
		}

		// members
		BSSpinLock actorToDisplayOnHUDLock;                                                     // 628
		BSSpinLock questTargetLock;                                                             // 630
		BSTHashMap<const TESFaction*, CrimeGoldStruct> crimeGoldMap;                            // 638
		BSTHashMap<const TESFaction*, StolenItemValueStruct> stolenItemValueMap;                // 668
		PlayerCoverData coverData;                                                              // 698
		ObjectRefHandle commandWaitMarker;                                                      // 6C4
		BSTHashMap<const TESFaction*, FriendshipFactionsStruct> factionOwnerFriendsMap;         // 6C8
		NiPoint3A lastKnownGoodPosition;                                                        // 700
		NiPoint3A lastKnownGoodNavmeshPosition;                                                 // 710
		NiPoint3 bulletAutoAim;                                                                 // 720
		NiPoint3 cachedVelocity;                                                                // 72C
		BSTArray<ObjectRefHandle> currentMapMarkers;                                            // 738
		BSTArray<BSTTuple<NiPoint3, AITimeStamp>> velocityArray;                                // 750
		BSTArray<ProjectileHandle> runesCast;                                                   // 768
		BSTArray<TESImageSpaceModifier*> animationImageSpaceModifiers;                          // 78-
		BSTArray<ImageSpaceModifierInstanceForm*> animationImageSpaceInstances;                 // 798
		BSTArray<BSTTuple<NiPointer<NiLight>, bool>> playerLights;                              // 7B0
		BSSimpleList<TESQuestStageItem*> questLog;                                              // 7C8
		BSTArray<BGSInstancedQuestObjective> objectives;                                        // 7D9
		BSTHashMap<TESQuest*, QuestTargetArray*> questTargets;                                  // 7F0
		BSTHashMap<std::uint32_t, SayOnceTimeStampStruct> currentSayOnceInfosMap;               // 820
		BSTHashMap<std::uint32_t, SayOnceTimeStampStruct> currentSpeechRepeatMap;               // 850
		BSSimpleList<ObjectRefHandle> droppedRefList;                                           // 880
		NiTMap<std::uint32_t, std::uint8_t> randomDoorSpaceMap;                                 // 890
		TESWorldSpace* cachedWorldspace;                                                        // 8B0
		NiPoint3 exteriorPosition;                                                              // 8B8
		BSTSmallArray<SubgraphHandle, 2> pipboyAnimSubGraph;                                    // 8C8
		PLAYER_TARGET_LOC queuedTargetLoc;                                                      // 8E8
		PLAYER_TARGET_LOC queuedFlightLoc;                                                      // 948
		NiPoint3A flightGridCenter;                                                             // 9B0
		BSPathingSolution* flightMountPathingSolution;                                          // 9C0
		const TESObjectCELL* flightMountPreloadCell;                                            // 9C8
		BSSoundHandle magicFailureSound;                                                        // 9D0
		BSTArray<std::uint32_t> rumorTopicInfoList;                                             // 9D8
		std::uint32_t testChallangeInfoID;                                                      // 9F0
		DialoguePackage* closestConversation;                                                   // 9F8
		DialoguePackage* aiConversationRunning;                                                 // A00
		std::int32_t numberofStealWarnings;                                                     // A08
		float stealWarningTimer;                                                                // A0C
		std::int32_t numberofPickpocketWarnings;                                                // A10
		float pickPocketWarningTimer;                                                           // A14
		AITimeStamp warnToLeaveTimeStamp;                                                       // A18
		AITimeStamp usingTeleportDoorTimeStamp;                                                 // A1C
		NiPointer<ImageSpaceModifierInstanceDOF> ironsightsDOFInstance;                         // A20
		TESFaction* currentPrisonFaction;                                                       // A28
		std::uint32_t jailSentence;                                                             // A30
		NiPointer<NiAVObject> autoAimDebugSphere;                                               // A38
		BGSNote* currHolotape;                                                                  // A40
		BSSoundHandle soundHand;                                                                // A48
		std::int32_t vampireFeedDetection;                                                      // A50
		std::uint32_t mapMarkerIterator;                                                        // A54
		ObjectRefHandle forceActivateRef;                                                       // A58
		ObjectRefHandle loopingActivateRef;                                                     // A5C
		std::uint32_t dialogueCameraLastSceneID;                                                // A60
		PlayerActionObject playerActionObjects[15];                                             // A64
		stl::enumeration<PLAYER_ACTION, std::int32_t> mostRecentAction;                         // B18
		ActorHandle actorDoingPlayerCommand;                                                    // B1C
		BSTValueEventSource<PlayerCommandTypeEvent> playerCurrentCommandType;                   // B20
		BSTArray<hkRefPtr<hknpBSMouseSpringAction>> grabSprings;                                // B38
		NiPoint3 grabUserRotation;                                                              // B50
		ObjectRefHandle grabbedObject;                                                          // B5C
		float grabObjectWeight;                                                                 // B60
		float grabDistance;                                                                     // B64
		std::uint32_t secondsToSleepPerUpdate;                                                  // B68
		std::uint32_t sleepSeconds;                                                             // B6C
		BSTSmartPointer<BipedAnim> firstPersonBipedAnim;                                        // B70
		NiPointer<NiNode> firstPerson3D;                                                        // B78
		NiAVObject* firstPersonTorso;                                                           // B80
		NiAVObject* firstPersonEye;                                                             // B88
		float eyeHeight;                                                                        // B90
		float greetTimer;                                                                       // B94
		float encumberedTimer;                                                                  // B98
		float powerAttackTimer;                                                                 // B9C
		float autoReloadTimer;                                                                  // BA0
		float pivotToFaceCamera;                                                                // BA4
		std::int32_t hourstosleep;                                                              // BA8
		std::int32_t amountStolenSold;                                                          // BAC
		std::uint32_t valueStolen;                                                              // BB0
		ActorHandle lastRiddenMount;                                                            // BB4
		ActorHandle lightTarget;                                                                // BB8
		float sortActorDistanceTimer;                                                           // BBC
		float sitHeadingDelta;                                                                  // BC0
		ObjectRefHandle playerMapMarker;                                                        // BC4
		TeleportPath* playerMarkerPath;                                                         // BC8
		std::uint32_t skillTrainingsThisLevel;                                                  // BD0
		TESClass* defaultClass;                                                                 // BD8
		std::uint32_t crimeCounts[7];                                                           // BE0
		AlchemyItem* pendingPoison;                                                             // C00
		std::time_t lastPlayingTimeUpdate;                                                      // C08
		std::time_t totalPlayingTime;                                                           // C10
		std::uint32_t characterSeed;                                                            // C18
		TESForm* lastKnownGoodLocation;                                                         // C20
		NiPointer<BSLight> firstPersonLight;                                                    // C28
		NiPointer<BSLight> thirdPersonLight;                                                    // C30
		NiPointer<BSLight> pipboyLight;                                                         // C38
		NiPointer<NiLight> niPipboyLight;                                                       // C40
		float dropAngleMod;                                                                     // C48
		float lastDropAngleMod;                                                                 // C4C
		BSTValueEventSource<PlayerAutoAimActorEvent> autoAimActor;                              // C50
		ObjectRefHandle homingTarget;                                                           // C68
		float homingTargetTimer;                                                                // C6C
		NiPointer<NiAVObject> targeted3D;                                                       // C70
		CombatGroup* combatGroup;                                                               // C78
		BSTArray<ActorHandle> actorsToDisplayOnTheHUD;                                          // C80
		BSTArray<EquippedItem> lastOneHandItems;                                                // C98
		std::uint32_t teammateCount;                                                            // CB0
		float combatTimer;                                                                      // CB4
		float yieldTimer;                                                                       // CB8
		float chaseTimer;                                                                       // CBC
		float drawSheatheSafetyTimer;                                                           // CC0
		std::uint32_t activeCombatantCount;                                                     // CC4
		BGSLocation* currentLocation;                                                           // CC8
		AITimeStamp cachedVelocityTimeStamp;                                                    // CD0
		float telekinesisDistance;                                                              // CD4
		float commandTimer;                                                                     // CD8
		float dialogueCameraChangeRate;                                                         // CDC
		float fireWeaponEventTimer;                                                             // CE0
		stl::enumeration<DEFAULT_OBJECT, std::int32_t> animationObjectAction;                   // CE4
		stl::enumeration<GrabbingType, std::int32_t> grabType;                                  // CE8
		ActorHandle assumedIdentity;                                                            // CEC
		std::int8_t murder;                                                                     // CF0
		std::int8_t perkCount;                                                                  // CF1
		std::int8_t byCharGenFlag;                                                              // CF2
		Crime* resistArrestCrime;                                                               // CF8
		BGSCharacterTint::Entries* tintingData;                                                 // D00
		BGSTextureSet* complexion;                                                              // D08
		TESRace* charGenRace;                                                                   // D10
		EffectSetting* currentAlchemyEffect;                                                    // D18
		ItemChange* currentTemperingInventoryItem;                                              // D20
		TESObjectREFR* commandTarget;                                                           // D28
		TESObjectREFR* walkThroughDoor;                                                         // D30
		stl::enumeration<COMMAND_TYPE, std::int32_t> currentCommand;                            // D38
		stl::enumeration<SCENE_ACTION_PLAYER_RESPONSE_TYPE, std::int32_t> playerDialogueInput;  // D3C
		ActorValueInfo* stimpakTarget;                                                          // D40
		float vatsCriticalCharge;                                                               // D48
		std::uint32_t vatsCriticalCount;                                                        // D4C
		std::uint32_t maxVATSCriticalCount;                                                     // D50
		float timeBlendingOutFirstPersonOffset;                                                 // D54
		ActorHandle lastMagnetismActor;                                                         // D58
		NiPoint3 magnetismActorPos;                                                             // D5C
		ObjectRefHandle workstationBeingLeft;                                                   // D68
		ActorHandle actorLeavingWorkstation;                                                    // D6C
		BGSScene* allowDialogueCameraScene;                                                     // D70
		ActorHandle helloActor;                                                                 // D78
		TESObjectREFR* weaponAmmoRef;                                                           // D80
		std::int32_t equippingAmmoCount;                                                        // D88
		float dialogueCameraResumeTimer;                                                        // D8C
		ObjectRefHandle lastUsedPowerArmor;                                                     // D90
		TeleportPath* lastUsedPowerArmorMarkerPath;                                             // D98
		TESObjectWEAP* lastUsedThrownWeapon;                                                    // DA0
		BSSoundHandle powerArmorInteriorSoundHandle;                                            // DA8
		BSTArray<BSTTuple<ObjectRefHandle, float>> lockedTerminals;                             // DB0
		BSTArray<BSTTuple<std::int32_t, std::int32_t>> boneMapping1stTo3rd;                     // DC8
		BSTOptional<XPChangeData> syncedXPChange;                                               // DE0
		std::int32_t queuedSwitch: 1;                                                           // DF4:00
		std::uint32_t charGenHUDMode;                                                           // DF8
		bool insideMemoryHUDMode: 1;                                                            // DFC:0
		bool xpSyncedWithHUDNotification: 1;                                                    // DFC:1
		bool travelUseDoor: 1;                                                                  // DFC:2
		bool transporting: 1;                                                                   // DFC:3
		bool overAutoAimTarget: 1;                                                              // DFC:4
		bool showQuestItemsInInventory: 1;                                                      // DFC:5
		bool hostileDetection: 1;                                                               // DFC:6
		bool escaping: 1;                                                                       // DFC:7
		bool forceQuestTargetRepath: 1;                                                         // DFD:0
		bool speaking: 1;                                                                       // DFD:1
		bool isSleeping: 1;                                                                     // DFD:2
		bool actorinSneakRange: 1;                                                              // DFD:3
		bool greetingPlayer: 1;                                                                 // DFD:4
		bool beenAttacked: 1;                                                                   // DFD:5
		bool allowEGMCacheClear: 1;                                                             // DFD:6
		bool aiControlledToPos: 1;                                                              // DFD:7
		bool aiControlledFromPos: 1;                                                            // DFE:0
		bool aiControlledPackage: 1;                                                            // DFE:1
		bool returnToLastKnownGoodPosition: 1;                                                  // DFE:2
		bool beingChased: 1;                                                                    // DFE:3
		bool is3rdPersonModelShown: 1;                                                          // DFE:4
		bool hideFirstPersonGeometry: 1;                                                        // DFE:5
		bool insufficientChargeMessageShownL: 1;                                                // DFE:6
		bool insufficientChargeMessageShownR: 1;                                                // DFE:7
		bool target3DDistant: 1;                                                                // DFF:0
		bool playerInCombat: 1;                                                                 // DFF:1
		bool attemptedYieldInCurrentCombat: 1;                                                  // DFF:2
		bool currentAlchemyIsPoison: 1;                                                         // DFF:3
		bool positioning: 1;                                                                    // DFF:4
		bool crimeReporting: 1;                                                                 // DFF:5
		bool healthTutorialShown: 1;                                                            // DFF:6
		bool magickaTutorialShown: 1;                                                           // DFF:7
		bool staminaTutorialShown: 1;                                                           // E00:0
		bool goToJailQueued: 1;                                                                 // E00:1
		bool doorAutosaveQueued: 1;                                                             // E00:2
		bool sprintToggled: 1;                                                                  // E00:3
		bool useHighSpeedLoading: 1;                                                            // E00:4
		bool sceneActionActive: 1;                                                              // E00:5
		bool sayingHello: 1;                                                                    // E00:6
		bool disabledRadio: 1;                                                                  // E00:7
		bool updateAutoAimActor: 1;                                                             // E01:0
		bool autoReload: 1;                                                                     // E01:1
		bool usingScopeWithOverlay: 1;                                                          // E01:2
		bool steadyingWeapon: 1;                                                                // E01:3
		bool speechChallengeReward: 1;                                                          // E01:4
		bool blendOutFirstPersonOffset: 1;                                                      // E01:5
		bool dialogueCameraConsiderResume: 1;                                                   // E01:6
		bool shouldFollowerSupressIdleChatter: 1;                                               // E01:7
		bool idleChatter: 1;                                                                    // E02:0
		bool switchingPerspectives: 1;                                                          // E02:1
		bool onElevator: 1;                                                                     // E02:2
		bool sayCommandResponse: 1;                                                             // E02:3
		bool inLooksMenu: 1;                                                                    // E02:4
		bool playingTimeFrozen: 1;                                                              // E02:5
		bool everModded: 1;                                                                     // E02:6
	};
	static_assert(sizeof(PlayerCharacter) == 0xE10);
}
