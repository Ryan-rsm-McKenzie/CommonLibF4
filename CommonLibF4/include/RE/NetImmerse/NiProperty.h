#pragma once

#include "RE/NetImmerse/NiObjectNET.h"

namespace RE
{
	class NiUpdateData;

	class NiProperty :
		public NiObjectNET	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_NiProperty };
		static constexpr auto Ni_RTTI{ NiRTTI_NiProperty };

		// add
		virtual std::int32_t Type() const = 0;			  // 28
		virtual void Update(NiUpdateData& a_updateData);  // 29
	};
	static_assert(sizeof(NiProperty) == 0x28);
}
