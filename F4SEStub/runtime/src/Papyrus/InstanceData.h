#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace InstanceData
	{
		using DamageTypeInfo = structure_wrapper<"InstanceData", "DamageTypeInfo">;
		using Owner = structure_wrapper<"InstanceData", "Owner">;

		inline std::int32_t GetAccuracyBonus(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0;
		}

		inline float GetActionPointCost(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0.0;
		}

		inline RE::TESLevItem* GetAddAmmoList(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return nullptr;
		}

		inline RE::TESAmmo* GetAmmo(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return nullptr;
		}

		inline std::int32_t GetAmmoCapacity(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0;
		}

		inline std::int32_t GetArmorHealth(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0;
		}

		inline std::int32_t GetArmorRating(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0;
		}

		inline std::int32_t GetAttackDamage(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0;
		}

		inline float GetAttackDelay(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0.0;
		}

		inline float GetCritChargeBonus(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0.0;
		}

		inline float GetCritMultiplier(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0.0;
		}

		inline std::vector<DamageTypeInfo> GetDamageTypes(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return {};
		}

		inline bool GetFlag(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] std::uint32_t a_flag)
		{
			return false;
		}

		inline std::int32_t GetGoldValue(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] std::uint32_t a_flag)
		{
			return 0;
		}

		inline std::vector<RE::BGSKeyword*> GetKeywords(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return {};
		}

		inline float GetMaxRange(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0.0;
		}

		inline float GetMinRange(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0.0;
		}

		inline std::int32_t GetNumProjectiles(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0;
		}

		inline float GetOutOfRangeMultiplier(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0.0;
		}

		inline RE::BGSProjectile* GetProjectileOverride(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return nullptr;
		}

		inline float GetReach(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0.0;
		}

		inline float GetReloadSpeed(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0.0;
		}

		inline RE::ActorValueInfo* GetResist(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return nullptr;
		}

		inline float GetSightedTransition(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0.0;
		}

		inline RE::ActorValueInfo* GetSkill(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return nullptr;
		}

		inline float GetSpeed(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0.0;
		}

		inline std::int32_t GetStagger(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0;
		}

		inline float GetWeight(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner)
		{
			return 0.0;
		}

		inline void SetAccuracyBonus(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] std::int32_t a_bonus)
		{}

		inline void SetActionPointCost(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] float a_cost)
		{}

		inline void SetAddAmmoList(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] RE::TESLevItem* a_ammo)
		{}

		inline void SetAmmo(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] RE::TESAmmo* a_ammo)
		{}

		inline void SetAmmoCapacity(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] std::int32_t a_capacity)
		{}

		inline void SetArmorHealth(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] std::int32_t a_health)
		{}

		inline void SetArmorRating(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] std::int32_t a_health)
		{}

		inline void SetAttackDamage(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] std::int32_t a_damage)
		{}

		inline void SetAttackDelay(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] float a_delay)
		{}

		inline void SetCritChargeBonus(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] float a_bonus)
		{}

		inline void SetCritMultiplier(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] float a_crit)
		{}

		inline void SetDamageTypes(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] std::vector<DamageTypeInfo> a_damageTypes)
		{}

		inline void SetFlag(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] std::uint32_t a_flag,
			[[maybe_unused]] bool a_set)
		{}

		inline void SetGoldValue(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] std::uint32_t a_value)
		{}

		inline void SetKeywords(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] std::vector<RE::BGSKeyword*> a_keywords)
		{}

		inline void SetMaxRange(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] float a_maxRange)
		{}

		inline void SetMinRange(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] float a_minRange)
		{}

		inline void SetNumProjectiles(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] std::int32_t a_numProj)
		{}

		inline void SetOutOfRangeMultiplier(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] float a_mult)
		{}

		inline void SetProjectileOverride(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] RE::BGSProjectile* a_proj)
		{}

		inline void SetReach(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] float a_speed)
		{}

		inline void SetReloadSpeed(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] float a_speed)
		{}

		inline void SetResist(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] RE::ActorValueInfo* a_resist)
		{}

		inline void SetSightedTransition(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] float a_seconds)
		{}

		inline void SetSkill(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] RE::ActorValueInfo* a_skill)
		{}

		inline void SetSpeed(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] float a_speed)
		{}

		inline void SetStagger(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] std::int32_t a_stagger)
		{}

		inline void SetWeight(
			[[maybe_unused]] std::monostate,
			[[maybe_unused]] Owner a_owner,
			[[maybe_unused]] float a_weight)
		{}

		inline void Bind([[maybe_unused]] RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "InstanceData"sv;

			// TODO
			//BIND(GetAccuracyBonus);
			//BIND(GetActionPointCost);
			//BIND(GetAddAmmoList);
			//BIND(GetAmmo);
			//BIND(GetAmmoCapacity);
			//BIND(GetArmorHealth);
			//BIND(GetArmorRating);
			//BIND(GetAttackDamage);
			//BIND(GetAttackDelay);
			//BIND(GetCritChargeBonus);
			//BIND(GetCritMultiplier);
			//BIND(GetDamageTypes);
			//BIND(GetFlag);
			//BIND(GetGoldValue);
			//BIND(GetKeywords);
			//BIND(GetMaxRange);
			//BIND(GetMinRange);
			//BIND(GetNumProjectiles);
			//BIND(GetOutOfRangeMultiplier);
			//BIND(GetProjectileOverride);
			//BIND(GetReach);
			//BIND(GetReloadSpeed);
			//BIND(GetResist);
			//BIND(GetSightedTransition);
			//BIND(GetSkill);
			//BIND(GetSpeed);
			//BIND(GetStagger);
			//BIND(GetWeight);
			//BIND(SetAccuracyBonus);
			//BIND(SetActionPointCost);
			//BIND(SetAddAmmoList);
			//BIND(SetAmmo);
			//BIND(SetAmmoCapacity);
			//BIND(SetArmorHealth);
			//BIND(SetArmorRating);
			//BIND(SetAttackDamage);
			//BIND(SetAttackDelay);
			//BIND(SetCritChargeBonus);
			//BIND(SetCritMultiplier);
			//BIND(SetDamageTypes);
			//BIND(SetFlag);
			//BIND(SetGoldValue);
			//BIND(SetKeywords);
			//BIND(SetMaxRange);
			//BIND(SetMinRange);
			//BIND(SetNumProjectiles);
			//BIND(SetOutOfRangeMultiplier);
			//BIND(SetProjectileOverride);
			//BIND(SetReach);
			//BIND(SetReloadSpeed);
			//BIND(SetResist);
			//BIND(SetSightedTransition);
			//BIND(SetSkill);
			//BIND(SetSpeed);
			//BIND(SetStagger);
			//BIND(SetWeight);

			logger::info("bound {} script"sv, obj);
		}
	}
}
