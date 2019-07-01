#pragma once

#include "RE/BaseFormComponent.h"
#include "RE/BSFixedString.h"
#include "RE/FileHash.h"


namespace RE
{
	class TESModel : public BaseFormComponent
	{
	public:
		inline static const void* RTTI = RTTI_TESModel;


		virtual ~TESModel();												// 00

		// override (BaseFormComponent)
		virtual void	Unk_02() override;									// 02
		virtual void	ReleaseRefs() override;								// 03
		virtual void	CopyFromBase(BaseFormComponent* a_other) override;	// 06

		// add
		virtual void	Unk_07();											// 07
		virtual void	Unk_08();											// 08
		virtual void	Unk_09();											// 09 - { return 0; }


		// members
		BSFixedString	unk08;		// 08
		FileHash*		unkHash1;	// 10
		FileHash*		unkHash2;	// 18
		FileHash*		unkHash3;	// 20
		UInt16			unkState1;	// 28
		UInt8			unkState3;	// 2A
		UInt8			unkState2;	// 2B
		UInt32			unk2C;		// 2C
	};
	//STATIC_ASSERT(sizeof(TESModel) == 0x);
}
