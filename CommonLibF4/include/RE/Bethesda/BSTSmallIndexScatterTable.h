#pragma once

namespace RE
{
	// maps a key to a uint32_t index
	// the value of the index is provided externally (typically just some counter)
	// this index is used to index an array, which is also provided externally
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
