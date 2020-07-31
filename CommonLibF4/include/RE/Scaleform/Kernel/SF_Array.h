#pragma once

#include "RE/Scaleform/Kernel/SF_Allocator.h"

namespace RE
{
	namespace Scaleform
	{
		struct ArrayDefaultPolicy;

		struct ArrayDefaultPolicy
		{
		public:
			~ArrayDefaultPolicy() noexcept {}  // intentional

			// members
			std::size_t capacity;  // 0
		};
		static_assert(sizeof(ArrayDefaultPolicy) == 0x8);

		template <std::int32_t = 0, std::int32_t = 4, bool = false>
		struct ArrayConstPolicy
		{
		public:
			~ArrayConstPolicy() noexcept {}	 // intentional

			// members
			std::size_t capacity;  // 0
		};
		static_assert(sizeof(ArrayConstPolicy<>) == 0x8);

		template <class T, class Allocator, class SizePolicy>
		struct ArrayDataBase
		{
		public:
			T* data;			// 00
			std::size_t size;	// 08
			SizePolicy policy;	// 10
		};

		template <class T, class Allocator, class SizePolicy>
		struct ArrayData :
			public ArrayDataBase<T, Allocator, SizePolicy>	// 0
		{
		public:
		};

		template <class ArrayData>
		class ArrayBase
		{
		public:
			ArrayData data;	 // 0
		};

		template <class T, std::int32_t SID = 2, class SizePolicy = ArrayDefaultPolicy>
		class Array :
			public ArrayBase<ArrayData<T, AllocatorGH<T, SID>, SizePolicy>>	 // 0
		{
		public:
		};
	}
}
