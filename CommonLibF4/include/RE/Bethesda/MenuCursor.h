#pragma once

#include "RE/Bethesda/BSInputEventSingleUser.h"
#include "RE/Bethesda/BSTSingleton.h"

namespace RE
{
	class __declspec(novtable) MenuCursor :
		public BSTSingletonSDM<MenuCursor>,  // 20
		public BSInputEventSingleUser        // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::MenuCursor };
		static constexpr auto VTABLE{ VTABLE::MenuCursor };

		[[nodiscard]] static MenuCursor* GetSingleton()
		{
			REL::Relocation<MenuCursor**> singleton{ REL::ID(695696) };
			return *singleton;
		}

		void CenterCursor()
		{
			using func_t = decltype(&MenuCursor::CenterCursor);
			REL::Relocation<func_t> func{ REL::ID(1107298) };
			return func(this);
		}

		// members
		std::int32_t cursorPosX;          // 24
		std::int32_t cursorPosY;          // 28
		std::int32_t minCursorX;          // 2C
		std::int32_t minCursorY;          // 30
		std::int32_t maxCursorX;          // 34
		std::int32_t maxCursorY;          // 38
		float leftConstraintPct;          // 3C
		float rightConstraintPct;         // 40
		float topConstraintPct;           // 44
		float bottomConstraintPct;        // 48
		float gamepadCursorSpeed;         // 4C
		std::uint32_t registeredCursors;  // 50
		bool forceOSCursorPos;            // 54
		bool allowGamepadCursorOverride;  // 55
	};
	static_assert(sizeof(MenuCursor) == 0x58);
}
