#pragma once


namespace RE
{
	class BGSOpenCloseForm
	{
	public:
		inline static const void* RTTI = RTTI_BGSOpenCloseForm;


		virtual ~BGSOpenCloseForm();	// 00

		// add
		virtual void	Unk_01();		// 01 - { return; }
		virtual void	Unk_02();		// 02 - { return; }
		virtual void	Unk_03();		// 03 - { return; }
		virtual void	Unk_04();		// 04 - { return; }

		FO_HEAP_REDEFINE_NEW();
	};
	STATIC_ASSERT(sizeof(BGSOpenCloseForm) == 0x8);
}
