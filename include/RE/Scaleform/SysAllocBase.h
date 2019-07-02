#pragma once


namespace RE
{
	namespace Scaleform
	{
		class SysAllocBase
		{
		public:
			inline static const void* RTTI = RTTI_Scaleform__SysAllocBase;


			virtual ~SysAllocBase() = default;						// 00

			// add
			virtual bool InitHeapEngine(const void* a_heapDesc);	// 01 - { return false; }
			virtual bool ShutdownHeapEngine();						// 02 - { return true; }

			FO_HEAP_REDEFINE_NEW();
		};
		STATIC_ASSERT(sizeof(SysAllocBase) == 0x8);
	}
}
