#pragma once

namespace RE
{
	struct hkContainerHeapAllocator;

	template <class T>
	class hkArrayBase
	{
	public:
		using size_type = std::int32_t;
		using value_type = T;
		using pointer = value_type*;

	private:
		pointer _data;                // 00
		size_type _size;              // 08
		size_type _capacityAndFlags;  // 0C
	};

	template <class T, class Allocator = hkContainerHeapAllocator>
	class hkArray :
		public hkArrayBase<T>  // 00
	{
	public:
	};

	template <class T, std::uint32_t N, class Allocator = hkContainerHeapAllocator>
	class hkInplaceArray :
		public hkArray<T, Allocator>  // 00
	{
	public:
		using value_type = T;

	private:
		value_type _buffer[N];  // 10
	};

	template <class T, std::uint32_t N, class Allocator = hkContainerHeapAllocator>
	class hkInplaceArrayAligned16
	{
	public:
		using value_type = T;

	private:
		std::int32_t _padding;                                    // 10
		alignas(0x10) std::byte _buffer[N * sizeof(value_type)];  // 20
	};
}
