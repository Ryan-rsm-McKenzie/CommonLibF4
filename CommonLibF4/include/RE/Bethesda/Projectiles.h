#pragma once

#include "RE/Bethesda/BSPointerHandle.h"
#include "RE/Bethesda/BSSoundHandle.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/CELLJobs.h"
#include "RE/Bethesda/TESObjectREFRs.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/NetImmerse/NiTransform.h"

namespace RE
{
	enum class COL_LAYER;
	enum class ImpactResult;

	namespace BGSBodyPartDefs
	{
		enum class LIMB_ENUM;
	}

	namespace MagicSystem
	{
		enum class CastingSource;
	}

	class ActorCause;
	class bhkNPCollisionObject;
	class BSMagicShaderParticles;
	class BSProceduralGeomEvent;
	class EffectSetting;
	class hknpShape;
	class NiAVObject;
	class NiLight;
	class NiNode;
	class QueuedFile;

	struct BeamProjectileImpactEvent;

	struct bhkCollisionQueryResultHandle
	{
	public:
		// members
		std::uint64_t data;  // 0
	};
	static_assert(sizeof(bhkCollisionQueryResultHandle) == 0x8);

	class __declspec(novtable) Projectile :
		public TESObjectREFR  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::Projectile };
		static constexpr auto VTABLE{ VTABLE::Projectile };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kREFR };

		struct ImpactCreation;

		class ImpactData
		{
		public:
			// members
			NiPoint3 location;                                                      // 00
			NiPoint3 normal;                                                        // 0C
			bhkCollisionQueryResultHandle impactDecalQuery;                         // 18
			ObjectRefHandle collidee;                                               // 20
			NiPointer<bhkNPCollisionObject> colObj;                                 // 28
			BGSMaterialType* materialType;                                          // 30
			stl::enumeration<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> damageLimb;  // 38
			stl::enumeration<COL_LAYER, std::int32_t> collisionLayer;               // 3C
			NiPointer<NiNode> closestBone;                                          // 40
			stl::enumeration<ImpactResult, std::int32_t> resultOverride;            // 48
			float decalSize;                                                        // 4C
			std::uint32_t collisionShapeKey;                                        // 50
			std::int16_t targetWorldObjectCount;                                    // 54
			std::int16_t targetWorldObjectIndex;                                    // 56
			bool processed;                                                         // 58
			bool spellCast;                                                         // 59
			bool effectSpawned;                                                     // 5A
			bool backface;                                                          // 5B
		};
		static_assert(sizeof(ImpactData) == 0x60);

		// add
		virtual bool IsMissileProjectile() const { return false; }                                                       // C6
		virtual bool IsGrenadeProjectile() const { return false; }                                                       // C7
		virtual bool IsFlameProjectile() const { return false; }                                                         // C8
		virtual bool IsBeamProjectile() const { return false; }                                                          // C9
		virtual bool IsFogProjectile() const { return false; }                                                           // CA
		virtual bool IsBarrierProjectile() const { return false; }                                                       // CB
		virtual void OnKill() { return; }                                                                                // CC
		virtual void Process3D() { return; }                                                                             // CD
		virtual void PostLoad3D(NiAVObject* a_obj3D);                                                                    // CE
		virtual void UpdateImpl(float a_delta) = 0;                                                                      // CF
		virtual bool ProcessImpacts();                                                                                   // D0
		virtual void Update3D(CELLJobs::AnimatedRefJobData* a_data);                                                     // D1
		virtual bool IsMine() const { return false; }                                                                    // D2
		virtual float GetPowerSpeedMult() const { return spell ? 1.0F : power; }                                         // D3
		virtual float GetWeaponSpeedMult() const { return 1.0F; }                                                        // D4
		virtual bool GetStopMainSoundAfterImpact() const { return false; }                                               // D5
		virtual void ReportHavokDeactivation() { return; }                                                               // D6
		virtual bool TurnOff(Actor* a_actionActor, bool a_silent);                                                       // D7
		virtual bool IsPermanent();                                                                                      // D8
		virtual float GetGravity() const;                                                                                // D9
		virtual void CleanUpPointersOnDisable();                                                                         // DA
		virtual bool RunTargetPick();                                                                                    // DB
		virtual bool GetKillOnCollision() const { return true; }                                                         // DC
		virtual bool ShouldBeLimited() const { return false; }                                                           // DD
		virtual bool TargetsWholeBody() const { return false; }                                                          // DE
		virtual bool GetAllowMovement() const;                                                                           // DF
		virtual std::uint32_t GetCollisionGroup() const;                                                                 // E0
		virtual hknpShape* GetCollisionShape();                                                                          // E1
		virtual void InitializeImpl() { return; }                                                                        // E2
		virtual void Relaunch() { return; }                                                                              // E3
		virtual std::uint32_t AddImpact(const ImpactCreation& a_data);                                                   // E4
		virtual bool HandleHits(const hknpAllHitsCollector& a_collector, const NiPoint3& a_from, const NiPoint3& a_to);  // E5
		virtual void OnEnterTrigger() { return; }                                                                        // E6
		virtual void AddInitialVelocity();                                                                               // E7
		virtual void Handle3DLoaded() { return; }                                                                        // E8
		virtual bool ShouldUseDesiredTarget() { return false; }                                                          // E9

		// members
		BSTArray<ImpactData> impacts;                                              // 110
		NiTransform followOffset;                                                  // 130
		NiPointer<bhkNPCollisionObject> collisionObject;                           // 170
		NiPointer<TESObjectREFR> droppedRefr;                                      // 178
		NiPoint3 movementDirection;                                                // 180
		NiPoint3 velocity;                                                         // 18C
		NiPointer<NiLight> light;                                                  // 198
		NiPointer<ActorCause> actorCause;                                          // 1A0
		ObjectRefHandle shooter;                                                   // 1A8
		ObjectRefHandle desiredTarget;                                             // 1AC
		BSSoundHandle sndHandle;                                                   // 1B0
		BSSoundHandle sndCountdown;                                                // 1B8
		BGSExplosion* explosion;                                                   // 1C0
		MagicItem* spell;                                                          // 1C8
		stl::enumeration<MagicSystem::CastingSource, std::int32_t> castingSource;  // 1D0
		EffectSetting* avEffect;                                                   // 1D8
		NiPointer<QueuedFile> projectileDBFiles;                                   // 1E0
		void* muzzleFlashDBHandle;                                                 // 1E8 - TODO
		NiPointer<NiNode> muzzleFlashArt;                                          // 1F0
		BSMagicShaderParticles* particles;                                         // 1F8
		stl::enumeration<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> targetLimb;     // 200
		NiPointer<NiAVObject> targetLimbObj;                                       // 208
		NiAVObject* clonePoolKey;                                                  // 210
		float power;                                                               // 218
		float speedMult;                                                           // 21C
		float range;                                                               // 220
		float age;                                                                 // 224
		float damage;                                                              // 228
		float alpha;                                                               // 22C
		float explosionTimer;                                                      // 230
		float blinkTimer;                                                          // 234
		BGSObjectInstanceT<TESObjectWEAP> weaponSource;                            // 238
		TESAmmo* ammoSource;                                                       // 248
		BGSEquipIndex equipIndex;                                                  // 250
		float distanceMoved;                                                       // 254
		float movementDelta;                                                       // 258
		float scale;                                                               // 25C
		std::uint64_t flags;                                                       // 260
		bool artRequested;                                                         // 268
		bool animationsLoaded;                                                     // 269
	};
	static_assert(sizeof(Projectile) == 0x270);

	class __declspec(novtable) MissileProjectile :
		public Projectile  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::MissileProjectile };
		static constexpr auto VTABLE{ VTABLE::MissileProjectile };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kPMIS };

		// add
		virtual bool ShouldReorient() const;  // EA

		// members
		NiMatrix3 dismemberedLimbRotation;                          // 270
		NiPoint3 dismemberedLimbOffset;                             // 2A0
		NiPointer<bhkNPCollisionObject> modelCollision;             // 2B0
		stl::enumeration<ImpactResult, std::int32_t> impactResult;  // 2B8
		bool waitingToInitialize3D;                                 // 2BC
		bool deferProcessImpale;                                    // 2BD
	};
	static_assert(sizeof(MissileProjectile) == 0x2C0);

	class __declspec(novtable) ArrowProjectile :
		public MissileProjectile  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::ArrowProjectile };
		static constexpr auto VTABLE{ VTABLE::ArrowProjectile };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kPARW };

		// members
		AlchemyItem* poison;  // 2C0
	};
	static_assert(sizeof(ArrowProjectile) == 0x2D0);

	class __declspec(novtable) GrenadeProjectile :
		public Projectile  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::GrenadeProjectile };
		static constexpr auto VTABLE{ VTABLE::GrenadeProjectile };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kPGRE };

		// members
		BGSDecalGroup* decalGroup;  // 270
		bool collisionGroupReset;   // 278
	};
	static_assert(sizeof(GrenadeProjectile) == 0x280);

	class ProjectileLaunchData
	{
	public:
		// members
		NiPoint3 origin;                                                           // 00
		NiPoint3 contactNormal;                                                    // 0C
		BGSProjectile* projectileBase;                                             // 18
		TESObjectREFR* shooter;                                                    // 20
		CombatController* shooterCombatController;                                 // 28
		BGSObjectInstanceT<TESObjectWEAP> fromWeapon;                              // 30
		TESAmmo* fromAmmo;                                                         // 40
		BGSEquipIndex equipIndex;                                                  // 48
		float zAngle;                                                              // 4C
		float xAngle;                                                              // 50
		float yAngle;                                                              // 54
		TESObjectREFR* homingTarget;                                               // 58
		TESObjectCELL* parentCell;                                                 // 60
		MagicItem* spell;                                                          // 68
		stl::enumeration<MagicSystem::CastingSource, std::int32_t> castingSource;  // 70
		AlchemyItem* poison;                                                       // 78
		std::int32_t area;                                                         // 80
		float power;                                                               // 84
		float scale;                                                               // 88
		float coneOfFireRadiusMult;                                                // 8C
		stl::enumeration<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> targetLimb;     // 90
		bool alwaysHit;                                                            // 94
		bool noDamageOutsideCombat;                                                // 95
		bool autoAim;                                                              // 96
		bool useOrigin;                                                            // 97
		bool deferInitialization;                                                  // 98
		bool tracer;                                                               // 99
		bool forceConeOfFire;                                                      // 9A
		bool intentionalMiss;                                                      // 9B
		bool allow3D;                                                              // 9C
		bool penetrates;                                                           // 9D
		bool ignoreNearCollisions;                                                 // 9E
	};
	static_assert(sizeof(ProjectileLaunchData) == 0xA0);

	class __declspec(novtable) BeamProjectile :
		public Projectile,                                 // 000
		public BSTEventSource<BeamProjectileImpactEvent>,  // 278
		public BSTEventSink<BSProceduralGeomEvent>         // 270
	{
	public:
		static constexpr auto RTTI{ RTTI::BeamProjectile };
		static constexpr auto VTABLE{ VTABLE::BeamProjectile };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kPBEA };

		// members
		ProjectileLaunchData launchData;           // 2D0
		bhkCollisionQueryResultHandle castResult;  // 370
		float baseModelLength;                     // 378
		bool transformSet;                         // 37C
		bool queueUncull;                          // 37D
		bool dealtDamage;                          // 37E
	};
	static_assert(sizeof(BeamProjectile) == 0x380);

	class __declspec(novtable) FlameProjectile :
		public Projectile  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::FlameProjectile };
		static constexpr auto VTABLE{ VTABLE::FlameProjectile };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kPFLA };

		// members
		float expirationTimer;  // 270
		float coneAngle;        // 274
	};
	static_assert(sizeof(FlameProjectile) == 0x280);

	class __declspec(novtable) ConeProjectile :
		public Projectile  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::ConeProjectile };
		static constexpr auto VTABLE{ VTABLE::ConeProjectile };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kPCON };

		// members
		float expirationTimer;  // 270
		float coneAngle;        // 274
	};
	static_assert(sizeof(ConeProjectile) == 0x280);

	class __declspec(novtable) BarrierProjectile :
		public Projectile  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::BarrierProjectile };
		static constexpr auto VTABLE{ VTABLE::BarrierProjectile };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kPBAR };

		struct CollisionData
		{
		public:
			// members
			ObjectRefHandle ref;  // 0
			std::uint32_t count;  // 4
		};
		static_assert(sizeof(CollisionData) == 0x8);

		// members
		float width;                            // 270
		BSTArray<CollisionData> collisionData;  // 278
	};
	static_assert(sizeof(BarrierProjectile) == 0x290);
}
