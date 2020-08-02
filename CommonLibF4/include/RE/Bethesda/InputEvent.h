#pragma once

#include "RE/Bethesda/BSFixedString.h"

namespace RE
{
	enum class DIRECTION_VAL : std::int32_t
	{
		kNone,
		kUp,
		kRight,
		kDown,
		kLeft
	};

	enum class INPUT_EVENT_TYPE : std::int32_t
	{
		kButton,
		kMouseMove,
		kCursorMove,
		kChar,
		kTumbstick,
		kDeviceConnect,
		kKinect,
		kNone
	};

	enum class INPUT_DEVICE : std::int32_t
	{
		kNone = static_cast<std::underlying_type_t<INPUT_DEVICE>>(-1),

		kKeyboard = 0,
		kMouse,
		kGamepad,
		kKinect,
		kVirtualKeyboard
	};

	class InputEvent
	{
	public:
		static constexpr auto RTTI{ RTTI_InputEvent };

		enum class HANDLED_RESULT : std::int32_t
		{
			kUnhandled,
			kContinue,
			kStop
		};

		virtual ~InputEvent() = default;  // 00

		// add
		virtual bool HasIDCode() const { return false; }				// 02
		virtual const BSFixedString& QUserEvent() const { return {}; }	// 03

		// members
		stl::enumeration<INPUT_DEVICE, std::int32_t> device{ INPUT_DEVICE::kNone };				// 08
		std::int32_t deviceID{ 0 };																// 0C
		stl::enumeration<INPUT_EVENT_TYPE, std::int32_t> eventType{ INPUT_EVENT_TYPE::kNone };	// 10
		InputEvent* next{ nullptr };															// 18
		std::uint32_t timeCode{ static_cast<std::uint32_t>(-1) };								// 20
		stl::enumeration<HANDLED_RESULT, std::int32_t> handled{ HANDLED_RESULT::kUnhandled };	// 24
	};
	static_assert(sizeof(InputEvent) == 0x28);

	class CharacterEvent :
		public InputEvent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_CharacterEvent };

		virtual ~CharacterEvent() = default;  // 00

		// members
		std::uint32_t charCode{ 0 };  // 28
	};
	static_assert(sizeof(CharacterEvent) == 0x30);

	class DeviceConnectEvent :
		public InputEvent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_DeviceConnectEvent };

		virtual ~DeviceConnectEvent() = default;  // 00

		// members
		bool connected{ true };	 // 28
	};
	static_assert(sizeof(DeviceConnectEvent) == 0x30);

	class IDEvent :
		public InputEvent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_IDEvent };

		virtual ~IDEvent() = default;  // 00

		// override (InputEvent)
		bool HasIDCode() const override { return true; }						   // 02
		const BSFixedString& QUserEvent() const override { return "DISABLED"sv; }  // 03

		// members
		BSFixedString strUserEvent;	 // 28
		std::int32_t idCode{ -1 };	 // 30
		bool disabled{ false };		 // 34
	};
	static_assert(sizeof(IDEvent) == 0x38);

	class ButtonEvent :
		public IDEvent	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_ButtonEvent };

		virtual ~ButtonEvent() = default;  // 00

		// members
		float value{ 0.0F };		 // 38
		float heldDownSecs{ 0.0F };	 // 3C
	};
	static_assert(sizeof(ButtonEvent) == 0x40);

	class CursorMoveEvent :
		public IDEvent	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_CursorMoveEvent };

		virtual ~CursorMoveEvent() = default;  // 00

		// members
		std::int32_t cursorPosX{ 0 };  // 38
		std::int32_t cursorPosY{ 0 };  // 3C
	};
	static_assert(sizeof(CursorMoveEvent) == 0x40);

	class KinectEvent :
		public IDEvent	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_KinectEvent };

		virtual ~KinectEvent() = default;  // 00

		// members
		BSFixedString strHeard;	 // 38
	};
	static_assert(sizeof(KinectEvent) == 0x40);

	class MouseMoveEvent :
		public IDEvent	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_MouseMoveEvent };

		virtual ~MouseMoveEvent() = default;  // 00

		// members
		std::int32_t mouseInputX{ 0 };	// 38
		std::int32_t mouseInputY{ 0 };	// 3C
	};
	static_assert(sizeof(MouseMoveEvent) == 0x40);

	class ThumbstickEvent :
		public IDEvent	// 00
	{
	public:
		enum THUMBSTICK_ID : std::int32_t
		{
			kLeft = 0xB,
			kRight = 0xC,
		};

		static constexpr auto RTTI{ RTTI_ThumbstickEvent };

		virtual ~ThumbstickEvent() = default;  // 00

		// members
		float xValue{ 0.0F };							// 38
		float yValue{ 0.0F };							// 3C
		DIRECTION_VAL prevDir{ DIRECTION_VAL::kNone };	// 40
		DIRECTION_VAL currDir{ DIRECTION_VAL::kNone };	// 44
	};
	static_assert(sizeof(ThumbstickEvent) == 0x48);
}
