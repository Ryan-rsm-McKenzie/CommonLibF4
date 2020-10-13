#pragma once

#include "RE/NetImmerse/NiTCollection.h"

namespace RE
{
	template <class T, class Allocator>
	class NiTLargeArray
	{
	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::uint32_t;
		using pointer = value_type*;

		virtual ~NiTLargeArray();

	private:
		pointer _data;        // 08
		size_type _capacity;  // 10
		size_type _freeIdx;   // 14
		size_type _size;      // 18
		size_type _growBy;    // 1C
	};

	template <class T>
	using NiTLargeObjectArray = NiTLargeArray<T, NiTNewInterface<T>>;

	template <class T>
	using NiTLargePrimitiveArray = NiTLargeArray<T, NiTMallocInterface<T>>;
}
