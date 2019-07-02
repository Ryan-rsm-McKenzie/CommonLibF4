#pragma once

#include "RE/Scaleform/List.h"
#include "RE/Scaleform/ListNode.h"
#include "RE/Scaleform/Lock.h"
#include "RE/Scaleform/Stats.h"


namespace RE
{
	namespace Scaleform
	{
		namespace Heap
		{
			class MemVisitor;
			class SegVisitor;
		}


		class StatBag;
		class SysAllocPaged;


		class MemoryHeap : public ListNode<MemoryHeap>
		{
		public:
			using ChildListType = List<MemoryHeap>;


			enum class HeapFlags : UInt32
			{
				kNone = 0,
				kThreadUnsafe = 1 << 0,
				kFastTinyBlocks = 1 << 1,
				kFixedGranularity = 1 << 2,
				kRoot = 1 << 3,
				kNoDebugInfo = 1 << 4,
				kUserDebug = 1 << 12
			};


			struct HeapDesc
			{
				HeapDesc(HeapFlags a_flags = HeapFlags::kNone,
						 UPInt a_minAlign = 16,
						 UPInt a_granularity = 8 * 1024,
						 UPInt a_reserve = 8 * 1024,
						 UPInt a_threshold = ~UPInt(0),
						 UPInt a_limit = 0,
						 UPInt a_heapID = 0,
						 UPInt a_arena = 0);

				void Clear();


				// members
				HeapFlags	flags;			// 00
				UInt32		pad04;			// 04
				UPInt		minAlign;		// 08
				UPInt		granularity;	// 10
				UPInt		reserve;		// 18
				UPInt		threshold;		// 20
				UPInt		limit;			// 28
				UPInt		heapID;			// 30
				UPInt		arena;			// 38
			};
			STATIC_ASSERT(sizeof(HeapDesc) == 0x40);


			struct RootHeapDesc : public HeapDesc
			{
				enum : UInt32
				{
					kMinAlign = 16,
					kGranularity = 16 * 1024,
					kReserve = 16 * 1024,
					kThreshold = 256 * 1024,
					kLimit = 0
				};


				RootHeapDesc();
			};
			STATIC_ASSERT(sizeof(RootHeapDesc) == 0x40);


			struct HeapInfo
			{
				HeapDesc	desc;	// 00
				MemoryHeap*	parent;	// 40 - null == root heap
				char*		name;	// 48
			};
			STATIC_ASSERT(sizeof(HeapInfo) == 0x50);


			struct HeapVisitor
			{
				virtual ~HeapVisitor() = default;											// 00

				// add
				virtual void Visit(MemoryHeap* a_parentHeap, MemoryHeap* a_childHeap) = 0;	// 01
			};
			STATIC_ASSERT(sizeof(HeapVisitor) == 0x8);


			struct LimitHandler
			{
				virtual ~LimitHandler() = default;											// 00

				// add
				virtual bool OnExceedLimit(MemoryHeap* a_heap, UPInt a_overLimit) = 0;		// 01
				virtual void OnFreeSegment(MemoryHeap* a_heap, UPInt a_freeingSize) = 0;	// 02
			};
			STATIC_ASSERT(sizeof(LimitHandler) == 0x8);


			struct HeapTracer
			{
				virtual ~HeapTracer() = default;																					// 00

				// add
				virtual void OnCreateHeap(const MemoryHeap* a_heap) = 0;															// 01
				virtual void OnDestroyHeap(const MemoryHeap* a_heap) = 0;															// 02
				virtual void OnAlloc(const MemoryHeap* a_heap, UPInt a_size, UPInt a_align, UInt32 a_sid, const void* a_ptr) = 0;	// 03
				virtual void OnRealloc(const MemoryHeap* a_heap, const void* a_oldPtr, UPInt a_newSize, const void* a_newPtr) = 0;	// 04
				virtual void OnFree(const MemoryHeap* a_heap, const void* a_ptr) = 0;												// 05
			};
			STATIC_ASSERT(sizeof(HeapTracer) == 0x8);


			struct RootStats
			{
				UPInt	sysMemFootprint;		// 00
				UPInt	sysMemUsedSpace;		// 08
				UPInt	pageMapFootprint;		// 10
				UPInt	pageMapUsedSpace;		// 18
				UPInt	bookkeepingFootprint;	// 20
				UPInt	bookkeepingUsedSpace;	// 28
				UPInt	debugInfoFootprint;		// 30
				UPInt	debugInfoUsedSpace;		// 38
				UPInt	userDebugFootprint;		// 40
				UPInt	userDebugUsedSpace;		// 48
			};
			STATIC_ASSERT(sizeof(RootStats) == 0x50);


