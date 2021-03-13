#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace Form
	{
		inline std::uint32_t AddSlotToMask(
			RE::TESForm& a_self,
			std::uint32_t a_slotMask)
		{
			const auto biped = a_self.As<RE::BGSBipedObjectForm>();
			return biped ? biped->bipedModelData.bipedObjectSlots |= a_slotMask : 0;
		}

		inline std::string GetDescription(const RE::TESForm& a_self)
		{
			const auto desc = a_self.As<RE::TESDescription>();
			if (desc) {
				RE::BSStringT<char> buf;
				desc->descriptionText.GetDescription(buf, nullptr);
				return std::string(buf);
			} else {
				return {};
			}
		}

		inline RE::EnchantmentItem* GetEnchantment(const RE::TESForm& a_self)
		{
			const auto ench = a_self.As<RE::TESEnchantableForm>();
			return ench ? ench->GetBaseEnchanting() : nullptr;
		}

		inline std::int32_t GetEnchantmentValue(const RE::TESForm& a_self)
		{
			const auto ench = a_self.As<RE::TESEnchantableForm>();
			return ench && ench->GetBaseEnchanting() ? ench->GetBaseCharge() : 0;
		}

		inline RE::BGSEquipSlot* GetEquipType(const RE::TESForm& a_self)
		{
			const auto equip = a_self.As<RE::BGSEquipType>();
			return equip ? equip->GetEquipSlot(nullptr) : nullptr;
		}

		inline std::string_view GetIconPath(const RE::TESForm& a_self)
		{
			const auto icon = a_self.As<RE::TESIcon>();
			return icon ? static_cast<std::string_view>(icon->textureName) : ""sv;
		}

		inline std::vector<RE::BGSKeyword*> GetKeywords(const RE::TESForm& a_self)
		{
			std::vector<RE::BGSKeyword*> result;
			const auto keywords = a_self.As<RE::BGSKeywordForm>();
			if (keywords) {
				result.resize(keywords->numKeywords, nullptr);
				// TODO: IKeywordFormBase::CollectAllKeywords a better choice?
				std::copy_n(
					std::execution::unseq,
					keywords->keywords,
					keywords->numKeywords,
					result.begin());
			}

			return result;
		}

		inline std::uint32_t GetMaskForSlot(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			std::monostate,
			std::uint32_t a_slot)
		{
			if (30 <= a_slot && a_slot <= 61) {
				return 1 << (a_slot - 30);
			} else {
				a_vm.PostError("slot is out of range"sv, a_stackID, Severity::kError);
				return 0;
			}
		}

		inline std::string_view GetMessageIconPath(const RE::TESForm& a_self)
		{
			const auto msg = a_self.As<RE::BGSMessageIcon>();
			return msg ? static_cast<std::string_view>(msg->GetMessageIconTextureName()) : ""sv;
		}

		inline std::string_view GetName(const RE::TESForm& a_self)
		{
			const auto full = a_self.As<RE::TESFullName>();
			const auto str = full ? full->GetFullName() : "";
			return str ? str : ""sv;
		}

		inline RE::TESRace* GetRaceForm(const RE::TESForm& a_self)
		{
			const auto race = a_self.As<RE::TESRaceForm>();
			return race ? race->GetFormRace() : nullptr;
		}

		inline std::uint32_t GetSlotMask(const RE::TESForm& a_self)
		{
			const auto biped = a_self.As<RE::BGSBipedObjectForm>();
			return biped ? biped->GetFilledSlots() : 0;
		}

		inline float GetWeight(const RE::TESForm& a_self)
		{
			const auto weight = a_self.As<RE::TESWeightForm>();
			return weight ? weight->GetFormWeight() : 0.0F;
		}

		inline std::string_view GetWorldModelPath(const RE::TESForm& a_self)
		{
			const auto model = a_self.As<RE::TESModel>();
			const auto str = model ? model->GetModel() : nullptr;
			return str ? str : ""sv;
		}

		inline bool HasWorldModel(const RE::TESForm& a_self)
		{
			return a_self.As<RE::TESModel>() != nullptr;
		}

		inline std::uint32_t RemoveSlotFromMask(
			RE::TESForm& a_self,
			std::uint32_t a_slotMask)
		{
			const auto biped = a_self.As<RE::BGSBipedObjectForm>();
			return biped ? biped->bipedModelData.bipedObjectSlots &= ~a_slotMask : 0;
		}

		inline void SetEnchantment(
			RE::TESForm& a_self,
			RE::EnchantmentItem* a_enchantment)
		{
			const auto ench = a_self.As<RE::TESEnchantableForm>();
			if (ench) {
				ench->SetBaseEnchanting(a_enchantment);
			}
		}

		inline void SetEnchantmentValue(
			RE::TESForm& a_self,
			std::uint16_t a_value)
		{
			const auto ench = a_self.As<RE::TESEnchantableForm>();
			if (ench) {
				ench->SetBaseCharge(a_value);
			}
		}

		inline void SetEquipType(
			RE::TESForm& a_self,
			RE::BGSEquipSlot* a_type)
		{
			const auto equip = a_self.As<RE::BGSEquipType>();
			if (equip) {
				equip->SetEquipSlot(a_type);
			}
		}

		inline void SetGoldValue(
			RE::TESForm& a_self,
			std::int32_t a_value)
		{
			RE::TESValueForm::SetFormValue(a_self, a_value);  // divergent
		}

		inline void SetIconPath(
			RE::TESForm& a_self,
			std::string_view a_path)
		{
			const auto icon = a_self.As<RE::TESIcon>();
			if (icon) {
				icon->textureName = a_path;
			}
		}

		inline void SetMessageIconPath(
			RE::TESForm& a_self,
			std::string_view a_name)
		{
			const auto icon = a_self.As<RE::BGSMessageIcon>();
			if (icon) {
				icon->SetMessageIconTextureName(a_name);
			}
		}

		inline void SetName(
			RE::TESForm& a_self,
			std::string_view a_name)
		{
			RE::TESFullName::SetFullName(a_self, a_name);  // divergent
		}

		inline void SetRaceForm(
			RE::TESForm& a_self,
			RE::TESRace* a_newRace)
		{
			const auto race = a_self.As<RE::TESRaceForm>();
			if (race) {
				race->SetFormRace(a_newRace);
			}
		}

		inline void SetSlotMask(
			RE::TESForm& a_self,
			std::uint32_t a_slotMask)
		{
			const auto biped = a_self.As<RE::BGSBipedObjectForm>();
			if (biped) {
				biped->bipedModelData.bipedObjectSlots = a_slotMask;
			}
		}

		inline void SetWeight(
			RE::TESForm& a_self,
			float a_weight)
		{
			const auto weight = a_self.As<RE::TESWeightForm>();
			if (weight) {
				weight->SetFormWeight(a_weight);
			}
		}

		inline void SetWorldModelPath(
			RE::TESForm& a_self,
			std::string_view a_path)
		{
			const auto model = a_self.As<RE::TESModel>();
			if (model) {
				model->SetModel(a_path.empty() ? "" : a_path.data());
			}
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "Form"sv;

			BIND(AddSlotToMask);
			BIND(GetDescription);
			BIND(GetEnchantment);
			BIND(GetEnchantmentValue);
			BIND(GetEquipType);
			BIND(GetIconPath);
			BIND(GetKeywords);
			BIND(GetMaskForSlot, true);
			BIND(GetMessageIconPath);
			BIND(GetName);
			BIND(GetRaceForm);
			BIND(GetSlotMask);
			BIND(GetWeight);
			BIND(GetWorldModelPath);
			BIND(HasWorldModel);
			BIND(RemoveSlotFromMask);
			BIND(SetEnchantment);
			BIND(SetEnchantmentValue);
			BIND(SetEquipType);
			BIND(SetGoldValue);
			BIND(SetIconPath);
			BIND(SetMessageIconPath);
			BIND(SetName);
			BIND(SetRaceForm);
			BIND(SetSlotMask);
			BIND(SetWeight);
			BIND(SetWorldModelPath);

			logger::info("bound {} script"sv, obj);
		}
	}
}
