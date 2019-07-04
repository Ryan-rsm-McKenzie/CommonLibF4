#pragma once


namespace RE
{
	class BSInputEventUser
	{
	public:
		virtual ~BSInputEventUser();	// 00

		// add
		virtual void	Unk_01(void);	// 01 - { return 0; }
		virtual void	Unk_02(void);	// 02 - { return; }
		virtual void	Unk_03(void);	// 03 - { return; }
		virtual void	Unk_04(void);	// 04 - { return; }
		virtual void	Unk_05(void);	// 05 - { return; }
		virtual void	Unk_06(void);	// 06 - { return; }
		virtual void	Unk_07(void);	// 07 - { return; }
		virtual void	Unk_08(void);	// 08 - { return; }
	};
	//STATIC_ASSERT(sizeof(BSInputEventUser) == 0x);
}
