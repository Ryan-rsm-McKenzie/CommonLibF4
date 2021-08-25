#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/InputDevice.h"

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
		kThumbstick,
		kDeviceConnect,
		kKinect,
		kNone
	};

	class IDEvent;

	class __declspec(novtable) InputEvent
	{
	public:
		static constexpr auto RTTI{ RTTI::InputEvent };
		static constexpr auto VTABLE{ VTABLE::InputEvent };

		enum class HANDLED_RESULT : std::int32_t
		{
			kUnhandled,
			kContinue,
			kStop
		};

		virtual ~InputEvent() = default;  // 00

		// add
		virtual bool HasIDCode() const { return false; }  // 02
		virtual const BSFixedString& QUserEvent() const;  // 03

		template <class T>
		[[nodiscard]] T* As() noexcept  //
			requires(std::derived_from<T, InputEvent> &&
					 !std::same_as<std::decay_t<T>, IDEvent>)
		{
			if (*eventType == T::TYPE) {
				return static_cast<T*>(this);
			} else {
				return nullptr;
			}
		}

		template <class T>
		[[nodiscard]] const T* As() const noexcept  //
			requires(std::derived_from<T, InputEvent> &&
					 !std::same_as<std::decay_t<T>, IDEvent>)
		{
			if (*eventType == T::TYPE) {
				return static_cast<const T*>(this);
			} else {
				return nullptr;
			}
		}

		template <class T>
		[[nodiscard]] T* As()  //
			requires(std::same_as<std::decay_t<T>, IDEvent>)
		{
			if (HasIDCode()) {
				return static_cast<T*>(this);
			} else {
				return nullptr;
			}
		}

		template <class T>
		[[nodiscard]] const T* As() const  //
			requires(std::same_as<std::decay_t<T>, IDEvent>)
		{
			if (HasIDCode()) {
				return static_cast<const T*>(this);
			} else {
				return nullptr;
			}
		}

		// members
		stl::enumeration<INPUT_DEVICE, std::int32_t> device{ INPUT_DEVICE::kNone };             // 08
		std::int32_t deviceID{ 0 };                                                             // 0C
		stl::enumeration<INPUT_EVENT_TYPE, std::int32_t> eventType{ INPUT_EVENT_TYPE::kNone };  // 10
		InputEvent* next{ nullptr };                                                            // 18
		std::uint32_t timeCode{ static_cast<std::uint32_t>(-1) };                               // 20
		stl::enumeration<HANDLED_RESULT, std::int32_t> handled{ HANDLED_RESULT::kUnhandled };   // 24
	};
	static_assert(sizeof(InputEvent) == 0x28);

	class __declspec(novtable) CharacterEvent :
		public InputEvent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::CharacterEvent };
		static constexpr auto VTABLE{ VTABLE::CharacterEvent };
		static constexpr auto TYPE{ INPUT_EVENT_TYPE::kChar };

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~CharacterEvent() = default;  // 00

		// members
		std::uint32_t charCode{ 0 };  // 28
	};
	static_assert(sizeof(CharacterEvent) == 0x30);

	extern template CharacterEvent* InputEvent::As() noexcept;
	extern template const CharacterEvent* InputEvent::As() const noexcept;

	class __declspec(novtable) DeviceConnectEvent :
		public InputEvent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::DeviceConnectEvent };
		static constexpr auto VTABLE{ VTABLE::DeviceConnectEvent };
		static constexpr auto TYPE{ INPUT_EVENT_TYPE::kDeviceConnect };

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~DeviceConnectEvent() = default;  // 00

		// members
		bool connected{ true };  // 28
	};
	static_assert(sizeof(DeviceConnectEvent) == 0x30);

	extern template DeviceConnectEvent* InputEvent::As() noexcept;
	extern template const DeviceConnectEvent* InputEvent::As() const noexcept;

	class __declspec(novtable) IDEvent :
		public InputEvent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::IDEvent };
		static constexpr auto VTABLE{ VTABLE::IDEvent };

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~IDEvent() = default;  // 00

		// override (InputEvent)
		bool HasIDCode() const override { return true; }   // 02
		const BSFixedString& QUserEvent() const override;  // 03

		// members
		BSFixedString strUserEvent;  // 28
		std::int32_t idCode{ -1 };   // 30
		bool disabled{ false };      // 34
	};
	static_assert(sizeof(IDEvent) == 0x38);

	extern template IDEvent* InputEvent::As();
	extern template const IDEvent* InputEvent::As() const;

	class __declspec(novtable) ButtonEvent :
		public IDEvent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ButtonEvent };
		static constexpr auto VTABLE{ VTABLE::ButtonEvent };
		static constexpr auto TYPE{ INPUT_EVENT_TYPE::kButton };

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~ButtonEvent() = default;  // 00

		[[nodiscard]] bool JustPressed() const noexcept { return value != 0.0F && heldDownSecs == 0.0F; }

		// members
		float value{ 0.0F };         // 38
		float heldDownSecs{ 0.0F };  // 3C
	};
	static_assert(sizeof(ButtonEvent) == 0x40);

	extern template ButtonEvent* InputEvent::As() noexcept;
	extern template const ButtonEvent* InputEvent::As() const noexcept;

	class __declspec(novtable) CursorMoveEvent :
		public IDEvent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::CursorMoveEvent };
		static constexpr auto VTABLE{ VTABLE::CursorMoveEvent };
		static constexpr auto TYPE{ INPUT_EVENT_TYPE::kCursorMove };

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~CursorMoveEvent() = default;  // 00

		// members
		std::int32_t cursorPosX{ 0 };  // 38
		std::int32_t cursorPosY{ 0 };  // 3C
	};
	static_assert(sizeof(CursorMoveEvent) == 0x40);

	extern template CursorMoveEvent* InputEvent::As() noexcept;
	extern template const CursorMoveEvent* InputEvent::As() const noexcept;

	class __declspec(novtable) KinectEvent :
		public IDEvent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::KinectEvent };
		static constexpr auto VTABLE{ VTABLE::KinectEvent };
		static constexpr auto TYPE{ INPUT_EVENT_TYPE::kKinect };

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~KinectEvent() = default;  // 00

		// members
		BSFixedString strHeard;  // 38
	};
	static_assert(sizeof(KinectEvent) == 0x40);

	extern template KinectEvent* InputEvent::As() noexcept;
	extern template const KinectEvent* InputEvent::As() const noexcept;

	class __declspec(novtable) MouseMoveEvent :
		public IDEvent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::MouseMoveEvent };
		static constexpr auto VTABLE{ VTABLE::MouseMoveEvent };
		static constexpr auto TYPE{ INPUT_EVENT_TYPE::kMouseMove };

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~MouseMoveEvent() = default;  // 00

		// members
		std::int32_t mouseInputX{ 0 };  // 38
		std::int32_t mouseInputY{ 0 };  // 3C
	};
	static_assert(sizeof(MouseMoveEvent) == 0x40);

	extern template MouseMoveEvent* InputEvent::As() noexcept;
	extern template const MouseMoveEvent* InputEvent::As() const noexcept;

	class __declspec(novtable) ThumbstickEvent :
		public IDEvent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ThumbstickEvent };
		static constexpr auto VTABLE{ VTABLE::ThumbstickEvent };
		static constexpr auto TYPE{ INPUT_EVENT_TYPE::kThumbstick };

		enum THUMBSTICK_ID : std::int32_t
		{
			kLeft = 0xB,
			kRight = 0xC,
		};

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~ThumbstickEvent() = default;  // 00

		// members
		float xValue{ 0.0F };                           // 38
		float yValue{ 0.0F };                           // 3C
		DIRECTION_VAL prevDir{ DIRECTION_VAL::kNone };  // 40
		DIRECTION_VAL currDir{ DIRECTION_VAL::kNone };  // 44
	};
	static_assert(sizeof(ThumbstickEvent) == 0x48);

	extern template ThumbstickEvent* InputEvent::As() noexcept;
	extern template const ThumbstickEvent* InputEvent::As() const noexcept;
}
