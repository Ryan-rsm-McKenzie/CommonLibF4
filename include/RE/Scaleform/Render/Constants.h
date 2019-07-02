#pragma once


namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			enum class EdgeAAMode : UInt32
			{
				kInherit = 0,
				kOn = 1 << 2,
				kOff = 1 << 3,
				kDisable = kOn | kOff
			};
		}
	}
}
