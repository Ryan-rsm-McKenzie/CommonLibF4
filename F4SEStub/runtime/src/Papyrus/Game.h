#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace Game
	{
		namespace detail
		{
			[[nodiscard]] inline RE::Setting* GetGameSetting(const RE::BSFixedString& a_setting)
			{
				const auto gmst = RE::GameSettingCollection::GetSingleton();
				if (gmst) {
					const auto setting = gmst->settings.find(a_setting);
					if (setting != gmst->settings.end()) {
						return setting->second;
					}
				}

				return nullptr;
			}
		}

		using PluginInfo = structure_wrapper<"Game", "PluginInfo">;

		inline RE::CameraState GetCameraState(std::monostate)
		{
			const auto camera = RE::PlayerCamera::GetSingleton();
			return camera && camera->currentState ?
                       *camera->currentState->id :
                       static_cast<RE::CameraState>(-1);
		}

		inline RE::TESObjectREFR* GetCurrentConsoleRef(std::monostate)
		{
			return RE::Console::GetPickRef().get().get();
		}

		inline std::vector<PluginInfo> GetInstalledLightPlugins(std::monostate)
		{
			std::vector<PluginInfo> result;
			const auto data = RE::TESDataHandler::GetSingleton();
			if (data) {
				for (const auto& mod : data->compiledFileCollection.smallFiles) {
					auto& back = result.emplace_back();
					back.insert("index"sv, mod->GetCompileIndex());
					back.insert("name"sv, mod->GetFilename());
					back.insert<std::string_view>("author"sv, mod->createdBy);
					back.insert<std::string_view>("description"sv, mod->summary);
				}
			}

			return result;
		}

		inline std::vector<PluginInfo> GetInstalledPlugins(std::monostate)
		{
			std::vector<PluginInfo> result;
			const auto data = RE::TESDataHandler::GetSingleton();
			if (data) {
				for (const auto& mod : data->compiledFileCollection.files) {
					auto& back = result.emplace_back();
					back.insert("index"sv, mod->GetCompileIndex());
					back.insert("name"sv, mod->GetFilename());
					back.insert<std::string_view>("author"sv, mod->createdBy);
					back.insert<std::string_view>("description"sv, mod->summary);
				}
			}

			return result;
		}

		inline std::vector<std::string_view> GetPluginDependencies(
			std::monostate,
			RE::BSFixedString a_plugin)
		{
			std::vector<std::string_view> result;
			const auto data = RE::TESDataHandler::GetSingleton();
			if (!data) {
				return result;
			}

			std::span<RE::TESFile*> masters;
			for (const auto& mod : data->files) {
				if (mod->GetFilename() == a_plugin) {
					if (mod->GetCompileIndex() != 0xFFu) {
						masters = std::span{ mod->masterPtrs, mod->masterCount };
					}
					break;
				}
			}

			for (const auto master : masters) {
				if (master) {
					result.push_back(master->GetFilename());
				}
			}

			return result;
		}

		inline void SetGameSettingBool(
			std::monostate,
			RE::BSFixedString a_setting,
			bool a_value)
		{
			const auto setting = detail::GetGameSetting(a_setting);
			if (setting) {
				setting->SetBinary(a_value);
			}
		}

		inline void SetGameSettingFloat(
			std::monostate,
			RE::BSFixedString a_setting,
			float a_value)
		{
			const auto setting = detail::GetGameSetting(a_setting);
			if (setting) {
				setting->SetFloat(a_value);
			}
		}

		inline void SetGameSettingInt(
			std::monostate,
			RE::BSFixedString a_setting,
			std::int32_t a_value)
		{
			const auto setting = detail::GetGameSetting(a_setting);
			if (setting) {
				setting->SetInt(a_value);
			}
		}

		inline void SetGameSettingString(
			std::monostate,
			RE::BSFixedString a_setting,
			std::string_view a_value)
		{
			const auto setting = detail::GetGameSetting(a_setting);
			if (setting) {
				setting->SetString(nullptr);
				static std::string buf;
				buf = a_value;
				buf.shrink_to_fit();
				setting->SetString(buf.data());
			}
		}

		inline void UpdateThirdPerson(std::monostate)
		{
			const auto player = RE::PlayerCharacter::GetSingleton();
			const auto camera = RE::PlayerCamera::GetSingleton();
			const auto third = camera ? camera->GetState<RE::ThirdPersonState>() : nullptr;
			if (player && third) {
				third->ProcessWeaponDrawnChange(player->GetWeaponMagicDrawn());
			}
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "Game"sv;

			BIND(GetCameraState, true);
			BIND(GetCurrentConsoleRef);
			BIND(GetInstalledLightPlugins);
			BIND(GetInstalledPlugins);
			BIND(GetPluginDependencies);
			BIND(SetGameSettingBool);
			BIND(SetGameSettingFloat);
			BIND(SetGameSettingInt);
			BIND(SetGameSettingString);
			BIND(UpdateThirdPerson);

			logger::info("bound {} script"sv, obj);
		}
	}
}
