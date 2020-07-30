#pragma once

namespace RE
{
	namespace Scaleform
	{
		struct AllocInfo
		{
		public:
			// members
			std::uint32_t statID;  // 0
		};
		static_assert(sizeof(AllocInfo) == 0x4);
	}
}
