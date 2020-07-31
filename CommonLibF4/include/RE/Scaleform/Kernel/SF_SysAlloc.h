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
		};
		static_assert(sizeof(SysAllocPaged) == 0x8);
	}
}
