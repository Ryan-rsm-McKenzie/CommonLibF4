#pragma once

#include "RE/BaseFormComponent.h"
#include "RE/BGSTypedKeywordValueArray.h"


namespace RE
{
	class BGSAttachParentArray :
		public BaseFormComponent,			// 00
		public BGSTypedKeywordValueArray<2>	// 08
	{
	public:
		inline static const void* RTTI = RTTI_BGSAttachParentArray;


		virtual ~BGSAttachParentArray();									// 00

		// override (BaseFormComponent)
		virtual UInt32	GetTypeCode() override;								// 01 - { return 'APPA'; }
		virtual void	Unk_02() override;									// 02 - { return; }
		virtual void	ReleaseRefs() override;								// 03
		virtual void	Unk_05() override;									// 05
		virtual void	CopyFromBase(BaseFormComponent* a_other) override;	// 06 - { return; }
	};
}
