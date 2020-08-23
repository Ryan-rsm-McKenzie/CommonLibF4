#pragma once

#include "RE/Scaleform/Kernel/SF_MemoryHeap.h"

namespace RE
{
	namespace Scaleform
	{
		class Memory;

		class Memory
		{
		public:
			static inline void SetGlobalHeap(MemoryHeap* a_heap)
			{
				REL::Relocation<MemoryHeap**> heap{ REL::ID(939898) };
				*heap = a_heap;
			}

			[[nodiscard]] static inline MemoryHeap* GetGlobalHeap()
			{
				REL::Relocation<MemoryHeap**> heap{ REL::ID(939898) };
				return *heap;
			}

			static inline void CreateArena(std::size_t a_arena, SysAllocPaged* a_sysAlloc)
			{
				GetGlobalHeap()->CreateArena(a_arena, a_sysAlloc);
			}

			static inline void DestroyArena(std::size_t a_arena)
			{
				GetGlobalHeap()->DestroyArena(a_arena);
			}

			[[nodiscard]] static inline bool ArenaIsEmpty(std::size_t a_arena)
			{
				return GetGlobalHeap()->ArenaIsEmpty(a_arena);
			}

			[[nodiscard]] static inline void* Alloc(std::size_t a_size)
			{
				return GetGlobalHeap()->Alloc(a_size);
			}

			[[nodiscard]] static inline void* Alloc(std::size_t a_size, std::size_t a_align)
			{
				return GetGlobalHeap()->Alloc(a_size, a_align);
			}

			[[nodiscard]] static inline void* Alloc(std::size_t a_size, const AllocInfo& a_info)
			{
				return GetGlobalHeap()->Alloc(a_size, std::addressof(a_info));
			}

			[[nodiscard]] static inline void* Alloc(std::size_t a_size, std::size_t a_align, const AllocInfo& a_info)
			{
				return GetGlobalHeap()->Alloc(a_size, a_align, std::addressof(a_info));
			}

			[[nodiscard]] static inline void* AllocAutoHeap(const void* a_ptr, std::size_t a_size)
			{
				return GetGlobalHeap()->AllocAutoHeap(a_ptr, a_size);
			}

			[[nodiscard]] static inline void* AllocAutoHeap(const void* a_ptr, std::size_t a_size, std::size_t a_align)
			{
				return GetGlobalHeap()->AllocAutoHeap(a_ptr, a_size, a_align);
			}

			[[nodiscard]] static inline void* AllocAutoHeap(const void* a_ptr, std::size_t a_size, const AllocInfo& a_info)
			{
				return GetGlobalHeap()->AllocAutoHeap(a_ptr, a_size, std::addressof(a_info));
			}

			[[nodiscard]] static inline void* AllocAutoHeap(const void* a_ptr, std::size_t a_size, std::size_t a_align, const AllocInfo& a_info)
			{
				return GetGlobalHeap()->AllocAutoHeap(a_ptr, a_size, a_align, std::addressof(a_info));
			}

			[[nodiscard]] static inline void* AllocInHeap(MemoryHeap* a_heap, std::size_t a_size)
			{
				return a_heap->Alloc(a_size);
			}

			[[nodiscard]] static inline void* AllocInHeap(MemoryHeap* a_heap, std::size_t a_size, std::size_t a_align)
			{
				return a_heap->Alloc(a_size, a_align);
			}

			[[nodiscard]] static inline void* AllocInHeap(MemoryHeap* a_heap, std::size_t a_size, const AllocInfo& a_info)
			{
				return a_heap->Alloc(a_size, std::addressof(a_info));
			}

			[[nodiscard]] static inline void* AllocInHeap(MemoryHeap* a_heap, std::size_t a_size, std::size_t a_align, const AllocInfo& a_info)
			{
				return a_heap->Alloc(a_size, a_align, std::addressof(a_info));
			}

			[[nodiscard]] static inline void* Realloc(void* a_ptr, std::size_t a_newSize)
			{
				return GetGlobalHeap()->Realloc(a_ptr, a_newSize);
			}

			static inline void Free(void* a_ptr)
			{
				GetGlobalHeap()->Free(a_ptr);
			}

			[[nodiscard]] static inline MemoryHeap* GetHeapByAddress(const void* a_ptr)
			{
				return GetGlobalHeap()->GetAllocHeap(a_ptr);
			}
		};
		static_assert(std::is_empty_v<Memory>);

