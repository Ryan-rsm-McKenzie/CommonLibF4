#include "RE/Scaleform/GFx/MovieDef.h"

#include "RE/Scaleform/GFx/MemoryParams.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			Movie* MovieDef::CreateInstance(bool a_initFirstFrame = false, UPInt a_memoryArena = 0, ActionControl * a_actionControl = 0, Render::ThreadCommandQueue * a_queue = 0)
			{
				MemoryParams memParams(a_memoryArena);
				return CreateInstance(memParams, a_initFirstFrame, a_actionControl, a_queue);
			}
		}
	}
}
