#pragma once

#include "RE/Bethesda/InputEvent.h"
#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	class BSInputEventUser
	{
	public:
		static constexpr auto RTTI{ RTTI::BSInputEventUser };
		static constexpr auto VTABLE{ VTABLE::BSInputEventUser };

		virtual ~BSInputEventUser() = default;  // 00

		// add
		virtual bool ShouldHandleEvent(const InputEvent*) { return false; }  // 01
		virtual void HandleEvent(const ButtonEvent*) { return; }             // 08
		virtual void HandleEvent(const CharacterEvent*) { return; }          // 07
		virtual void HandleEvent(const MouseMoveEvent*) { return; }          // 06
		virtual void HandleEvent(const CursorMoveEvent*) { return; }         // 05
		virtual void HandleEvent(const ThumbstickEvent*) { return; }         // 04
		virtual void HandleEvent(const DeviceConnectEvent*) { return; }      // 03
		virtual void HandleEvent(const KinectEvent*) { return; }             // 02

		F4_HEAP_REDEFINE_NEW(BSInputEventUser);

		// members
		bool inputEventHandlingEnabled{ true };  // 08
	};
	static_assert(sizeof(BSInputEventUser) == 0x10);

	struct __declspec(novtable) DisconnectHandler :
		public BSInputEventUser
	{
	public:
		static constexpr auto RTTI{ RTTI::DisconnectHandler };
		static constexpr auto VTABLE{ VTABLE::DisconnectHandler };
	};
	static_assert(sizeof(DisconnectHandler) == 0x10);
}
