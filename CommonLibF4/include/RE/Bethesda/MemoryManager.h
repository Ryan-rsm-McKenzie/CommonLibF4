#pragma once

namespace RE
{
	namespace CompactingStore
	{
		class Store;
	}

	enum class MEM_CONTEXT : std::int32_t;

	class BSSmallBlockAllocator;

	struct HeapStats;
	struct MemoryStats;

	class __declspec(novtable) IMemoryStoreBase
	{
	public:
		static constexpr auto RTTI{ RTTI::IMemoryStoreBase };
		static constexpr auto VTABLE{ VTABLE::IMemoryStoreBase };

		virtual ~IMemoryStoreBase() = default;  // 00

		// add
		virtual std::size_t Size(void const* a_mem) const = 0;          // 01
		virtual void GetMemoryStats(MemoryStats* a_stats) = 0;          // 02
		virtual bool ContainsBlockImpl(const void* a_block) const = 0;  // 03
	};
	static_assert(sizeof(IMemoryStoreBase) == 0x8);

	class __declspec(novtable) IMemoryStore :
		public IMemoryStoreBase  // 0
	{
	public:
		static constexpr auto RTTI{ RTTI::IMemoryStore };
		static constexpr auto VTABLE{ VTABLE::IMemoryStore };

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~IMemoryStore() = default;  // 00

		// add
		virtual void* AllocateAlignImpl(std::size_t a_size, std::uint32_t a_alignment) = 0;                                                 // 04
		virtual void DeallocateAlignImpl(void*& a_block) = 0;                                                                               // 05
		virtual void* TryAllocateImpl([[maybe_unused]] std::size_t a_size, [[maybe_unused]] std::uint32_t a_alignment) { return nullptr; }  // 06
	};
	static_assert(sizeof(IMemoryStore) == 0x8);

