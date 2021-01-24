#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace ObjectMod
	{
		using PropertyModifier = structure_wrapper<"ObjectMod", "PropertyModifier">;

		inline RE::TESObjectMISC* GetLooseMod(const RE::BGSMod::Attachment::Mod& a_self)
		{
			const auto& mods = RE::BGSMod::Attachment::GetAllLooseMods();
			const auto it = mods.find(std::addressof(a_self));
			return it != mods.end() ? it->second : nullptr;
		}

		inline std::int8_t GetMaxRank(const RE::BGSMod::Attachment::Mod& a_self)
		{
			return a_self.maxRank;
		}

		inline std::int8_t GetPriority(const RE::BGSMod::Attachment::Mod& a_self)
		{
			return a_self.priority;
		}

		inline std::vector<PropertyModifier> GetPropertyModifiers(
			[[maybe_unused]] const RE::BGSMod::Attachment::Mod& a_self)
		{
			std::vector<PropertyModifier> result;
			return result;
		}

		inline void SetMaxRank(
			RE::BGSMod::Attachment::Mod& a_self,
			std::int8_t a_rank)
		{
			a_self.maxRank = a_rank;
		}

		inline void SetPriority(
			RE::BGSMod::Attachment::Mod& a_self,
			std::int8_t a_priority)
		{
			a_self.priority = a_priority;
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "ObjectMod"sv;

			// TODO
			BIND(GetLooseMod);
			BIND(GetMaxRank);
			BIND(GetPriority);
			//BIND(GetPropertyModifiers);
			BIND(SetMaxRank);
			BIND(SetPriority);

			logger::info("bound {} script"sv, obj);
		}
	}
}
