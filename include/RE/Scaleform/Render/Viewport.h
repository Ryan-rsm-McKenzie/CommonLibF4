#pragma once


namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			class Viewport
			{
			public:
				enum class Flag : UInt32
				{
					kNone = 0,

					kIsRenderTexture = 1 << 0,

					kAlphaComposite = 1 << 1,
					kUseScissorRect = 1 << 2,

					kNoSetState = 1 << 3,

					kOrientation_Normal = 0x00,
					kOrientation_R90 = 0x10,
					kOrientation_180 = 0x20,
					kOrientation_L90 = 0x30,
					kOrientation_Mask = 0x30,

					kStereo_SplitV = 0x40,
					kStereo_SplitH = 0x80,
					kStereo_AnySplit = 0xC0,

					kRenderTextureAlpha = kIsRenderTexture | kAlphaComposite,

					kFirstHalFlag = 1 << 8
				};


				Viewport();


				SInt32	bufferWidth;	// 00
				SInt32	bufferHeight;	// 04
				SInt32	left;			// 08
				SInt32	top;			// 0C
				SInt32	width;			// 10
				SInt32	height;			// 14
				SInt32	scissorLeft;	// 18
				SInt32	scissorTop;		// 1C
				SInt32	scissorWidth;	// 20
				SInt32	scissorHeight;	// 24
				Flag	flags;			// 28
			};
			STATIC_ASSERT(sizeof(Viewport) == 0x2C);


			inline Viewport::Viewport() :
				bufferWidth(0),
				bufferHeight(0),
				left(0),
				top(0),
				width(0),
				height(0),
				scissorLeft(0),
				scissorTop(0),
				scissorWidth(0),
				scissorHeight(0),
				flags(Flag::kNone)
			{}
		}
	}
}
