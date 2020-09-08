#pragma once

namespace RE
{
	namespace Scaleform
	{
		namespace Heap
		{
			class MemVisitor;
			class SegVisitor;
		}

		class SysAllocBase;
		class SysAllocPaged;

		class SysAllocBase
		{
		public:
			static constexpr auto RTTI{ RTTI::Scaleform__SysAllocBase };
			static constexpr auto VTABLE{ VTABLE::Scaleform__SysAllocBase };

			virtual ~SysAllocBase() = default;	// 00

			// add
			virtual bool InitHeapEngine([[maybe_unused]] const void* a_heapDesc) { return false; }	// 01
			virtual bool ShutdownHeapEngine() { return true; }										// 02
		};
		static_assert(sizeof(SysAllocBase) == 0x8);

		class SysAllocPaged :
			public SysAllocBase	 // 00
		{
		public:
			static constexpr auto RTTI{ RTTI::Scaleform__SysAllocPaged };
			static constexpr auto VTABLE{ VTABLE::Scaleform__SysAllocPaged };
		};
		static_assert(sizeof(SysAllocPaged) == 0x8);
	}
}
