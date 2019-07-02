#pragma once

#include "RE/Scaleform/SysAlloc.h"
#include "RE/Scaleform/SysAllocBase_SingletonSupport.h"


namespace RE
{
	namespace Scaleform
	{
		class SysAllocMalloc : public SysAllocBase_SingletonSupport<SysAllocMalloc, SysAlloc>
		{
		public:
			inline static const void* RTTI = RTTI_Scaleform__SysAllocMalloc;


			SysAllocMalloc() = default;
			virtual ~SysAllocMalloc() = default;

			// override (SysAllocBase_SingletonSupport<SysAllocMalloc, SysAlloc>)
			virtual void*	Alloc(UPInt a_size, UPInt a_align) override;										// 03
			virtual void	Free(void* a_ptr, UPInt a_size, UPInt a_align) override;							// 04
			virtual void*	Realloc(void* a_oldPtr, UPInt a_oldSize, UPInt a_newSize, UPInt a_align) override;	// 05
		};
	}
}
