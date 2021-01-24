#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace Location
	{
		inline RE::BGSEncounterZone* GetEncounterZone(
			const RE::BGSLocation& a_self,
			bool a_recursive)
		{
			if (a_recursive) {
				auto loc = std::addressof(a_self);
				while (loc->parentLoc) {
					loc = loc->parentLoc;
				}
				return loc->zone;
			} else {
				return a_self.zone;
			}
		}

		inline RE::BGSLocation* GetParent(const RE::BGSLocation& a_self)
		{
			return a_self.parentLoc;
		}

		inline void SetEncounterZone(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			RE::BGSLocation& a_self,
			RE::BGSEncounterZone* a_zone)
		{
			if (!a_zone) {
				a_vm.PostError("ez cannot be a none form"sv, a_stackID, Severity::kError);
			}

			a_self.zone = a_zone;
		}

		inline void SetParent(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			RE::BGSLocation& a_self,
			RE::BGSLocation* a_location)
		{
			if (!a_location) {
				a_vm.PostError("akLocation cannot be a none form"sv, a_stackID, Severity::kError);
			}

			a_self.parentLoc = a_location;
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "Location"sv;

			BIND(GetEncounterZone);
			BIND(GetParent);
			BIND(SetEncounterZone);
			BIND(SetParent);

			logger::info("bound {} script"sv, obj);
		}
	}
}
