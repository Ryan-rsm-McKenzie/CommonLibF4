#pragma once

#include "RE/Scaleform/Kernel/SF_Memory.h"

namespace RE::Scaleform::Render
{
	class LinearHeap;

	class LinearHeap
	{
	public:
		struct PageType
		{
		public:
			// members
			std::byte* start;  // 00
			std::byte* end;    // 08
			std::byte* free;   // 10
		};
		static_assert(sizeof(PageType) == 0x18);

		// members
		MemoryHeap* heap;         // 00
		std::size_t granularity;  // 08
		PageType* pagePool;       // 10
		PageType* lastPage;       // 18
		std::size_t maxPages;     // 20
	};
	static_assert(sizeof(LinearHeap) == 0x28);

	template <class C, std::int32_t N>
	class PagedItemBuffer
	{
	public:
		struct Page
		{
		public:
			// members
			Page* next;          // 00
			std::int32_t count;  // 08
			C items[N];          // ??
		};

		// members
		Page* pages;  // 00
		Page* last;   // 08
	};
	//static_assert(sizeof(PagedItemBuffer<void*, 0>) == 0x10);
}
