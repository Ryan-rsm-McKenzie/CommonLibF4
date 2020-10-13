#pragma once

#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/BSTSingleton.h"

namespace RE
{
	class ConsoleLog :
		public BSTSingletonSDM<ConsoleLog>  // 00
	{
	public:
		[[nodiscard]] static ConsoleLog* GetSingleton()
		{
			REL::Relocation<ConsoleLog**> singleton{ REL::ID(689441) };
			return *singleton;
		}

		void AddString(char const* a_string)
		{
			using func_t = decltype(&ConsoleLog::AddString);
			REL::Relocation<func_t> func{ REL::ID(764) };
			return func(this, a_string);
		}

		// members
		BSStringT<char> buffer;  // 08
		bool useConsoleOverlay;  // 18
	};
	static_assert(sizeof(ConsoleLog) == 0x20);
}
