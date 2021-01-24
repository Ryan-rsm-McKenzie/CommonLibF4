#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace EncounterZone
	{
		inline RE::BGSLocation* GetLocation(const RE::BGSEncounterZone& a_self)
		{
			return a_self.data.location;
		}

		inline std::int32_t GetMaxLevel(const RE::BGSEncounterZone& a_self)
		{
			return a_self.data.maxLevel;
		}

		inline std::int32_t GetMinLevel(const RE::BGSEncounterZone& a_self)
		{
			return a_self.data.minLevel;
		}

		inline std::int32_t GetRank(const RE::BGSEncounterZone& a_self)
		{
			return a_self.data.ownerRank;
		}

		inline bool IsNeverResetable(const RE::BGSEncounterZone& a_self)
		{
			return a_self.NeverResets();
		}

		inline bool IsWorkshop(const RE::BGSEncounterZone& a_self)
		{
			return a_self.IsWorkshop();
		}

		inline void SetLocation(
			RE::BGSEncounterZone& a_self,
			RE::BGSLocation* a_loc)
		{
			a_self.data.location = a_loc;
		}

		inline void SetMaxLevel(
			RE::BGSEncounterZone& a_self,
			std::int8_t a_level)
		{
			a_self.data.maxLevel = a_level;
		}

		inline void SetMinLevel(
			RE::BGSEncounterZone& a_self,
			std::int8_t a_level)
		{
			a_self.data.minLevel = a_level;
		}

		inline void SetNeverResetable(
			RE::BGSEncounterZone& a_self,
			bool a_set)
		{
			if (a_set) {
				a_self.data.flags.set(RE::ENCOUNTER_ZONE_DATA::FLAG::kNeverReset);
			} else {
				a_self.data.flags.reset(RE::ENCOUNTER_ZONE_DATA::FLAG::kNeverReset);
			}

			a_self.AddChange(RE::CHANGE_TYPE::kEncounterZoneFlags);  // divergent
		}

		inline void SetRank(
			RE::BGSEncounterZone& a_self,
			std::int8_t a_rank)
		{
			a_self.data.ownerRank = a_rank;
		}

		inline void SetWorkshop(
			RE::BGSEncounterZone& a_self,
			bool a_set)
		{
			if (a_set) {
				a_self.data.flags.set(RE::ENCOUNTER_ZONE_DATA::FLAG::kWorkshopZone);
			} else {
				a_self.data.flags.reset(RE::ENCOUNTER_ZONE_DATA::FLAG::kWorkshopZone);
			}

			a_self.AddChange(RE::CHANGE_TYPE::kEncounterZoneFlags);  // divergent
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "EncounterZone"sv;

			BIND(GetLocation);
			BIND(GetMaxLevel);
			BIND(GetMinLevel);
			BIND(GetRank);
			BIND(IsNeverResetable);
			BIND(IsWorkshop);
			BIND(SetLocation);
			BIND(SetMaxLevel);
			BIND(SetMinLevel);
			BIND(SetNeverResetable);
			BIND(SetRank);
			BIND(SetWorkshop);

			logger::info("bound {} script"sv, obj);
		}
	}
}
