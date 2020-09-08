#pragma once

#include "RE/Bethesda/AITimeStamp.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSPointerHandle.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTTuple.h"
#include "RE/Bethesda/IMovementInterface.h"
#include "RE/Bethesda/TESObjectREFRs.h"
#include "RE/NetImmerse/NiFlags.h"
#include "RE/NetImmerse/NiPoint3.h"

namespace RE
{
	enum class ACTOR_CRITICAL_STAGE;
	enum class ACTOR_LIFE_STATE;
	enum class ACTOR_LOS_LOCATION;
	enum class POWER_ATTACK_TYPE;
	enum class RESET_3D_FLAGS;
	enum class SIT_SLEEP_STATE;
	enum class WEAPON_STATE;

	template <class>
	class BSPointerHandleSmartPointer;

	class ActiveEffect;
	class ActiveEffectList;
	class ActorMagicCaster;
	class ActorMover;
	class AIProcess;
	class bhkCharacterController;
	class bhkCharacterMoveFinishEvent;
	class bhkCharacterStateChangeEvent;
	class bhkNonSupportContactEvent;
	class BipedAnim;
	class BSPathingRequest;
	class BSTransformDeltaEvent;
	class CombatController;
	class CombatGroup;
	class EffectItem;
	class MovementControllerNPC;
	class MovementMessageActorCollision;
	class MovementMessageNewPath;
	class MovementMessageUpdateRequestImmediate;
	class PackageLocation;
	class PerkEntryVisitor;

	struct ActorCPMEvent;
	struct ActorMotionFeedbackData;
	struct ActorMotionFeedbackOutput;
	struct BSMovementDataChangedEvent;
	struct BSSubGraphActivationUpdate;
	struct CastPowerItem;
	struct Perks;

	namespace MagicSystem
	{
		enum class CannotCastReason;
	}

	namespace PerkValueEvents
	{
		struct PerkValueChangedEvent;
		struct PerkEntryUpdatedEvent;
	}

	class MagicTarget
	{
	public:
		static constexpr auto RTTI{ RTTI::MagicTarget };
		static constexpr auto VTABLE{ VTABLE::MagicTarget };

		struct AddTargetData;
		struct SpellDispelData;

		// members
		virtual ~MagicTarget();	 // 00

		// add
		virtual bool AddTarget(AddTargetData& a_data);																																 // 01
		virtual TESObjectREFR* GetTargetStatsObject() { return nullptr; }																											 // 02
		virtual bool MagicTargetIsActor() { return false; }																															 // 03
		virtual bool IsInvulnerable() const { return false; }																														 // 04
		virtual void InvalidateCommandedActorEffect([[maybe_unused]] ActiveEffect* a_effect) { return; }																			 // 05
		virtual bool CanAddActiveEffect() const = 0;																																 // 06
		virtual ActiveEffectList* GetActiveEffectList() = 0;																														 // 07
		virtual float CheckResistance([[maybe_unused]] MagicItem* a_spell, [[maybe_unused]] EffectItem* a_effect, [[maybe_unused]] TESBoundObject* a_source) const { return 1.0F; }	 // 08
		virtual void EffectAdded([[maybe_unused]] ActiveEffect* a_effect) { return; }																								 // 09
		virtual void EffectRemoved([[maybe_unused]] ActiveEffect* a_effect) { return; }																								 // 0A
		virtual void EffectActiveStatusChanged([[maybe_unused]] ActiveEffect* a_effect) { return; }																					 // 0B
		virtual bool CheckAbsorb([[maybe_unused]] Actor* a_caster, [[maybe_unused]] MagicItem* a_spell, [[maybe_unused]] const EffectItem* a_effectItem) { return false; }			 // 0C

		// members
		SpellDispelData* postUpdateDispelList;	// 08
		std::int8_t flags;						// 10
	};
	static_assert(sizeof(MagicTarget) == 0x18);

