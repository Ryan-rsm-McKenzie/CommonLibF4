#pragma once

namespace RE
{
	enum class INPUT_DEVICE : std::int32_t
	{
		kNone = static_cast<std::underlying_type_t<INPUT_DEVICE>>(-1),

		kKeyboard = 0,
		kMouse,
		kGamepad,

		kSupported,

		kKinect = 3,
		kVirtualKeyboard,

		kTotal
	};
}
