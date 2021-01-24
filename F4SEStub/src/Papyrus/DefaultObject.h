#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace DefaultObject
	{
		inline RE::TESForm* Get(
			const RE::BGSDefaultObject& a_self)
		{
			return a_self.form;
		}

		inline RE::TESForm* GetDefaultObject(
			std::monostate,
			std::string_view a_editorID)
		{
			return RE::TESForm::GetFormByEditorID(a_editorID);
		}

		inline void Set(
			RE::BGSDefaultObject& a_self,
			RE::TESForm* a_newForm)
		{
			a_self.form = a_newForm;
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "DefaultObject"sv;

			BIND(Get);
			BIND(GetDefaultObject);
			BIND(Set);

			logger::info("bound {} script"sv, obj);
		}
	}
}
