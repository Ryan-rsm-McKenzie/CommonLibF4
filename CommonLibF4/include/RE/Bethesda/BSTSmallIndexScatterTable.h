#pragma once

namespace RE
{
	template <class T, class Accessor>
	class BSTSmallIndexScatterTable
	{
	public:
		std::uint64_t pad;       // 00
		std::uint32_t* table;    // 08
		std::uint32_t size;      // 10
		std::uint32_t mask;      // 14
		std::uint32_t avail;     // 18
		std::uint32_t lastFree;  // 1C
	};
}
