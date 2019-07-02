#pragma once

#include "RE/Scaleform/Render/Matrix4x4Data.h"


namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			template <class T>
			class Matrix4x4 : public Matrix4x4Data<T>
			{
			public:
				using Parent = Matrix4x4Data<T>;


				Matrix4x4() :
					Parent()
				{}
			};


			using Matrix4F = Matrix4x4<float>;
			STATIC_ASSERT(sizeof(Matrix4F) == 0x40);
		}
	}
}
