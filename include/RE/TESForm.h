#pragma once

#include "RE/BaseFormComponent.h"
#include "RE/FormTypes.h"


namespace RE
{
	class TESFile;


	class TESForm : public BaseFormComponent
	{
	public:
		inline static const void* RTTI = RTTI_TESForm;


		enum { kTypeID = FormType::kNone };	// special-case


		struct RecordFlags
		{
			enum RecordFlag : UInt32
			{};
		};


		struct TESFileArray
		{
			TESFile**	files;		// 00
			UInt64		numFiles;	// 08
		};


		virtual ~TESForm();															// 00

		// override (BaseFormComponent)
		virtual void		Unk_02() override;											// 02 - { return; }
		virtual void		ReleaseRefs() override;										// 03 - { return Unk_3B(""); }
		virtual void		CopyFromBase(BaseFormComponent* a_other) override;			// 06

		// add
		virtual void		Unk_07();													// 07 - { return; }
		virtual void		Unk_08();													// 08 - { return; }
		virtual void		Unk_09();													// 09 - { return 1; }
		virtual void		Unk_0A();													// 0A - { return 1; }
		virtual void		Unk_0B();													// 0B - { return Unk_09(); }
		virtual void		Unk_0C();													// 0C
		virtual void		Unk_0D();													// 0D
		virtual void		Unk_0E();													// 0E
		virtual void		Unk_0F();													// 0F - { return 0; }
		virtual void		Unk_10();													// 10 - { return 1; }
		virtual void		Unk_11();													// 11
		virtual void		Unk_12();													// 12
		virtual void		Unk_13();													// 13 - { return; }
		virtual void		Unk_14();													// 14 - { return; }
		virtual void		Unk_15();													// 15 - { return; }
		virtual void		Unk_16();													// 16 - { return; }
		virtual void		Unk_17();													// 17
		virtual void		Unk_18();													// 18 - "TESFile* GetSourceFile()"?
		virtual FormType	GetFormType();												// 19 - { return formType; }
		virtual UInt32		GetFormDescription(const char* a_buffer, UInt32 a_bufSize);	// 1A
		virtual void		Unk_1B();													// 1B - { return (flags >> 6) & 1; }
		virtual void		Unk_1C();													// 1C - { return (flags >> 16) & 1; }
		virtual void		Unk_1D();													// 1D - { return (~(flags >> 2)) & 1; }
		virtual void		Unk_1E();													// 1E - { return 0; }
		virtual void		Unk_1F();													// 1F - { return 0; }
		virtual void		Unk_20();													// 20 - { return (flags >> 17) & 1; }
		virtual void		Unk_21();													// 21 - { return (flags >> 19) & 1; }
		virtual void		Unk_22();													// 22 - { return (flags >> 25) & 1; }
		virtual void		Unk_23();													// 23 - { return 0; }
		virtual void		Unk_24();													// 24 - { return (~(flags >> 9)) & 1; }
		virtual void		Unk_25();													// 25 - { return (flags >> 8) & 1; }
		virtual void		Unk_26();													// 26 - { if (a_arg1) flags &= 0xFFFFFDFF; else flags |= 0x200u; }
		virtual void		Unk_27();													// 27 - { return 0; }
		virtual void		Unk_28();													// 28
		virtual void		Unk_29();													// 29
		virtual void		Unk_2A();													// 2A - { return; }
		virtual void		Unk_2B();													// 2B - { return; }
		virtual void		Unk_2C();													// 2C - { return; }
		virtual void		Unk_2D();													// 2D - { return; }
		virtual void		Unk_2E();													// 2E - { return 0; }
		virtual void		Unk_2F();													// 2F - { return 0; }
		virtual void		Unk_30();													// 30 - { return 0; }
		virtual void		Unk_31();													// 31 - { return 0; }
		virtual void		Unk_32();													// 32 - { return 0; }
		virtual void		Unk_33();													// 33 - { return 0; }
		virtual void		Unk_34();													// 34 - { return 0; }
		virtual void		Unk_35();													// 35 - "const char* GetFullName()"?
		virtual void		Unk_36();													// 36 - { return; }
		virtual void		Unk_37();													// 37
		virtual void		Unk_38();													// 38
		virtual void		Unk_39();													// 39
		virtual void		Unk_3A();													// 3A - { return ""; }
		virtual void		Unk_3B();													// 3B - { return 1; }
		virtual void		Unk_3C();													// 3C - { return 0; }
		virtual void		Unk_3D();													// 3D - { return 0; }
		virtual void		Unk_3E();													// 3E - { return 0; }
		virtual void		Unk_3F();													// 3F
		virtual void		Unk_40();													// 40 - { return 0; }
		virtual void		Unk_41();													// 41
		virtual void		Unk_42();													// 42 - { return ""; }
		virtual void		Unk_43();													// 43 - { return 1; }
		virtual void		Unk_44();													// 44 - { return 0; }
		virtual void		Unk_45();													// 45 - { return 0; }
		virtual void		Unk_46();													// 46 - { return 0; }
		virtual void		Unk_47();													// 47
		virtual void		Unk_48();													// 48 - { return -1; }
		virtual void		Unk_49();													// 49 - { return 0.0; }


		// members
		TESFileArray*	sourceFiles;	// 08
		UInt32			flags;			// 10
		FormID			formID;			// 14
		UInt16			unk18;			// 18
		FormType		formType;		// 1A
		UInt8			unk1B;			// 1B
		UInt32			pad1C;			// 1C
	};
	STATIC_ASSERT(sizeof(TESForm) == 0x20);
}
