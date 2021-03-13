#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace ObjectReference
	{
		using ConnectPoint = structure_wrapper<"ObjectReference", "ConnectPoint">;

		inline std::vector<structure_wrapper<"MatSwap", "RemapData">> ApplyMaterialSwap(
			[[maybe_unused]] const RE::GameScript::RefrOrInventoryObj a_self,
			[[maybe_unused]] RE::BGSMaterialSwap* a_swap,
			[[maybe_unused]] bool a_renameMaterial)
		{
			return {};
		}

		inline RE::TESObjectREFR* AttachWire(
			[[maybe_unused]] const RE::TESObjectREFR& a_self,
			[[maybe_unused]] RE::TESObjectREFR* a_ref,
			[[maybe_unused]] RE::TESForm* a_spline)
		{
			return nullptr;
		}

		inline std::vector<RE::BGSMod::Attachment::Mod*> GetAllMods(const RE::GameScript::RefrOrInventoryObj a_self)
		{
			std::vector<RE::BGSMod::Attachment::Mod*> result;
			const auto data = GetReferenceData(a_self);
			if (data) {
				const auto& [obj, extra] = *data;
				const auto xInst = extra ? extra->GetByType<RE::BGSObjectInstanceExtra>() : nullptr;
				if (xInst) {
					const auto indices = xInst->GetIndexData();
					for (const auto& idx : indices) {
						result.push_back(RE::TESForm::GetFormByID<RE::BGSMod::Attachment::Mod>(idx.objectID));
					}
				}
			}

			return result;
		}

		inline std::vector<RE::TESObjectREFR*> GetConnectedObjects(const RE::TESObjectREFR& a_self)
		{
			std::vector<RE::TESObjectREFR*> result;

			const auto xPower = a_self.extraList ? a_self.extraList->GetByType<RE::ExtraPowerLinks>() : nullptr;
			if (xPower) {
				for (const auto& link : xPower->powerLinks) {
					if (const auto ref = RE::TESForm::GetFormByID<RE::TESObjectREFR>(link.formID); ref) {
						result.push_back(ref);
					}
				}
			}

			return result;
		}

		inline std::vector<ConnectPoint> GetConnectPoints([[maybe_unused]] const RE::TESObjectREFR& a_self)
		{
			return {};
		}

		inline RE::BSFixedString GetDisplayName(const RE::GameScript::RefrOrInventoryObj a_self)
		{
			const auto data = GetReferenceData(a_self);
			if (data) {
				const auto& [obj, extra] = *data;
				const auto xText = extra ? extra->GetByType<RE::ExtraTextDisplayData>() : nullptr;
				if (xText) {
					return xText->GetDisplayName(obj);
				}

				const auto full = obj ? obj->As<RE::TESFullName>() : nullptr;
				if (full) {
					return full->fullName;
				}
			}

			return ""sv;
		}

		inline std::vector<RE::TESForm*> GetInventoryItems(const RE::TESObjectREFR& a_self)
		{
			std::vector<RE::TESForm*> result;
			if (const auto inv = a_self.inventoryList; inv) {
				const RE::BSAutoReadLock l{ inv->rwLock };
				for (const auto& item : inv->data) {
					result.push_back(item.object);
				}
			}

			return result;
		}

		inline float GetInventoryWeight(RE::TESObjectREFR& a_self)
		{
			return a_self.GetWeightInContainer();
		}

		inline RE::BGSMaterialSwap* GetMaterialSwap(
			const RE::GameScript::RefrOrInventoryObj a_self)
		{
			const auto data = GetReferenceData(a_self);
			if (data) {
				const auto& [obj, extra] = *data;
				const auto xSwap = extra ? extra->GetByType<RE::ExtraMaterialSwap>() : nullptr;
				if (xSwap) {
					return xSwap->swap;
				}
			}

			return nullptr;
		}

		inline bool Scrap(
			[[maybe_unused]] const RE::TESObjectREFR& a_self,
			[[maybe_unused]] RE::TESObjectREFR* a_workshop)
		{
			return false;
		}

		inline void SetMaterialSwap(
			const RE::GameScript::RefrOrInventoryObj a_self,
			RE::BGSMaterialSwap* a_swap)
		{
			const auto data = GetReferenceData(a_self);
			if (data) {
				const auto& [obj, extra] = *data;
				if (extra) {
					if (a_swap) {
						auto xSwap = extra->GetByType<RE::ExtraMaterialSwap>();
						if (!xSwap) {
							xSwap = new RE::ExtraMaterialSwap();
							extra->AddExtra(xSwap);
						}

						xSwap->swap = a_swap;
					} else {
						extra->RemoveExtra<RE::ExtraMaterialSwap>();
					}
				}
			}
		}

		inline bool TransmitConnectedPower([[maybe_unused]] const RE::TESObjectREFR& a_self)
		{
			return false;
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "ObjectReference"sv;

			// TODO
			//BIND(ApplyMaterialSwap, true);
			//BIND(AttachWire, true);
			BIND(GetAllMods);
			BIND(GetConnectedObjects);
			//BIND(GetConnectPoints, true);
			BIND(GetDisplayName);
			BIND(GetInventoryItems, true);
			BIND(GetInventoryWeight);
			BIND(GetMaterialSwap);
			//BIND(Scrap, true);
			BIND(SetMaterialSwap);
			//BIND(TransmitConnectedPower, true);

			logger::info("bound {} script"sv, obj);
		}
	}
}
