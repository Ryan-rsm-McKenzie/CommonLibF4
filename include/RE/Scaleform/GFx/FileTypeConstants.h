#pragma once


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class FileTypeConstants
			{
			public:
				enum class FileFormatType : UInt32
				{
					kUnopened,
					kUnknown,

					kSWF,
					kGFX,

					kJPEG = 10,
					kPNG = 11,
					kGIF = 12,
					kTGA = 13,
					kDDS = 14,
					kHDR = 15,
					kBMP = 16,
					kDIB = 17,
					kPFM = 18,
					kTIFF = 19,

					kWAVE = 20,

					kPVR = 21,
					kETC = 22,
					kSIF = 23,
					kGXT = 24,
					kGTX = 25,

					kNextAvail,
					kMultiFormat = 65534,
					kOriginal = 65535
				};
			};
			STATIC_ASSERT(sizeof(FileTypeConstants) == 0x1);
		}
	}
}
