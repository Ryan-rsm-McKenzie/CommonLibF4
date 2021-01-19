#pragma once

namespace Papyrus
{
	namespace InstanceData
	{
		using DamageTypeInfo = structure_wrapper<"InstanceData", "DamageTypeInfo">;
		using Owner = structure_wrapper<"InstanceData", "Owner">;

		inline std::int32_t GetAttackDamage(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			std::monostate,
			std::optional<Owner> a_owner)
		{
			if (!a_owner) {
				a_vm.PostError("akOwner cannot be a none struct"sv, a_stackID, Severity::kError);
				return 0;
			}

			const auto owner = a_owner->find<RE::TESForm*>("owner"sv);
			const auto index = a_owner->find<RE::BIPED_OBJECT>("slotIndex"sv);
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "InstanceData"sv;

			BIND(GetAttackDamage);

			logger::info("bound {} script"sv, obj);
		}
	}
}
