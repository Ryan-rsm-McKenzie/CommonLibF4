#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTTuple.h"

namespace RE
{
	class BGSObjectInstanceExtra;
	class BSExtraData;
	class ExtraLocation;
	class ExtraTextDisplayData;

	enum EXTRA_DATA_TYPE : std::uint32_t
	{
		kNone,  // BSExtraData
		kHavok,
		kCell3D,
		kWaterType,
		kRegionList,
		kSeenData,
		kEditorID,
		kCellMusicType,
		kSkyRegion,
		kCellMidLowProcess,
		kCellDetachTime,
		kPersistentCell,
		kKeywords,
		kAction,
		kStartingPosition,
		kAnim,
		kHavokAnim,
		kBiped,
		kUsedMarkers,
		kDistantData,
		kRagdollData,
		kCellPrevisRefs,
		kInitActions,
		kEssentialProtected,
		kPackagesStartLoc,
		kPackage,
		kTrespassPackage,
		kRunOncePackages,
		kReferenceHandle,
		kFollower,
		kLevCreaMod,
		kGhost,
		kOriginalReference,
		kOwnership,
		kGlobal,
		kRank,
		kCount,
		kHealth,
		kRangeDistOverride,
		kTimeLeft,
		kCharge,
		kLight,
		kLock,
		kTeleport,
		kMapMarker,
		kLeveledCreature,
		kLevelItem,
		kScale,
		kSeed,
		kMagicCaster,
		kMagicTarget,
		kMasterFileCell,
		kPlayerCrimeList,
		kObjectInstance,  // BGSObjectInstanceExtra
		kEnableStateParent,
		kEnableStateChildren,
		kItemDropper,
		kDroppedItemList,
		kTeleportMarker,
		kInactivePowerArmor,
		kSavedHavokData,
		kCannotWear,
		kPoison,
		kMagicLight,
		kLastFinishedSequence,
		kSavedAnimation,
		kNorthRotation,
		kSpawnCount,
		kFriendHits,
		kHeadTrackTarget,
		kBoundArmor,
		kRefractionProperty,
		kStartingWorldOrCell,
		kFavorite,
		kEditorRef3DData,
		kEditorRefMoveData,
		kInfoGeneralTopic,
		kNoRumors,
		kSound,
		kTerminalState,
		kLinkedRef,
		kLinkedRefChildren,
		kActivateRef,
		kActivateRefChildren,
		kTalkToPlayer,
		kObjectHealth,
		kImageSpace,
		kNavmeshPortal,
		kModelSwap,
		kRadius,
		kRadiation,
		kFactionChanges,
		kDismemberedLimbs,
		kActorCause,
		kMultibound,
		kMultiboundData,
		kMultiboundRef,
		kReflectedRefs,
		kReflectorRefs,
		kEmittanceSource,
		kRadioData,
		kCombatStyle,
		kLinkColorPair,
		kPrimitive,
		kOpenCloseActivateRef,
		kAnimNoteReceiver,
		kAmmo,
		kPatrolRefData,
		kPackageData,
		kOcclusionShape,
		kCollisionData,
		kSayOnceADayTopicInfo,
		kEncounterZone,
		kSayToTopicInfo,
		kOcclusionPlaneRefData,
		kPortalRefData,
		kPortal,
		kRoom,
		kGodRays,
		kRoomRefData,
		kGuardedRefData,
		kCreatureAwakeSound,
		kWaterZoneMap,
		kHorse,
		kIgnoredBySandbox,
		kCellAcousticSpace,
		kReservedMarkers,
		kCellTransCount,
		kWaterLightRefs,
		kLitWaterRefs,
		kRadioRepeater,
		kActivateLoopSound,
		kPatrolRefInUseData,
		kAshpileRef,
		kCreatureMovementSound,
		kFollowerSwimBreadcrumbs,
		kAliasInstanceArray,
		kLocation,  // ExtraLocation
		kMasterLocation,
		kLocationRefType,
		kPromotedRef,
		kAnimSequencer,
		kOutfitItem,
		kEditorLocation,
		kLeveledItemBase,
		kLightData,
		kScene,
		kBadPosition,
		kHeadTrackingWeight,
		kFromAlias,
		kShouldWear,
		kFavorCost,
		kAttachArrows3D,
		kTextDisplayData,  // ExtraTextDisplayData
		kAlphaCutoff,
		kEnchantment,
		kSoul,
		kForcedTarget,
		kSoundOutput,
		kUniqueID,
		kFlags,
		kRefrPath,
		kDecalGroup,
		kLockList,
		kForcedLandingMarker,
		kLargeRefOwnerCells,
		kCellWaterEnvMap,
		kCellGrassData,
		kTeleportName,
		kActorInteraction,
		kWaterData,
		kWaterCurrentZoneData,
		kAttachRef,
		kAttachRefChildren,
		kGroupConstraint,
		kScriptedAnimDependence,
		kCachedScale,
		kRaceData,
		kGIDBuffer,
		kMissingRefIDs,
		kBendableSplineParams,
		kReferenceGroup,
		kLayer,
		kMovementController,
		kReferenceCharacterController,
		kMaterialSwap,
		kInstanceData,
		kPowerArmor,
		kAcousticParent,
		kInputEnableLayer,
		kProjectedDecalRef,
		kWorkshop,
		kRadioReceiver,
		kCulledBone,
		kActorValueStorage,
		kDirectAtTarget,
		kActivateNext,
		kCellCombinedRefs,
		kObjectBreakable,
		kSavedDynamicIdles,
		kIgnoredAttractKeywords,
		kModRank,
		kInteriorLODWorldspace,
		kActorBoneScaleMap,
		kActorFXPickNodes,
		kPowerArmorPreload,
		kAnimGraphPreload,
		kAnimSounds,
		kPowerLinks,
		kSavedUnrecoverableSubgraphs,
		kRefWeaponSounds,
		kRefInvestedGold,
		kRefFurnitureEntryData,
		kVoiceType,

