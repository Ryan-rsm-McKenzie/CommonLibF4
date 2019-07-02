#pragma once


namespace RE
{
	namespace Scaleform
	{
		class MemoryHeap;
		class SysAllocPaged;


		class Memory
		{
		public:
			static void			SetGlobalHeap(MemoryHeap* a_heap);
			static MemoryHeap*	GetGlobalHeap();
			static void			CreateArena(UPInt a_arena, SysAllocPaged* a_sysAlloc);
			static void			DestroyArena(UPInt a_arena);
			static bool			ArenaIsEmpty(UPInt a_arena);
			static void*		Alloc(UPInt a_size);
			static void*		Alloc(UPInt a_size, UPInt a_align);
			static void*		AllocAutoHeap(const void* a_ptr, UPInt a_size);
			static void*		AllocAutoHeap(const void* a_ptr, UPInt a_size, UPInt a_align);
			static void*		AllocInHeap(MemoryHeap* a_heap, UPInt a_size);
			static void*		AllocInHeap(MemoryHeap* a_heap, UPInt a_size, UPInt a_align);
			static void*		Realloc(void* a_ptr, UPInt a_newSize);
			static void			Free(void* a_ptr);
			static MemoryHeap*	GetHeapByAddress(const void* a_ptr);
			static bool			DetectMemoryLeaks();

		private:
			static MemoryHeap*&	GetGlobalHeapRef();
		};
	}
}


// Global heap
#define SF_ALLOC(a_count)				RE::Scaleform::Memory::Alloc((a_count))
#define SF_MEMALIGN(a_count, a_align)	RE::Scaleform::Memory::Alloc((a_count), (a_align))
#define SF_REALLOC(a_ptr, a_count)		RE::Scaleform::Memory::Realloc((a_ptr), (a_count))
#define SF_FREE(a_ptr)					RE::Scaleform::Memory::Free((a_ptr))
#define SF_FREE_ALIGN(a_count)			RE::Scaleform::Memory::Free((a_count))


// Local heap
#define SF_HEAP_ALLOC(a_heap, a_count)				RE::Scaleform::Memory::AllocInHeap((a_heap), (a_count))
#define SF_HEAP_MEMALIGN(a_heap, a_count, a_align)	RE::Scaleform::Memory::AllocInHeap((a_heap), (a_count), (a_align))
#define SF_HEAP_AUTO_ALLOC(a_addr, a_count)			RE::Scaleform::Memory::AllocAutoHeap((a_addr), (a_count))
#define SF_HEAP_FREE(a_heap, a_ptr)					RE::Scaleform::Memory::Free((a_ptr))


#define SF_MEMORY_REDEFINE_NEW_IMPL(a_className, a_checkDelete, a_statType)																	\
	void*	operator new(std::size_t a_count)													{ return SF_ALLOC(a_count); }				\
	void*	operator new[](std::size_t a_count)													{ return SF_ALLOC(a_count); }				\
	void*	operator new([[maybe_unused]] std::size_t a_count, void* a_plcmnt)					{ return a_plcmnt; }						\
	void*	operator new[]([[maybe_unused]] std::size_t a_count, void* a_plcmnt)				{ return a_plcmnt; }						\
	void*	operator new(std::size_t a_count, RE::Scaleform::MemoryHeap* a_heap)				{ return SF_HEAP_ALLOC(a_heap, a_count); }	\
	void*	operator new[](std::size_t a_count, RE::Scaleform::MemoryHeap* a_heap)				{ return SF_HEAP_ALLOC(a_heap, a_count); }	\
	void	operator delete(void* a_ptr)														{ SF_FREE(a_ptr); }							\
	void	operator delete[](void* a_ptr)														{ SF_FREE(a_ptr); }							\
	void	operator delete([[maybe_unused]] void* a_ptr, [[maybe_unused]] void* a_plcmnt)		{ }											\
	void	operator delete[]([[maybe_unused]] void* a_ptr, [[maybe_unused]] void* a_plcmnt)	{ }											\
	void	operator delete(void* a_ptr, RE::Scaleform::MemoryHeap* a_heap)						{ SF_HEAP_FREE(a_heap, a_ptr); }


#define SF_MEMORY_CHECK_DELETE_NONE(a_className, a_ptr)
#define SF_MEMORY_REDEFINE_NEW(a_className, a_statType) SF_MEMORY_REDEFINE_NEW_IMPL(a_className, SF_MEMORY_CHECK_DELETE_NONE, a_statType)
