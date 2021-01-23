#pragma once

namespace Papyrus
{
	namespace ObjectReference
	{
		using ConnectPoint = structure_wrapper<"ObjectReference", "ConnectPoint">;

		inline RE::TESObjectREFR* AttachWire(const RE::TESObjectREFR&, RE::TESObjectREFR*, RE::TESForm*)
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

		inline bool Scrap(const RE::TESObjectREFR&, RE::TESObjectREFR*)
		{
			return false;
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "ObjectReference"sv;

			//BIND(AttachWire); TODO
			BIND(GetAllMods);
			BIND(GetConnectedObjects);
			BIND(GetDisplayName);
			//BIND(Scrap); TODO

			logger::info("bound {} script"sv, obj);
		}
	}
}
