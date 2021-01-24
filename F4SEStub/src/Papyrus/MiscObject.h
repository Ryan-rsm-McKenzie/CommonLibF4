#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace MiscObject
	{
		using MiscComponent = structure_wrapper<"MiscObject", "MiscComponent">;

		inline std::vector<MiscComponent> GetMiscComponents(const RE::TESObjectMISC& a_self)
		{
			std::vector<MiscComponent> result;
			if (a_self.componentData) {
				for (const auto& [first, second] : *a_self.componentData) {
					if (const auto comp = first ? first->As<RE::BGSComponent>() : nullptr; comp) {
						auto& back = result.emplace_back();
						back.insert("object"sv, comp);
						back.insert("count"sv, second.i);
					}
				}
			}

			return result;
		}

		inline void SetMiscComponents(
			RE::TESObjectMISC& a_self,
			std::vector<MiscComponent> a_components)
		{
			if (!a_self.componentData) {
				a_self.componentData = new std::remove_pointer_t<decltype(a_self.componentData)>;
			}

			for (const auto& comp : a_components) {
				a_self.componentData->emplace_back(
					comp.find<RE::BGSComponent*>("object"sv).value_or(nullptr),
					comp.find<std::uint32_t>("count"sv).value_or(0));
			}
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "MiscObject"sv;

			BIND(GetMiscComponents);
			BIND(SetMiscComponents);

			logger::info("bound {} script"sv, obj);
		}
	}
}
