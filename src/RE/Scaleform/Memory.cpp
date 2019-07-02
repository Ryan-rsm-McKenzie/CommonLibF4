#include "RE/Scaleform/Memory.h"

#include "f4se/ScaleformAPI.h"

#include "RE/Scaleform/MemoryHeap.h"


namespace RE
{
	namespace Scaleform
	{
		void Memory::SetGlobalHeap(MemoryHeap* a_heap)
		{
			GetGlobalHeapRef() = a_heap;
		}


		MemoryHeap* Memory::GetGlobalHeap()
		{
			return GetGlobalHeapRef();
		}


		void Memory::CreateArena(UPInt a_arena, SysAllocPaged* a_sysAlloc)
		{
			GetGlobalHeap()->CreateArena(a_arena, a_sysAlloc);
		}


		void Memory::DestroyArena(UPInt a_arena)
		{
			GetGlobalHeap()->DestroyArena(a_arena);
		}


		bool Memory::ArenaIsEmpty(UPInt a_arena)
		{
			return GetGlobalHeap()->ArenaIsEmpty(a_arena);
		}


		void* Memory::Alloc(UPInt a_size)
		{
			return GetGlobalHeap()->Alloc(a_size);
		}


		void* Memory::Alloc(UPInt a_size, UPInt a_align)
		{
			return GetGlobalHeap()->Alloc(a_size, a_align);
		}


		void* Memory::AllocAutoHeap(const void* a_ptr, UPInt a_size)
		{
			return GetGlobalHeap()->AllocAutoHeap(a_ptr, a_size);
		}


		void* Memory::AllocAutoHeap(const void* a_ptr, UPInt a_size, UPInt a_align)
		{
			return GetGlobalHeap()->AllocAutoHeap(a_ptr, a_size, a_align);
		}


		void* Memory::AllocInHeap(MemoryHeap* a_heap, UPInt a_size)
		{
			return a_heap->Alloc(a_size);
		}


		void* Memory::AllocInHeap(MemoryHeap* a_heap, UPInt a_size, UPInt a_align)
		{
			return a_heap->Alloc(a_size, a_align);
		}


		void* Memory::Realloc(void* a_ptr, UPInt a_newSize)
		{
			return GetGlobalHeap()->Realloc(a_ptr, a_newSize);
		}


		void Memory::Free(void* a_ptr)
		{
			return GetGlobalHeap()->Free(a_ptr);
		}


		MemoryHeap* Memory::GetHeapByAddress(const void* a_ptr)
		{
			return GetGlobalHeap()->GetAllocHeap(a_ptr);
		}


		bool Memory::DetectMemoryLeaks()
		{
			return GetGlobalHeap()->DumpMemoryLeaks();
		}


		MemoryHeap*& Memory::GetGlobalHeapRef()
		{
			return *unrestricted_cast<MemoryHeap**>(g_scaleformHeap.GetUIntPtr());
		}
	}
}
