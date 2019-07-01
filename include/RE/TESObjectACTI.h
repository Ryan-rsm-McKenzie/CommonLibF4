#pragma once

#include "RE/BGSDestructibleObjectForm.h"
#include "RE/BGSForcedLocRefType.h"
#include "RE/BGSKeywordForm.h"
#include "RE/BGSModelMaterialSwap.h"
#include "RE/BGSNativeTerminalForm.h"
#include "RE/BGSNavmeshableObject.h"
#include "RE/BGSOpenCloseForm.h"
#include "RE/BGSPropertySheet.h"
#include "RE/TESBoundAnimObject.h"
#include "RE/TESFullName.h"
#include "RE/TESMagicTargetForm.h"


namespace RE
{
	class TESObjectACTI :
		public TESBoundAnimObject,			// 000
		public TESFullName,					// 068
		public BGSModelMaterialSwap,		// 078
		public TESMagicTargetForm,			// 120 <- offset issues
		public BGSDestructibleObjectForm,	// 0B8
		public BGSOpenCloseForm,			// 0C8
		public BGSKeywordForm,				// 0D0
		public BGSPropertySheet,			// 0F0
		public BGSForcedLocRefType,			// 100
		public BGSNativeTerminalForm,		// 110
		public BGSNavmeshableObject			// 120 <- offset issues
	{
	public:
		inline static const void* RTTI = RTTI_TESObjectACTI;


		virtual ~TESObjectACTI();			// 00

		// override (TESBoundAnimObject)
		virtual void	Unk_07() override;	// 07
		virtual void	Unk_08() override;	// 08
		virtual void	Unk_09() override;	// 09
		virtual void	Unk_11() override;	// 11
		virtual void	Unk_12() override;	// 12
		virtual void	Unk_16() override;	// 16
		virtual void	Unk_1D() override;	// 1D - { return 1; }
		virtual void	Unk_1E() override;	// 1E - { return (unk10 >> 2) & 1; }
		virtual void	Unk_1F() override;	// 1F - { return (unk10 >> 10) & 1; }
		virtual void	Unk_27() override;	// 27 - { return (unk140 >> 1) & 1; }
		virtual void	Unk_31() override;	// 31 - { return unk138 != 0; }
		virtual void	Unk_40() override;	// 40
		virtual void	Unk_4B() override;	// 4B - { returnk unk138; }
		virtual void	Unk_60() override;	// 60
		virtual void	Unk_61() override;	// 61


		// members
		UInt64	unk128;	// 128
		UInt64	unk130;	// 130
		UInt64	unk138;	// 138
	};
	STATIC_ASSERT(sizeof(TESObjectACTI) == 0x140);
}
