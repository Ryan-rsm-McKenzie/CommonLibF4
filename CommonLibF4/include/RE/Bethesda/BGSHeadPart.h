#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/TESCondition.h"
#include "RE/Bethesda/TESForms.h"

namespace RE
{
	class __declspec(novtable) BGSHeadPart :
		public TESForm,              // 000
		public TESFullName,          // 020
		public BGSModelMaterialSwap  // 030
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSHeadPart };
		static constexpr auto VTABLE{ VTABLE::BGSHeadPart };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kHDPT };

		enum class Flag
		{
			kPlayable = 1u << 0,
			kCantBeFemale = 1u << 1,
			kCantBeMale = 1u << 2,
			kExtraPart = 1u << 3,
			kUseSolidTint = 1u << 4,
			kUseBodyTexture = 1u << 5
		};

		enum class HeadPartType
		{
			kMisc,
			kFace,
			kEyes,
			kHair,
			kFacialHair,
			kScar,
			kEyebrows,
			kMeatcaps,
			kTeeth,
			kHeadRear
		};

		[[nodiscard]] bool IsExtraPart() const noexcept { return flags.all(Flag::kExtraPart); }

		// members
		stl::enumeration<Flag, std::uint8_t> flags;         // 070
		stl::enumeration<HeadPartType, std::int32_t> type;  // 074
		BSTArray<BGSHeadPart*> extraParts;                  // 078
		BGSTextureSet* textureSet;                          // 090
		TESModel ChargenModel;                              // 098
		TESModelTri morphs[3];                              // 0C8
		BGSColorForm* colorForm;                            // 158
		BGSListForm* validRaces;                            // 160
		TESCondition chargenConditions;                     // 168
		BSFixedString formEditorID;                         // 170
	};
	static_assert(sizeof(BGSHeadPart) == 0x178);
}
