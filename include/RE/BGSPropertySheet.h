#pragma once

#include "RE/BaseFormComponent.h"


namespace RE
{
	class BGSPropertySheet : public BaseFormComponent
	{
	public:
		inline static const void* RTTI = RTTI_BGSPropertySheet;


		virtual ~BGSPropertySheet();										// 00

		// override (BaseFormComponent)
		virtual UInt32	GetTypeCode() override;								// 01 - { return 'CPRS'; }
		virtual void	Unk_02() override;									// 02 - { return; }
		virtual void	ReleaseRefs() override;								// 03
		virtual void	LoadFromForm(TESForm* a_form) override;				// 04
		virtual void	Unk_05() override;									// 05
		virtual void	CopyFromBase(BaseFormComponent* a_other) override;	// 06 - { return; }


		// members
		UInt64 unk08;	// 08
	};
	STATIC_ASSERT(sizeof(BGSPropertySheet) == 0x10);
}
