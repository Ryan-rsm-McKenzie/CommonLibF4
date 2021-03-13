#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace Component
	{
		inline RE::TESObjectMISC* GetScrapItem(const RE::BGSComponent& a_self)
		{
			return a_self.scrapItem;
		}

		inline RE::TESGlobal* GetScrapScalar(const RE::BGSComponent& a_self)
		{
			return a_self.modScrapScalar;
		}

		inline void SetScrapItem(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			RE::BGSComponent& a_self,
			RE::TESObjectMISC* a_misc)
		{
			if (!a_misc) {
				a_vm.PostError("akMisc cannot be a none form"sv, a_stackID, Severity::kError);
			} else {
				a_self.scrapItem = a_misc;
			}
		}

		inline void SetScrapScalar(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			RE::BGSComponent& a_self,
			RE::TESGlobal* a_global)
		{
			if (!a_global) {
				a_vm.PostError("akGlobal cannot be a none form"sv, a_stackID, Severity::kError);
			} else {
				a_self.modScrapScalar = a_global;
			}
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "Component"sv;

			BIND(GetScrapItem);
			BIND(GetScrapScalar);
			BIND(SetScrapItem);
			BIND(SetScrapScalar);

			logger::info("bound {} script"sv, obj);
		}
	}
}
