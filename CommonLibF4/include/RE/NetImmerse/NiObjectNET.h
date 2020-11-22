#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/NetImmerse/NiObject.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class NiExtraDataContainer;
	class NiTimeController;

	class __declspec(novtable) NiObjectNET :
		public NiObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::NiObjectNET };
		static constexpr auto VTABLE{ VTABLE::NiObjectNET };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiObjectNET };

		NiObjectNET();
		virtual ~NiObjectNET();  // NOLINT(modernize-use-override) 00

		F4_HEAP_REDEFINE_NEW(NiObjectNET);

		[[nodiscard]] std::string_view GetName() const { return name; }

		// members
		BSFixedString name{ "" };                 // 10
		NiPointer<NiTimeController> controllers;  // 18
		NiExtraDataContainer* extra{ nullptr };   // 20
	};
	static_assert(sizeof(NiObjectNET) == 0x28);
}
