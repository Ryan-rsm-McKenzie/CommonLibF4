#pragma once

#include "RE/BSTArray.h"
#include "RE/FormTypes.h"


namespace RE
{
	class TESDataHandler
	{
	public:
		static TESDataHandler* GetSingleton();

		BSTArray<TESForm*>&					GetFormArray(FormType a_formType);
		template <class T> BSTArray<T*>&	GetFormArray();


		// members
		UInt64				unk00;											// 0000
		BSTArray<void*>		unk08;											// 0008
		BSTArray<void*>		unk20;											// 0020
		BSTArray<void*>		unk38;											// 0038
		BSTArray<void*>		unk50;											// 0050
		BSTArray<TESForm*>	formArrays[to_underlying(FormType::kTotal)];	// 0068
		// more...
	};
	//STATIC_ASSERT(sizeof(TESDataHandler) == 0x);


	template <class T>
	BSTArray<T*>& TESDataHandler::GetFormArray()
	{
		return reinterpret_cast<BSTArray<T*>&>(GetFormArray(static_cast<FormType>(T::kTypeID)));
	}
}
