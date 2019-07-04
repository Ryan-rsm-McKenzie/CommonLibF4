#pragma once

#include "RE/Scaleform/GFx/Value.h"
#include "RE/GameMenuBase.h"


namespace RE
{
	class TerminalMenu : public GameMenuBase
	{
	public:
		virtual ~TerminalMenu();								// 00

		// override (GameMenuBase)
		virtual void	Call(const Params& a_params) override;	// 01
		virtual void	RegisterCallbacks() override;			// 02
		virtual void	Unk_03(void) override;					// 03
		virtual void	Unk_04(void) override;					// 04
		virtual void	Unk_0E(void) override;					// 0E
		virtual void	Unk_0F(void) override;					// 0F


		// members
		Scaleform::GFx::Value	unk0E0;	// 0E0
		Scaleform::GFx::Value	unk100;	// 100
		Scaleform::GFx::Value	unk120;	// 120
		Scaleform::GFx::Value	unk140;	// 140
		Scaleform::GFx::Value	unk160;	// 160
		Scaleform::GFx::Value	unk180;	// 180
		BSTArray<void*>			unk1A0;	// 1A0
		UInt64					unk1B8;	// 1B8
		UInt64					unk1C0;	// 1C0
		UInt64					unk1C8;	// 1C8
		BSTArray<void*>			unk1D0;	// 1D0
		UInt64					unk1E8;	// 1E8
		UInt64					unk1F0;	// 1F0
		UInt64					unk1F8;	// 1F8
		UInt64					unk200;	// 200
		UInt64					unk208;	// 208
		UInt64					unk210;	// 210
		void*					unk218;	// 218
		UInt64					unk220;	// 220
		UInt64					unk228;	// 228
		UInt64					unk230;	// 230
		UInt64					unk238;	// 238
		UInt64					unk240;	// 240
		UInt64					unk248;	// 248
		UInt64					unk250;	// 250
		UInt64					unk258;	// 258
		UInt64					unk260;	// 260
	};
	STATIC_ASSERT(sizeof(TerminalMenu) == 0x268);
}