		[[nodiscard]] inline void* malloc(std::size_t a_size)
		{
			return Memory::Alloc(a_size);
		}

		template <class T>
		[[nodiscard]] inline T* malloc()
		{
			return static_cast<T*>(malloc(sizeof(T)));
		}

		[[nodiscard]] inline void* aligned_alloc(std::size_t a_alignment, std::size_t a_size)
		{
			return Memory::Alloc(a_size, a_alignment);
		}

		template <class T>
		[[nodiscard]] inline T* aligned_alloc()
		{
			return static_cast<T*>(alignof(T), sizeof(T));
		}

		[[nodiscard]] inline void* calloc(std::size_t a_num, std::size_t a_size)
		{
			return malloc(a_num * a_size);
		}

		template <class T>
		[[nodiscard]] inline T* calloc(std::size_t a_num)
		{
			return static_cast<T*>(calloc(a_num, sizeof(T)));
		}

		[[nodiscard]] inline void* realloc(void* a_ptr, std::size_t a_newSize)
		{
			return Memory::Realloc(a_ptr, a_newSize);
		}

		[[nodiscard]] inline void free(void* a_ptr)
		{
			return Memory::Free(a_ptr);
		}
	}
}

#define SF_HEAP_REDEFINE_NEW(a_type)                                                                                    \
	[[nodiscard]] inline void* operator new(std::size_t a_count)                                                        \
	{                                                                                                                   \
		const auto mem = RE::Scaleform::malloc(a_count);                                                                \
		if (mem) {                                                                                                      \
			return mem;                                                                                                 \
		} else {                                                                                                        \
			stl::report_and_fail("out of memory"sv);                                                                    \
		}                                                                                                               \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] inline void* operator new[](std::size_t a_count)                                                      \
	{                                                                                                                   \
		const auto mem = RE::Scaleform::malloc(a_count);                                                                \
		if (mem) {                                                                                                      \
			return mem;                                                                                                 \
		} else {                                                                                                        \
			stl::report_and_fail("out of memory"sv);                                                                    \
		}                                                                                                               \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] inline void* operator new(std::size_t a_count, std::align_val_t)                                      \
	{                                                                                                                   \
		const auto mem = RE::Scaleform::aligned_alloc(alignof(a_type), a_count);                                        \
		if (mem) {                                                                                                      \
			return mem;                                                                                                 \
		} else {                                                                                                        \
			stl::report_and_fail("out of memory"sv);                                                                    \
		}                                                                                                               \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] inline void* operator new[](std::size_t a_count, std::align_val_t)                                    \
	{                                                                                                                   \
		const auto mem = RE::Scaleform::aligned_alloc(alignof(a_type), a_count);                                        \
		if (mem) {                                                                                                      \
			return mem;                                                                                                 \
		} else {                                                                                                        \
			stl::report_and_fail("out of memory"sv);                                                                    \
		}                                                                                                               \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] constexpr void* operator new(std::size_t, void* a_ptr) noexcept { return a_ptr; }                     \
	[[nodiscard]] constexpr void* operator new[](std::size_t, void* a_ptr) noexcept { return a_ptr; }                   \
	[[nodiscard]] constexpr void* operator new(std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; }   \
	[[nodiscard]] constexpr void* operator new[](std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; } \
                                                                                                                        \
	inline void operator delete(void* a_ptr) { RE::Scaleform::free(a_ptr); }                                            \
	inline void operator delete[](void* a_ptr) { RE::Scaleform::free(a_ptr); }                                          \
	inline void operator delete(void* a_ptr, std::align_val_t) { RE::Scaleform::free(a_ptr); }                          \
	inline void operator delete[](void* a_ptr, std::align_val_t) { RE::Scaleform::free(a_ptr); }                        \
	inline void operator delete(void* a_ptr, std::size_t) { RE::Scaleform::free(a_ptr); }                               \
	inline void operator delete[](void* a_ptr, std::size_t) { RE::Scaleform::free(a_ptr); }                             \
	inline void operator delete(void* a_ptr, std::size_t, std::align_val_t) { RE::Scaleform::free(a_ptr); }             \
	inline void operator delete[](void* a_ptr, std::size_t, std::align_val_t) { RE::Scaleform::free(a_ptr); }

namespace RE
{
	namespace Scaleform
	{
		template <std::int32_t>
		class NewOverrideBase
		{
		public:
			SF_HEAP_REDEFINE_NEW(NewOverrideBase)
		};
		//static_assert(std::is_empty_v<NewOverrideBase<0>>);
	}
}
