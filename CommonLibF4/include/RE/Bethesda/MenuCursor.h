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

		void ClearConstraints() noexcept
		{
			leftConstraintPct = 0.0f;
			rightConstraintPct = 0.0f;
			topConstraintPct = 0.0f;
			bottomConstraintPct = 0.0f;
		}

		void ConstrainForPipboy();
		void ConstrainForPipboyPA();

		void RegisterCursor()
		{
			using func_t = decltype(&MenuCursor::RegisterCursor);
			REL::Relocation<func_t> func{ REL::ID(1318193) };
			return func(this);
		}

		void SetCursorConstraintsRaw(std::uint32_t a_tlx, std::uint32_t a_tly, std::uint32_t a_width, std::uint32_t a_height)
		{
			using func_t = decltype(&MenuCursor::SetCursorConstraintsRaw);
			REL::Relocation<func_t> func{ REL::ID(907092) };
			return func(this, a_tlx, a_tly, a_width, a_height);
		}

		void UnregisterCursor()
		{
			using func_t = decltype(&MenuCursor::UnregisterCursor);
			REL::Relocation<func_t> func{ REL::ID(1225249) };
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
