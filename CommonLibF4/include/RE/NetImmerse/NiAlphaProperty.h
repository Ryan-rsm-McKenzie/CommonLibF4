#pragma once

#include "RE/NetImmerse/NiFlags.h"
#include "RE/NetImmerse/NiProperty.h"

namespace RE
{
	class NiAlphaProperty :
		NiProperty	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_NiAlphaProperty };
		static constexpr auto Ni_RTTI{ NiRTTI_NiAlphaProperty };

		enum class AlphaFunction
		{
			kOne,
			kZero,
			kSrcColor,
			kInvSrcColor,
			kDestColor,
			kInvDestColor,
			kSrcAlpha,
			kInvSrcAlpha,
			kDestAlpha,
			kInvDestAlpha,
			kSrcAlphaTest
		};

		enum class TestFunction
		{
			kAlways,
			kLess,
			kEqual,
			kLessEqual,
			kGreater,
			kNotEqual,
			kGreaterEqual,
			kNever
		};

		// members
		NiTFlags<std::uint16_t, NiProperty> flags;	// 28
		std::int8_t alphaTestRef;					// 2A
	};
	static_assert(sizeof(NiAlphaProperty) == 0x30);
}
