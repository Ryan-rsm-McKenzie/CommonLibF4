#include "RE/Bethesda/TESForms.h"

#include "RE/Bethesda/BSExtraData.h"
#include "RE/Bethesda/TESWorldSpace.h"

namespace RE
{
	TESWaterForm* TESObjectCELL::GetWaterType() const noexcept
	{
		const auto xWater = extraList ? extraList->GetByType<ExtraCellWaterType>() : nullptr;
		auto water = xWater ? xWater->water : nullptr;
		if (!water) {
			water = IsExterior() && worldSpace ? worldSpace->GetWaterType() : nullptr;
			if (!water) {
				REL::Relocation<TESWaterForm**> defaultWater{ REL::ID(289864) };
				water = *defaultWater;
			}
		}

		return water;
	}
}
