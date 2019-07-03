#pragma once

#define SF_RGB(r,g,b)		(UInt32(((UInt32)b) | (((UInt32)g) << 8) | (((UInt32)r) << 16)))
#define SF_RGBA(r,g,b,a)	(UInt32(SF_RGB(r,g,b) | (((UInt32)a) << 24)))



namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			class Color
			{
			public:
				enum StandardColors : UInt32
				{
					kBlack = SF_RGB(0, 0, 0),
					kWhite = SF_RGB(255, 255, 255),
					kVeryLightGray = SF_RGB(224, 224, 224),
					kLightGray = SF_RGB(192, 192, 192),
					kGray = SF_RGB(128, 128, 128),
					kDarkGray = SF_RGB(64, 64, 64),
					kVeryDarkGray = SF_RGB(32, 32, 32),

					kRed = SF_RGB(255, 0, 0),
					kLightRed = SF_RGB(255, 128, 128),
					kDarkRed = SF_RGB(128, 0, 0),
					kVeryDarkRed = SF_RGB(64, 0, 0),
					kGreen = SF_RGB(0, 255, 0),
					kLightGreen = SF_RGB(128, 255, 128),
					kDarkGreen = SF_RGB(0, 128, 0),
					kVeryDarkGreen = SF_RGB(0, 64, 0),
					kBlue = SF_RGB(0, 0, 255),
					kLightBlue = SF_RGB(128, 128, 255),
					kDarkBlue = SF_RGB(0, 0, 128),
					kVeryDarkBlue = SF_RGB(0, 0, 64),

					kCyan = SF_RGB(0, 255, 255),
					kLightCyan = SF_RGB(128, 255, 255),
					kDarkCyan = SF_RGB(0, 128, 128),
					kMagenta = SF_RGB(255, 0, 255),
					kLightMagenta = SF_RGB(255, 128, 255),
					kDarkMagenta = SF_RGB(128, 0, 128),
					kYellow = SF_RGB(255, 255, 0),
					kLightYellow = SF_RGB(255, 255, 128),
					kDarkYellow = SF_RGB(128, 128, 0),

					kPurple = SF_RGB(255, 0, 255),
					kDarkPurple = SF_RGB(128, 0, 128),
					kPink = SF_RGB(255, 192, 192),
					kDarkPink = SF_RGB(192, 128, 128),
					kBeige = SF_RGB(255, 192, 128),
					kLightBeige = SF_RGB(255, 224, 192),
					kDarkBeige = SF_RGB(192, 128, 64),
					kOrange = SF_RGB(255, 128, 0),
					kBrown = SF_RGB(128, 64, 0),
					kLightBrown = SF_RGB(192, 96, 0),
					kDarkBrown = SF_RGB(64, 32, 0)
				};


				enum StandardAlphas : UInt32
				{
					kAlpha0 = SF_RGBA(0, 0, 0, 0),
					kAlpha25 = SF_RGBA(0, 0, 0, 64),
					kAlpha50 = SF_RGBA(0, 0, 0, 127),
					kAlpha75 = SF_RGBA(0, 0, 0, 191),
					kAlpha100 = SF_RGBA(0, 0, 0, 255)
				};


				struct RGB32
				{
					UInt8	blue;
					UInt8	green;
					UInt8	red;
					UInt8	alpha;
				};
				STATIC_ASSERT(sizeof(RGB32) == 0x4);


				union ChannelRaw
				{
					ChannelRaw();


					RGB32	channels;
					UInt32	raw;
				};
				STATIC_ASSERT(sizeof(ChannelRaw) == 0x4);


				Color();


				// members
				ChannelRaw data;	// 0
			};
			STATIC_ASSERT(sizeof(Color) == 0x4);
		}
	}
}
