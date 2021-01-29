#include "RE/Bethesda/BGSInventoryItem.h"

namespace RE
{
	std::uint32_t BGSInventoryItem::GetCount() const noexcept
	{
		std::uint32_t count = 0;
		for (auto iter = stackData.get(); iter; iter = iter->nextStack.get()) {
			count += iter->GetCount();
		}
		return count;
	}
}
