#pragma once

namespace RE
{
	struct BSTextureStreamer
	{
	public:
		class LocalHeap
		{
		public:
			struct FreeBlock;

			// members
			std::byte* memoryBase;          // 00
			FreeBlock* freeList;            // 08
			std::uint32_t freeBlocks;       // 10
			std::uint32_t allocatedBlocks;  // 14
		};
		static_assert(sizeof(LocalHeap) == 0x18);
	};
	static_assert(std::is_empty_v<BSTextureStreamer>);
}
