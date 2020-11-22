#pragma once

#include "RE/Scaleform/Render/Render_Types2D.h"

namespace RE::Scaleform::Render
{
	class Viewport;

	class Viewport
	{
	public:
		enum class Flag : std::uint32_t
		{
			kIsRenderTexture = 1 << 0,

			kAlphaComposite = 1 << 1,
			kUseScissorRect = 1 << 2,

			kNoSetState = 1 << 3,

			kOrientation_Normal = 0,
			kOrientation_R90 = 1 << 4,
			kOrientation_180 = 1 << 5,
			kOrientation_L90 = kOrientation_R90 | kOrientation_180,
			kOrientation_Mask = kOrientation_Normal | kOrientation_R90 | kOrientation_180 | kOrientation_L90,

			kStereo_SplitV = 1 << 6,
			kStereo_SplitH = 1 << 7,
			kStereo_AnySplit = kStereo_SplitV | kStereo_SplitH,

			kRenderTextureAlpha = kIsRenderTexture | kAlphaComposite,

			kFirstHalFlag = 1 << 8
		};

		// members
		std::int32_t bufferWidth;                     // 00
		std::int32_t bufferHeight;                    // 04
		std::int32_t left;                            // 08
		std::int32_t top;                             // 0C
		std::int32_t width;                           // 10
		std::int32_t height;                          // 14
		std::int32_t scissorLeft;                     // 18
		std::int32_t scissorTop;                      // 1C
		std::int32_t scissorWidth;                    // 20
		std::int32_t scissorHeight;                   // 24
		stl::enumeration<Flag, std::uint32_t> flags;  // 28
	};
	static_assert(sizeof(Viewport) == 0x2C);
}
