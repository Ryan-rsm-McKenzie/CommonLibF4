#pragma once

#include "RE/BSFixedString.h"
#include "RE/BSTArray.h"
#include "RE/Condition.h"
#include "RE/TESFurniture.h"


namespace RE
{
	class BGSTerminal : public TESFurniture
	{
	public:
		inline static const void* RTTI = RTTI_BGSTerminal;


		enum { kTypeID = FormType::kTerminal };


		struct RecordFlags
		{
			enum RecordFlag : UInt32
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kHasDistantLOD = 1 << 15,
				kRandomAnimStart = 1 << 16
			};
		};


		struct Item
		{
			BSFixedString	text;		// 00 - BTXT
			Condition		conditions;	// 08
		};
		STATIC_ASSERT(sizeof(Item) == 0x10);


		struct MenuItem
		{
			enum class Type : UInt8	// ANAM
			{
				kSubmenu_Terminal = 4,
				kSubmenu_ReturnToTopLevel = 5,
				kSubmenu_ForceRedraw = 6,
				kDisplayText = 8,
				kDisplayImage = 16
			};


			union Item
			{
				BSFixedString*	displayText;	// UNAM
				BGSTerminal*	submenu;		// TNAM
			};
			STATIC_ASSERT(sizeof(Item) == 0x8);


			BSFixedString	itemText;		// 00 - ITXT
			BSFixedString	responseText;	// 08 - RNAM
			Item			item;			// 10
			Condition		conditions;		// 18
			UInt16			itemID;			// 20 - ITID
			Type			type;			// 22 - ANAM
			UInt8			pad23;			// 24
			UInt32			pad24;			// 24
		};
		STATIC_ASSERT(sizeof(MenuItem) == 0x28);


		virtual ~BGSTerminal();				// 00

		// override (TESFurniture)
		virtual void	Unk_07() override;	// 07 - { return TESFurniture::Unk_07(); }
		virtual void	Unk_08() override;	// 08
		virtual void	Unk_09() override;	// 09
		virtual void	Unk_11() override;	// 11 - { return TESObjectACTI::Unk_11(); }
		virtual void	Unk_12() override;	// 12 - { return TESObjectACTI::Unk_12(); }
		virtual void	Unk_15() override;	// 15 - { return TESForm::Unk_15(); }
		virtual void	Unk_16() override;	// 16
		virtual void	Unk_40() override;	// 40
		virtual void	Unk_61() override;	// 61


		// members
		BSTArray<Item>		bodyText;		// 1A0
		BSTArray<MenuItem>	menuItems;		// 1B8
		BSFixedString		headerText;		// 1D0 - NAM0
		BSFixedString		welcomeText;	// 1D8 - WNAM
	};
	STATIC_ASSERT(sizeof(BGSTerminal) == 0x1E0);
}
