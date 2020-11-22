#include "RE/NetImmerse/NiObjectNET.h"

#include "RE/NetImmerse/NiTimeController.h"

namespace RE
{
	NiObjectNET::NiObjectNET() { emplace_vtable(this); }

	NiObjectNET::~NiObjectNET() {}  // NOLINT(modernize-use-equals-default)
}
