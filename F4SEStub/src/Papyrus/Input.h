#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace Input
	{
		namespace detail
		{
			enum
			{
				kKeyboardBegin = 0,
				kKeyboardEnd = 256,

				kMouseBegin = kKeyboardEnd,
				kMouseEnd = 266,

				kGamepadBegin = kMouseEnd,
				kGamepadEnd = 282
			};

			namespace Gamepad
			{
				struct Mask
				{
					// XINPUT_GAMEPAD
					enum
					{
						kUp = 1u << 0,
						kDown = 1u << 1,
						kLeft = 1u << 2,
						kRight = 1u << 3,
						kStart = 1u << 4,
						kBack = 1u << 5,
						kLS = 1u << 6,
						kRS = 1u << 7,
						kLB = 1u << 8,
						kRB = 1u << 9,
						kA = 1u << 12,
						kB = 1u << 13,
						kX = 1u << 14,
						kY = 1u << 15,

						kLT = kUp | kRight,
						kRT = kDown | kRight
					};
				};

				struct Key
				{
					enum
					{
						kUp = kGamepadBegin,
						kDown,
						kLeft,
						kRight,
						kStart,
						kBack,
						kLS,
						kRS,
						kLB,
						kRB,
						kA,
						kB,
						kX,
						kY,
						kLT,
						kRT
					};
				};

				[[nodiscard]] inline std::optional<std::int32_t> Key2Mask(std::int32_t a_key) noexcept
				{
#define GAMEPAD_CASE(a_case) \
	case Key::a_case:        \
		return Mask::a_case

					switch (a_key) {
						GAMEPAD_CASE(kUp);
						GAMEPAD_CASE(kDown);
						GAMEPAD_CASE(kLeft);
						GAMEPAD_CASE(kRight);
						GAMEPAD_CASE(kStart);
						GAMEPAD_CASE(kBack);
						GAMEPAD_CASE(kLS);
						GAMEPAD_CASE(kRS);
						GAMEPAD_CASE(kLB);
						GAMEPAD_CASE(kRB);
						GAMEPAD_CASE(kA);
						GAMEPAD_CASE(kB);
						GAMEPAD_CASE(kX);
						GAMEPAD_CASE(kY);
						GAMEPAD_CASE(kLT);
						GAMEPAD_CASE(kRT);
					default:
						return std::nullopt;
					}

#undef GAMEPAD_CASE
				}

				[[nodiscard]] inline std::optional<std::int32_t> Mask2Key(std::int32_t a_mask) noexcept
				{
#define GAMEPAD_CASE(a_case) \
	case Mask::a_case:       \
		return Key::a_case

					switch (a_mask) {
						GAMEPAD_CASE(kUp);
						GAMEPAD_CASE(kDown);
						GAMEPAD_CASE(kLeft);
						GAMEPAD_CASE(kRight);
						GAMEPAD_CASE(kStart);
						GAMEPAD_CASE(kBack);
						GAMEPAD_CASE(kLS);
						GAMEPAD_CASE(kRS);
						GAMEPAD_CASE(kLB);
						GAMEPAD_CASE(kRB);
						GAMEPAD_CASE(kA);
						GAMEPAD_CASE(kB);
						GAMEPAD_CASE(kX);
						GAMEPAD_CASE(kY);
						GAMEPAD_CASE(kLT);
						GAMEPAD_CASE(kRT);
					default:
						return std::nullopt;
					}

#undef GAMEPAD_CASE
				}
			}
		}

		inline std::string_view GetMappedControl(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			std::monostate,
			std::int32_t a_keycode)
		{
			const auto find = [](std::int32_t a_button, RE::INPUT_DEVICE a_device) noexcept
				-> std::optional<std::string_view> {
				const auto controls = RE::ControlMap::GetSingleton();
				const auto context =
					controls ?
                        controls->controlMaps[stl::to_underlying(RE::UserEvents::INPUT_CONTEXT_ID::kMainGameplay)] :
                        nullptr;
				if (context) {
					const auto& mappings = context->deviceMappings[stl::to_underlying(a_device)];
					const auto it = std::find_if(
						mappings.begin(),
						mappings.end(),
						[&](const auto& a_mapping) noexcept { return a_mapping.inputKey == a_button; });
					if (it != mappings.end()) {
						return it->eventID;
					}
				}

				return std::nullopt;
			};

			std::optional<std::string_view> result;
			if (detail::kKeyboardBegin <= a_keycode && a_keycode < detail::kKeyboardEnd) {
				result = find(a_keycode - detail::kGamepadBegin, RE::INPUT_DEVICE::kKeyboard);
			} else if (detail::kMouseBegin <= a_keycode && a_keycode < detail::kMouseEnd) {
				result = find(a_keycode - detail::kMouseBegin, RE::INPUT_DEVICE::kMouse);
			} else if (detail::kGamepadBegin <= a_keycode && a_keycode < detail::kGamepadEnd) {
				const auto mask = detail::Gamepad::Key2Mask(a_keycode - detail::kGamepadBegin);
				result = mask ? find(*mask, RE::INPUT_DEVICE::kGamepad) : std::nullopt;
			} else {
				a_vm.PostError("keycode is out of range"sv, a_stackID, Severity::kError);
				result = std::nullopt;
			}

			return result.value_or(""sv);
		}

		inline std::int32_t GetMappedKey(
			RE::BSScript::IVirtualMachine& a_vm,
			std::uint32_t a_stackID,
			std::monostate,
			RE::BSFixedString a_control,
			RE::INPUT_DEVICE a_deviceType)
		{
			using Context = RE::UserEvents::INPUT_CONTEXT_ID;
			if (a_deviceType > RE::INPUT_DEVICE::kSupported && a_deviceType != RE::INPUT_DEVICE::kNone) {
				a_vm.PostError("deviceType is out of range"sv, a_stackID, Severity::kError);
				return -1;
			}

			const auto controls = RE::ControlMap::GetSingleton();
			const auto context =
				controls ?
                    controls->controlMaps[stl::to_underlying(Context::kMainGameplay)] :
                    nullptr;
			std::optional<std::int32_t> key;
			if (context) {
				const auto find = [&](RE::INPUT_DEVICE a_device) -> std::optional<std::int32_t> {
					assert(a_device < RE::INPUT_DEVICE::kSupported);
					const auto& mappings = context->deviceMappings[stl::to_underlying(a_device)];
					const auto it = std::find_if(
						mappings.begin(),
						mappings.end(),
						[&](const auto& a_mapping) { return a_mapping.eventID == a_control; });
					return it != mappings.end() ?
                               std::make_optional(it->inputKey) :
                               std::nullopt;
				};

				if (a_deviceType != RE::INPUT_DEVICE::kNone) {
					key = find(a_deviceType);
				} else if (const auto devices = RE::BSInputDeviceManager::GetSingleton();
						   devices && devices->IsGamepadConnected()) {
					key = find(RE::INPUT_DEVICE::kGamepad);
					a_deviceType = RE::INPUT_DEVICE::kGamepad;
				} else if (const auto keyboard = find(RE::INPUT_DEVICE::kKeyboard); keyboard) {
					key = keyboard;
					a_deviceType = RE::INPUT_DEVICE::kKeyboard;
				} else if (const auto mouse = find(RE::INPUT_DEVICE::kMouse); mouse) {
					key = mouse;
					a_deviceType = RE::INPUT_DEVICE::kMouse;
				} else {
					key = std::nullopt;
					a_deviceType = RE::INPUT_DEVICE::kNone;
				}
			}

			if (key) {
				switch (a_deviceType) {
				case RE::INPUT_DEVICE::kKeyboard:
					*key += detail::kKeyboardBegin;
					break;
				case RE::INPUT_DEVICE::kMouse:
					*key += detail::kMouseBegin;
					break;
				case RE::INPUT_DEVICE::kGamepad:
					key = detail::Gamepad::Mask2Key(*key);
					break;
				default:
					break;
				}
			}

			return key.value_or(-1);
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "Input"sv;

			BIND(GetMappedControl, true);
			BIND(GetMappedKey, true);

			logger::info("bound {} script"sv, obj);
		}
	}
}
