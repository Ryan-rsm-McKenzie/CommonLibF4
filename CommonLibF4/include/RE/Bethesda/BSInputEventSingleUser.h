#pragma once

#include "RE/Bethesda/BSInputEventReceiver.h"
#include "RE/Bethesda/BSInputEventUser.h"

namespace RE
{
	class BSInputEventSingleUser :
		public BSInputEventReceiver,  // 00
		public BSInputEventUser       // 10
	{
	public:
		static constexpr auto RTTI{ RTTI::BSInputEventSingleUser };
		static constexpr auto VTABLE{ VTABLE::BSInputEventSingleUser };
	};
	static_assert(sizeof(BSInputEventSingleUser) == 0x20);
}
