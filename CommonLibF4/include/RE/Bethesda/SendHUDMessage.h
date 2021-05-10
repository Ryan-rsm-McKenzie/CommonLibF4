#pragma once

namespace RE
{
	namespace SendHUDMessage
	{
		inline void ShowHUDMessage(const char* a_message, const char* a_sound, bool a_throttle, bool a_warning)
		{
			using func_t = decltype(&ShowHUDMessage);
			REL::Relocation<func_t> func{ REL::ID(1163005) };
			return func(a_message, a_sound, a_throttle, a_warning);
		}
	}
}
