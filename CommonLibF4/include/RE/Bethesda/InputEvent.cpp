#include "RE/Bethesda/InputEvent.h"

namespace RE
{
	template CharacterEvent* InputEvent::As() noexcept;
	template const CharacterEvent* InputEvent::As() const noexcept;

	template DeviceConnectEvent* InputEvent::As() noexcept;
	template const DeviceConnectEvent* InputEvent::As() const noexcept;

	template IDEvent* InputEvent::As<IDEvent>();
	template const IDEvent* InputEvent::As<IDEvent>() const;

	template ButtonEvent* InputEvent::As() noexcept;
	template const ButtonEvent* InputEvent::As() const noexcept;

	template CursorMoveEvent* InputEvent::As() noexcept;
	template const CursorMoveEvent* InputEvent::As() const noexcept;

	template KinectEvent* InputEvent::As() noexcept;
	template const KinectEvent* InputEvent::As() const noexcept;

	template MouseMoveEvent* InputEvent::As() noexcept;
	template const MouseMoveEvent* InputEvent::As() const noexcept;

	template ThumbstickEvent* InputEvent::As() noexcept;
	template const ThumbstickEvent* InputEvent::As() const noexcept;
}
