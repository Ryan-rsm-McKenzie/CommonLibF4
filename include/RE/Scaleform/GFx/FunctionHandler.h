#pragma once

#include "RE/Scaleform/RefCountBase.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class Movie;
			class Value;


			class FunctionHandler : public RefCountBase<FunctionHandler, kStat_Default_Mem>
			{
			public:
				inline static const void* RTTI = RTTI_Scaleform__GFx__FunctionHandler;


				struct Params
				{
					Value*	retVal;				// 00
					Movie*	movie;				// 08
					Value*	thisPtr;			// 10
					Value*	argsWithThisRef;	// 18
					Value*	args;				// 20
					UInt32	argCount;			// 28
					UInt32	pad2C;				// 2C
					void*	userData;			// 30
				};
				STATIC_ASSERT(sizeof(Params) == 0x38);


				virtual ~FunctionHandler() = default;			// 00

				// add
				virtual void Call(const Params& a_params) = 0;	// 01
			};
			STATIC_ASSERT(sizeof(FunctionHandler) == 0x10);
		}
	}
}
