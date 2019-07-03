#pragma once


namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			template <class T>
			class RectData
			{
			public:
				RectData() :
					x1{},
					y1{},
					x2{},
					y2{}
				{}


				// members
				T	x1;	// 00
				T	y1;	// ??
				T	x2;	// ??
				T	y2;	// ??
			};
		}
	}
}
