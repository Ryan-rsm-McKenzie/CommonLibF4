#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace ArmorAddon
	{
		inline std::vector<RE::TESRace*> GetAdditionalRaces(const RE::TESObjectARMA& a_self)
		{
			std::vector<RE::TESRace*> result(a_self.additionalRaces.size(), nullptr);
			std::copy_n(
				std::execution::unseq,
				a_self.additionalRaces.begin(),
				a_self.additionalRaces.size(),
				result.begin());

			return result;
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "ArmorAddon"sv;

			BIND(GetAdditionalRaces);

			logger::info("bound {} script"sv, obj);
		}
	}
}
