#pragma once

namespace RE
{
	class MemoryManager
	{
	public:
		[[nodiscard]] static inline MemoryManager& GetSingleton()
		{
			using func_t = decltype(&MemoryManager::GetSingleton);
			const REL::Relocation<func_t> func{ REL::ID(343176) };
			return func();
		}

		[[nodiscard]] inline void* Allocate(std::size_t a_size, std::uint32_t a_alignment, bool a_alignmentRequired)
		{
			using func_t = decltype(&MemoryManager::Allocate);
			const REL::Relocation<func_t> func{ REL::ID(652767) };
			return func(this, a_size, a_alignment, a_alignmentRequired);
		}

		inline void Deallocate(void* a_mem, bool a_alignmentRequired)
		{
			using func_t = decltype(&MemoryManager::Deallocate);
			const REL::Relocation<func_t> func{ REL::ID(1582181) };
			return func(this, a_mem, a_alignmentRequired);
		}

		[[nodiscard]] inline void* Reallocate(void* a_oldMem, std::size_t a_newSize, std::uint32_t a_alignment, bool a_alignmentRequired)
		{
			using func_t = decltype(&MemoryManager::Reallocate);
			const REL::Relocation<func_t> func{ REL::ID(1502917) };
			return func(this, a_oldMem, a_newSize, a_alignment, a_alignmentRequired);
		}

		// members
		std::uint8_t unk[0x480];  // 000
	};
	static_assert(sizeof(MemoryManager) == 0x480);

	[[nodiscard]] inline void* malloc(std::size_t a_size)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Allocate(a_size, 0, false);
	}

	template <class T>
	[[nodiscard]] inline T* malloc()
	{
		return static_cast<T*>(malloc(sizeof(T)));
	}

	[[nodiscard]] inline void* aligned_alloc(std::size_t a_alignment, std::size_t a_size)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Allocate(a_size, static_cast<std::uint32_t>(a_alignment), true);
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
		auto& mem = MemoryManager::GetSingleton();
		return mem.Reallocate(a_ptr, a_newSize, 0, false);
	}

	[[nodiscard]] inline void free(void* a_ptr)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Deallocate(a_ptr, false);
	}

	[[nodiscard]] inline void aligned_free(void* a_ptr)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Deallocate(a_ptr, true);
	}
}

#define F4_HEAP_REDEFINE_NEW(a_type)                                                                                    \
	[[nodiscard]] inline void* operator new(std::size_t a_count)                                                        \
	{                                                                                                                   \
		const auto mem = RE::malloc(a_count);                                                                           \
		if (mem) {                                                                                                      \
			return mem;                                                                                                 \
		} else {                                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] inline void* operator new[](std::size_t a_count)                                                      \
	{                                                                                                                   \
		const auto mem = RE::malloc(a_count);                                                                           \
		if (mem) {                                                                                                      \
			return mem;                                                                                                 \
		} else {                                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] inline void* operator new(std::size_t a_count, std::align_val_t)                                      \
	{                                                                                                                   \
		const auto mem = RE::aligned_alloc(alignof(a_type), a_count);                                                   \
		if (mem) {                                                                                                      \
			return mem;                                                                                                 \
		} else {                                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] inline void* operator new[](std::size_t a_count, std::align_val_t)                                    \
	{                                                                                                                   \
		const auto mem = RE::aligned_alloc(alignof(a_type), a_count);                                                   \
		if (mem) {                                                                                                      \
			return mem;                                                                                                 \
		} else {                                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] constexpr void* operator new(std::size_t, void* a_ptr) noexcept { return a_ptr; }                     \
	[[nodiscard]] constexpr void* operator new[](std::size_t, void* a_ptr) noexcept { return a_ptr; }                   \
	[[nodiscard]] constexpr void* operator new(std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; }   \
	[[nodiscard]] constexpr void* operator new[](std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; } \
                                                                                                                        \
	inline void operator delete(void* a_ptr) { RE::free(a_ptr); }                                                       \
	inline void operator delete[](void* a_ptr) { RE::free(a_ptr); }                                                     \
	inline void operator delete(void* a_ptr, std::align_val_t) { RE::aligned_free(a_ptr); }                             \
	inline void operator delete[](void* a_ptr, std::align_val_t) { RE::aligned_free(a_ptr); }                           \
	inline void operator delete(void* a_ptr, std::size_t) { RE::free(a_ptr); }                                          \
	inline void operator delete[](void* a_ptr, std::size_t) { RE::free(a_ptr); }                                        \
	inline void operator delete(void* a_ptr, std::size_t, std::align_val_t) { RE::aligned_free(a_ptr); }                \
	inline void operator delete[](void* a_ptr, std::size_t, std::align_val_t) { RE::aligned_free(a_ptr); }
