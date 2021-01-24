#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace MatSwap
	{
		using RemapData = structure_wrapper<"MatSwap", "RemapData">;

		inline std::vector<RemapData> GetRemapData(const RE::BGSMaterialSwap& a_self)
		{
			std::vector<RemapData> result;
			for (const auto& [key, value] : a_self.swapMap) {
				auto& back = result.emplace_back();
				back.insert<std::string_view>("source"sv, key);
				back.insert<std::string_view>("target"sv, value.swapMaterial);
				back.insert("colorIndex"sv, value.colorRemappingIndex);
			}

			return result;
		}

		inline void SetRemapData(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			RE::BGSMaterialSwap& a_self,
			std::vector<RemapData> a_data)
		{
			if (a_data.empty()) {
				a_vm.PostError("data cannot be empty"sv, a_stackID, Severity::kError);
				return;
			}

			decltype(a_self.swapMap) map;
			map.reserve(static_cast<std::uint32_t>(a_data.size() / 0.7));
			for (const auto& data : a_data) {
				map.emplace(
					data.find<RE::BSFixedString>("source"sv).value_or(""sv),
					RE::BGSMaterialSwap::Entry{
						data.find<RE::BSFixedString>("target"sv).value_or(""sv),
						data.find<float>("colorIndex"sv).value_or(0.0f) });
			}

			std::swap(map, a_self.swapMap);
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "MatSwap"sv;

			BIND(GetRemapData);
			BIND(SetRemapData);

			logger::info("bound {} script"sv, obj);
		}
	}
}
