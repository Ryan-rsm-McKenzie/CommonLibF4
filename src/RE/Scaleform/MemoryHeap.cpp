#include "RE/Scaleform/MemoryHeap.h"


namespace RE
{
	namespace Scaleform
	{
		MemoryHeap::HeapDesc::HeapDesc(HeapFlags a_flags, UPInt a_minAlign, UPInt a_granularity, UPInt a_reserve, UPInt a_threshold, UPInt a_limit, UPInt a_heapID, UPInt a_arena) :
			flags(a_flags),
			pad04(0),
			minAlign(a_minAlign),
			granularity(a_granularity),
			reserve(a_reserve),
			threshold(a_threshold),
			limit(a_limit),
			heapID(a_heapID),
			arena(a_arena)
		{}


		void MemoryHeap::HeapDesc::Clear()
		{
			flags = HeapFlags::kNone;
			granularity = 0;
			minAlign = 16;
			reserve = 0;
			threshold = ~UPInt(0);
			limit = 0;
			heapID = 0;
			arena = 0;
		}


		MemoryHeap::RootHeapDesc::RootHeapDesc() :
			HeapDesc(HeapFlags::kNone, kMinAlign, kGranularity, kReserve, kThreshold, kLimit, kHeapID_Global)
		{}


		MemoryHeap* MemoryHeap::CreateHeap(const char* a_name, HeapFlags a_flags, UPInt a_minAlign, UPInt a_granularity, UPInt a_reserve, UPInt a_threshold, UPInt a_limit, UPInt a_heapID, UPInt a_arena)
		{
			HeapDesc desc(a_flags, a_minAlign, a_granularity, a_reserve, a_threshold, a_limit, a_heapID, a_arena);
			return CreateHeap(a_name, desc);
		}


		const char* MemoryHeap::GetName() const
		{
			return info.name;
		}


		UPInt MemoryHeap::GetID() const
		{
			return info.desc.heapID;
		}


		MemoryHeap* MemoryHeap::GetParentHeap() const
		{
			return info.parent;
		}


		auto MemoryHeap::GetFlags() const
			-> HeapFlags
		{
			return info.desc.flags;
		}


		UPInt MemoryHeap::GetGranularity() const
		{
			return info.desc.granularity;
		}


		UPInt MemoryHeap::GetLimit() const
		{
			return info.desc.limit;
		}


		bool MemoryHeap::IsThreadSafe() const
		{
			return (info.desc.flags & HeapFlags::kThreadUnsafe) == HeapFlags::kNone;
		}
	}
}
