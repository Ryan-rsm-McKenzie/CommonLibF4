#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace UI
	{
		using MenuData = structure_wrapper<"UI", "MenuData">;

		inline bool CloseMenu(
			std::monostate,
			RE::BSFixedString a_menuName)
		{
			const auto msg = RE::UIMessageQueue::GetSingleton();
			const auto ui = RE::UI::GetSingleton();
			if (msg && ui && ui->GetMenu(a_menuName)) {
				msg->AddMessage(a_menuName, RE::UI_MESSAGE_TYPE::kHide);
				return true;
			} else {
				return false;
			}
		}

		inline const RE::BSScript::Variable* Get(
			std::monostate,
			[[maybe_unused]] std::string_view a_menu,
			[[maybe_unused]] std::string_view a_path)
		{
			return nullptr;
		}

		inline bool IsMenuOpen(
			std::monostate,
			RE::BSFixedString a_menu)
		{
			const auto ui = RE::UI::GetSingleton();
			return ui ? ui->GetMenuOpen(a_menu) : false;
		}

		inline bool IsMenuRegistered(
			std::monostate,
			RE::BSFixedString a_menu)
		{
			const auto ui = RE::UI::GetSingleton();
			return ui ? ui->GetMenu(a_menu) != nullptr : false;
		}

		inline const RE::BSScript::Variable* Invoke(
			std::monostate,
			[[maybe_unused]] std::string_view a_menu,
			[[maybe_unused]] std::string_view a_path,
			[[maybe_unused]] std::vector<const RE::BSScript::Variable*> a_args)
		{
			return nullptr;
		}

		inline bool Load(
			std::monostate,
			[[maybe_unused]] std::string_view a_menu,
			[[maybe_unused]] std::string_view a_sourceVar,
			[[maybe_unused]] std::string_view a_assetPath,
			[[maybe_unused]] RE::BSScript::Object* a_receiver,
			[[maybe_unused]] std::string_view a_callback)
		{
			return false;
		}

		inline bool OpenMenu(
			std::monostate,
			RE::BSFixedString a_menuName)
		{
			const auto msg = RE::UIMessageQueue::GetSingleton();
			const auto ui = RE::UI::GetSingleton();
			if (msg && ui && ui->GetMenu(a_menuName)) {
				msg->AddMessage(a_menuName, RE::UI_MESSAGE_TYPE::kShow);
				return true;
			} else {
				return false;
			}
		}

		inline bool RegisterCustomMenu(
			std::monostate,
			[[maybe_unused]] std::string_view a_menuName,
			[[maybe_unused]] std::string_view a_menuPath,
			[[maybe_unused]] std::string_view a_rootPath,
			[[maybe_unused]] MenuData a_data)
		{
			return false;
		}

		inline bool Set(
			std::monostate,
			[[maybe_unused]] std::string_view a_menu,
			[[maybe_unused]] std::string_view a_path,
			[[maybe_unused]] const RE::BSScript::Variable* a_arg)
		{
			return false;
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "UI"sv;

			// TODO
			BIND(CloseMenu);
			//BIND(Get, true);
			BIND(IsMenuOpen, true);
			BIND(IsMenuRegistered, true);
			//BIND(Invoke, true);
			//BIND(Load, true);
			BIND(OpenMenu);
			//BIND(RegisterCustomMenu, true);
			//BIND(Set, true);

			logger::info("bound {} script"sv, obj);
		}
	}
}
