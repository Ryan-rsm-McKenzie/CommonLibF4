#include "RE/Scaleform/GFx/GFx_Player.h"

#include "RE/Scaleform/GFx/GFx_ASMovieRootBase.h"

namespace RE::Scaleform::GFx
{
	void Movie::CreateFunction(Value* a_value, FunctionHandler* a_function, void* a_userData)
	{
		asMovieRoot->CreateFunction(a_value, a_function, a_userData);
	}

	bool Movie::GetVariable(Value* a_val, const char* a_pathToVar) const
	{
		return asMovieRoot->GetVariable(a_val, a_pathToVar);
	}
}
