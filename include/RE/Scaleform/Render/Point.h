#pragma once


namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			template <class T>
			class Point
			{
			public:
				T	x;	// 00
				T	y;	// ??
			};


			using PointF = Point<float>;
		}
	}
}
