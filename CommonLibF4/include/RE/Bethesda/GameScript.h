#pragma once

#include "RE/Bethesda/BSScript.h"

namespace RE
{
	namespace GameScript
	{
		inline void LogFormError(
			const TESForm* a_obj,
			const char* a_error,
			BSScript::IVirtualMachine* a_vm,
			std::uint32_t a_stackID,
			BSScript::ErrorLogger::Severity a_severity = BSScript::ErrorLogger::Severity::kError)
		{
			using func_t = decltype(&LogFormError);
			REL::Relocation<func_t> func{ REL::ID(1081933) };
			return func(a_obj, a_error, a_vm, a_stackID, a_severity);
		}
	}
}
