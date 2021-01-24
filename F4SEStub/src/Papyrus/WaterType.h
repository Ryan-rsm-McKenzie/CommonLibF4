#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace WaterType
	{
		inline RE::SpellItem* GetConsumeSpell(const RE::TESWaterForm& a_self)
		{
			return a_self.consumeSpell;
		}

		inline RE::SpellItem* GetContactSpell(const RE::TESWaterForm& a_self)
		{
			return a_self.contactSpell;
		}

		inline void SetConsumeSpell(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			RE::TESWaterForm& a_self,
			RE::SpellItem* a_spell)
		{
			if (!a_spell) {
				a_vm.PostError("sp cannot be a none form"sv, a_stackID, Severity::kError);
			} else {
				a_self.consumeSpell = a_spell;
			}
		}

		inline void SetContactSpell(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			RE::TESWaterForm& a_self,
			RE::SpellItem* a_spell)
		{
			if (!a_spell) {
				a_vm.PostError("sp cannot be a none form"sv, a_stackID, Severity::kError);
			} else {
				a_self.contactSpell = a_spell;
			}
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "WaterType"sv;

			BIND(GetConsumeSpell);
			BIND(GetContactSpell);
			BIND(SetConsumeSpell);
			BIND(SetContactSpell);

			logger::info("bound {} script"sv, obj);
		}
	}
}
