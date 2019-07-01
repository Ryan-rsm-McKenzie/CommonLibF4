#pragma once

#include "RE/BaseFormComponent.h"


namespace RE
{
	class BGSForcedLocRefType : public BaseFormComponent
	{
	public:
		inline static const void* RTTI = RTTI_BGSForcedLocRefType;


		virtual ~BGSForcedLocRefType();										// 00

		// override (BaseFormComponent)
		virtual UInt32	GetTypeCode() override;								// 01 - { return 'CFLR'; }
		virtual void	Unk_02() override;									// 02 - { unk08 = 0; }
		virtual void	ReleaseRefs() override;								// 03 - { return; }
		virtual void	LoadFromForm(TESForm* a_form) override;				// 04
		virtual void	Unk_05() override;									// 05
		virtual void	CopyFromBase(BaseFormComponent* a_other) override;	// 06


		// members
		UInt64 unk08;	// 08
	};
	STATIC_ASSERT(sizeof(BGSForcedLocRefType) == 0x10);
}