	class ActorState :
		public IMovementState  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ActorState };
		static constexpr auto VTABLE{ VTABLE::ActorState };

		// add
		virtual bool SetWeaponMagicDrawn(bool a_drawn);				   // 21
		virtual bool SetWeaponState(WEAPON_STATE a_state);			   // 22
		virtual bool DoSetSitSleepState(SIT_SLEEP_STATE a_state) = 0;  // 23
		virtual SIT_SLEEP_STATE DoGetSitSleepState() const = 0;		   // 24
		virtual bool SetInIronSightsImpl(bool a_sighted) = 0;		   // 25
		virtual void SetReloadingImpl(bool a_reloading);			   // 26

		// members
		std::uint32_t moveMode : 14;			// 08:00
		std::uint32_t flyState : 3;				// 08:14
		std::uint32_t lifeState : 4;			// 08:17
		std::uint32_t knockState : 4;			// 08:21
		std::uint32_t meleeAttackState : 3;		// 08:25
		std::uint32_t talkingToPlayer : 1;		// 08:28
		std::uint32_t forceRun : 1;				// 08:29
		std::uint32_t forceSneak : 1;			// 08:30
		std::uint32_t headTracking : 1;			// 08:31
		std::uint32_t reanimating : 1;			// 0C:00
		std::uint32_t weaponState : 3;			// 0C:01
		std::uint32_t wantBlocking : 1;			// 0C:04
		std::uint32_t flightBlocked : 1;		// 0C:05
		std::uint32_t recoil : 2;				// 0C:06
		std::uint32_t allowFlying : 1;			// 0C:08
		std::uint32_t staggered : 1;			// 0C:09
		std::uint32_t inWrongProcessLevel : 1;	// 0C:10
		std::uint32_t stance : 3;				// 0C:11
		std::uint32_t gunState : 4;				// 0C:14
		std::uint32_t interactingState : 2;		// 0C:18
		std::uint32_t headTrackRotation : 1;	// 0C:20
		std::uint32_t inSyncAnim : 1;			// 0C:21
	};
	static_assert(sizeof(ActorState) == 0x10);

	class IPostAnimationChannelUpdateFunctor
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
		float modifiers[3];	 // 0
	};
	static_assert(sizeof(Modifiers) == 0xC);

	class ActorValueStorage
	{
	public:
		// members
		BSTArray<BSTTuple<std::uint32_t, float>> baseValues;	 // 00
		BSTArray<BSTTuple<std::uint32_t, Modifiers>> modifiers;	 // 18
		BSReadWriteLock avLock;									 // 30
	};
	static_assert(sizeof(ActorValueStorage) == 0x38);

	class Actor :
		public TESObjectREFR,											// 000
		public MagicTarget,												// 110
		public ActorState,												// 128
		public BSTEventSink<BSMovementDataChangedEvent>,				// 138
		public BSTEventSink<BSTransformDeltaEvent>,						// 140
		public BSTEventSink<BSSubGraphActivationUpdate>,				// 148
		public BSTEventSink<bhkCharacterMoveFinishEvent>,				// 150
		public BSTEventSink<bhkNonSupportContactEvent>,					// 158
		public BSTEventSink<bhkCharacterStateChangeEvent>,				// 160
		public IPostAnimationChannelUpdateFunctor,						// 168
		public BSTEventSource<MovementMessageUpdateRequestImmediate>,	// 170
		public BSTEventSource<PerkValueEvents::PerkValueChangedEvent>,	// 1C8
		public BSTEventSource<PerkValueEvents::PerkEntryUpdatedEvent>,	// 220
		public BSTEventSource<ActorCPMEvent>							// 278
	{
	public:
		static constexpr auto RTTI{ RTTI::Actor };
		static constexpr auto VTABLE{ VTABLE::Actor };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kACHR };

		// add
		virtual void PlayPickUpSound(TESBoundObject* a_boundObj, bool a_pickUp, bool a_use);																											 // 0C6
		virtual float GetHeading() const { return data.angle.z; }																																		 // 0C7
		virtual void SetAvoidanceDisabled([[maybe_unused]] bool a_tf) { return; }																														 // 0C8
		virtual void DrawWeaponMagicHands(bool a_draw);																																					 // 0C9
		virtual void SetPosition(const NiPoint3& a_pos, bool a_updateCharController);																													 // 0CA
		virtual void KillDying();																																										 // 0CB
		virtual void Resurrect(bool a_resetInventory, bool a_attach3D);																																	 // 0CC
		virtual bool PutActorInChairBedQuick(TESObjectREFR* a_furniture, std::uint32_t a_index);																										 // 0CD
		virtual bool PutActorOnMountQuick();																																							 // 0CE
		virtual void Update(float a_delta);																																								 // 0CF
		virtual void UpdateNoAI(float);																																									 // 0D0
		virtual void UpdateMotionDrivenState();																																							 // 0D1
		virtual void UpdateCharacterControllerSimulationSettings(bhkCharacterController& a_charController);																								 // 0D2
		virtual void PotentiallyFixRagdollState();																																						 // 0D3
		virtual void UpdateNonRenderSafe(float);																																						 // 0D4
		virtual bool ShouldHandleEquipNow() const;																																						 // 0D5
		virtual void SetCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::uint32_t a_value);																									 // 0D6
		virtual std::uint32_t ModCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::int32_t a_value);																							 // 0D7
		virtual void RemoveCrimeGoldValue(TESFaction* a_faction, bool a_violent, std::int32_t a_value);																									 // 0D8
		virtual std::uint32_t GetCrimeGoldValue(const TESFaction* a_faction) const;																														 // 0D9
		virtual void GoToPrison([[maybe_unused]] TESFaction* a_faction, [[maybe_unused]] bool a_removeItems, [[maybe_unused]] bool a_realJail) { return; }												 // 0DA
		virtual void ServePrisonTime() { return; }																																						 // 0DB
		virtual void PayFine([[maybe_unused]] TESFaction* a_faction, [[maybe_unused]] bool a_movetoMarker, [[maybe_unused]] bool a_removeStolenItems) { return; }										 // 0DC
		virtual float GetCurrentEyeLevel() const;																																						 // 0DD
		virtual void SetInDialoguewithPlayer(bool a_flag);																																				 // 0DE
		virtual bool GetCannibal() { return false; }																																					 // 0DF
		virtual void SetCannibal(bool) { return; }																																						 // 0E0
		virtual bool GetVampireFeed() { return false; }																																					 // 0E1
		virtual void SetVampireFeed(bool) { return; }																																					 // 0E2
		virtual void InitiateVampireFeedPackage(Actor* a_target, TESObjectREFR* a_furniture);																											 // 0E3
		virtual void InitiateCannibalPackage(Actor* a_target);																																			 // 0E4
		virtual float GetEyeHeading() const;																																							 // 0E5
		virtual void GetEyeAngles(float& a_eyeHeading, float& a_eyeLooking) const;																														 // 0E6
		virtual void GetEyeVector(NiPoint3& a_origin, NiPoint3& a_direction, bool a_includeCameraOffset) const;																							 // 0E7
		virtual void SetRefraction(bool a_enable, float a_refractionPower);																																 // 0E8
		virtual float GetAcrobatics() const { return 1.0F; }																																			 // 0E9
		virtual bool Get3DUpdateFlag(RESET_3D_FLAGS a_flag) const;																																		 // 0EA
		virtual ObjectRefHandle DropObject(const BGSObjectInstance& a_object, BSTSmallArray<std::uint32_t, 4>* a_stackData, std::int32_t a_number, const NiPoint3* a_point, const NiPoint3* a_rotate);	 // 0EB
		virtual void PickUpObject(TESObjectREFR* a_objREFR, std::int32_t a_count, bool a_playPickUpSounds);																								 // 0EC
		virtual void AttachArrow(const BSTSmartPointer<BipedAnim>& a_biped, BGSEquipIndex a_equipIndex);																								 // 0ED
		virtual void DetachArrow(const BSTSmartPointer<BipedAnim>& a_biped, BGSEquipIndex a_equipIndex);																								 // 0EE
		virtual bool ReloadWeapon(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, BGSEquipIndex a_equipIndex);																						 // 0EF
		virtual std::uint32_t UseAmmo(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, BGSEquipIndex a_equipIndex, std::uint32_t a_shotCount);														 // 0F0
		virtual bool CalculateCachedOwnerIsInCombatantFaction() const;																																	 // 0F1
		virtual CombatGroup* GetCombatGroup() const;																																					 // 0F2
		virtual void SetCombatGroup(CombatGroup* a_group);																																				 // 0F3
		virtual bool CheckValidTarget(TESObjectREFR& a_ref) const;																																		 // 0F4
		virtual bool InitiateDialogue(Actor* a_target, PackageLocation* a_packLoc, PackageLocation* a_packSecondLoc);																					 // 0F5
		virtual void EndDialogue();																																										 // 0F6
		virtual Actor* SetUpTalkingActivatorActor(Actor* a_target, Actor*& a_talkingactivator);																											 // 0F7
		virtual void InitiateFlee(TESObjectREFR* a_fleeRef, bool a_runonce, bool a_knows, bool a_combatMode, TESObjectCELL* a_cell, TESObjectREFR* a_ref, float a_fleeFromDist, float a_fleeToDist);	 // 0F8
		virtual void InitiateGetUpPackage();																																							 // 0F9
		virtual void PutCreatedPackage(TESPackage* a_pack, bool a_tempPack, bool a_isACreatedPackage, bool a_allowFromFurniture);																		 // 0FA
		virtual void UpdateAlpha();																																										 // 0FB
		virtual void SetAlpha(float a_newAlpha);																																						 // 0FC
		virtual float GetAlpha();																																										 // 0FD
		virtual bool IsInCombat() const;																																								 // 0FE
		virtual void UpdateCombat();																																									 // 0FF
		virtual void StopCombat();																																										 // 100
		virtual bool GetUsesAttackPercents() { return false; }																																			 // 101
		virtual std::uint8_t GetPowerAttackPercent(POWER_ATTACK_TYPE) { return 0; }																														 // 102
		virtual void WeaponSwingCallBack(BGSEquipIndex a_equipIndex);																																	 // 103
		virtual void SetActorStartingPosition();																																						 // 104
		virtual void SetLifeState(ACTOR_LIFE_STATE a_lifeState);																																		 // 105
		virtual bool HasBeenAttacked();																																									 // 106
		virtual void SetBeenAttacked(bool a_flag);																																						 // 107
		virtual void UseSkill(ActorValueInfo*, float, TESForm*) { return; }																																 // 108
		virtual bool IsAtPoint(const NiPoint3& a_point, float a_radius, bool a_expandRadius, bool a_alwaysTestHeight);																					 // 109
		virtual bool IsInFaction(const TESFaction* a_faction) const;																																	 // 10A
		virtual bool HasPerkEntries(std::uint8_t a_entryPoint) const;																																	 // 10B
		virtual void ForEachPerkEntry(std::uint8_t a_entryPoint, PerkEntryVisitor& a_visitor) const;																									 // 10C
		virtual void ApplyPerksFromBase();																																								 // 10D
		virtual void StartPowerAttackCoolDown() { return; }																																				 // 10E
		virtual bool IsPowerAttackCoolingDown() const { return false; }																																	 // 10F
		virtual void HandleHealthDamage(Actor* a_attacker, float a_damage);																																 // 110
		virtual bool QSpeakingDone() const;																																								 // 111
		virtual void SetSpeakingDone(bool a_done);																																						 // 112
		virtual NiPoint3 CalculateLOSLocation(ACTOR_LOS_LOCATION a_location) const;																														 // 113
		virtual void CreateMovementController();																																						 // 114
		virtual bool ShouldPivotToFaceCamera() const { return false; }																																	 // 115
		virtual BGSKeyword* GetSpeakingAnimArchType() { return speakingAnimArchType; }																													 // 116
		virtual void KillImpl(Actor* a_attacker, float a_damage, bool a_sendEvent, bool a_ragdollInstant);																								 // 117
		virtual void DoReparentWeapon(const TESObjectWEAP* a_weapon, BGSEquipIndex a_equipIndex, bool a_weaponDrawn);																					 // 118
		virtual bool DrinkPotion(AlchemyItem* a_potion, std::uint32_t a_stackID);																														 // 119
		virtual bool CheckCast(MagicItem* a_spell, bool a_dualCast, MagicSystem::CannotCastReason* a_reason);																							 // 11A
		virtual void CheckTempModifiers() { return; }																																					 // 11B
		virtual void SetLastRiddenMount(ActorHandle a_mount) { return; }																																 // 11C
		virtual ActorHandle QLastRiddenMount() const;																																					 // 11D
		virtual bool CalculateCachedOwnerIsUndead() const;																																				 // 11E
		virtual bool CalculateCachedOwnerIsNPC() const;																																					 // 11F
		virtual bool SetSneaking(bool a_sneaking);																																						 // 120
		virtual void ResetHavokPhysics();																																								 // 121
		virtual bool ShouldDoCharacterUpdate() const { return true; }																																	 // 122
		virtual bool GetAnimationCanBeInterpolated() const;																																				 // 123
		virtual const BSFixedString& GetResponseString() const;																																			 // 124
		virtual void ModifyMovementData(float a_delta, NiPoint3& a_moveDelta, NiPoint3& a_angleDelta);																									 // 125
		virtual void UpdateCombatControllerSettings();																																					 // 126
		virtual void UpdateFadeSettings(bhkCharacterController* a_charController);																														 // 127
		virtual bool ComputeMotionFeedbackSpeedAndDirection(const ActorMotionFeedbackData& a_data, float a_delta, ActorMotionFeedbackOutput& a_retData);												 // 128
		virtual bool UpdateFeedbackGraphSpeedAndDirection(const ActorMotionFeedbackOutput& a_data);																										 // 129
		virtual void UpdateActor3DPosition();																																							 // 12A
		virtual void PrecacheData();																																									 // 12B
		virtual void WornArmorChanged(const BGSObjectInstance& a_object);																																 // 12C
		virtual void ProcessTracking(float a_delta, NiAVObject* a_ob3D);																																 // 12D
		virtual void CreateActorMover();																																								 // 12E
		virtual void DestroyActorMover();																																								 // 12F
		virtual bool ShouldRespondToActorCollision(const MovementMessageActorCollision&, const BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<Actor, HandleManager>>& a_otherActor) const;	 // 130
		virtual float CheckClampDamageModifier(ActorValueInfo& a_info, float a_delta);																													 // 131
		virtual void ValidateNewPath([[maybe_unused]] const MovementMessageNewPath& a_newPathMessage) { return; }																						 // 132

		// members
		NiTFlags<std::uint32_t, Actor> niFlags;								 // 2D0
		float updateTargetTimer;											 // 2D4
		NiPoint3 editorLocCoord;											 // 2D8
		NiPoint3 editorLocRot;												 // 2E4
		TESForm* editorLocForm;												 // 2F0
		BGSLocation* editorLocation;										 // 2F8
		AIProcess* currentProcess;											 // 300
		ActorMover* actorMover;												 // 308
		BGSKeyword* speakingAnimArchType;									 // 310
		BSTSmartPointer<MovementControllerNPC> movementController;			 // 318
		TESPackage* initialPackage;											 // 320
		CombatController* combatController;									 // 328
		TESFaction* vendorFaction;											 // 330
		ActorValueStorage avStorage;										 // 338
		BGSDialogueBranch* exclusiveBranch;									 // 370
		stl::enumeration<ACTOR_CRITICAL_STAGE, std::int32_t> criticalStage;	 // 378
		ObjectRefHandle dialogueItemTarget;									 // 37C
		ActorHandle currentCombatTarget;									 // 380
		ActorHandle myKiller;												 // 384
		float checkMyDeadBodyTimer;											 // 388
		float voiceTimer;													 // 38C
		float voiceLengthTotal;												 // 390
		float underWaterTimer;												 // 394
		std::int32_t thiefCrimeStamp;										 // 398
		std::int32_t actionValue;											 // 39C
		float timeronAction;												 // 3A0
		AITimeStamp calculateVendorFactionTimer;							 // 3A4
		std::uint32_t intimidateBribeDayStamp;								 // 3A8
		float equippedWeight;												 // 3AC
		BSTSmallArray<SpellItem*> addedSpells;								 // 3B0
		ActorMagicCaster* magicCasters[4];									 // 3C8
		MagicItem* selectedSpell[4];										 // 3E8
		CastPowerItem* castPowerItems;										 // 408
		TESForm* selectedPower;												 // 410
		TESRace* race;														 // 418
		Perks* perks;														 // 420
		BSTSmartPointer<BipedAnim> biped;									 // 428
		BSNonReentrantSpinLock addingToOrRemovingFromScene;					 // 430
		BSReadWriteLock perkArrayLock;										 // 434
		std::uint32_t flags;												 // 43C
		std::uint32_t moreFlags;											 // 440
		Modifiers healthModifiers;											 // 444
		Modifiers actionPointsModifiers;									 // 450
		Modifiers staminaModifiers;											 // 45C
		Modifiers radsModifiers;											 // 468
		float lastUpdate;													 // 474
		std::uint32_t lastSeenTime;											 // 478
		float armorRating;													 // 47C
		float armorBaseFactorSum;											 // 480
		std::uint32_t visFlags : 4;											 // 484:00
		std::int8_t raceSwitchPending : 1;									 // 488:0
		std::int8_t soundCallBackSet;										 // 489
		bool trespassing;													 // 48A
	};
	static_assert(sizeof(Actor) == 0x490);
}
