#pragma once

#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	class ScrapHeap;

	class BSTArrayHeapAllocator
	{
	public:
		using size_type = std::uint32_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::true_type;

		BSTArrayHeapAllocator() noexcept = default;
		BSTArrayHeapAllocator(const BSTArrayHeapAllocator&) = delete;

		BSTArrayHeapAllocator(BSTArrayHeapAllocator&& a_rhs) noexcept :
			_data{ std::exchange(a_rhs._data, nullptr) },
			_capacity{ std::exchange(a_rhs._capacity, 0) }
		{}

		~BSTArrayHeapAllocator() noexcept = default;

		BSTArrayHeapAllocator& operator=(const BSTArrayHeapAllocator&) = delete;

		BSTArrayHeapAllocator& operator=(BSTArrayHeapAllocator&& a_rhs) noexcept
		{
			if (this != std::addressof(a_rhs)) {
				_data = std::exchange(a_rhs._data, nullptr);
				_capacity = std::exchange(a_rhs._capacity, 0);
			}
			return *this;
		}

		[[nodiscard]] void* allocate(uint32_t a_bytes) { return malloc(a_bytes); }
		void deallocate(void* a_ptr) { free(a_ptr); }

		[[nodiscard]] void* data() noexcept { return _data; }
		[[nodiscard]] const void* data() const noexcept { return _data; }
		void set_data(void* a_data) noexcept { _data = a_data; }

		[[nodiscard]] size_type capacity() const noexcept { return _capacity; }
		void set_capacity(size_type a_capacity, size_type) noexcept { _capacity = a_capacity; }

	private:
		// members
		void* _data{ nullptr };    // 00
		size_type _capacity{ 0 };  // 08
	};

	template <std::uint32_t N>
	struct BSTAlignedHeapArrayAllocator
	{
	public:
		class Allocator
		{
		public:
			using size_type = std::uint32_t;
			using difference_type = std::ptrdiff_t;
			using propagate_on_container_move_assignment = std::true_type;

			Allocator() noexcept = default;
			Allocator(const Allocator&) = delete;

			Allocator(Allocator&& a_rhs) noexcept :
				_data{ std::exchange(a_rhs._data, nullptr) },
				_capacity{ std::exchange(a_rhs._capacity, 0) }
			{}

			~Allocator() noexcept = default;

			Allocator& operator=(const Allocator&) = delete;

			Allocator& operator=(Allocator&& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					_data = std::exchange(a_rhs._data, nullptr);
					_capacity = std::exchange(a_rhs._capacity, 0);
				}
				return *this;
			}

			[[nodiscard]] void* allocate(uint32_t a_bytes) { return aligned_alloc(N, a_bytes); }
			void deallocate(void* a_ptr) { aligned_free(a_ptr); }

			[[nodiscard]] void* data() noexcept { return _data; }
			[[nodiscard]] const void* data() const noexcept { return _data; }
			void set_data(void* a_data) noexcept { _data = a_data; }

			[[nodiscard]] size_type capacity() const noexcept { return _capacity; }
			void set_capacity(size_type a_capacity, size_type) noexcept { _capacity = a_capacity; }

		private:
			void* _data{ nullptr };    // 00
			size_type _capacity{ 0 };  // 08
		};
	};

	extern template class BSTAlignedHeapArrayAllocator<0x10>::Allocator;

	template <std::uint32_t N>
	class BSTSmallArrayHeapAllocator
	{
	public:
		using size_type = std::uint32_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::false_type;

		BSTSmallArrayHeapAllocator() noexcept = default;
		BSTSmallArrayHeapAllocator(const BSTSmallArrayHeapAllocator&) = delete;
		BSTSmallArrayHeapAllocator(BSTSmallArrayHeapAllocator&&) = delete;

		~BSTSmallArrayHeapAllocator() noexcept = default;

		BSTSmallArrayHeapAllocator& operator=(const BSTSmallArrayHeapAllocator&) = delete;
		BSTSmallArrayHeapAllocator& operator=(BSTSmallArrayHeapAllocator&&) = delete;

		[[nodiscard]] void* allocate(uint32_t a_bytes)
		{
			if (a_bytes > N) {
				return malloc(a_bytes);
			} else {
				return _stack;
			}
		}

		void deallocate(void* a_ptr)
		{
			if (a_ptr != _stack) {
				free(a_ptr);
			}
		}

		[[nodiscard]] void* data() noexcept { return _local ? _stack : _heap; }
		[[nodiscard]] const void* data() const noexcept { return _local ? _stack : _heap; }

		void set_data(void* a_data) noexcept
		{
			if (a_data != _stack) {
				_heap = a_data;
			}
		}

		[[nodiscard]] size_type capacity() const noexcept { return _capacity; }

		void set_capacity(size_type a_capacity, size_type a_bytes) noexcept
		{
			_local = a_bytes <= N ? true : false;
			_capacity = a_capacity;
		}

	private:
		// members
		size_type _capacity: 31 { 0 };  // 00:00
		size_type _local: 1 { 0 };      // 00:31
		union
		{
			void* _heap{ nullptr };
			std::byte _stack[N];
		};  // 08
	};

	class BSScrapArrayAllocator
	{
	public:
		using size_type = std::uint32_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::false_type;

		BSScrapArrayAllocator() noexcept = default;
		BSScrapArrayAllocator(const BSScrapArrayAllocator&) = delete;
		BSScrapArrayAllocator(BSScrapArrayAllocator&&) = delete;

		~BSScrapArrayAllocator() noexcept = default;

		BSScrapArrayAllocator& operator=(const BSScrapArrayAllocator&) = delete;
		BSScrapArrayAllocator& operator=(BSScrapArrayAllocator&&) = delete;

		[[nodiscard]] void* allocate(uint32_t a_bytes)
		{
			if (!_allocator) {
				auto& heap = MemoryManager::GetSingleton();
				_allocator = heap.GetThreadScrapHeap();
			}

			if (!_allocator) {
				stl::report_and_fail("failed to get thread scrap heap"sv);
			}

			const auto mem = _allocator->Allocate(a_bytes, alignof(void*));
			if (!mem) {
				stl::report_and_fail("failed to handle allocation request"sv);
			} else {
				return mem;
			}
		}

		void deallocate(void* a_ptr)
		{
			if (_allocator) {
				_allocator->Deallocate(a_ptr);
			} else {
				stl::report_and_fail("failed to deallocate block"sv);
			}
		}

		[[nodiscard]] void* data() noexcept { return _data; }
		[[nodiscard]] const void* data() const noexcept { return _data; }
		void set_data(void* a_data) noexcept { _data = a_data; }

		[[nodiscard]] size_type capacity() const noexcept { return _capacity; }
		void set_capacity(size_type a_capacity, size_type) noexcept { _capacity = a_capacity; }

	private:
		// members
		ScrapHeap* _allocator{ nullptr };  // 00
		void* _data{ nullptr };            // 08
		size_type _capacity{ 0 };          // 10
	};

	template <
		class T,
		class Allocator = BSTArrayHeapAllocator>
	class BSTArray :
		public boost::stl_interfaces::sequence_container_interface<
			BSTArray<T, Allocator>,
			boost::stl_interfaces::element_layout::contiguous>
	{
	private:
		using super =
			boost::stl_interfaces::sequence_container_interface<
				BSTArray<T, Allocator>,
				boost::stl_interfaces::element_layout::contiguous>;

	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::uint32_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		using super::operator=;
		using super::operator[];

		using super::assign;
		using super::at;
		using super::back;
		using super::begin;
		using super::cbegin;
		using super::cend;
		using super::clear;
		using super::crbegin;
		using super::crend;
		using super::data;
		using super::empty;
		using super::end;
		using super::erase;
		using super::front;
		using super::insert;
		using super::push_back;
		using super::rbegin;
		using super::rend;
		using super::size;

		// 1)
		BSTArray() noexcept = default;

		// 3)
		explicit BSTArray(size_type a_count, const_reference a_value) { assign(a_count, a_value); }

		// 4)
		explicit BSTArray(size_type a_count) { resize(a_count); }

		// 5)
		template <class InputIt>
		BSTArray(InputIt a_first, InputIt a_last)  //
			requires(std::derived_from<typename std::iterator_traits<InputIt>::iterator_category, std::input_iterator_tag>)
		{
			assign(a_first, a_last);
		}

		// 6)
		BSTArray(const BSTArray& a_rhs) { assign(a_rhs.begin(), a_rhs.end()); }

		// 8)
		BSTArray(BSTArray&& a_rhs)
		{
			if constexpr (allocator_type::propagate_on_container_move_assignment::value) {
				_allocator = std::move(a_rhs._allocator);
				_size = std::exchange(a_rhs._size, 0);
			} else {
				reserve_exact(a_rhs.size());
				std::for_each(
					a_rhs.begin(),
					a_rhs.end(),
					[&](auto& a_elem) {
						emplace_back(std::move(a_elem));
					});
				a_rhs.clear();
			}
		}

		// 10)
		BSTArray(std::initializer_list<T> a_init) :
			BSTArray(a_init.begin(), a_init.end())
		{}

		~BSTArray()
		{
			if (capacity() > 0) {
				clear();
				_allocator.deallocate(data());
				_allocator.set_data(nullptr);
				_allocator.set_capacity(0, 0);
			}
		}

		// 1)
		BSTArray& operator=(const BSTArray& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				clear();
				assign(a_rhs.begin(), a_rhs.end());
			}
			return *this;
		}

		// 2)
		BSTArray& operator=(BSTArray&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				clear();
				if constexpr (allocator_type::propagate_on_container_move_assignment::value) {
					_allocator = std::move(a_rhs._allocator);
					_size = std::exchange(a_rhs._size, 0);
				} else {
					reserve_exact(a_rhs.size());
					std::for_each(
						a_rhs.begin(),
						a_rhs.end(),
						[&](auto& a_elem) {
							emplace_back(std::move(a_elem));
						});
					a_rhs.clear();
				}
			}
			return *this;
		}

		F4_HEAP_REDEFINE_NEW(BSTArray<T, Allocator>);

		[[nodiscard]] iterator begin() noexcept { return static_cast<pointer>(_allocator.data()); }
		[[nodiscard]] iterator end() noexcept { return begin() + _size; }

		[[nodiscard]] size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

		void reserve(size_type a_capacity)
		{
			if (a_capacity > capacity()) {
				reserve_exact(a_capacity);
			}
		}

		[[nodiscard]] size_type capacity() const noexcept { return _allocator.capacity(); }

		void shrink_to_fit() { reserve_exact(size()); }

		template <class ForwardIt>
		iterator insert(const_iterator a_pos, ForwardIt a_first, ForwardIt a_last)  //
			requires(std::derived_from<typename std::iterator_traits<ForwardIt>::iterator_category, std::forward_iterator_tag>)
		{
			const auto distance = static_cast<size_type>(std::distance(a_first, a_last));
			if (distance == 0) {
				return decay_iterator(a_pos);
			}

			const auto pos = static_cast<size_type>(std::distance(cbegin(), a_pos));
			resize(size() + distance);
			const auto iter = begin() + pos;
			std::move_backward(iter, iter + distance, end());
			std::copy(a_first, a_last, iter);
			return iter;
		}

		template <class... Args>
		iterator emplace(const_iterator a_pos, Args&&... a_args)  //
			requires(std::constructible_from<value_type, Args&&...>)
		{
			const auto pos = static_cast<size_type>(std::distance(cbegin(), a_pos));
			if (pos < size()) {
				emplace_back(std::move(back()));
				std::move_backward(begin() + pos, end() - 2, end() - 1);
			} else {
				reserve_auto(size() + 1);
				_size += 1;
			}

			std::construct_at(data() + pos, std::forward<Args>(a_args)...);
			return begin() + pos;
		}

		iterator erase(const_iterator a_first, const_iterator a_last)
		{
			const auto first = decay_iterator(a_first);
			const auto last = decay_iterator(a_last);
			const auto distance = static_cast<size_type>(std::distance(first, last));
			if (distance == 0) {
				return last;
			}

			assert(distance <= size());
			std::move(last, end(), first);
			std::destroy(end() - distance, end());
			_size -= distance;
			return end();
		}

		template <class... Args>
		reference emplace_back(Args&&... a_args)  //
			requires(std::constructible_from<value_type, Args&&...>)
		{
			return *emplace(end(), std::forward<Args>(a_args)...);
		}

		void pop_back() { erase(std::prev(end())); }

		void resize(size_type a_count) { resize_impl(a_count, nullptr); }
		void resize(size_type a_count, const value_type& a_value) { resize_impl(a_count, std::addressof(a_value)); }

		void swap(BSTArray& a_rhs)
		{
			auto tmp = std::move(*this);
			*this = std::move(a_rhs);
			a_rhs = std::move(tmp);
		}

	private:
		[[nodiscard]] iterator decay_iterator(const_iterator a_iter) noexcept
		{
			return const_cast<pointer>(std::addressof(*a_iter));
		}

		void reserve_auto(size_type a_capacity)
		{
			if (a_capacity > capacity()) {
				const auto grow = std::max(a_capacity, capacity() * 2);
				reserve_exact(grow);
			}
		}

		void reserve_exact(size_type a_capacity)
		{
			assert(a_capacity >= size());
			if (a_capacity == capacity()) {
				return;
			}

			const auto ndata =
				static_cast<pointer>(
					_allocator.allocate(a_capacity * sizeof(value_type)));
			const auto odata = data();
			if (ndata != odata) {
				std::uninitialized_move_n(odata, size(), ndata);
				std::destroy_n(odata, size());
				_allocator.deallocate(odata);
				_allocator.set_data(ndata);
				_allocator.set_capacity(a_capacity, a_capacity * sizeof(value_type));
			}
		}

		void resize_impl(size_type a_count, const value_type* a_value)
		{
			if (a_count < size()) {
				erase(begin() + a_count, end());
			} else if (a_count > size()) {
				reserve_auto(a_count);
				std::span<value_type> range{ data() + _size, a_count - _size };
				if (a_value) {
					std::for_each(
						range.begin(),
						range.end(),
						[=](auto& a_elem) {
							std::construct_at(std::addressof(a_elem), *a_value);
						});
				} else {
					std::uninitialized_default_construct(
						range.begin(),
						range.end());
				}
				_size = a_count;
			}
		}

		// members
		allocator_type _allocator;  // 00
		size_type _size{ 0 };       // ??
	};

	template <class T, std::uint32_t N = alignof(T)>
	using BSTAlignedArray = BSTArray<T, typename BSTAlignedHeapArrayAllocator<N>::Allocator>;

	template <class T, std::uint32_t N = 1>
	using BSTSmallArray = BSTArray<T, BSTSmallArrayHeapAllocator<sizeof(T) * N>>;

	template <class T>
	using BSScrapArray = BSTArray<T, BSScrapArrayAllocator>;

	namespace BSScript
	{
		template <class>
		struct script_traits;

		template <class T, class Allocator>
		struct script_traits<
			BSTArray<T, Allocator>>
			final
		{
			using is_array = std::true_type;
		};
	}

	template <class T>
	class BSStaticArray
	{
	public:
		using value_type = T;
		using size_type = std::uint32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;

		[[nodiscard]] reference operator[](size_type a_pos) noexcept
		{
			assert(a_pos < _size);
			return _data[a_pos];
		}

		[[nodiscard]] const_reference operator[](size_type a_pos) const noexcept
		{
			assert(a_pos < _size);
			return _data[a_pos];
		}

		[[nodiscard]] reference front() noexcept { return operator[](0); }
		[[nodiscard]] const_reference front() const noexcept { return operator[](0); }

		[[nodiscard]] reference back() noexcept { return operator[](size() - 1); }
		[[nodiscard]] const_reference back() const noexcept { return operator[](size() - 1); }

		[[nodiscard]] pointer data() noexcept { return _data; }
		[[nodiscard]] const_pointer data() const noexcept { return _data; }

		[[nodiscard]] iterator begin() noexcept { return empty() ? nullptr : data(); }
		[[nodiscard]] const_iterator begin() const noexcept { return empty() ? nullptr : data(); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] iterator end() noexcept { return empty() ? nullptr : data() + size(); }
		[[nodiscard]] const_iterator end() const noexcept { return empty() ? nullptr : data() + size(); }
		[[nodiscard]] const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] bool empty() const noexcept { return size() == 0; }

		[[nodiscard]] size_type size() const noexcept { return _size; }

	private:
		// members
		pointer _data{ nullptr };  // 00
		std::uint32_t _size{ 0 };  // 08
	};

	template <class T>
	class BSTSmallSharedArray
	{
	public:
		using value_type = T;
		using size_type = std::uint32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;

		~BSTSmallSharedArray() { stl::report_and_fail("unimplemented"sv); }

		[[nodiscard]] reference operator[](size_type a_pos) noexcept
		{
			assert(a_pos < _size);
			return data()[a_pos];
		}

		[[nodiscard]] const_reference operator[](size_type a_pos) const noexcept
		{
			assert(a_pos < _size);
			return data()[a_pos];
		}

		[[nodiscard]] pointer data() noexcept
		{
			return size() > 1 ? heap : std::addressof(local);
		}

		[[nodiscard]] const_pointer data() const noexcept
		{
			return size() > 1 ? heap : std::addressof(local);
		}

		[[nodiscard]] iterator begin() noexcept { return data(); }
		[[nodiscard]] const_iterator begin() const noexcept { return data(); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] iterator end() noexcept { return data() + size(); }
		[[nodiscard]] const_iterator end() const noexcept { return data() + size(); }
		[[nodiscard]] const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] bool empty() const noexcept { return size() != 0; }

		[[nodiscard]] size_type size() const noexcept { return _size; }

	private:
		// members
		std::uint32_t _size{ 0 };  // 00
		union
		{
			pointer heap{ 0 };
			value_type local;
		};  // 08
	};

	class BSDataBufferHeapAllocator;

	template <std::uint32_t N, class Allocator = BSDataBufferHeapAllocator>
	class BSTDataBuffer
	{
	public:
		class Block
		{
		public:
			// members
			std::uint32_t size: 24;  // 0:00
			std::uint32_t id: 8;     // 0:24
		};
		static_assert(sizeof(Block) == 0x4);

		[[nodiscard]] std::pair<const Block*, std::uint32_t> GetBlock(std::uint8_t a_id) const noexcept
		{
			if (!buffer) {
				return { nullptr, 0 };
			}

			std::uint32_t offset = 0;
			const auto blocks = reinterpret_cast<const Block*>(buffer + size);
			for (std::uint32_t i = 0; i < N && blocks[i].id != 0xFFu; ++i) {
				if (blocks[i].id == a_id) {
					return { blocks + i, offset };
				} else {
					offset += blocks[i].size;
				}
			}

			return { nullptr, 0 };
		}

		template <class T>
		[[nodiscard]] std::span<T> GetBuffer(std::uint8_t a_id) const noexcept
		{
			const auto [block, offset] = GetBlock(a_id);
			if (block) {
				return { reinterpret_cast<T*>(buffer + offset), block->size / sizeof(T) };
			} else {
				return {};
			}
		}

		// members
		std::byte* buffer;   // 00
		std::uint32_t size;  // 08
	};

	extern template class BSTDataBuffer<1>;
	extern template class BSTDataBuffer<2>;
}
