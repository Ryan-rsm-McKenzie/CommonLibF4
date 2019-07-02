#pragma once


namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			template <class T>
			class Matrix3x4Data
			{
			public:
				Matrix3x4Data() :
					data{}
				{}


				// members
				T data[3][4];
			};
		}
	}
}
