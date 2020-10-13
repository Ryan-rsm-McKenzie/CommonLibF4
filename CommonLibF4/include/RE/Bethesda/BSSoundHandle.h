#pragma once

namespace RE
{
	class BSSoundHandle
	{
	public:
		~BSSoundHandle() noexcept {}  // intentional

		// members
		std::uint32_t soundID;  // 0
		bool assumeSuccess;     // 4
		std::int8_t state;      // 5
	};
	static_assert(sizeof(BSSoundHandle) == 0x8);
}
