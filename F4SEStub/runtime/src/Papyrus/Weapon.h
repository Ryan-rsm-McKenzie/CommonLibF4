#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace Weapon
	{
		inline RE::BGSMod::Attachment::Mod* GetEmbeddedMod(const RE::TESObjectWEAP& a_self)
		{
			return a_self.embeddedWeaponMod;
		}

		inline void SetEmbeddedMod(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			RE::TESObjectWEAP& a_self,
			RE::BGSMod::Attachment::Mod* a_mod)
		{
			if (!a_mod) {
				a_vm.PostError("mod cannot be a none form"sv, a_stackID, Severity::kError);
			} else {
				a_self.embeddedWeaponMod = a_mod;
			}
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "Weapon"sv;

			BIND(GetEmbeddedMod);
			BIND(SetEmbeddedMod);

			logger::info("bound {} script"sv, obj);
		}
	}
}