			virtual ~MemoryHeap() = default;														// 00

			// add
			virtual void		CreateArena(UPInt a_arena, SysAllocPaged* a_sysAlloc) = 0;			// 01
			virtual void		DestroyArena(UPInt a_arena) = 0;									// 02
			virtual bool		ArenaIsEmpty(UPInt a_arena) = 0;									// 03
			virtual MemoryHeap*	CreateHeap(const char* a_name, const HeapDesc& a_desc) = 0;			// 04
			virtual void		SetLimitHandler(LimitHandler* a_handler) = 0;						// 05
			virtual void		SetLimit(UPInt a_newLimit) = 0;										// 06
			virtual void		AddRef() = 0;														// 07
			virtual void		Release() = 0;														// 08
			virtual void*		Alloc(UPInt a_size) = 0;											// 09
			virtual void*		Alloc(UPInt a_size, UPInt a_align) = 0;								// 0A
			virtual void*		Realloc(void* a_oldPtr, UPInt a_newSize) = 0;						// 0B
			virtual void		Free(void* a_ptr) = 0;												// 0C
			virtual void*		AllocAutoHeap(const void* a_this, UPInt a_size) = 0;				// 0D
			virtual void*		AllocAutoHeap(const void* a_this, UPInt a_size, UPInt a_align) = 0;	// 0E
			virtual MemoryHeap*	GetAllocHeap(const void* a_this) = 0;								// 0F
			virtual UPInt		GetUsableSize(const void* a_ptr) = 0;								// 10
			virtual void*		AllocSysDirect(UPInt a_size) = 0;									// 11
			virtual void		FreeSysDirect(void* a_ptr, UPInt a_size) = 0;						// 12
			virtual bool		GetStats(StatBag* a_bag) = 0;										// 13
			virtual UPInt		GetFootprint() const = 0;											// 14
			virtual UPInt		GetTotalFootprint() const = 0;										// 15
			virtual UPInt		GetUsedSpace() const = 0;											// 16
			virtual UPInt		GetTotalUsedSpace() const = 0;										// 17
			virtual void		GetRootStats(RootStats* a_stats) = 0;								// 18
			virtual void		VisitMem(Heap::MemVisitor* a_visitor, UInt32 a_flags) = 0;			// 19
			virtual void		VisitRootSegments(Heap::SegVisitor* a_visitor) = 0;					// 1A
			virtual void		VisitHeapSegments(Heap::SegVisitor* a_visitor) const = 0;			// 1B
			virtual void		SetTracer(HeapTracer* a_tracer) = 0;								// 1C
			virtual void		DestroyItself() = 0;												// 1D
			virtual void		UltimateCheck() = 0;												// 1E
			virtual void		ReleaseCachedMem() = 0;												// 1F
			virtual bool		DumpMemoryLeaks() = 0;												// 20
			virtual void		CheckIntegrity() const = 0;											// 21
			virtual void		GetUserDebugStats(RootStats* a_stats) const = 0;					// 22

			MemoryHeap* CreateHeap(const char* a_name,
								   HeapFlags a_flags = HeapFlags::kNone,
								   UPInt a_minAlign = 16,
								   UPInt a_granularity = 16 * 1024,
								   UPInt a_reserve = 16 * 1024,
								   UPInt a_threshold = ~UPInt(0),
								   UPInt a_limit = 0,
								   UPInt a_heapID = 0,
								   UPInt a_arena = 0);
			const char*	GetName() const;
			UPInt		GetID() const;
			MemoryHeap*	GetParentHeap() const;
			HeapFlags	GetFlags() const;
			UPInt		GetGranularity() const;
			UPInt		GetLimit() const;
			bool		IsThreadSafe() const;


			// members
			UPInt			selfSize;		// 18
			volatile UInt32	refCount;		// 20
			UInt32			pad24;			// 24
			UPInt			ownerThreadID;	// 28
			void*			autoRelease;	// 30
			HeapInfo		info;			// 38
			ChildListType	childHeaps;		// 88
			mutable Lock	heapLock;		// 98
			bool			useLocks;		// C0
			bool			trackDebugInfo;	// C1
			UInt16			padC2;			// C2
			UInt32			padC4;			// C4
		};
		STATIC_ASSERT(sizeof(MemoryHeap) == 0xC8);
	}
}
