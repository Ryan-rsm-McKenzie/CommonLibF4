#pragma once

#include "RE/BaseFormComponent.h"
#include "RE/IKeywordFormBase.h"


namespace RE
{
	class BGSKeyword;


	class BGSKeywordForm :
		public BaseFormComponent,	// 00
		public IKeywordFormBase		// 08
	{
	public:
		inline static const void* RTTI = RTTI_BGSKeywordForm;


		virtual ~BGSKeywordForm();											// 00

		// override (BaseFormComponent)
		virtual void	Unk_02() override;									// 02 - { return; }
		virtual void	ReleaseRefs() override;								// 03
		virtual void	LoadFromForm(TESForm* a_form) override;				// 04 - { return; }
		virtual void	CopyFromBase(BaseFormComponent* a_other) override;	// 06

		// add
		virtual void	Unk_07();											// 07 - { return 0; }


		// members
		BGSKeyword**	keywords;		// 10 - KWDA
		UInt32			keywordCount;	// 18 - KSIZ
		UInt32			unk1C;			// 1C
	};
	STATIC_ASSERT(sizeof(BGSKeywordForm) == 0x20);
}
