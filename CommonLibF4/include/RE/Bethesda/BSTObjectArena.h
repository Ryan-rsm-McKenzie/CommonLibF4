#pragma once

namespace RE
{
	class ScrapHeap;

	struct BSTObjectArenaScrapAllocBase
	{
	public:
		// members
		ScrapHeap* scrapHeap;  // 0
	};
	static_assert(sizeof(BSTObjectArenaScrapAllocBase) == 0x8);

	struct BSTObjectArenaScrapAlloc :
		public BSTObjectArenaScrapAllocBase	 // 0
	{
	public:
	};
	static_assert(sizeof(BSTObjectArenaScrapAlloc) == 0x8);

	template <
		class T,
		class Allocator = BSTObjectArenaScrapAlloc,
		std::uint32_t N = 32>
	class BSTObjectArena :
		public Allocator  // 00
	{
	public:
		struct Page
		{
			std::byte buffer[256];	// 000
			Page* next;				// 100
		};

		// members
		Page* head;			 // 08
		Page** tail;		 // 10
		Page* curr;			 // 18
		Page* avail;		 // 20
		char* currAddPos;	 // 28
		char* currHeadPos;	 // 30
		std::uint32_t size;	 // 38
	};
}
