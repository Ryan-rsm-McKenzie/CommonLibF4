#pragma once

#include "RE/Scaleform/Kernel/SF_AllocInfo.h"
#include "RE/Scaleform/Kernel/SF_Atomic.h"
#include "RE/Scaleform/Kernel/SF_List.h"
#include "RE/Scaleform/Kernel/SF_Stats.h"
#include "RE/Scaleform/Kernel/SF_SysAlloc.h"

namespace RE::Scaleform
{
	class __declspec(novtable) MemoryHeap :
		public ListNode<MemoryHeap>  // 08
	{
	public:
		using ChildListType = List<MemoryHeap>;

		struct HeapDesc
		{
		public:
			// members
			std::uint32_t flags{ 0 };                               // 00
			std::size_t minAlign{ 16 };                             // 08
			std::size_t granularity{ 8 * 1024 };                    // 10
			std::size_t reserve{ 8 * 1024 };                        // 18
			std::size_t threshold{ static_cast<std::size_t>(-1) };  // 20
			std::size_t limit{ 0 };                                 // 28
			std::size_t heapID{ 0 };                                // 30
			std::size_t arena{ 0 };                                 // 38
		};
		static_assert(sizeof(HeapDesc) == 0x40);

		struct HeapInfo
		{
		public:
			// members
			HeapDesc desc;       // 00
			MemoryHeap* parent;  // 40
			char* name;          // 48
		};
		static_assert(sizeof(HeapInfo) == 0x50);

		struct __declspec(novtable) HeapVisitor
		{
		public:
			virtual ~HeapVisitor() = default;  // 00

			// add
			virtual void Visit(MemoryHeap* a_parentHeap, MemoryHeap* a_childHeap) = 0;  // 01
		};
		static_assert(sizeof(HeapVisitor) == 0x8);

		struct __declspec(novtable) LimitHandler
		{
		public:
			virtual ~LimitHandler() = default;  // 00

			// add
			virtual bool OnExceedLimit(MemoryHeap* a_heap, std::size_t a_overLimit) = 0;    // 01
			virtual void OnFreeSegment(MemoryHeap* a_heap, std::size_t a_freeingSize) = 0;  // 02
		};
		static_assert(sizeof(LimitHandler) == 0x8);

		struct __declspec(novtable) HeapTracer
		{
		public:
			virtual ~HeapTracer() = default;  // 00

			// add
			virtual void OnCreateHeap(const MemoryHeap* a_heap) = 0;                                                                              // 01
			virtual void OnDestroyHeap(const MemoryHeap* a_heap) = 0;                                                                             // 02
			virtual void OnAlloc(const MemoryHeap* a_heap, std::size_t a_size, std::size_t a_align, std::uint32_t a_sid, const void* a_ptr) = 0;  // 03
			virtual void OnRealloc(const MemoryHeap* a_heap, const void* a_oldPtr, std::size_t a_newSize, const void* a_newPtr) = 0;              // 04
			virtual void OnFree(const MemoryHeap* a_heap, const void* a_ptr) = 0;                                                                 // 05
		};
		static_assert(sizeof(HeapTracer) == 0x8);

		struct RootStats
		{
		public:
			// members
			std::size_t sysMemFootprint;       // 00
			std::size_t sysMemUsedSpace;       // 08
			std::size_t pageMapFootprint;      // 10
			std::size_t pageMapUsedSpace;      // 18
			std::size_t bookkeepingFootprint;  // 20
			std::size_t bookkeepingUsedSpace;  // 28
			std::size_t debugInfoFootprint;    // 30
			std::size_t debugInfoUsedSpace;    // 38
			std::size_t userDebugFootprint;    // 40
			std::size_t userDebugUsedSpace;    // 48
		};
		static_assert(sizeof(RootStats) == 0x50);

		virtual ~MemoryHeap() = default;  // 00

		// add
		virtual void CreateArena(std::size_t a_arena, SysAllocPaged* a_sysAlloc) = 0;                                                        // 01
		virtual void DestroyArena(std::size_t a_arena) = 0;                                                                                  // 02
		virtual bool ArenaIsEmpty(std::size_t a_arena) = 0;                                                                                  // 03
		virtual MemoryHeap* CreateHeap(const char* a_name, const HeapDesc& a_desc) = 0;                                                      // 04
		virtual void SetLimitHandler(LimitHandler* a_handler) = 0;                                                                           // 05
		virtual void SetLimit(std::size_t a_newLimit) = 0;                                                                                   // 06
		virtual void AddRef() = 0;                                                                                                           // 07
		virtual void Release() = 0;                                                                                                          // 08
		virtual void* Alloc(std::size_t a_size, const AllocInfo* a_info = nullptr) = 0;                                                      // 09
		virtual void* Alloc(std::size_t a_size, std::size_t a_align, const AllocInfo* a_info = nullptr) = 0;                                 // 0A
		virtual void* Realloc(void* a_oldPtr, std::size_t a_newSize) = 0;                                                                    // 0B
		virtual void Free(void* a_ptr) = 0;                                                                                                  // 0C
		virtual void* AllocAutoHeap(const void* a_thisPtr, std::size_t a_size, const AllocInfo* a_info = nullptr) = 0;                       // 0D
		virtual void* AllocAutoHeap(const void* a_thisPtr, std::size_t a_size, std::size_t a_align, const AllocInfo* a_info = nullptr) = 0;  // 0E
		virtual MemoryHeap* GetAllocHeap(const void* a_thisPtr) = 0;                                                                         // 0F
		virtual std::size_t GetUsableSize(const void* a_ptr) = 0;                                                                            // 10
		virtual void* AllocSysDirect(std::size_t a_size) = 0;                                                                                // 11
		virtual void FreeSysDirect(void* a_ptr, std::size_t a_size) = 0;                                                                     // 12
		virtual bool GetStats(StatBag* a_bag) = 0;                                                                                           // 13
		virtual std::size_t GetFootprint() const = 0;                                                                                        // 14
		virtual std::size_t GetTotalFootprint() const = 0;                                                                                   // 15
		virtual std::size_t GetUsedSpace() const = 0;                                                                                        // 16
		virtual std::size_t GetTotalUsedSpace() const = 0;                                                                                   // 17
		virtual void GetRootStats(RootStats* a_stats) = 0;                                                                                   // 18
		virtual void VisitMem(Heap::MemVisitor* a_visitor, std::uint32_t a_flags) = 0;                                                       // 19
		virtual void VisitRootSegments(Heap::SegVisitor* a_visitor) = 0;                                                                     // 1A
		virtual void VisitHeapSegments(Heap::SegVisitor* a_visitor) const = 0;                                                               // 1B
		virtual void SetTracer(HeapTracer* a_tracer) = 0;                                                                                    // 1C
		virtual void DestroyItself() = 0;                                                                                                    // 1D
		virtual void UltimateCheck() = 0;                                                                                                    // 1E
		virtual void ReleaseCachedMem() = 0;                                                                                                 // 1F
		virtual bool DumpMemoryLeaks() = 0;                                                                                                  // 20
		virtual void CheckIntegrity() const = 0;                                                                                             // 21
		virtual void GetUserDebugStats(RootStats* a_stats) const = 0;                                                                        // 22

		void AssignToCurrentThread() { ownerThreadID = WinAPI::GetCurrentThreadID(); }

		// members
		std::size_t selfSize;             // 18
		volatile std::uint32_t refCount;  // 20
		std::size_t ownerThreadID;        // 28
		void* autoRelease;                // 30
		HeapInfo info;                    // 38
		ChildListType childHeaps;         // 88
		mutable Lock heapLock;            // 98
		bool useLocks;                    // C0
		bool trackDebugInfo;              // C1
	};
	static_assert(sizeof(MemoryHeap) == 0xC8);
}
