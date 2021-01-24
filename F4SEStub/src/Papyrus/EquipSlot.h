#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace EquipSlot
	{
		inline std::vector<RE::BGSEquipSlot*> GetParents(const RE::BGSEquipSlot& a_self)
		{
			std::vector<RE::BGSEquipSlot*> result(a_self.parentSlots.size(), nullptr);
			std::copy_n(
				std::execution::unseq,
				a_self.parentSlots.begin(),
				a_self.parentSlots.size(),
				result.begin());

			return result;
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "EquipSlot"sv;

			BIND(GetParents);

			logger::info("bound {} script"sv, obj);
		}
	}
}
