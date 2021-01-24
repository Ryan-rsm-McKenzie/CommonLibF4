#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace HeadPart
	{
		inline std::vector<RE::BGSHeadPart*> GetExtraParts(const RE::BGSHeadPart& a_self)
		{
			std::vector<RE::BGSHeadPart*> result;
			std::copy_n(
				std::execution::unseq,
				a_self.extraParts.begin(),
				a_self.extraParts.size(),
				result.begin());

			return result;
		}

		inline RE::BGSHeadPart::HeadPartType GetType(const RE::BGSHeadPart& a_self)
		{
			return *a_self.type;
		}

		inline RE::BGSListForm* GetValidRaces(const RE::BGSHeadPart& a_self)
		{
			return a_self.validRaces;
		}

		inline bool HasExtraPart(
			const RE::BGSHeadPart& a_self,
			RE::BGSHeadPart* a_part)
		{
			const auto it =
				std::find(
					a_self.extraParts.begin(),
					a_self.extraParts.end(),
					a_part);
			return a_part && it != a_self.extraParts.end();
		}

		inline bool IsExtraPart(const RE::BGSHeadPart& a_self)
		{
			return a_self.IsExtraPart();
		}

		inline void SetValidRaces(
			RE::BGSHeadPart& a_self,
			RE::BGSListForm* a_races)
		{
			if (a_races) {
				a_self.validRaces = a_races;
			}
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "HeadPart"sv;

			BIND(GetExtraParts);
			BIND(GetType);
			BIND(GetValidRaces);
			BIND(HasExtraPart);
			BIND(IsExtraPart);
			BIND(SetValidRaces);

			logger::info("bound {} script"sv, obj);
		}
	}
}
