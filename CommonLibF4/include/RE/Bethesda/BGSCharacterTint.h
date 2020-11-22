#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/TESCondition.h"

namespace RE
{
	class TESFile;
	class TESForm;

	namespace BGSCharacterTint
	{
		enum class EntrySlot
		{
			kForeheadMask,
			kEyesMask,
			kNoseMask,
			kEarsMask,
			kCheeksMask,
			kMouthMask,
			kNeckMask,
			kLipColor,
			kCheekColor,
			kEyeliner,
			kEyeSocketUpper,
			kEyeSocketLower,
			kSkinTone,
			kPaint,
			kLaughLines,
			kCheekColorLower,
			kNose,
			kChin,
			kNeck,
			kForehead,
			kDirt,
			kScars,
			kFaceDetail,
			kBrow,
			kWrinkles,
			kBeard
		};

		namespace Template
		{
			class __declspec(novtable) Entry
			{
			public:
				static constexpr auto RTTI{ RTTI::BGSCharacterTint__Template__Entry };
				static constexpr auto VTABLE{ VTABLE::BGSCharacterTint__Template__Entry };

				virtual ~Entry();  // 00

				// add
				virtual float GetDefaultValue() { return 0.0F; }  // 01
				virtual void InitItem(TESForm* a_owner);          // 02
				virtual void CopyData(Entry* a_copy);             // 03
				virtual void LoadImpl(TESFile* a_file) = 0;       // 04

				// members
				BGSLocalizedString name;                         // 08
				TESCondition chargenConditions;                  // 10
				stl::enumeration<EntrySlot, std::int32_t> slot;  // 18
				const std::uint16_t uniqueID{ 0 };               // 1C
				std::int8_t flags;                               // 1E
			};
			static_assert(sizeof(Entry) == 0x20);

			class Group
			{
			public:
				// members
				BGSLocalizedString name;     // 00
				std::uint32_t id;            // 08
				std::uint32_t chargenIndex;  // 0C
				BSTArray<Entry*> entries;    // 10
			};
			static_assert(sizeof(Group) == 0x28);

			class Groups
			{
			public:
				// members
				BSTArray<Group*> groups;  // 00
			};
			static_assert(sizeof(Groups) == 0x18);
		}
	}
}
