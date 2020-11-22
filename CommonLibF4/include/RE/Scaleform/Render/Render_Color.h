#pragma once

namespace RE::Scaleform::Render
{
	class Color;

	class Color
	{
	public:
		struct Rgb32
		{
		public:
			// members
			std::uint8_t blue;   // 0
			std::uint8_t green;  // 1
			std::uint8_t red;    // 2
			std::uint8_t alpha;  // 3
		};
		static_assert(sizeof(Rgb32) == 0x4);

		// members
		union
		{
			Rgb32 channels;
			std::uint32_t raw;
		};  // 0
	};
	static_assert(sizeof(Color) == 0x4);
}
