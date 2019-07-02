#pragma once

#include "RE/Scaleform/SysAllocBase.h"


namespace RE
{
	namespace Scaleform
	{
		class SysAlloc : public SysAllocBase
		{
		public:
			inline static const void* RTTI = RTTI_Scaleform__SysAlloc;


			SysAlloc() = default;
			virtual ~SysAlloc() = default;																// 00

			// override (SysAllocBase)
			virtual bool InitHeapEngine(const void* a_heapDesc) override;								// 01
			virtual bool ShutdownHeapEngine() override;													// 02

			// add
			virtual void* Alloc(UPInt a_size, UPInt a_align) = 0;										// 03
			virtual void  Free(void* a_ptr, UPInt a_size, UPInt a_align) = 0;							// 04
			virtual void* Realloc(void* a_oldPtr, UPInt a_oldSize, UPInt a_newSize, UPInt a_align) = 0;	// 05
		};
		STATIC_ASSERT(sizeof(SysAlloc) == 0x8);
	}
}
