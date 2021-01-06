#include "RE/Bethesda/TESObjectREFRs.h"

#include "RE/NetImmerse/NiAVObject.h"

namespace RE
{
	BIPOBJECT::~BIPOBJECT()
	{
		Dtor();
		stl::memzero(this);
	}
}
