#include "RE/Bethesda/MenuCursor.h"

#include "RE/Bethesda/Settings.h"

namespace RE
{
	void MenuCursor::ConstrainForPipboy()
	{
		REL::Relocation<Setting*> tlx{ REL::ID(60674) };
		REL::Relocation<Setting*> tly{ REL::ID(719279) };
		REL::Relocation<Setting*> width{ REL::ID(1376729) };
		REL::Relocation<Setting*> height{ REL::ID(452591) };
		SetCursorConstraintsRaw(
			tlx->GetUInt(),
			tly->GetUInt(),
			width->GetUInt(),
			height->GetUInt());
	}

	void MenuCursor::ConstrainForPipboyPA()
	{
		REL::Relocation<Setting*> tlx{ REL::ID(1110986) };
		REL::Relocation<Setting*> tly{ REL::ID(187113) };
		REL::Relocation<Setting*> width{ REL::ID(844985) };
		REL::Relocation<Setting*> height{ REL::ID(1503497) };
		SetCursorConstraintsRaw(
			tlx->GetUInt(),
			tly->GetUInt(),
			width->GetUInt(),
			height->GetUInt());
	}
}
