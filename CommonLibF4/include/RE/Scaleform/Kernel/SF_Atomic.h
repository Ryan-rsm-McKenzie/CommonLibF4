#pragma once

namespace RE
{
	namespace Scaleform
	{
		class Lock
		{
		public:
			// members
			CRITICAL_SECTION cs;  // 00
		};
		static_assert(sizeof(Lock) == 0x28);
	}
}
