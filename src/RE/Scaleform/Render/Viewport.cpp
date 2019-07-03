#include "RE/Scaleform/Render/Viewport.h"


namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			Viewport::Viewport() :
				bufferWidth(0),
				bufferHeight(0),
				left(0),
				top(0),
				width(0),
				height(0),
				scissorLeft(0),
				scissorTop(0),
				scissorWidth(0),
				scissorHeight(0),
				flags(Flag::kNone)
			{}
		}
	}
}
