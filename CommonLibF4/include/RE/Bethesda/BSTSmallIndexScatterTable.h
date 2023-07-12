#pragma once

namespace RE
{
	// maps a key to a uint32_t index
	// the value of the index is provided externally (typically just some counter)
	// this index is used to index an array, which is also provided externally
	// essentially implements a scatter table with chaining for conflict resolution
	// it is honestly impressive how awful this data structure is, bethesda never fails to impress
	template <class Traits, class Accessor>
	class BSTSmallIndexScatterTable
	{
	public:
		struct entry_type
		{
			std::uint16_t next = 0xFFFF;   // the next slot the check for conflict resolution, or 0xFFFF if no chain
			std::uint16_t index = 0xFFFF;  // the actual index, or 0xFFFF if invalid
		};

		std::uint64_t pad;       // 00
		entry_type* table;       // 08
		std::uint32_t size;      // 10
		std::uint32_t mask;      // 14
		std::uint32_t avail;     // 18
		std::uint32_t lastFree;  // 1C
	};
	// static_assert(sizeof(BSTSmallIndexScatterTable) == 0x20);
}
