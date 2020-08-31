#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/NetImmerse/NiObject.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class NiExtraDataContainer;
	class NiTimeController;

	class NiObjectNET :
		public NiObject	 // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_NiProperty };
		static constexpr auto Ni_RTTI{ NiRTTI_NiProperty };

		// members
		BSFixedString name;						  // 10
		NiPointer<NiTimeController> controllers;  // 18
		NiExtraDataContainer* extra;			  // 20
	};
	static_assert(sizeof(NiObjectNET) == 0x28);
}
