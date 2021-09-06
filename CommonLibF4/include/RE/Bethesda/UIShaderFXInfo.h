#pragma once

#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiRect.h"

namespace RE
{
	struct UIShaderColors
	{
	public:
		enum class Flags
		{
			kBackgroundQuad = 1u << 0,
			kColorMultiplier = 1u << 1,
			kVerticalGradient = 1u << 2,
			kUseAlphaForDropshadow = 1u << 3
		};

		// members
		NiRect<float> backgroundQuad;                          // 00
		NiColorA backgroundColor;                              // 10
		NiColorA colorMultipliers;                             // 20
		float colorBrightness;                                 // 30
		stl::enumeration<Flags, std::uint32_t> enabledStates;  // 34
	};
	static_assert(sizeof(UIShaderColors) == 0x38);

	struct alignas(0x10) UIShaderFXInfo
	{
	public:
		// members
		NiRect<float> renderQuad;  // 00
		UIShaderColors shaderFX;   // 10
	};
	static_assert(sizeof(UIShaderFXInfo) == 0x50);
}
