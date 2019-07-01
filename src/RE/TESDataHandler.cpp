#include "RE/TESDataHandler.h"

#include "f4se/GameData.h"


namespace RE
{
	TESDataHandler* TESDataHandler::GetSingleton()
	{
		return *reinterpret_cast<TESDataHandler**>(g_dataHandler.GetUIntPtr());
	}


	BSTArray<TESForm*>& TESDataHandler::GetFormArray(FormType a_formType)
	{
		return formArrays[to_underlying(a_formType)];
	}
}
