#pragma once

namespace RE::Scaleform
{
	namespace Heap
	{
		class MemVisitor;
		class SegVisitor;
	}

	class SysAlloc;
	class SysAllocBase;
	class SysAllocPaged;

	class __declspec(novtable) SysAllocBase
	{
	public:
		static constexpr auto RTTI{ RTTI::Scaleform__SysAllocBase };
		static constexpr auto VTABLE{ VTABLE::Scaleform__SysAllocBase };

		virtual ~SysAllocBase() = default;  // 00

		// add
		virtual bool InitHeapEngine([[maybe_unused]] const void* a_heapDesc) { return false; }  // 01
		virtual bool ShutdownHeapEngine() { return true; }                                      // 02
	};
	static_assert(sizeof(SysAllocBase) == 0x8);

	class __declspec(novtable) SysAlloc :
		public SysAllocBase  // 0
	{
	public:
		static constexpr auto RTTI{ RTTI::Scaleform__SysAlloc };
		static constexpr auto VTABLE{ VTABLE::Scaleform__SysAlloc };

		// override (SysAllocBase)
		bool InitHeapEngine(const void* a_heapDesc) override  // 01
		{
			using func_t = decltype(&SysAlloc::InitHeapEngine);
			REL::Relocation<func_t> func{ REL::ID(1047970) };
			return func(this, a_heapDesc);
		}

		bool ShutdownHeapEngine() override  // 02
		{
			using func_t = decltype(&SysAlloc::ShutdownHeapEngine);
			REL::Relocation<func_t> func{ REL::ID(1207169) };
			return func(this);
		}

		// add
		virtual void* Alloc(std::size_t a_size, std::size_t a_align) = 0;                                              // 03
		virtual void Free(void* a_ptr, std::size_t a_size, std::size_t a_align) = 0;                                   // 04
		virtual void* Realloc(void* a_oldPtr, std::size_t a_oldSize, std::size_t a_newSize, std::size_t a_align) = 0;  // 05
	};
	static_assert(sizeof(SysAlloc) == 0x8);

	class __declspec(novtable) SysAllocPaged :
		public SysAllocBase  // 0
	{
	public:
		static constexpr auto RTTI{ RTTI::Scaleform__SysAllocPaged };
		static constexpr auto VTABLE{ VTABLE::Scaleform__SysAllocPaged };

		struct Info
		{
		public:
			// members
			std::size_t minAlign;            // 00
			std::size_t maxAlign;            // 08
			std::size_t granularity;         // 10
			std::size_t sysDirectThreshold;  // 18
			std::size_t maxHeapGranularity;  // 20
			bool hasRealloc;                 // 28
		};
		static_assert(sizeof(Info) == 0x30);

		// add
		virtual void GetInfo(Info* a_info) const = 0;                                 // 03
		virtual void* Alloc(std::size_t a_size, std::size_t a_align) = 0;             // 04
		virtual bool Free(void* a_ptr, std::size_t a_size, std::size_t a_align) = 0;  // 05
		virtual bool ReallocInPlace(
			[[maybe_unused]] void* a_oldPtr,
			[[maybe_unused]] std::size_t a_oldSize,
			[[maybe_unused]] std::size_t a_newSize,
			[[maybe_unused]] std::size_t a_align) { return false; }  // 06
		virtual void* AllocSysDirect(
			[[maybe_unused]] std::size_t a_size,
			[[maybe_unused]] std::size_t a_alignment,
			[[maybe_unused]] std::size_t* a_actualSize,
			[[maybe_unused]] std::size_t* a_actualAlign) { return nullptr; }  // 07
		virtual bool FreeSysDirect(
			[[maybe_unused]] void* a_ptr,
			[[maybe_unused]] std::size_t a_size,
			[[maybe_unused]] std::size_t a_alignment) { return false; }                        // 08
		virtual std::size_t GetBase() const { return 0; }                                      // 09
		virtual std::size_t GetSize() const { return 0; }                                      // 0A
		virtual std::size_t GetFootprint() const { return 0; }                                 // 0B
		virtual std::size_t GetUsedSpace() const { return 0; }                                 // 0C
		virtual void VisitMem([[maybe_unused]] Heap::MemVisitor* a_visitor) const { return; }  // 0D
		virtual void VisitSegments(
			[[maybe_unused]] Heap::SegVisitor* a_visitor,
			[[maybe_unused]] std::size_t a_catSeg,
			[[maybe_unused]] std::size_t a_catUnused) const { return; }  // 0E
	};
	static_assert(sizeof(SysAllocPaged) == 0x8);
}
