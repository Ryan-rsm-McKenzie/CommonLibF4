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

		template <class U>
		class iterator_base :
			public boost::stl_interfaces::iterator_interface<
				iterator_base<U>,
				std::bidirectional_iterator_tag,
				U>
		{
		private:
			using super =
				boost::stl_interfaces::iterator_interface<
					iterator_base<U>,
					std::bidirectional_iterator_tag,
					U>;

		public:
			using difference_type = typename super::difference_type;
			using value_type = typename super::value_type;
			using pointer = typename super::pointer;
			using reference = typename super::reference;
			using iterator_category = typename super::iterator_category;

			~iterator_base() noexcept = default;
			iterator_base() noexcept = default;
			iterator_base(const volatile iterator_base&) = delete;
			iterator_base& operator=(const volatile iterator_base&) = delete;

			template <class V>
			iterator_base(const iterator_base<V>& a_rhs)  //
				requires(std::convertible_to<typename iterator_base<V>::reference, reference>) :
				_pos(a_rhs._pos),
				_head(a_rhs._head),
				_tail(a_rhs._tail)
			{}

			template <class V>
			iterator_base& operator=(const iterator_base<V>& a_rhs)  //
				requires(std::convertible_to<typename iterator_base<V>::reference, reference>)
			{
				_pos = a_rhs._pos;
				_head = a_rhs._head;
				_tail = a_rhs._tail;
				return *this;
			}

			[[nodiscard]] reference operator*() const noexcept
			{
				assert(validate());
				return *_pos;
			}

			template <class V>
			[[nodiscard]] bool operator==(const iterator_base<V>& a_rhs) const noexcept
			{
				assert(_head == a_rhs._head);
				assert(_tail == a_rhs._tail);
				return _pos == a_rhs._pos;
			}

			using super::operator++;

			void operator++() noexcept
			{
				assert(validate());
				do {
					++_pos;
				} while (_pos < _tail && !slot_filled());
			}

			using super::operator--;

			void operator--() noexcept
			{
				assert(validate());
				do {
					--_pos;
				} while (_head <= _pos && !slot_filled());
			}

		private:
			friend iterator_base;
			friend NiTArray;

			explicit iterator_base(pointer a_pos, pointer a_head, pointer a_tail) noexcept :
				_pos(a_pos),
				_head(a_head),
				_tail(a_tail)
			{}

			[[nodiscard]] bool validate() const noexcept
			{
				return _pos != nullptr &&
				       _head != nullptr &&
				       _tail != nullptr &&
				       _head <= _pos && _pos < _tail;
			}

			[[nodiscard]] bool slot_filled() const noexcept
			{
				assert(validate());
				return static_cast<bool>(*_pos);
			}

			pointer _pos{ nullptr };
			pointer _head{ nullptr };
			pointer _tail{ nullptr };
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		explicit NiTArray(std::uint32_t a_maxSize = 0, std::uint32_t a_growBy = 1) :
			_capacity(static_cast<std::uint16_t>(a_maxSize)),
			_growthSize(static_cast<std::uint16_t>(a_growBy))
		{
			if (capacity() > 0) {
				_data = allocator_type::allocate(capacity());
			}
		}

		virtual ~NiTArray() { allocator_type::deallocate(_data); }  // 00

		[[nodiscard]] reference operator[](size_type a_pos) noexcept
		{
			assert(a_pos < capacity());
			return _data[a_pos];
		}

		[[nodiscard]] const_reference operator[](size_type a_pos) const noexcept
		{
			assert(a_pos < capacity());
			return _data[a_pos];
		}

		[[nodiscard]] const_pointer data() const noexcept { return _data; }

		[[nodiscard]] iterator begin() noexcept { return make_iterator<iterator>(0); }
		[[nodiscard]] const_iterator begin() const noexcept { return make_iterator<const_iterator>(0); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return make_iterator<const_iterator>(0); }

		[[nodiscard]] iterator end() noexcept { return make_iterator<iterator>(_capacity); }
		[[nodiscard]] const_iterator end() const noexcept { return make_iterator<const_iterator>(_capacity); }
		[[nodiscard]] const_iterator cend() const noexcept { return make_iterator<const_iterator>(_capacity); }

		[[nodiscard]] bool empty() const noexcept { return size() == 0; }
		[[nodiscard]] size_type size() const noexcept { return _size; }
		[[nodiscard]] size_type capacity() const noexcept { return _capacity; }

	private:
		template <class T>
		[[nodiscard]] T make_iterator(size_type a_pos) const noexcept
		{
			return T(_data + a_pos, _data, _data + _capacity);
		}

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
