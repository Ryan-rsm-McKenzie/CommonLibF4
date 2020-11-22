#include "RE/Bethesda/BSSpring.h"

namespace RE::BSSpring
{
	template struct SpringState<float>;
	static_assert(sizeof(SpringState<float>) == 0xC);

	template struct SpringState<NiPoint2>;
	static_assert(sizeof(SpringState<NiPoint2>) == 0x14);

	template struct SpringState<NiPoint3>;
	static_assert(sizeof(SpringState<NiPoint3>) == 0x1C);
}
