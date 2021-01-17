#include "RE/Bethesda/Actor.h"

#include "RE/Bethesda/TESBoundAnimObjects.h"
#include "RE/Bethesda/TESBoundObjects.h"

namespace RE
{
	TESNPC* Actor::GetNPC() const noexcept
	{
		const auto objRef = GetObjectReference();
		assert(objRef->GetFormType() == ENUM_FORM_ID::kNPC_);
		return static_cast<TESNPC*>(objRef);
	}
}
