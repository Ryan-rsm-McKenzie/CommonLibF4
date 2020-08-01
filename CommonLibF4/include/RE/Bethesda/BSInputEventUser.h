#pragma once

namespace RE
{
	class ButtonEvent;
	class CharacterEvent;
	class CursorMoveEvent;
	class DeviceConnectEvent;
	class InputEvent;
	class KinectEvent;
	class MouseMoveEvent;
	class ThumbstickEvent;

	class BSInputEventUser
	{
	public:
		virtual ~BSInputEventUser() = default;	// 00

		// add
		virtual bool ShouldHandleEvent(const InputEvent*) { return false; }	 // 01
		virtual void HandleEvent(const ButtonEvent*) { return; }			 // 08
		virtual void HandleEvent(const CharacterEvent*) { return; }			 // 07
		virtual void HandleEvent(const MouseMoveEvent*) { return; }			 // 06
		virtual void HandleEvent(const CursorMoveEvent*) { return; }		 // 05
		virtual void HandleEvent(const ThumbstickEvent*) { return; }		 // 04
		virtual void HandleEvent(const DeviceConnectEvent*) { return; }		 // 03
		virtual void HandleEvent(const KinectEvent*) { return; }			 // 02

		// members
		bool inputEventHandlingEnabled;	 // 08
	};
	static_assert(sizeof(BSInputEventUser) == 0x10);
}
