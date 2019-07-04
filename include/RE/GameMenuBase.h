#pragma once

#include "RE/BSFixedString.h"
#include "RE/BSSpinLock.h"
#include "RE/BSTArray.h"
#include "RE/IMenu.h"


namespace RE
{
	class GameMenuBase : public IMenu
	{
	public:
		virtual ~GameMenuBase();				// 00

		// override (IMenu)
		virtual void	Unk_08(void) override;	// 08
		virtual void	Unk_0A(void) override;	// 0A
		virtual void	Unk_0B(void) override;	// 0B
		virtual void	Unk_0C(void) override;	// 0C
		virtual void	Unk_10(void) override;	// 10
		virtual void	Unk_11(void) override;	// 11
		virtual void	Unk_12(void) override;	// 12

		// add
		virtual void	Unk_13(void);			// 13


		// members
		UInt64			unk68;	// 68
		BSTArray<void*>	unk70;	// 70
		void*			unk88;	// 88
		void*			unk90;	// 90
		BSTArray<void*>	unk98;	// 98
		BSTArray<void*>	unkB0;	// B0
		BSSpinLock		unkC8;	// C8
		UInt64			unkD0;	// D0
		BSFixedString	unkD8;	// D8
	};
	//STATIC_ASSERT(sizeof(GameMenuBase) == 0x);
}
