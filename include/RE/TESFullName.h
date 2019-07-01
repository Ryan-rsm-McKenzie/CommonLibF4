#pragma once

#include "RE/BaseFormComponent.h"  // BaseFormComponent
#include "RE/BSFixedString.h"  // BSFixedString


namespace RE
{
	class TESFullName : public BaseFormComponent
	{
	public:
		inline static const void* RTTI = RTTI_TESFullName;


		virtual ~TESFullName();												// 00

		// override (BaseFormComponent)
		virtual void	Unk_02() override;									// 02
		virtual void	ReleaseRefs() override;								// 03 - { return; }
		virtual void	CopyFromBase(BaseFormComponent* a_other) override;	// 06

		// add
		virtual void	Unk_07();											// 07
		virtual void	Unk_08();											// 08


		// members
		BSFixedString fullName;	// 08
	};
	STATIC_ASSERT(sizeof(TESFullName) == 0x10);
}
