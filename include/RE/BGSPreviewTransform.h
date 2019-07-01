#pragma once

#include "RE/BaseFormComponent.h"


namespace RE
{
	class BGSPreviewTransform : public BaseFormComponent
	{
	public:
		inline static const void* RTTI = RTTI_BGSPreviewTransform;


		virtual ~BGSPreviewTransform();	// 00

		// override (BaseFormComponent)
		virtual UInt32	GetTypeCode() override;								// 01 - { return 'PTRN'; }
		virtual void	Unk_02() override;									// 02 - { unk08 = 0; }
		virtual void	ReleaseRefs() override;								// 03 - { return; }
		virtual void	LoadFromForm(TESForm* a_form) override;				// 04
		virtual void	Unk_05() override;									// 05
		virtual void	CopyFromBase(BaseFormComponent* a_other) override;	// 06 - { return; }


		// members
		UInt64 unk08;	// 08
	};
	STATIC_ASSERT(sizeof(BGSPreviewTransform) == 0x10);
}
