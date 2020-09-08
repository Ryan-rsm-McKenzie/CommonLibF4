#pragma once

#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/TESForms.h"

namespace RE
{
	namespace BGSMod
	{
		class Container :
			public BSTDataBuffer<2>	 // 00
		{
		public:
			static constexpr auto RTTI{ RTTI::BGSMod__Container };
		};
		static_assert(sizeof(Container) == 0x10);

		namespace Attachment
		{
			class Mod :
				public TESForm,				  // 00
				public TESFullName,			  // 20
				public TESDescription,		  // 30
				public BGSModelMaterialSwap,  // 48
				public Container			  // 88
			{
			public:
				static constexpr auto RTTI{ RTTI::BGSMod__Attachment__Mod };
				static constexpr auto VTABLE{ VTABLE::BGSMod__Attachment__Mod };
				static constexpr auto FORM_ID{ ENUM_FORM_ID::kOMOD };

				// members
				BGSAttachParentArray attachParents;			  // 98
				BGSTypedKeywordValueArray<4> filterKeywords;  // B0
				BGSTypedKeywordValue<2> attachPoint;		  // C0
				std::int8_t targetFormType;					  // C2
				std::int8_t maxRank;						  // C3
				std::int8_t lvlsPerTierScaledOffset;		  // C4
				std::int8_t priority;						  // C5
				bool optional : 1;							  // C6:0
				bool childrenExclusive : 1;					  // C6:1
			};
			static_assert(sizeof(Mod) == 0xC8);
		}

		namespace Template
		{
			class Item :
				public TESFullName,		  // 00
				public BGSMod::Container  // 10
			{
			public:
				static constexpr auto RTTI{ RTTI::BGSMod__Template__Item };
				static constexpr auto VTABLE{ VTABLE::BGSMod__Template__Item };

				// members
				BGSMod::Template::Items* parentTemplate;  // 20
				BGSKeyword** nameKeywordA;				  // 28
				std::uint16_t parent;					  // 30
				std::int8_t levelMin;					  // 32
				std::int8_t levelMax;					  // 33
				std::int8_t keywords;					  // 34
				std::int8_t tierStartLevel;				  // 35
				std::int8_t altLevelsPerTier;			  // 36
				bool isDefault : 1;						  // 37:1
				bool fullNameEditorOnly : 1;			  // 37:2
			};
			static_assert(sizeof(Item) == 0x38);

			class Items :
				public BaseFormComponent  // 00
			{
			public:
				static constexpr auto RTTI{ RTTI::BGSMod__Template__Items };
				static constexpr auto VTABLE{ VTABLE::BGSMod__Template__Items };

				// override (BaseFormComponent)
				std::uint32_t GetFormComponentType() const override { return 'TJBO'; }	// 01
				void InitializeDataComponent() override { return; }						// 02
				void ClearDataComponent() override;										// 03
				void InitComponent() override;											// 04
				void CopyComponent(BaseFormComponent*) override { return; }				// 06
				void CopyComponent(BaseFormComponent*, TESForm*) override;				// 05

				// members
				BSTArray<Item*> items;	// 08
			};
			static_assert(sizeof(Items) == 0x20);
		}
	}
}
