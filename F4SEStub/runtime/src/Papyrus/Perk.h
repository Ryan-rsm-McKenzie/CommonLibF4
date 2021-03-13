#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace Perk
	{
		inline std::int8_t GetLevel(const RE::BGSPerk& a_self)
		{
			return a_self.data.level;
		}

		inline RE::BGSPerk* GetNextPerk(const RE::BGSPerk& a_self)
		{
			return a_self.nextPerk;
		}

		inline std::int8_t GetNumRanks(const RE::BGSPerk& a_self)
		{
			return a_self.data.numRanks;
		}

		inline RE::BSFixedStringCS GetSWFPath(const RE::BGSPerk& a_self)
		{
			return a_self.swfFile;
		}

		inline bool IsEligible(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			const RE::BGSPerk& a_self,
			RE::Actor* a_actor)
		{
			if (!a_actor) {
				a_vm.PostError("akActor cannot be a none form"sv, a_stackID, Severity::kError);
				return false;
			}

			return a_self.perkConditions ? a_self.perkConditions(a_actor, a_actor) : true;
		}

		inline bool IsHidden(const RE::BGSPerk& a_self)
		{
			return a_self.data.hidden;  // divergent, f4se always returns true
		}

		inline bool IsPlayable(const RE::BGSPerk& a_self)
		{
			return a_self.data.playable;  // divergent, f4se always returns true
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "Perk"sv;

			BIND(GetLevel);
			BIND(GetNextPerk);
			BIND(GetNumRanks);
			BIND(GetSWFPath);
			BIND(IsEligible);
			BIND(IsHidden);
			BIND(IsPlayable);

			logger::info("bound {} script"sv, obj);
		}
	}
}
