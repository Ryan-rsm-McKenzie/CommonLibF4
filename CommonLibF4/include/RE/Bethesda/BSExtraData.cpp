#include "RE/Bethesda/BSExtraData.h"

#include "RE/Bethesda/BGSMod.h"

namespace RE
{
	std::span<BGSMod::ObjectIndexData> BGSObjectInstanceExtra::GetIndexData() const noexcept
	{
		return values->GetBuffer<BGSMod::ObjectIndexData>(0);
	}
}
