#pragma once

#include "RE/Scaleform/GFx/GFx_Player.h"

namespace RE
{
	class SWFToCodeFunctionHandler :
		public Scaleform::GFx::FunctionHandler	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_SWFToCodeFunctionHandler };

		virtual ~SWFToCodeFunctionHandler() = default;

		// add
		virtual void MapCodeObjectFunction() { return; }  // 02
	};
	static_assert(sizeof(SWFToCodeFunctionHandler) == 0x10);
}
