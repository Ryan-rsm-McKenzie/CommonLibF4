#pragma once

#include "RE/TESModel.h"  // TESModel


namespace RE
{
	class BGSModelMaterialSwap : public TESModel
	{
	public:
		inline static const void* RTTI = RTTI_BGSModelMaterialSwap;


		virtual ~BGSModelMaterialSwap();									// 00

		// override (TESModel)
		virtual void	Unk_02() override;									// 02
		virtual void	ReleaseRefs() override;								// 03
		virtual void	LoadFromForm(TESForm* a_form) override;				// 04
		virtual void	CopyFromBase(BaseFormComponent* a_other) override;	// 06
		virtual void	Unk_09() override;									// 09


		// members
		UInt64	unk30;	// 30
		UInt64	unk38;	// 38
	};
	STATIC_ASSERT(sizeof(BGSModelMaterialSwap) == 0x40);
}
