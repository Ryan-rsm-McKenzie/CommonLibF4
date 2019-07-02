#pragma once

#include "RE/Scaleform/Render/Matrix3x4Data.h"


namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			template <class T>
			class Matrix3x4 : public Matrix3x4Data<T>
			{
			public:
				using Parent = Matrix3x4Data<T>;


				Matrix3x4() :
					Parent()
				{}
			};


			using Matrix3F = Matrix3x4<float>;
			STATIC_ASSERT(sizeof(Matrix3F) == 0x30);
		}
	}
}