	class __declspec(novtable) IMemoryHeap :
		public IMemoryStore  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::IMemoryHeap };
		static constexpr auto VTABLE{ VTABLE::IMemoryHeap };

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~IMemoryHeap() = default;

		// override (IMemoryStore)
		bool ContainsBlockImpl(const void* a_block) const override { return PointerInHeap(a_block); }                              // 03
		void* AllocateAlignImpl(std::size_t a_size, std::uint32_t a_alignment) override { return Allocate(a_size, a_alignment); }  // 04
		void DeallocateAlignImpl(void*& a_block) override { Deallocate(a_block, 0); }                                              // 05

		// add
		virtual const char* GetName() const = 0;                                               // 07
		virtual void* Allocate(std::size_t a_size, std::uint32_t a_alignment) = 0;             // 08
		virtual void Deallocate(void* a_mem, std::uint32_t) = 0;                               // 09
		virtual bool PointerInHeap(const void* a_pointer) const = 0;                           // 0A
		virtual std::size_t TotalSize(const void* a_pointer) const = 0;                        // 0B
		virtual void GetHeapStats(HeapStats* a_stats, bool a_fullBlockInfo) = 0;               // 0C
		virtual bool ShouldTrySmallBlockPools(std::size_t a_size, MEM_CONTEXT a_context) = 0;  // 0D
		virtual std::uint32_t GetPageSize() const = 0;                                         // 0E
	};
	static_assert(sizeof(IMemoryHeap) == 0x8);

	class __declspec(novtable) ScrapHeap :
		public IMemoryStore  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ScrapHeap };
		static constexpr auto VTABLE{ VTABLE::ScrapHeap };

		struct Block
		{
		public:
			// members
			std::size_t sizeFlags;  // 00
			Block* prev;            // 08
		};
		static_assert(sizeof(Block) == 0x10);

		struct FreeBlock :
			public Block  // 00
		{
		public:
			// members
			FreeBlock* left;   // 10
			FreeBlock* right;  // 18
		};
		static_assert(sizeof(FreeBlock) == 0x20);

		struct FreeTreeNode :
			public FreeBlock  // 00
		{
		public:
			// members
			FreeTreeNode** root;         // 20
			FreeTreeNode* leftNode;      // 28
			FreeTreeNode* rightNode;     // 30
			std::size_t parentAndBlack;  // 38
		};
		static_assert(sizeof(FreeTreeNode) == 0x40);

		// NOLINTNEXTLINE(modernize-use-equals-default)
		~ScrapHeap() override { WinAPI::VirtualFree(baseAddress, 0, (WinAPI::MEM_RELEASE)); }  // 00

		// override (IMemoryStore)
		std::size_t Size(void const* a_mem) const override { return *static_cast<const std::size_t*>(a_mem) & ~(std::size_t{ 3 } << 62); }  // 01
		void GetMemoryStats(MemoryStats*) override { return; }                                                                              // 02
		bool ContainsBlockImpl(const void* a_block) const override { return baseAddress <= a_block && a_block <= endAddress; }              // 03
		void* AllocateAlignImpl(std::size_t a_size, std::uint32_t a_alignment) override { return Allocate(a_size, a_alignment); }           // 04
		void DeallocateAlignImpl(void*& a_block) override { Deallocate(a_block), a_block = nullptr; }                                       // 05

		void* Allocate(std::size_t a_size, std::size_t a_alignment)
		{
			using func_t = decltype(&ScrapHeap::Allocate);
			REL::Relocation<func_t> func{ REL::ID(1085394) };
			return func(this, a_size, a_alignment);
		}

		void Deallocate(void* a_mem)
		{
			using func_t = decltype(&ScrapHeap::Deallocate);
			REL::Relocation<func_t> func{ REL::ID(923307) };
			return func(this, a_mem);
		}

		// members
		FreeBlock* smallBlocks[6]{ nullptr };     // 08
		FreeTreeNode* freeList{ nullptr };        // 38
		Block* lastBlock{ nullptr };              // 40
		std::byte* baseAddress{ nullptr };        // 48
		std::byte* endAddress{ nullptr };         // 50
		std::byte* commitEnd{ nullptr };          // 58
		std::size_t reserveSize;                  // 60
		std::size_t minCommit{ 1u << 17 };        // 68
		std::size_t totalAllocated{ 0 };          // 70
		std::uint32_t keepPagesRequest{ 0 };      // 78
		std::uint32_t totalFreeBlocks{ 0 };       // 7C
		std::uint32_t freeSmallBlocks{ 0 };       // 80
		std::uint32_t totalAllocatedBlocks{ 0 };  // 84
		std::uint32_t pmpBarrier{ 0 };            // 88
	};
	static_assert(sizeof(ScrapHeap) == 0x90);

	class MemoryManager
	{
	public:
		struct AutoScrapBuffer
		{
		public:
			AutoScrapBuffer() { Ctor(); }
			~AutoScrapBuffer() { Dtor(); }

			[[nodiscard]] void* GetPtr() const noexcept { return ptr; }

			// members
			void* ptr{ nullptr };  // 0

		private:
			AutoScrapBuffer* Ctor()
			{
				using func_t = decltype(&AutoScrapBuffer::Ctor);
				REL::Relocation<func_t> func{ REL::ID(1571567) };
				return func(this);
			}

			void Dtor()
			{
				using func_t = decltype(&AutoScrapBuffer::Dtor);
				REL::Relocation<func_t> func{ REL::ID(68625) };
				return func(this);
			}
		};
		static_assert(sizeof(AutoScrapBuffer) == 0x8);

		struct ThreadScrapHeap
		{
		public:
			// members
			ScrapHeap heap;                                              // 00
			ThreadScrapHeap* next{ nullptr };                            // 90
			std::uint32_t owningThread{ WinAPI::GetCurrentThreadID() };  // 98
		};
		static_assert(sizeof(ThreadScrapHeap) == 0xA0);

		[[nodiscard]] static MemoryManager& GetSingleton()
		{
			using func_t = decltype(&MemoryManager::GetSingleton);
			const REL::Relocation<func_t> func{ REL::ID(343176) };
			return func();
		}

		[[nodiscard]] void* Allocate(std::size_t a_size, std::uint32_t a_alignment, bool a_alignmentRequired)
		{
			using func_t = decltype(&MemoryManager::Allocate);
			const REL::Relocation<func_t> func{ REL::ID(652767) };
			return func(this, a_size, a_alignment, a_alignmentRequired);
		}

		void Deallocate(void* a_mem, bool a_alignmentRequired)
		{
			using func_t = decltype(&MemoryManager::Deallocate);
			const REL::Relocation<func_t> func{ REL::ID(1582181) };
			return func(this, a_mem, a_alignmentRequired);
		}

		[[nodiscard]] ScrapHeap* GetThreadScrapHeap()
		{
			using func_t = decltype(&MemoryManager::GetThreadScrapHeap);
			const REL::Relocation<func_t> func{ REL::ID(1495205) };
			return func(this);
		}

		[[nodiscard]] void* Reallocate(void* a_oldMem, std::size_t a_newSize, std::uint32_t a_alignment, bool a_alignmentRequired)
		{
			using func_t = decltype(&MemoryManager::Reallocate);
			const REL::Relocation<func_t> func{ REL::ID(1502917) };
			return func(this, a_oldMem, a_newSize, a_alignment, a_alignmentRequired);
		}

		void RegisterMemoryManager()
		{
			using func_t = decltype(&MemoryManager::RegisterMemoryManager);
			const REL::Relocation<func_t> func{ REL::ID(453212) };
			return func(this);
		}

		// members
		bool initialized{ false };                              // 000
		std::uint16_t numHeaps{ 0 };                            // 002
		std::uint16_t numPhysicalHeaps{ 0 };                    // 004
		IMemoryHeap** heaps{ nullptr };                         // 008
		bool* allowOtherContextAllocs{ nullptr };               // 010
		IMemoryHeap* heapsByContext[127]{ nullptr };            // 018
		ThreadScrapHeap* threadScrapHeap{ nullptr };            // 410
		IMemoryHeap** physicalHeaps{ nullptr };                 // 418
		IMemoryHeap* bigAllocHeap{ nullptr };                   // 420
		IMemoryHeap* emergencyHeap{ nullptr };                  // 428
		BSSmallBlockAllocator* smallBlockAllocator{ nullptr };  // 430
		CompactingStore::Store* compactingStore{ nullptr };     // 438
		IMemoryHeap* externalHavokAllocator{ nullptr };         // 440
		bool specialHeaps{ false };                             // 448
		bool allowPoolUse{ true };                              // 449
		std::uint32_t sysAllocBytes{ 0 };                       // 44C
		std::uint32_t mallocBytes{ 0 };                         // 450
		std::uint32_t alignmentForPools{ 4 };                   // 454
		std::uint32_t mainThreadMemoryProblemPassSignal{ 0 };   // 458
		std::size_t failedAllocationSize{ 0 };                  // 460
		std::uint32_t numMemoryProblemPassesRun{ 0 };           // 468
		std::size_t timeOfLastMemoryProblemPass{ 0 };           // 470
		IMemoryHeap* defaultHeap{ nullptr };                    // 478
	};
	static_assert(sizeof(MemoryManager) == 0x480);

	[[nodiscard]] inline void* malloc(std::size_t a_size)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Allocate(a_size, 0, false);
	}

	template <class T>
	[[nodiscard]] T* malloc()
	{
		return static_cast<T*>(malloc(sizeof(T)));
	}

	[[nodiscard]] inline void* aligned_alloc(std::size_t a_alignment, std::size_t a_size)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Allocate(a_size, static_cast<std::uint32_t>(a_alignment), true);
	}

	template <class T>
	[[nodiscard]] T* aligned_alloc()
	{
		return static_cast<T*>(aligned_alloc(alignof(T), sizeof(T)));
	}

	[[nodiscard]] inline void* calloc(std::size_t a_num, std::size_t a_size)
	{
		const auto ret = malloc(a_num * a_size);
		if (ret) {
			std::memset(ret, 0, a_num * a_size);
		}
		return ret;
	}

	template <class T>
	[[nodiscard]] T* calloc(std::size_t a_num)
	{
		return static_cast<T*>(calloc(a_num, sizeof(T)));
	}

	[[nodiscard]] inline void* realloc(void* a_ptr, std::size_t a_newSize)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Reallocate(a_ptr, a_newSize, 0, false);
	}

	[[nodiscard]] inline void* aligned_realloc(void* a_ptr, std::size_t a_alignment, std::size_t a_newSize)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Reallocate(a_ptr, a_newSize, static_cast<std::uint32_t>(a_alignment), true);
	}

	inline void free(void* a_ptr)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Deallocate(a_ptr, false);
	}

	inline void aligned_free(void* a_ptr)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Deallocate(a_ptr, true);
	}
}

