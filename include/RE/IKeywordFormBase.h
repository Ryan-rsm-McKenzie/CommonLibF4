#pragma once


namespace RE
{
	class IKeywordFormBase
	{
	public:
		inline static const void* RTTI = RTTI_IKeywordFormBase;


		virtual ~IKeywordFormBase();	// 00

		// add
		virtual void	Unk_01() = 0;	// 01
		virtual void	Unk_02() = 0;	// 02

		FO_HEAP_REDEFINE_NEW();
	};
	//STATIC_ASSERT(sizeof(IKeywordFormBase) == 0x);
}
