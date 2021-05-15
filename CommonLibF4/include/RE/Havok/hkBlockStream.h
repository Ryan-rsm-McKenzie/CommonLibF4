#pragma once

#include "RE/Havok/hkArray.h"

namespace RE
{
	class hkBlockStreamAllocator;

	namespace hkBlockStreamBase
	{
		struct Block;

		class Stream
		{
		public:
			// members
			hkBlockStreamAllocator* allocator;           // 00
			std::int32_t numTotalElements;               // 08
			Stream* blockStreamPpu;                      // 10
			bool partiallyFreed;                         // 18
			bool zeroNewBlocks;                          // 19
			bool isLocked;                               // 1A
			bool spuWronglySentConsumedBlockStreamBack;  // 1B
			hkInplaceArrayAligned16<Block*, 24> blocks;  // 20
		};
	}

	template <class T>
	class hkBlockStream :
		public hkBlockStreamBase::Stream  // 00
	{
	public:
		class Writer;
	};
}
