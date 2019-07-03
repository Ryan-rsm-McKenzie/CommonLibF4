#pragma once

#include "RE/Scaleform/Render/RectData.h"


namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			template <class T>
			class Rect : public RectData<T>
			{
			public:
				using Parent = RectData<T>;


				Rect() :
					Parent()
				{}
			};


			using RectF = Rect<float>;
			STATIC_ASSERT(sizeof(RectF) == 0x10);
		}
	}
}
