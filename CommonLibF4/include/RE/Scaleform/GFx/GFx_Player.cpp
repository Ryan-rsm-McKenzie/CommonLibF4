#include "RE/Scaleform/GFx/GFx_Player.h"

#include "RE/Scaleform/GFx/GFx_ASMovieRootBase.h"

namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			bool Movie::GetVariable(Value* a_val, const char* a_pathToVar) const
			{
				return asMovieRoot->GetVariable(a_val, a_pathToVar);
			}
		}
	}
}
