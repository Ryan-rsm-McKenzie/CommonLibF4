#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace Cell
	{
		inline RE::TESWaterForm* GetWaterType(const RE::TESObjectCELL& a_self)
		{
			return a_self.GetWaterType();
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "Cell"sv;

			BIND(GetWaterType);

			logger::info("bound {} script"sv, obj);
		}
	}
}
