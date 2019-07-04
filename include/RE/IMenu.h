#pragma once

#include "RE/BSFixedString.h"
#include "RE/BSInputEventUser.h"
#include "RE/SWFToCodeFunctionHandler.h"


namespace RE
{
	class IMenu :
		public SWFToCodeFunctionHandler,	// 00
		public BSInputEventUser				// 10
	{
	public:
		virtual ~IMenu();				// 00

		// add
		virtual void	Unk_03(void);	// 03
		virtual void	Unk_04(void);	// 04
		virtual void	Unk_05(void);	// 05 - { return; }
		virtual void	Unk_06(void);	// 06 - { return; }
		virtual void	Unk_07(void);	// 07
		virtual void	Unk_08(void);	// 08 - { return; }
		virtual void	Unk_09(void);	// 09
		virtual void	Unk_0A(void);	// 0A - { return; }
		virtual void	Unk_0B(void);	// 0B
		virtual void	Unk_0C(void);	// 0C
		virtual void	Unk_0D(void);	// 0D
		virtual void	Unk_0E(void);	// 0E - { return 0; }
		virtual void	Unk_0F(void);	// 0F - { return 0; }
		virtual void	Unk_10(void);	// 10 - { return 0; }
		virtual void	Unk_11(void);	// 11 - { return; }
		virtual void	Unk_12(void);	// 12 - { return; }


		// members
		UInt64					unk18;	// 18
		Scaleform::GFx::Value	unk20;	// 20
		void*					unk40;	// 40
		BSFixedString			unk48;	// 48
		BSFixedString			unk50;	// 50
		UInt32					flags;	// 58
		UInt32					unk5C;	// 5C
		UInt8					unk60;	// 60
		UInt8					unk61;	// 61
		UInt8					unk62;	// 62
		UInt8					unk63;	// 63
		UInt32					unk64;	// 64
	};
	//STATIC_ASSERT(sizeof(IMenu) == 0x);
}
