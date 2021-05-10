#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSPointerHandle.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTTuple.h"
#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	class BGSObjectInstanceExtra;
	class BSExtraData;
	class ExtraAliasInstanceArray;
	class ExtraCellWaterType;
	class ExtraInstanceData;
	class ExtraLocation;
	class ExtraMaterialSwap;
	class ExtraPowerLinks;
	class ExtraReferenceHandles;
	class ExtraTextDisplayData;
	class ExtraUniqueID;

	enum EXTRA_DATA_TYPE : std::uint32_t
	{
		kNone,  // BSExtraData
		kHavok,
		kCell3D,
		kWaterType,  // ExtraCellWaterType
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
		kReferenceHandle,  // ExtraReferenceHandles
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
		kAliasInstanceArray,  // ExtraAliasInstanceArray
		kLocation,            // ExtraLocation
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
		kUniqueID,  // ExtraUniqueID
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
		kMaterialSwap,  // ExtraMaterialSwap
		kInstanceData,  // ExtraInstanceData
		kPowerArmor,
		kAcousticParent,
		kInputEnableLayer,
		kProjectedDecalRef,
		kWorkshop,  // Workshop::ExtraData
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
		kPowerLinks,  // ExtraPowerLinks
		kSavedUnrecoverableSubgraphs,
		kRefWeaponSounds,
		kRefInvestedGold,
		kRefFurnitureEntryData,
		kVoiceType,

		kTotal
	};

	class BGSAttachParentArray;
	class BGSLocation;
	class BGSMaterialSwap;
	class BGSMessage;
	class BGSRefAlias;
	class TBO_InstanceData;
	class TESBoundObject;
	class TESForm;
	class TESPackage;
	class TESQuest;
	class TESWaterForm;

	struct INSTANCE_FILTER;

	namespace BGSMod
	{
		struct ObjectIndexData;

		namespace Attachment
		{
			class Mod;
		}

		namespace Template
		{
			class Item;
		}
	}

	class __declspec(novtable) BSExtraData
	{
	public:
		static constexpr auto RTTI{ RTTI::BSExtraData };
		static constexpr auto VTABLE{ VTABLE::BSExtraData };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kNone };

		BSExtraData() :
			BSExtraData(EXTRA_DATA_TYPE::kNone)
		{}

		BSExtraData(EXTRA_DATA_TYPE a_type) :
			type(a_type)
		{
			stl::emplace_vtable(this);
		}

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

		F4_HEAP_REDEFINE_NEW(BSExtraData);

		[[nodiscard]] EXTRA_DATA_TYPE GetExtraType() const noexcept { return *type; }

		// members
		BSExtraData* next{ nullptr };                                                    // 08
		std::uint16_t flags{ 0 };                                                        // 10
		stl::enumeration<EXTRA_DATA_TYPE, std::uint8_t> type{ EXTRA_DATA_TYPE::kNone };  // 12
	};
	static_assert(sizeof(BSExtraData) == 0x18);

	class __declspec(novtable) ExtraCellWaterType :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraCellWaterType };
		static constexpr auto VTABLE{ VTABLE::ExtraCellWaterType };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kWaterType };

		// members
		TESWaterForm* water;  // 18
	};
	static_assert(sizeof(ExtraCellWaterType) == 0x20);

	class __declspec(novtable) ExtraReferenceHandles :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraReferenceHandles };
		static constexpr auto VTABLE{ VTABLE::ExtraReferenceHandles };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kReferenceHandle };

		// members
		ObjectRefHandle originalRef;   // 18
		ObjectRefHandle containerRef;  // 1C
	};
	static_assert(sizeof(ExtraReferenceHandles) == 0x20);

	class __declspec(novtable) ExtraInstanceData :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraInstanceData };
		static constexpr auto VTABLE{ VTABLE::ExtraInstanceData };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kInstanceData };

		ExtraInstanceData();
		ExtraInstanceData(const TESBoundObject* a_base, BSTSmartPointer<TBO_InstanceData> a_data);

		// members
		const TESBoundObject* base{ nullptr };   // 18
		BSTSmartPointer<TBO_InstanceData> data;  // 20
	};
	static_assert(sizeof(ExtraInstanceData) == 0x28);

	class __declspec(novtable) BGSObjectInstanceExtra :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSObjectInstanceExtra };
		static constexpr auto VTABLE{ VTABLE::BGSObjectInstanceExtra };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kObjectInstance };

		BGSObjectInstanceExtra() :
			BSExtraData(TYPE)
		{
			stl::emplace_vtable(this);
		}

		BGSObjectInstanceExtra(const BGSMod::Template::Item* a_item, TESForm* a_parentForm, const INSTANCE_FILTER* a_filter)
		{
			ctor(a_item, a_parentForm, a_filter);
		}

		void AddMod(const BGSMod::Attachment::Mod& a_newMod, std::uint8_t a_attachIndex, std::uint8_t a_rank, bool a_removeInvalidMods)
		{
			using func_t = decltype(&BGSObjectInstanceExtra::AddMod);
			REL::Relocation<func_t> func{ REL::ID(1191757) };
			return func(this, a_newMod, a_attachIndex, a_rank, a_removeInvalidMods);
		}

		void CreateBaseInstanceData(const TESBoundObject& a_object, BSTSmartPointer<TBO_InstanceData>& a_instanceData) const;

		[[nodiscard]] std::span<BGSMod::ObjectIndexData> GetIndexData() const noexcept;

		std::uint32_t RemoveInvalidMods(const BGSAttachParentArray* a_baseObjectParents)
		{
			using func_t = decltype(&BGSObjectInstanceExtra::RemoveInvalidMods);
			REL::Relocation<func_t> func{ REL::ID(1548060) };
			return func(this, a_baseObjectParents);
		}

		std::uint32_t RemoveMod(const BGSMod::Attachment::Mod* a_mod, std::uint8_t a_attachIndex)
		{
			using func_t = decltype(&BGSObjectInstanceExtra::RemoveMod);
			REL::Relocation<func_t> func{ REL::ID(1136607) };
			return func(this, a_mod, a_attachIndex);
		}

		// members
		const BSTDataBuffer<1>* values{ nullptr };  // 18
		std::uint16_t itemIndex{ 0 };               // 20

	private:
		BGSObjectInstanceExtra* ctor(const BGSMod::Template::Item* a_item, TESForm* a_parentForm, const INSTANCE_FILTER* a_filter)
		{
			using func_t = decltype(&BGSObjectInstanceExtra::ctor);
			REL::Relocation<func_t> func{ REL::ID(1222521) };
			return func(this, a_item, a_parentForm, a_filter);
		}
	};
	static_assert(sizeof(BGSObjectInstanceExtra) == 0x28);

	struct BGSRefAliasInstanceData
	{
	public:
		// members
		TESQuest* quest;                           // 00
		BGSRefAlias* alias;                        // 08
		BSTArray<TESPackage*>* instancedPackages;  // 10
	};
	static_assert(sizeof(BGSRefAliasInstanceData) == 0x18);

	class __declspec(novtable) ExtraAliasInstanceArray :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraAliasInstanceArray };
		static constexpr auto VTABLE{ VTABLE::ExtraAliasInstanceArray };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kAliasInstanceArray };

		// members
		BSTArray<BGSRefAliasInstanceData> aliasArray;  // 18
		BSReadWriteLock aliasArrayLock;                // 30
	};
	static_assert(sizeof(ExtraAliasInstanceArray) == 0x38);

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

	class __declspec(novtable) ExtraMaterialSwap :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraMaterialSwap };
		static constexpr auto VTABLE{ VTABLE::ExtraMaterialSwap };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kMaterialSwap };

		ExtraMaterialSwap() :
			BSExtraData(TYPE)
		{
			stl::emplace_vtable(this);
		}

		// members
		BGSMaterialSwap* swap{ nullptr };  // 18
	};
	static_assert(sizeof(ExtraMaterialSwap) == 0x20);

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

	class __declspec(novtable) ExtraUniqueID :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraUniqueID };
		static constexpr auto VTABLE{ VTABLE::ExtraUniqueID };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kUniqueID };

		// members
		std::uint16_t uniqueID;  // 18
		std::uint32_t baseID;    // 1C
	};
	static_assert(sizeof(ExtraUniqueID) == 0x20);

	class __declspec(novtable) ExtraPowerLinks :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraPowerLinks };
		static constexpr auto VTABLE{ VTABLE::ExtraPowerLinks };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kPowerLinks };

		struct Element
		{
		public:
			// members
			std::uint32_t formID;    // 0
			std::uint32_t linkType;  // 4
		};
		static_assert(sizeof(Element) == 0x8);

		// members
		BSTArray<Element> powerLinks;  // 18
	};
	static_assert(sizeof(ExtraPowerLinks) == 0x30);

	class BaseExtraList
	{
	public:
		void AddExtra(BSExtraData* a_extra)
		{
			assert(a_extra != nullptr);
			assert(a_extra->next == nullptr);

			const auto type = a_extra->GetExtraType();
			assert(!HasType(type));

			if (!_head || !IsHighUseExtra(type)) {
				assert(_tail != nullptr);
				*_tail = a_extra;
				_tail = std::addressof(a_extra->next);
			} else {
				a_extra->next = _head;
				_head = a_extra;
			}

			MarkType(type, true);
		}

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
			assert(a_type < EXTRA_DATA_TYPE::kTotal);
			const auto idx = stl::to_underlying(a_type) / 8;
			const auto flags = GetFlags();
			if (!flags.empty() && idx < flags.size()) {
				const auto pos = static_cast<std::uint8_t>(1u << (stl::to_underlying(a_type) % 8));
				return (flags[idx] & pos) != 0;
			} else {
				return false;
			}
		}

		std::unique_ptr<BSExtraData> RemoveExtra(EXTRA_DATA_TYPE a_type)
		{
			if (HasType(a_type)) {
				BSExtraData* prev = nullptr;
				for (auto iter = _head; iter; prev = iter, iter = iter->next) {
					if (iter->GetExtraType() == a_type) {
						if (prev) {
							prev->next = iter->next;
						} else {
							_head = iter->next;
						}

						if (!_tail || *_tail == iter) {
							_tail = std::addressof(prev ? prev->next : _head);
						}

						MarkType(a_type, false);
						return std::unique_ptr<BSExtraData>{ iter };
					}
				}
			}

			return nullptr;
		}

	private:
		static constexpr std::size_t N = (stl::to_underlying(EXTRA_DATA_TYPE::kTotal) / 8) + 1;

		[[nodiscard]] static bool IsHighUseExtra(EXTRA_DATA_TYPE a_type) noexcept
		{
			return !((stl::to_underlying(a_type) - 11) & ~0x22u) && a_type != EXTRA_DATA_TYPE::kLeveledCreature;
		}

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

		void MarkType(EXTRA_DATA_TYPE a_type, bool a_set)
		{
			assert(a_type < EXTRA_DATA_TYPE::kTotal);
			const auto idx = stl::to_underlying(a_type) / 8;
			const auto pos = static_cast<std::uint8_t>(1u << (stl::to_underlying(a_type) % 8));
			const auto flags = GetOrCreateFlags();
			if (a_set) {
				flags[idx] |= pos;
			} else {
				flags[idx] &= ~pos;
			}
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
		void AddExtra(BSExtraData* a_extra)
		{
			const BSAutoWriteLock l{ extraRWLock };
			extraData.AddExtra(a_extra);
		}

		stl::observer<TBO_InstanceData*> CreateInstanceData(TESBoundObject* a_object, bool a_generateName)
		{
			using func_t = decltype(&ExtraDataList::CreateInstanceData);
			REL::Relocation<func_t> func{ REL::ID(1280130) };
			return func(this, a_object, a_generateName);
		}

		[[nodiscard]] BSExtraData* GetByType(EXTRA_DATA_TYPE a_type) const noexcept
		{
			const BSAutoReadLock l{ extraRWLock };
			return extraData.GetByType(a_type);
		}

		template <detail::ExtraDataListConstraint T>
		[[nodiscard]] T* GetByType() const noexcept
		{
			return static_cast<T*>(GetByType(T::TYPE));
		}

		[[nodiscard]] bool HasType(EXTRA_DATA_TYPE a_type) const noexcept
		{
			const BSAutoReadLock l{ extraRWLock };
			return extraData.HasType(a_type);
		}

		template <detail::ExtraDataListConstraint T>
		[[nodiscard]] bool HasType() const noexcept
		{
			return HasType(T::TYPE);
		}

		std::unique_ptr<BSExtraData> RemoveExtra(EXTRA_DATA_TYPE a_type)
		{
			const BSAutoWriteLock l{ extraRWLock };
			return extraData.RemoveExtra(a_type);
		}

		template <detail::ExtraDataListConstraint T>
		std::unique_ptr<T> RemoveExtra()
		{
			return std::unique_ptr<T>{ static_cast<T*>(RemoveExtra(T::TYPE).release()) };
		}

		void SetDisplayNameFromInstanceData(BGSObjectInstanceExtra* a_instExtra, TESBoundObject* a_object, const BSTSmartPointer<TBO_InstanceData>& a_data)
		{
			using func_t = decltype(&ExtraDataList::SetDisplayNameFromInstanceData);
			REL::Relocation<func_t> func{ REL::ID(457340) };
			return func(this, a_instExtra, a_object, a_data);
		}

		// members
		BaseExtraList extraData;              // 08
		mutable BSReadWriteLock extraRWLock;  // 20
	};
	static_assert(sizeof(ExtraDataList) == 0x28);
}
