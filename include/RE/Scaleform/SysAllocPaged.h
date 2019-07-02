#pragma once

#include "RE/Scaleform/SysAllocBase.h"


namespace RE
{
	namespace Scaleform
	{
		namespace Heap
		{
			class MemVisitor;
			class SegVisitor;
		}


		class SysAllocPaged : public SysAllocBase
		{
		public:
			inline static const void* RTTI = RTTI_Scaleform__SysAllocPaged;


			struct Info
			{
				UPInt	minAlign;			// 00
				UPInt	maxAlign;			// 08
				UPInt	granularity;		// 10
				UPInt	sysDirectThreshold;	// 18
				UPInt	maxHeapGranularity;	// 20
				bool	hasRealloc;			// 28
				UInt8	pad29;				// 29
				UInt16	pad2A;				// 2A
				UInt32	pad2C;				// 2C
			};
			STATIC_ASSERT(sizeof(Info) == 0x30);


			SysAllocPaged() = default;
			virtual ~SysAllocPaged() = default;																	// 00

			// override (SysAllocBase)
			virtual bool	InitHeapEngine(const void* a_heapDesc) override;									// 02
			virtual bool	ShutdownHeapEngine() override;														// 03

			// add
			virtual void	GetInfo(Info* a_info) const = 0;													// 03
			virtual void*	Alloc(UPInt a_size, UPInt a_align) = 0;												// 04
			virtual bool	Free(void* a_ptr, UPInt a_size, UPInt a_align) = 0;									// 05
			virtual bool	ReallocInPlace(void* a_oldPtr, UPInt a_oldSize, UPInt a_newSize, UPInt a_align);	// 06 - { return false; }
			virtual void*	AllocSysDirect(UPInt, UPInt, UPInt*, UPInt*);										// 07 - { return 0; }
			virtual bool	FreeSysDirect(void*, UPInt, UPInt);													// 08 - { return false; }
			virtual UPInt	GetBase() const;																	// 09 - { return 0; }
			virtual UPInt	GetSize() const;																	// 0A - { return 0; }
			virtual UPInt	GetFootprint() const;																// 0B - { return 0; }
			virtual UPInt	GetUsedSpace() const;																// 0C - { return 0; }
			virtual void	VisitMem(Heap::MemVisitor*) const;													// 0D - { return; }
			virtual void	VisitSegments(Heap::SegVisitor*, UPInt, UPInt) const;								// 0E - { return; }
		};
		STATIC_ASSERT(sizeof(SysAllocPaged) == 0x8);
	}
}
