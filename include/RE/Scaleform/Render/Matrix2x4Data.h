#pragma once


namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			template <class T>
			class Matrix2x4Data
			{
			public:
				Matrix2x4Data() :
					data{}
				{}


				T data[2][4];
			};
		}
	}
}
