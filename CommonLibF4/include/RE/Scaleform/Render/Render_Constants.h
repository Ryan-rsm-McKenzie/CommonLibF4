#pragma once

namespace RE::Scaleform::Render
{
	enum class EdgeAAMode : std::int32_t
	{
		kInherit = 0x0000,
		kOn = 1 << 2,
		kOff = 1 << 3,
		kDisable = kOn | kOff
	};
}
