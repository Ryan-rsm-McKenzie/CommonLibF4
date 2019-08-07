#pragma once

#include "RE/Scaleform/Render/Viewport.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class Viewport : public Render::Viewport
			{
			public:
				Viewport();


				// members
				float	scale;			// 2C
				float	aspectRatio;	// 30
			};
			STATIC_ASSERT(sizeof(Viewport) == 0x34);


			inline Viewport::Viewport() :
				Render::Viewport(),
				scale(1.0),
				aspectRatio(1.0)
			{}
		}
	}
}
