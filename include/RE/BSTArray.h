#pragma once

#include <cassert>

#include "RE/Memory.h"


namespace RE
{
	template <class T>
	class BSTArray
	{
	public:
		using value_type = T;
		using size_type = UInt32;
		using difference_type = std::ptrdiff_t;
		using reference = value_type &;
		using const_reference = const value_type &;
		using pointer = T *;
		using const_pointer = const T*;
		using iterator = T *;
		using const_iterator = const T*;


		reference operator[](size_type a_pos)
		{
			assert(a_pos < _size);
			return _data[a_pos];
		}


		const_reference operator[](size_type a_pos) const
		{
			assert(a_pos < _size);
			return _data[a_pos];
		}


		reference front()
		{
			return operator[](0);
		}


		const_reference front() const
		{
			return operator[](0);
		}


		reference back()
		{
			return operator[](_size - 1);
		}


		const_reference back() const
		{
			return operator[](_size - 1);
		}


		const T* data() const noexcept
		{
			return _data;
		}


		iterator begin() noexcept
		{
			return _data;
		}


		const_iterator begin() const noexcept
		{
			return _data;
		}


		const_iterator cbegin() const noexcept
		{
			return begin();
		}


		iterator end() noexcept
		{
			return _data + _size;
		}


		const_iterator end() const noexcept
		{
			return _data + _size;
		}


		const_iterator cend() const noexcept
		{
			return end();
		}


		[[nodiscard]] bool empty() const noexcept
		{
			return _size == 0;
		}


		size_type size() const noexcept
		{
			return _size;
		}


		size_type capacity() const noexcept
		{
			return _capacity;
		}


		// members
		T*		_data;		// 00
		UInt32	_capacity;	// 08
		UInt32	_pad0C;		// 0C
		UInt32	_size;		// 10
		UInt32	_pad14;		// 14
	};
	STATIC_ASSERT(sizeof(BSTArray<void*>) == 0x18);
}
