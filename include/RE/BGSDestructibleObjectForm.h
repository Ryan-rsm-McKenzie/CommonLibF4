#pragma once

#include "RE/BaseFormComponent.h"


namespace RE
{
	class BGSDestructibleObjectForm : public BaseFormComponent
	{
	public:
		inline static const void* RTTI = RTTI_BGSDestructibleObjectForm;


		virtual ~BGSDestructibleObjectForm();								// 00

		// override (BaseFormComponent)
		virtual void	Unk_02() override;									// 02 - { unk08 = 0; }
		virtual void	ReleaseRefs() override;								// 03
		virtual void	LoadFromForm(TESForm* a_form) override;				// 04
		virtual void	CopyFromBase(BaseFormComponent* a_other) override;	// 06


		// members
		UInt64	unk08;	// 08
	};
	STATIC_ASSERT(sizeof(BGSDestructibleObjectForm) == 0x10);
}
