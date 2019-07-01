#pragma once

#include "RE/TESForm.h"


namespace RE
{
	class TESObject : public TESForm
	{
	public:
		inline static const void* RTTI = RTTI_TESObject;


		virtual ~TESObject();				// 00

		// override (TESForm)
		virtual void	Unk_2F() override;	// 2F - { return 1; }
		virtual void	Unk_34() override;	// 34 - { return 0; }

		// add
		virtual void	Unk_4A();			// 4A - { return 0; }
		virtual void	Unk_4B();			// 4B - { return 0; }
		virtual void	Unk_4C();			// 4C - { return 0; }
		virtual void	Unk_4D();			// 4D - { return; }
		virtual void	Unk_4E();			// 4E - { return; }
		virtual void	Unk_4F();			// 4F
		virtual void	Unk_50();			// 50
		virtual void	Unk_51();			// 51
		virtual void	Unk_52();			// 52
		virtual void	Unk_53();			// 53 - { return 0; }
		virtual void	Unk_54();			// 54 - { return 0; }
		virtual void	Unk_55();			// 55
	};
	STATIC_ASSERT(sizeof(TESObject) == 0x20);
}
