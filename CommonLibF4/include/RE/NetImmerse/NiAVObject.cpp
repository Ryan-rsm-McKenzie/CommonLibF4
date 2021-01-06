#include "RE/NetImmerse/NiAVObject.h"

#include "RE/NetImmerse/NiCollisionObject.h"

namespace RE
{
	NiAVObject::NiAVObject()
	{
		stl::emplace_vtable(this);
		local.MakeIdentity();
		world.MakeIdentity();
		previousWorld.MakeIdentity();
		flags.flags = 0xE;
	}

	NiAVObject::~NiAVObject() {}  // NOLINT(modernize-use-equals-default)
}
