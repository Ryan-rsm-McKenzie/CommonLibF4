#pragma once

#include "RE/Bethesda/BSFixedString.h"

namespace RE
{
	class TESCondition;
	class TESQuest;

	class __declspec(novtable) BGSBaseAlias
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraReferenceHandles };
		static constexpr auto VTABLE{ VTABLE::ExtraReferenceHandles };

		enum class FLAGS : unsigned
		{
			kReserves = 1u << 0,
			kOptional = 1u << 1,
			kQuestObject = 1u << 2,
			kAllowReuse = 1u << 3,
			kAllowDead = 1u << 4,
			kLoadedOnly = 1u << 5,
			kEssential = 1u << 6,
			kAllowDisabled = 1u << 7,
			kStoreName = 1u << 8,
			kAllowReserved = 1u << 9,
			kProtected = 1u << 10,
			kForcedFromAlias = 1u << 11,
			kAllowDestroyed = 1u << 12,
			kFindPlayerClosest = 1u << 13,
			kUsesNames = 1u << 14,
			kInitiallyDisabled = 1u << 15,
			kAllowCleared = 1u << 16,
			kClearNameOnRemove = 1u << 17,
			kActorsOnly = 1u << 18,
			kTransient = 1u << 19,
			kExternalLink = 1u << 20,
			kNoPickPocket = 1u << 21,
			kDataAlias = 1u << 22,
			kSceneOptional = 1u << 24,
		};

		virtual ~BGSBaseAlias();  // 00

		// add
		virtual bool Load() = 0;                                         // 01
		virtual void InitItem() = 0;                                     // 02
		[[nodiscard]] virtual const BSFixedString& QType() const = 0;    // 03
		[[nodiscard]] virtual TESQuest* QExternalQuest() const = 0;      // 04
		virtual void ClearExternalQuest() = 0;                           // 05
		virtual void UpdateFromExternalAlias() const = 0;                // 06
		[[nodiscard]] virtual BGSBaseAlias* GetLinkedAlias() const = 0;  // 07

		[[nodiscard]] bool IsQuestObject() const noexcept { return flags.all(FLAGS::kQuestObject); }

		// mmebers
		BSFixedString aliasName;                       // 08
		TESQuest* owningQuest;                         // 10
		std::uint32_t aliasID;                         // 18
		stl::enumeration<FLAGS, std::uint32_t> flags;  // 1C
		std::uint16_t fillType;                        // 20
	};
	static_assert(sizeof(BGSBaseAlias) == 0x28);

	class __declspec(novtable) BGSRefAlias :
		public BGSBaseAlias  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSRefAlias };
		static constexpr auto VTABLE{ VTABLE::BGSRefAlias };
		static constexpr auto TYPE{ "Ref"sv };

		enum class FILL_TYPE
		{
			kConditions,
			kForced,
			kFromAlias,
			kFromEvent,
			kCreated,
			kFromExternal,
			kUniqueActor,
			kNearAlias,
		};

		struct GenericFillData
		{
		public:
			// members
			std::uint64_t data[3];
		};
		static_assert(sizeof(GenericFillData) == 0x18);

		// members
		GenericFillData fillData;  // 28
		TESCondition* conditions;  // 40
	};
	static_assert(sizeof(BGSRefAlias) == 0x48);
}
