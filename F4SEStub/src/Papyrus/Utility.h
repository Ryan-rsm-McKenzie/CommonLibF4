#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace Utility
	{
		inline const RE::BSScript::Variable* VarArrayToVar(
			std::monostate,
			std::vector<const RE::BSScript::Variable*> a_vars)
		{
			const auto var = new RE::BSScript::Variable;
			RE::BSScript::PackVariable(*var, a_vars);
			return var;
		}

		inline std::vector<const RE::BSScript::Variable*> VarToVarArray(
			std::monostate,
			const RE::BSScript::Variable* a_var)
		{
			if (a_var && a_var->is<RE::BSScript::Array>()) {
				return RE::BSScript::UnpackVariable<std::vector<const RE::BSScript::Variable*>>(*a_var);
			} else {
				return {};
			}
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "Utility"sv;

			BIND(VarArrayToVar, true);
			BIND(VarToVarArray, true);

			logger::info("bound {} script"sv, obj);
		}
	}
}
