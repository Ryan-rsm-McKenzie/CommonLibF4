#pragma once

#include "RE/BaseFormComponent.h"
#include "RE/BSTArray.h"


namespace RE
{
	namespace BGSMod
	{
		namespace Template
		{
			class Items : public BaseFormComponent
			{
			public:
				inline static const void* RTTI = RTTI_BGSMod__Template__Items;


				virtual ~Items();													// 00

				// override (BaseFormComponent)
				virtual UInt32	GetTypeCode() override;								// 01 - { return 'OBJT'; }
				virtual void	Unk_02() override;									// 02 - { return; }
				virtual void	ReleaseRefs() override;								// 03
				virtual void	LoadFromForm(TESForm* a_form) override;				// 04
				virtual void	Unk_05() override;									// 05
				virtual void	CopyFromBase(BaseFormComponent* a_other) override;	// 06 - { return; }


				// members
				BSTArray<void*> unk08;	// 08
			};
			STATIC_ASSERT(sizeof(Items) == 0x20);
		}
	}
}