#define F4_HEAP_REDEFINE_HELPER(...)                                                                          \
	[[nodiscard]] void* operator new(std::size_t a_count, std::align_val_t a_alignment)                       \
	{                                                                                                         \
		const auto mem = RE::aligned_alloc(static_cast<std::size_t>(a_alignment), a_count);                   \
		if (mem) {                                                                                            \
			return mem;                                                                                       \
		} else {                                                                                              \
			stl::report_and_fail("out of memory"sv);                                                          \
		}                                                                                                     \
	}                                                                                                         \
                                                                                                              \
	[[nodiscard]] void* operator new[](std::size_t a_count, std::align_val_t a_alignment)                     \
	{                                                                                                         \
		const auto mem = RE::aligned_alloc(static_cast<std::size_t>(a_alignment), a_count);                   \
		if (mem) {                                                                                            \
			return mem;                                                                                       \
		} else {                                                                                              \
			stl::report_and_fail("out of memory"sv);                                                          \
		}                                                                                                     \
	}                                                                                                         \
                                                                                                              \
	[[nodiscard]] void* operator new(std::size_t, void* a_ptr) noexcept { return a_ptr; }                     \
	[[nodiscard]] void* operator new[](std::size_t, void* a_ptr) noexcept { return a_ptr; }                   \
	[[nodiscard]] void* operator new(std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; }   \
	[[nodiscard]] void* operator new[](std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; } \
                                                                                                              \
	void operator delete(void*, void*) noexcept { return; }                                                   \
	void operator delete[](void*, void*) noexcept { return; }                                                 \
                                                                                                              \
	void operator delete(void* a_ptr, std::align_val_t) { RE::aligned_free(a_ptr); }                          \
	void operator delete[](void* a_ptr, std::align_val_t) { RE::aligned_free(a_ptr); }                        \
	void operator delete(void* a_ptr, std::size_t, std::align_val_t) { RE::aligned_free(a_ptr); }             \
	void operator delete[](void* a_ptr, std::size_t, std::align_val_t) { RE::aligned_free(a_ptr); }

