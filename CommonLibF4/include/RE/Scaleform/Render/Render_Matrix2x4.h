#pragma once

#include "RE/Scaleform/Render/Render_Types2D.h"

namespace RE::Scaleform::Render
{
	template <class T>
	class Matrix2x4Data
	{
	public:
		// members
		T m[2][4];  // 00
	};

	template <class T>
	class Matrix2x4 :
		public Matrix2x4Data<T>  // 00
	{
	public:
	};

	using Matrix2F = Matrix2x4<float>;
	static_assert(sizeof(Matrix2F) == 0x20);
}
