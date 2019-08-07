#pragma once

#include "RE/BGSMod/Template/Items.h"
#include "RE/BGSPreviewTransform.h"
#include "RE/BGSSoundTagComponent.h"
#include "RE/TESObject.h"


namespace RE
{
	class TESBoundObject : public TESObject
	{
	public:
		inline static const void* RTTI = RTTI_TESBoundObject;


		struct ObjectBounds	// OBND
		{
			SInt16	x1;	// 0
			SInt16	y1;	// 2
			SInt16	z1;	// 4
			SInt16	x2;	// 6
			SInt16	y2;	// 8
			SInt16	z2;	// A
		};
		STATIC_ASSERT(sizeof(ObjectBounds) == 0xC);


		virtual ~TESBoundObject();			// 00

		// override (TESObject)
		virtual void	Unk_2B() override;	// 2B
		virtual void	Unk_2D() override;	// 2D
		virtual void	Unk_2E() override;	// 2E - { return 1; }
		virtual void	Unk_40() override;	// 40
		virtual void	Unk_44() override;	// 44 - { return unk30; }
		virtual void	Unk_45() override;	// 45 - { return unk50; }
		virtual void	Unk_46() override;	// 46 - { return unk60; }
		virtual void	Unk_4E() override;	// 4E
		virtual void	Unk_52() override;	// 52

		// add
		virtual void	Unk_56();			// 56 - { return 0; }
		virtual void	Unk_57();			// 57 - { return 0; }
		virtual void	Unk_58();			// 58 - { return 0; }
		virtual void	Unk_59();			// 59 - { return; }
		virtual void	Unk_5A();			// 5A - { return 0; }
		virtual void	Unk_5B();			// 5B - { return; }
		virtual void	Unk_5C();			// 5C - { return 0; }
		virtual void	Unk_5D();			// 5D
		virtual void	Unk_5E();			// 5E
		virtual void	Unk_5F();			// 5F
		virtual void	Unk_60();			// 60
		virtual void	Unk_61();			// 61
		virtual void	Unk_62();			// 62 - { return; }
		virtual void	Unk_63();			// 63 - { return; }
		virtual void	Unk_64();			// 64 - { return; }
		virtual void	Unk_65();			// 65 - { return; }
		virtual void	Unk_66();			// 66 - { return; }


		// members
		ObjectBounds			objectBounds;	// 20 - OBND
		UInt32					unk2C;			// 2C
		BGSMod::Template::Items	unk30;			// 30 - OBJT
		BGSPreviewTransform		unk48;			// 48 - PTRN
		BGSSoundTagComponent	unk60;			// 60 - CATC
	};
	STATIC_ASSERT(sizeof(TESBoundObject) == 0x68);
}
