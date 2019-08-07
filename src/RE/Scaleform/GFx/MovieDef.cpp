#include "RE/Scaleform/GFx/MovieDef.h"

#include "RE/Scaleform/GFx/MemoryParams.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			Movie* MovieDef::CreateInstance(bool a_initFirstFrame, UPInt a_memoryArena, ActionControl* a_actionControl, Render::ThreadCommandQueue* a_queue)
			{
				MemoryParams memParams(a_memoryArena);
				return CreateInstance(memParams, a_initFirstFrame, a_actionControl, a_queue);
			}
		}
	}
}