		kTotal
	};

	class BGSLocation;
	class BGSMessage;
	class TESBoundObject;
	class TESForm;
	class TESQuest;

	namespace BGSMod
	{
		struct ObjectIndexData;
	}

	class __declspec(novtable) BSExtraData
	{
	public:
		static constexpr auto RTTI{ RTTI::BSExtraData };
		static constexpr auto VTABLE{ VTABLE::BSExtraData };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kNone };

		virtual ~BSExtraData() = default;  // 00

		// add
		virtual bool CompareImpl([[maybe_unused]] const BSExtraData& a_compare) const { return false; }  // 01
		virtual bool CompareForUI(const BSExtraData* a_compare) const                                    // 02
		{
			if (a_compare && type == a_compare->type) {
				return CompareImpl(*a_compare);
			} else {
				return true;
			}
		}

		[[nodiscard]] EXTRA_DATA_TYPE GetExtraType() const noexcept { return *type; }

		// members
		BSExtraData* next;                                     // 08
		std::uint16_t flags;                                   // 10
		stl::enumeration<EXTRA_DATA_TYPE, std::uint8_t> type;  // 12
	};
	static_assert(sizeof(BSExtraData) == 0x18);

	class __declspec(novtable) BGSObjectInstanceExtra :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSObjectInstanceExtra };
		static constexpr auto VTABLE{ VTABLE::BGSObjectInstanceExtra };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kObjectInstance };

		[[nodiscard]] std::span<BGSMod::ObjectIndexData> GetIndexData() const noexcept;

		// members
		const BSTDataBuffer<1>* values;  // 18
		std::uint16_t itemIndex;         // 20
	};
	static_assert(sizeof(BGSObjectInstanceExtra) == 0x28);

	class __declspec(novtable) ExtraLocation :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraLocation };
		static constexpr auto VTABLE{ VTABLE::ExtraLocation };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kLocation };

		// members
		BGSLocation* location;  // 18
	};
	static_assert(sizeof(ExtraLocation) == 0x20);

	class __declspec(novtable) ExtraTextDisplayData :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraTextDisplayData };
		static constexpr auto VTABLE{ VTABLE::ExtraTextDisplayData };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kTextDisplayData };

		enum class DisplayDataType
		{
			kUninitialized = -1,
			kCustomName = -2
		};

		[[nodiscard]] const BSFixedStringCS& GetDisplayName(TESBoundObject* a_baseObject)
		{
			using func_t = decltype(&ExtraTextDisplayData::GetDisplayName);
			REL::Relocation<func_t> func{ REL::ID(1523343) };
			return func(this, a_baseObject);
		}

		// members
		BSFixedStringCS displayName;                                    // 18
		BGSMessage* displayNameText;                                    // 20
		TESQuest* ownerQuest;                                           // 28
		stl::enumeration<DisplayDataType, std::int32_t> ownerInstance;  // 30
		BSTArray<BSTTuple<BSFixedString, TESForm*>>* textPairs;         // 38
		std::uint16_t customNameLength;                                 // 40
	};
	static_assert(sizeof(ExtraTextDisplayData) == 0x48);

	class BaseExtraList
	{
	public:
		[[nodiscard]] BSExtraData* GetByType(EXTRA_DATA_TYPE a_type) const noexcept
		{
			if (HasType(a_type)) {
				for (auto iter = _head; iter; iter = iter->next) {
					if (iter->GetExtraType() == a_type) {
						return iter;
					}
				}
			}

			return nullptr;
		}

		[[nodiscard]] bool HasType(EXTRA_DATA_TYPE a_type) const noexcept
		{
			const auto idx = stl::to_underlying(a_type) / 8;
			const auto flags = GetFlags();
			if (!flags.empty() && idx < flags.size()) {
				const auto pos = 1 << (stl::to_underlying(a_type) % 8);
				return (flags[idx] & pos) != 0;
			} else {
				return false;
			}
		}

	private:
		static constexpr std::size_t N = (stl::to_underlying(EXTRA_DATA_TYPE::kTotal) / 8) + 1;

		void CreateFlags() { _flags = calloc<std::uint8_t>(N); }

		[[nodiscard]] std::span<std::uint8_t> GetFlags() const noexcept
		{
			if (_flags) {
				return { _flags, N };
			} else {
				return {};
			}
		}

		[[nodiscard]] std::span<std::uint8_t, N> GetOrCreateFlags()
		{
			if (!_flags) {
				CreateFlags();
			}

			return std::span{ reinterpret_cast<std::uint8_t(&)[N]>(*_flags) };
		}

		// members
		BSExtraData* _head{ nullptr };                 // 00
		BSExtraData** _tail{ std::addressof(_head) };  // 08
		std::uint8_t* _flags{ nullptr };               // 10
	};
	static_assert(sizeof(BaseExtraList) == 0x18);

	namespace detail
	{
		template <class T>
		concept ExtraDataListConstraint =
			std::derived_from<T, BSExtraData> &&
			!std::is_pointer_v<T> &&
			!std::is_reference_v<T>;
	}

	class ExtraDataList :
		public BSIntrusiveRefCounted  // 00
	{
	public:
		[[nodiscard]] BSExtraData* GetByType(EXTRA_DATA_TYPE a_type) const noexcept
		{
			BSAutoReadLock l{ _extraRWLock };
			return _extraData.GetByType(a_type);
		}

		template <detail::ExtraDataListConstraint T>
		[[nodiscard]] T* GetByType() const noexcept
		{
			return static_cast<T*>(GetByType(T::TYPE));
		}

		[[nodiscard]] bool HasType(EXTRA_DATA_TYPE a_type) const noexcept
		{
			BSAutoReadLock l{ _extraRWLock };
			return _extraData.HasType(a_type);
		}

		template <detail::ExtraDataListConstraint T>
		[[nodiscard]] bool HasType() const noexcept
		{
			return HasType(T::TYPE);
		}

	private:
		// members
		BaseExtraList _extraData;              // 08
		mutable BSReadWriteLock _extraRWLock;  // 20
	};
	static_assert(sizeof(ExtraDataList) == 0x28);
}
