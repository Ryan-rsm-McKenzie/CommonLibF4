#include "RE/Bethesda/CRC.h"

namespace RE
{
	template struct BSCRC32<std::int8_t>;
	template struct BSCRC32<std::uint8_t>;
	template struct BSCRC32<std::int16_t>;
	template struct BSCRC32<std::uint16_t>;
	template struct BSCRC32<std::int32_t>;
	template struct BSCRC32<std::uint32_t>;
	template struct BSCRC32<std::int64_t>;
	template struct BSCRC32<std::uint64_t>;
}
