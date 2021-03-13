#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace ObjectMod
	{
		using PropertyModifier = structure_wrapper<"ObjectMod", "PropertyModifier">;

		enum class Operator
		{
			kSet,
			kAdd,
			kMultAdd,
			kAnd,
			kOr,
			kRem,

			kError = 0
		};

		inline RE::TESObjectMISC* GetLooseMod(const RE::BGSMod::Attachment::Mod& a_self)
		{
			const auto& mods = RE::BGSMod::Attachment::GetAllLooseMods();
			const auto it = mods.find(std::addressof(a_self));
			return it != mods.end() ? it->second : nullptr;
		}

		inline std::int8_t GetMaxRank(const RE::BGSMod::Attachment::Mod& a_self)
		{
			return a_self.maxRank;
		}

		inline std::int8_t GetPriority(const RE::BGSMod::Attachment::Mod& a_self)
		{
			return a_self.priority;
		}

		inline std::vector<PropertyModifier> GetPropertyModifiers(
			const RE::BGSMod::Attachment::Mod& a_self)
		{
			std::vector<PropertyModifier> result;
			for (const auto& mod : a_self.GetBuffer<RE::BGSMod::Property::Mod>(1)) {
				const auto [obj, v1, v2] = [&]() -> std::tuple<RE::TESForm*, float, float> {
					switch (mod.type) {
					case RE::BGSMod::Property::TYPE::kInt:
					case RE::BGSMod::Property::TYPE::kEnum:
						return {
							nullptr,
							static_cast<float>(mod.data.mm.min.i),
							static_cast<float>(mod.data.mm.max.i)
						};
					case RE::BGSMod::Property::TYPE::kFloat:
						return { nullptr, mod.data.mm.min.f, mod.data.mm.max.f };
					case RE::BGSMod::Property::TYPE::kBool:
						return {
							nullptr,
							static_cast<float>(static_cast<bool>(mod.data.mm.min.i)),
							static_cast<float>(static_cast<bool>(mod.data.mm.max.i))
						};
					case RE::BGSMod::Property::TYPE::kString:
						return { nullptr, 0.0f, 0.0f };
					case RE::BGSMod::Property::TYPE::kForm:
						return { mod.data.form, 0.0f, 0.0f };
					case RE::BGSMod::Property::TYPE::kPair:
						return { RE::TESForm::GetFormByID(mod.data.fv.formID), mod.data.fv.value, 0.0f };
					default:
						return { nullptr, 0.0f, 0.0f };
					}
				}();

				const auto op = [&]() -> Operator {
					switch (mod.type) {
					case RE::BGSMod::Property::TYPE::kInt:
					case RE::BGSMod::Property::TYPE::kFloat:
						switch (mod.op) {
						case RE::BGSMod::Property::OP::kSet:
							return Operator::kSet;
						case RE::BGSMod::Property::OP::kMul:
							return Operator::kMultAdd;
						case RE::BGSMod::Property::OP::kAdd:
							return Operator::kAdd;
						default:
							return Operator::kError;
						}
					case RE::BGSMod::Property::TYPE::kBool:
						switch (mod.op) {
						case RE::BGSMod::Property::OP::kSet:
							return Operator::kSet;
						case RE::BGSMod::Property::OP::kAnd:
							return Operator::kAnd;
						case RE::BGSMod::Property::OP::kOr:
							return Operator::kOr;
						default:
							return Operator::kError;
						}
					case RE::BGSMod::Property::TYPE::kString:
						return Operator::kError;
					case RE::BGSMod::Property::TYPE::kEnum:
						switch (mod.op) {
						case RE::BGSMod::Property::OP::kSet:
							return Operator::kSet;
						default:
							return Operator::kError;
						}
					case RE::BGSMod::Property::TYPE::kForm:
					case RE::BGSMod::Property::TYPE::kPair:
						switch (mod.op) {
						case RE::BGSMod::Property::OP::kSet:
							return Operator::kSet;
						case RE::BGSMod::Property::OP::kRem:
							return Operator::kRem;
						case RE::BGSMod::Property::OP::kAdd:
							return Operator::kAdd;
						default:
							return Operator::kError;
						}
					default:
						return Operator::kError;
					}
				}();

				auto& back = result.emplace_back();
				back.insert("target"sv, mod.target);
				back.insert("operator"sv, op);
				back.insert("object"sv, obj);
				back.insert("value1"sv, v1);
				back.insert("value2"sv, v2);
			}

			return result;
		}

		inline void SetMaxRank(
			RE::BGSMod::Attachment::Mod& a_self,
			std::int8_t a_rank)
		{
			a_self.maxRank = a_rank;
		}

		inline void SetPriority(
			RE::BGSMod::Attachment::Mod& a_self,
			std::int8_t a_priority)
		{
			a_self.priority = a_priority;
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "ObjectMod"sv;

			BIND(GetLooseMod);
			BIND(GetMaxRank);
			BIND(GetPriority);
			BIND(GetPropertyModifiers);
			BIND(SetMaxRank);
			BIND(SetPriority);

			logger::info("bound {} script"sv, obj);
		}
	}
}
