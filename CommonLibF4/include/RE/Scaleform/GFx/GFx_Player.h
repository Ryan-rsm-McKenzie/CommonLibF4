#pragma once

#include "RE/Scaleform/GFx/GFx_Loader.h"
#include "RE/Scaleform/Kernel/SF_RefCount.h"

namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class ASMovieRootBase;

			class Movie :
				public RefCountBase<Movie, 327>,  // 00
				public StateBag					  // 10
			{
			public:
				// members
				Ptr<ASMovieRootBase> asMovieRoot;  // 18
			};
			static_assert(sizeof(Movie) == 0x20);
		}
	}
}
