#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace Armor
	{
		inline std::vector<RE::TESObjectARMA*> GetArmorAddons(const RE::TESObjectARMO& a_self)
		{
			std::vector<RE::TESObjectARMA*> result;
			result.reserve(a_self.modelArray.size());
			for (const auto& model : a_self.modelArray) {
				result.push_back(model.armorAddon);
			}

			return result;
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "Armor"sv;

			BIND(GetArmorAddons);

			logger::info("bound {} script"sv, obj);
		}
	}
}
