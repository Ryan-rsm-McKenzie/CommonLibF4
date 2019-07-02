#pragma once


namespace RE
{
	class TESForm;


	class BaseFormComponent
	{
	public:
		inline static const void* RTTI = RTTI_BaseFormComponent;


		virtual ~BaseFormComponent();								// 00

		// add
		virtual UInt32	GetTypeCode();								// 01 - { return 0; }
		virtual void	Unk_02() = 0;								// 02
		virtual void	ReleaseRefs() = 0;							// 03
		virtual void	LoadFromForm(TESForm* a_form);				// 04 - { return; }
		virtual void	Unk_05();									// 05 - { return; }
		virtual void	CopyFromBase(BaseFormComponent* a_other);	// 06 - { return; }

		FO_HEAP_REDEFINE_NEW();
	};
	STATIC_ASSERT(sizeof(BaseFormComponent) == 0x8);
}
