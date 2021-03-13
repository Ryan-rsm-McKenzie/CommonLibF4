#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace ActorBase
	{
		using BodyWeight = structure_wrapper<"ActorBase", "BodyWeight">;

		inline BodyWeight GetBodyWeight(const RE::TESNPC& a_self)
		{
			constexpr std::array values = {
				"thin"sv,
				"muscular"sv,
				"large"sv
			};

			BodyWeight result;
			for (std::size_t i = 0; i < values.size(); ++i) {
				result.insert(values[i], a_self.morphWeight[i]);
			}

			return result;
		}

		inline std::vector<RE::BGSHeadPart*> GetHeadParts(
			const RE::TESNPC& a_self,
			bool a_overlays)
		{
			const auto parts = a_self.GetHeadParts(a_overlays);
			std::vector<RE::BGSHeadPart*> result(parts.size(), nullptr);
			std::copy_n(
				std::execution::unseq,
				parts.begin(),
				parts.size(),
				result.begin());

			return result;
		}

		inline RE::BGSOutfit* GetOutfit(
			const RE::TESNPC& a_self,
			bool a_sleepOutfit)
		{
			return a_sleepOutfit ? a_self.sleepOutfit : a_self.defOutfit;
		}

		inline RE::TESNPC* GetTemplate(
			const RE::TESNPC& a_self,
			bool a_topMost)
		{
			if (a_topMost && a_self.faceNPC) {
				auto top = a_self.faceNPC;
				while (top->faceNPC) {
					top = top->faceNPC;
				}
				return top;
			} else {
				return a_self.faceNPC;
			}
		}

		inline bool HasHeadPartOverlays(const RE::TESNPC& a_self)
		{
			return a_self.UsingAlternateHeadPartList();
		}

		inline void SetBodyWeight(
			RE::TESNPC& a_self,
			BodyWeight a_weight)
		{
			constexpr std::array values = {
				"thin"sv,
				"muscular"sv,
				"large"sv
			};

			for (std::size_t i = 0; i < values.size(); ++i) {
				a_self.morphWeight[i] =
					a_weight.find<float>(values[i]).value_or(a_self.morphWeight[i]);
			}

			a_self.AddChange(RE::CHANGE_TYPE::kNPCBodyScales);
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "ActorBase"sv;

			BIND(GetBodyWeight);
			BIND(GetHeadParts);
			BIND(GetOutfit);
			BIND(GetTemplate, true);
			BIND(HasHeadPartOverlays);
			BIND(SetBodyWeight);

			logger::info("bound {} script"sv, obj);
		}
	}
}
