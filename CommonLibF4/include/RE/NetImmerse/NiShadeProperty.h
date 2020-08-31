#pragma once

#include "RE/NetImmerse/NiProperty.h"

namespace RE
{
	class NiShadeProperty :
		public NiProperty  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_NiShadeProperty };
		static constexpr auto Ni_RTTI{ NiRTTI_NiShadeProperty };

		// add
		virtual bool SetupGeometry([[maybe_unused]] BSGeometry* a_geometry) { return true; }  // 2A
	};
	static_assert(sizeof(NiShadeProperty) == 0x28);
}
