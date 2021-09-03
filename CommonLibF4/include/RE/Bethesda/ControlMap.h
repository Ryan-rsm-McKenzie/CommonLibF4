#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTSingleton.h"
#include "RE/Bethesda/InputDevice.h"
#include "RE/Bethesda/UserEvents.h"

namespace RE
{
	enum class PC_GAMEPAD_TYPE
	{
		kDirectX,
		kOrbis,

		kTotal
	};

	class ControlMap :
		public BSTSingletonSDM<ControlMap>  // 000
	{
	public:
		struct UserEventMapping
		{
		public:
			// members
			BSFixedString eventID;                                                           // 00
			std::int32_t inputKey;                                                           // 08
			std::int8_t byIndexInContext;                                                    // 0C
			bool remappable;                                                                 // 0D
			bool linked;                                                                     // 0E
			stl::enumeration<UserEvents::USER_EVENT_FLAG, std::int32_t> userEventGroupFlag;  // 10
		};
		static_assert(sizeof(UserEventMapping) == 0x18);

		struct InputContext
		{
		public:
			// members
			BSTArray<UserEventMapping> deviceMappings[stl::to_underlying(INPUT_DEVICE::kSupported)];  // 00
		};
		static_assert(sizeof(InputContext) == 0x48);

		struct LinkedMapping
		{
		public:
			// members
			BSFixedString linkedMappingName;                                                    // 00
			stl::enumeration<UserEvents::INPUT_CONTEXT_ID, std::int32_t> linkedMappingContext;  // 08
			stl::enumeration<INPUT_DEVICE, std::int32_t> device;                                // 0C
			stl::enumeration<UserEvents::INPUT_CONTEXT_ID, std::int32_t> linkFromContext;       // 10
			BSFixedString linkFromName;                                                         // 18
		};
		static_assert(sizeof(LinkedMapping) == 0x20);

		[[nodiscard]] static ControlMap* GetSingleton()
		{
			REL::Relocation<ControlMap**> singleton{ REL::ID(325206) };
			return *singleton;
		}

		bool PopInputContext(UserEvents::INPUT_CONTEXT_ID a_context)
		{
			using func_t = decltype(&ControlMap::PopInputContext);
			REL::Relocation<func_t> func{ REL::ID(74587) };
			return func(this, a_context);
		}

		void PushInputContext(UserEvents::INPUT_CONTEXT_ID a_context)
		{
			using func_t = decltype(&ControlMap::PushInputContext);
			REL::Relocation<func_t> func{ REL::ID(1404410) };
			return func(this, a_context);
		}

		void SetIgnoreKeyboardMouse(bool a_value) noexcept { ignoreKeyboardMouse = a_value; }

		// members
		InputContext* controlMaps[stl::to_underlying(UserEvents::INPUT_CONTEXT_ID::kTotal)];          // 008
		BSTArray<LinkedMapping> linkedMappings;                                                       // 110
		BSTArray<stl::enumeration<UserEvents::INPUT_CONTEXT_ID, std::int32_t>> contextPriorityStack;  // 128
		std::int8_t byTextEntryCount;                                                                 // 140
		bool ignoreKeyboardMouse;                                                                     // 141
		bool ignoreActivateDisabledEvents;                                                            // 142
		stl::enumeration<PC_GAMEPAD_TYPE, std::int32_t> pcGamePadMapType;                             // 144
	};
	static_assert(sizeof(ControlMap) == 0x148);
}
