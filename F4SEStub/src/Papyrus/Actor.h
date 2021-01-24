#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace Actor
	{
		using WornItem = structure_wrapper<"Actor", "WornItem">;

		inline RE::TESObjectREFR* GetFurnitureReference(const RE::Actor& a_self)
		{
			const auto proc = a_self.currentProcess;
			const auto middleHigh = proc ? proc->middleHigh : nullptr;
			if (middleHigh) {
				const auto& furn =
					a_self.interactingState != RE::INTERACTING_STATE::kNotInteracting ?
                        middleHigh->currentFurniture :
                        middleHigh->occupiedFurniture;
				return furn.get().get();
			} else {
				return nullptr;
			}
		}

		inline std::optional<WornItem> GetWornItem(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			const RE::Actor& a_self,
			RE::BIPED_OBJECT a_slotIndex,
			bool a_firstPerson)
		{
			if (a_slotIndex >= RE::BIPED_OBJECT::kTotal) {
				a_vm.PostError("slotIndex out of range"sv, a_stackID, Severity::kError);
				return std::nullopt;
			}

			const auto biped = [&]() {
				if (a_firstPerson && a_self.IsPlayerRef()) {
					return static_cast<const RE::PlayerCharacter&>(a_self).firstPersonBipedAnim;
				} else {
					return a_self.biped;
				}
			}();

			if (!biped) {
				return std::nullopt;
			}

			WornItem result;
			const auto& slot = biped->object[stl::to_underlying(a_slotIndex)];
			result.insert("item"sv, slot.parent.object);
			result.insert("model"sv, slot.armorAddon);
			if (slot.part) {
				const auto modelName = slot.part->GetModel();
				result.insert<std::string_view>("modelName"sv, modelName ? modelName : ""sv);
				if (const auto swap = slot.part->GetAsModelMaterialSwap(); swap) {
					result.insert("materialSwap"sv, swap->swapForm);
				}
			}
			result.insert("texture"sv, slot.skinTexture);

			return result;
		}

		inline std::optional<std::vector<RE::BGSMod::Attachment::Mod*>> GetWornItemMods(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			const RE::Actor& a_self,
			RE::BIPED_OBJECT a_slotIndex)
		{
			if (a_slotIndex >= RE::BIPED_OBJECT::kTotal) {
				a_vm.PostError("slotIndex out of range"sv, a_stackID, Severity::kError);
				return std::nullopt;
			}

			const auto object =
				a_self.biped ?
                    a_self.biped->object[stl::to_underlying(a_slotIndex)].parent.object :  // TODO: GetCurrentBiped()?
                    nullptr;
			const auto inv = a_self.inventoryList;
			if (!object || !inv) {
				return std::nullopt;
			}

			const RE::BSAutoReadLock l{ inv->rwLock };
			for (const auto& item : inv->data) {
				for (auto stack = item.stackData.get(); stack; stack = stack->nextStack.get()) {
					if (stack->IsEquipped() && stack->extra) {
						std::vector<RE::BGSMod::Attachment::Mod*> mods;
						const auto xInstance = stack->extra->GetByType<RE::BGSObjectInstanceExtra>();
						if (xInstance && xInstance->values) {
							const auto data = xInstance->GetIndexData();
							mods.reserve(data.size());
							for (const auto& elem : data) {
								const auto mod = RE::TESForm::GetFormByID<RE::BGSMod::Attachment::Mod>(elem.objectID);
								if (mod) {
									mods.push_back(mod);
								}
							}
						}

						return mods;
					}
				}
			}

			return std::nullopt;
		}

		inline void QueueUpdate(
			RE::Actor& a_self,
			bool a_doEquipment,
			std::uint32_t a_flags)
		{
			a_self.Reset3D(a_doEquipment, 0, true, a_flags);
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "Actor"sv;

			BIND(GetFurnitureReference);
			BIND(GetWornItem);
			BIND(GetWornItemMods);
			BIND(QueueUpdate);

			logger::info("bound {} script"sv, obj);
		}
	}
}