#define F4_HEAP_REDEFINE_NEW(...)                                         \
	[[nodiscard]] void* operator new(std::size_t a_count)                 \
	{                                                                     \
		const auto mem = RE::malloc(a_count);                             \
		if (mem) {                                                        \
			return mem;                                                   \
		} else {                                                          \
			stl::report_and_fail("out of memory"sv);                      \
		}                                                                 \
	}                                                                     \
                                                                          \
	[[nodiscard]] void* operator new[](std::size_t a_count)               \
	{                                                                     \
		const auto mem = RE::malloc(a_count);                             \
		if (mem) {                                                        \
			return mem;                                                   \
		} else {                                                          \
			stl::report_and_fail("out of memory"sv);                      \
		}                                                                 \
	}                                                                     \
                                                                          \
	void operator delete(void* a_ptr) { RE::free(a_ptr); }                \
	void operator delete[](void* a_ptr) { RE::free(a_ptr); }              \
	void operator delete(void* a_ptr, std::size_t) { RE::free(a_ptr); }   \
	void operator delete[](void* a_ptr, std::size_t) { RE::free(a_ptr); } \
                                                                          \
	F4_HEAP_REDEFINE_HELPER(__VA_ARGS__)

#define F4_HEAP_REDEFINE_ALIGNED_NEW(...)                                         \
	[[nodiscard]] void* operator new(std::size_t a_count)                         \
	{                                                                             \
		const auto mem = RE::aligned_alloc(alignof(__VA_ARGS__), a_count);        \
		if (mem) {                                                                \
			return mem;                                                           \
		} else {                                                                  \
			stl::report_and_fail("out of memory"sv);                              \
		}                                                                         \
	}                                                                             \
                                                                                  \
	[[nodiscard]] void* operator new[](std::size_t a_count)                       \
	{                                                                             \
		const auto mem = RE::aligned_alloc(alignof(__VA_ARGS__), a_count);        \
		if (mem) {                                                                \
			return mem;                                                           \
		} else {                                                                  \
			stl::report_and_fail("out of memory"sv);                              \
		}                                                                         \
	}                                                                             \
                                                                                  \
	void operator delete(void* a_ptr) { RE::aligned_free(a_ptr); }                \
	void operator delete[](void* a_ptr) { RE::aligned_free(a_ptr); }              \
	void operator delete(void* a_ptr, std::size_t) { RE::aligned_free(a_ptr); }   \
	void operator delete[](void* a_ptr, std::size_t) { RE::aligned_free(a_ptr); } \
                                                                                  \
	F4_HEAP_REDEFINE_HELPER(__VA_ARGS__)
