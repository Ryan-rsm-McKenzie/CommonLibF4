#include "RE/NetImmerse/NiRect.h"

namespace RE
{
	template class NiRect<float>;
	static_assert(sizeof(NiRect<float>) == 0x10);

	template class NiRect<std::int32_t>;
	static_assert(sizeof(NiRect<std::int32_t>) == 0x10);

	template class NiRect<std::uint32_t>;
	static_assert(sizeof(NiRect<std::uint32_t>) == 0x10);
}
