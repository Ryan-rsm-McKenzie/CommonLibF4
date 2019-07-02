#include "RE/Scaleform/SysAllocMalloc.h"

#include <cstring>


namespace RE
{
	namespace Scaleform
	{
		void* SysAllocMalloc::Alloc(UPInt a_size, UPInt a_align)
		{
			return aligned_alloc(a_align, a_size);
		}


		void SysAllocMalloc::Free(void* a_ptr, UPInt a_size, UPInt a_align)
		{
			if (a_ptr) {
				aligned_free(a_ptr);
			}
		}


		void* SysAllocMalloc::Realloc(void* a_oldPtr, UPInt a_oldSize, UPInt a_newSize, UPInt a_align)
		{
			if (a_newSize == a_oldSize) {
				return a_oldPtr;
			}

			auto newPtr = aligned_alloc(a_align, a_newSize);
			if (newPtr) {
				auto size = (a_oldSize < a_newSize) ? a_oldSize : a_newSize;
				std::memcpy(newPtr, a_oldPtr, size);
				if (a_oldPtr) {
					aligned_free(a_oldPtr);
				}
			}
			return newPtr;
		}
	}
}
