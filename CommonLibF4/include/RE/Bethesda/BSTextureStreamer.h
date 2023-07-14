#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSResource.h"

namespace RE
{
	namespace BSTextureStreamer
	{
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

		struct ChunkDesc
		{
		public:
			// members
			std::uint64_t dataFileOffset;    // 00
			std::uint32_t size;              // 08
			std::uint32_t uncompressedSize;  // 0C
			std::uint16_t mipFirst;          // 10
			std::uint16_t mipLast;           // 12
			std::uint32_t padding;           // 14
		};
		static_assert(sizeof(ChunkDesc) == 0x18);

		struct TextureDescHeader
		{
		public:
			// members
			BSResource::ID id;           // 00
			std::uint8_t dataFileIndex;  // 0C
			std::uint8_t chunkCount;     // 0D
			std::uint16_t chunkOffset;   // 0E
		};
		static_assert(sizeof(TextureDescHeader) == 0x10);

		template <class T>
		struct NativeDesc :
			public TextureDescHeader  // 00
		{
		public:
			// members
			T info;                    // 10
			ChunkDesc chunks[4];       // ??
			BSFixedString streamName;  // ??
		};
	}
}
