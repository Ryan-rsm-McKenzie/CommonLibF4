#pragma once

#include "RE/Scaleform/GFx/FunctionHandler.h"
#include "RE/Scaleform/GFx/Value.h"


namespace RE
{
	class SWFToCodeFunctionHandler : public Scaleform::GFx::FunctionHandler
	{
	public:
		virtual ~SWFToCodeFunctionHandler();				// 00

		// override (Scaleform::GFx::FunctionHandler)
		virtual void Call(const Params& a_params) override;	// 01 - { return; }

		// add
		virtual void RegisterCallbacks();					// 02 - { return; }
	};
	STATIC_ASSERT(sizeof(SWFToCodeFunctionHandler) == 0x10);
}
