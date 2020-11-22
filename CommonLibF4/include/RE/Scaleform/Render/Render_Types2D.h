#pragma once

namespace RE::Scaleform::Render
{
	template <class T>
	class Point
	{
	public:
		// members
		T x;  // 00
		T y;  // ??
	};

	template <class T>
	class RectData
	{
	public:
		// members
		T x1;  // 00
		T y1;  // ??
		T x2;  // ??
		T y2;  // ??
	};

	template <class T>
	class Rect :
		public RectData<T>  // 00
	{
	public:
	};

	using PointF = Point<float>;
	static_assert(sizeof(PointF) == 0x8);

	using RectF = Rect<float>;
	static_assert(sizeof(RectF) == 0x10);
}
