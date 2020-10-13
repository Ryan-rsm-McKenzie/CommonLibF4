#pragma once

namespace RE
{
	class __declspec(novtable) hkMemoryAllocator
	{
	public:
		static constexpr auto RTTI{ RTTI::hkMemoryAllocator };
		static constexpr auto VTABLE{ VTABLE::hkMemoryAllocator };

		struct ExtendedInterface;
		struct MemoryStatistics;

		virtual ~hkMemoryAllocator() = default;  // 00

		// add
		virtual void* BlockAlloc(std::int32_t a_numBytesIn) = 0;                                             // 01
		virtual void BlockFree(void* a_ptr, std::int32_t a_numBytesIn) = 0;                                  // 02
		virtual void* BufAlloc(std::int32_t& a_reqNumBytesInOut) { return BlockAlloc(a_reqNumBytesInOut); }  // 03
		virtual void BufFree(void* a_ptr, std::int32_t a_numBytes) { BlockFree(a_ptr, a_numBytes); }         // 04

		virtual void* BufRealloc(void* a_old, std::int32_t a_oldNumBytes, std::int32_t& a_reqNumBytesInOut)  // 05
		{
			auto mem = BufAlloc(a_reqNumBytesInOut);
			if (mem) {
				std::memcpy(
					mem,
					a_old,
					std::min(a_oldNumBytes, a_reqNumBytesInOut));
			}
			BufFree(a_old, a_oldNumBytes);
			return mem;
		}

		virtual void BlockAllocBatch(void** a_ptrsOut, std::int32_t a_numPtrs, std::int32_t a_blockSize)  // 06
		{
			if (a_numPtrs > 0) {
				for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(a_numPtrs); ++i) {
					a_ptrsOut[i] = BlockAlloc(a_blockSize);
				}
			}
		}

		virtual void BlockFreeBatch(void** a_ptrsIn, std::int32_t a_numPtrs, std::int32_t a_blockSize)  // 07
		{
			if (a_numPtrs > 0) {
				for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(a_numPtrs); ++i) {
					BlockFree(a_ptrsIn[i], a_blockSize);
				}
			}
		}

		virtual void GetMemoryStatistics(MemoryStatistics& a_stats) const = 0;                        // 08
		virtual std::int32_t GetAllocatedSize(const void* a_obj, std::int32_t a_numBytes) const = 0;  // 09
		virtual void ResetPeakMemoryStatistics() { return; }                                          // 0A
		virtual ExtendedInterface* GetExtendedInterface() { return nullptr; }                         // 0B
	};
	static_assert(sizeof(hkMemoryAllocator) == 0x8);
}
