#pragma once

#include "RE/Scaleform/Kernel/SF_Stats.h"

namespace RE
{
	namespace Scaleform
	{
		struct AllocInfo;

		struct AllocInfo
		{
		public:
			~AllocInfo() noexcept {}  // intentional

			// members
			std::uint32_t statID;  // 0
		};
		static_assert(sizeof(AllocInfo) == 0x4);
	}
}
