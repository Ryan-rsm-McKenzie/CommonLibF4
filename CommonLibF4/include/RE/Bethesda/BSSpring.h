#pragma once

#include "RE/NetImmerse/NiPoint2.h"
#include "RE/NetImmerse/NiPoint3.h"

namespace RE::BSSpring
{
	template <class T>
	struct SpringState
	{
	public:
		// members
		T position;            // 00
		T velocity;            // ??
		float springConstant;  // ??
	};

	extern template struct SpringState<float>;
	extern template struct SpringState<NiPoint2>;
	extern template struct SpringState<NiPoint3>;
}
