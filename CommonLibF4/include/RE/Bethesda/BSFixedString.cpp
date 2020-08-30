#include "RE/Bethesda/BSFixedString.h"

namespace RE
{
	namespace detail
	{
		template class BSFixedString<char, false>;
		static_assert(sizeof(BSFixedString<char, false>) == 0x8);

		template class BSFixedString<char, true>;
		static_assert(sizeof(BSFixedString<char, true>) == 0x8);

		template class BSFixedString<wchar_t, false>;
		static_assert(sizeof(BSFixedString<wchar_t, false>) == 0x8);

		template class BSFixedString<wchar_t, true>;
		static_assert(sizeof(BSFixedString<wchar_t, true>) == 0x8);
	}

	template struct BSCRC32<BSFixedString>;
	template struct BSCRC32<BSFixedStringCS>;
	template struct BSCRC32<BSFixedStringW>;
	template struct BSCRC32<BSFixedStringWCS>;
}
