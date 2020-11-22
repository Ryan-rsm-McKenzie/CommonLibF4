#pragma once

#include "RE/NetImmerse/NiTCollection.h"

namespace RE
{
	template <class T, class Allocator>
	class NiTArray
	{
	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::uint16_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = value_type*;
		using const_iterator = const value_type*;

		explicit NiTArray(std::uint32_t a_maxSize = 0, std::uint32_t a_growBy = 1) :
			_capacity(static_cast<std::uint16_t>(a_maxSize)),
			_growthSize(static_cast<std::uint16_t>(a_growBy))
		{
			if (capacity() > 0) {
				_data = allocator_type::allocate(capacity());
			}
		}

		virtual ~NiTArray() { allocator_type::deallocate(_data); }  // 00

		[[nodiscard]] reference operator[](size_type a_pos)
		{
			assert(a_pos < size());
			return _data[a_pos];
		}

		[[nodiscard]] const_reference operator[](size_type a_pos) const
		{
			assert(a_pos < size());
			return _data[a_pos];
		}

		[[nodiscard]] reference front() { return operator[](0); }
		[[nodiscard]] const_reference front() const { return operator[](0); }

		[[nodiscard]] reference back() { return operator[](size() - 1); }
		[[nodiscard]] const_reference back() const { return operator[](size() - 1); }

		[[nodiscard]] const_pointer data() const noexcept { return _data; }

		[[nodiscard]] iterator begin() { return _data; }
		[[nodiscard]] const_iterator begin() const { return _data; }
		[[nodiscard]] const_iterator cbegin() const { return _data; }

		[[nodiscard]] iterator end() { return _data + _size; }
		[[nodiscard]] const_iterator end() const { return _data + _size; }
		[[nodiscard]] const_iterator cend() const noexcept { return _data + _size; }

		[[nodiscard]] bool empty() const noexcept { return size() == 0; }

		[[nodiscard]] size_type size() const noexcept { return _size; }

		[[nodiscard]] size_type capacity() const noexcept { return _capacity; }

	private:
		// members
		pointer _data{ nullptr };    // 08
		size_type _capacity{ 0 };    // 10
		size_type _freeIdx{ 0 };     // 12
		size_type _size{ 0 };        // 14
		size_type _growthSize{ 0 };  // 16
	};

	template <class T>
	using NiTObjectArray = NiTArray<T, NiTNewInterface<T>>;

	template <class T>
	using NiTPrimitiveArray = NiTArray<T, NiTMallocInterface<T>>;
}
