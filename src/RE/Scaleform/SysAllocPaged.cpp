#include "RE/Scaleform/SysAllocPaged.h"


namespace RE
{
	namespace Scaleform
	{
		bool SysAllocPaged::ReallocInPlace(void* a_oldPtr, UPInt a_oldSize, UPInt a_newSize, UPInt a_align)	// 06
		{
			return false;
		}

		void* SysAllocPaged::AllocSysDirect(UPInt, UPInt, UPInt*, UPInt*)
		{
			return 0;
		}


		bool SysAllocPaged::FreeSysDirect(void*, UPInt, UPInt)
		{
			return false;
		}

		UPInt SysAllocPaged::GetBase() const
		{
			return 0;
		}


		UPInt SysAllocPaged::GetSize() const
		{
			return 0;
		}


		UPInt SysAllocPaged::GetFootprint() const
		{
			return 0;
		}


		UPInt SysAllocPaged::GetUsedSpace() const
		{
			return 0;
		}


		void SysAllocPaged::VisitMem(Heap::MemVisitor*) const
		{}


		void SysAllocPaged::VisitSegments(Heap::SegVisitor*, UPInt, UPInt) const
		{}
	}
}
