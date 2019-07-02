#pragma once


namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			class Cxform
			{
			public:
				enum Rows
				{
					kMult = 0,
					kAdd,
					kTotalRows
				};


				enum Columns
				{
					kR = 0,
					kG,
					kB,
					kA,
					kTotalColumns
				};


				Cxform() :
					data{ 0.0 }
				{}


				// members
				alignas(0x10) float data[kTotalRows][kTotalColumns];
			};
			STATIC_ASSERT(sizeof(Cxform) == 0x20);
		}
	}
}
