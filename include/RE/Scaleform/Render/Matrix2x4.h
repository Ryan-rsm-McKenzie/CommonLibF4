#pragma once

#include "RE/Scaleform/Render/Matrix2x4Data.h"


namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			template <class T>
			class Matrix2x4 : public Matrix2x4Data<T>
			{
			public:
				using Parent = Matrix2x4Data<T>;


				Matrix2x4() :
					Parent()
				{}
			};


			using Matrix2F = Matrix2x4<float>;
			STATIC_ASSERT(sizeof(Matrix2F) == 0x20);
		}
	}
}
