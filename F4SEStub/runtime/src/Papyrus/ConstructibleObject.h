#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace ConstructibleObject
	{
		using ConstructibleComponent = structure_wrapper<"ConstructibleObject", "ConstructibleComponent">;

		inline std::vector<ConstructibleComponent> GetConstructibleComponents(const RE::BGSConstructibleObject& a_self)
		{
			std::vector<ConstructibleComponent> result;
			if (a_self.requiredItems) {
				result.reserve(a_self.requiredItems->size());
				for (const auto& item : *a_self.requiredItems) {
					auto& back = result.emplace_back();
					back.insert("object"sv, item.first);
					back.insert("count"sv, item.second.i);
				}
			}

			return result;
		}

		inline std::uint32_t GetCreatedCount(const RE::BGSConstructibleObject& a_self)
		{
			return a_self.data.numConstructed;
		}

		inline RE::TESForm* GetCreatedObject(const RE::BGSConstructibleObject& a_self)
		{
			return a_self.createdItem;
		}

		inline std::uint32_t GetPriority(const RE::BGSConstructibleObject& a_self)
		{
			return a_self.data.workshopPriority;
		}

		inline RE::BGSKeyword* GetWorkbenchKeyword(const RE::BGSConstructibleObject& a_self)
		{
			return a_self.benchKeyword;
		}

		inline void SetConstructibleComponents(
			RE::BGSConstructibleObject& a_self,
			std::vector<ConstructibleComponent> a_components)
		{
			auto& items = a_self.requiredItems;
			if (!items) {
				items = new std::remove_pointer_t<decltype(a_self.requiredItems)>;
			}

			items->clear();
			items->reserve(static_cast<std::uint32_t>(a_components.size()));
			for (const auto& comp : a_components) {
				auto& back = items->emplace_back();
				back.first = comp.find<RE::TESForm*>("object"sv).value_or(nullptr);
				back.second.i = comp.find<std::uint32_t>("count"sv).value_or(0);
			}
		}

		inline void SetCreatedCount(
			RE::BGSConstructibleObject& a_self,
			std::uint16_t a_count)
		{
			a_self.data.numConstructed = a_count;
		}

		inline void SetCreatedObject(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			RE::BGSConstructibleObject& a_self,
			RE::TESForm* a_form)
		{
			if (!a_form) {
				a_vm.PostError("akForm cannot be a none form"sv, a_stackID, Severity::kError);
			} else {
				a_self.createdItem = a_form;
			}
		}

		inline void SetPriority(RE::BGSConstructibleObject& a_self, std::uint16_t a_priority)
		{
			a_self.data.workshopPriority = a_priority;
		}

		inline void SetWorkbenchKeyword(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			RE::BGSConstructibleObject& a_self,
			RE::BGSKeyword* a_keyword)
		{
			if (!a_keyword) {
				a_vm.PostError("akKeyword cannot be a none form"sv, a_stackID, Severity::kError);
			} else {
				a_self.benchKeyword = a_keyword;
			}
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "ConstructibleObject"sv;

			BIND(GetConstructibleComponents);
			BIND(GetCreatedCount);
			BIND(GetCreatedObject);
			BIND(GetPriority);
			BIND(GetWorkbenchKeyword);
			BIND(SetConstructibleComponents);
			BIND(SetCreatedCount);
			BIND(SetCreatedObject);
			BIND(SetPriority);
			BIND(SetWorkbenchKeyword);

			logger::info("bound {} script"sv, obj);
		}
	}
}
