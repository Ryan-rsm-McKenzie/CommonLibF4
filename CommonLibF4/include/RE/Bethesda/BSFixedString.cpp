#include "RE/Bethesda/BSFixedString.h"

namespace RE
{
	namespace detail
	{
		template class BSFixedString<char, false>;
		template class BSFixedString<char, true>;
		template class BSFixedString<wchar_t, false>;
		template class BSFixedString<wchar_t, true>;
	}
}
