#pragma once

#include "RE/Bethesda/BSTTuple.h"
#include "RE/Bethesda/CRC.h"
#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	// scatter table with chaining
	template <
		class Traits,
		std::uint32_t N,
		template <class, std::uint32_t> class Allocator,
		class Hash,
		class KeyEqual>
	struct BSTScatterTable
	{
	public:
		using traits_type = Traits;
		using key_type = typename traits_type::key_type;
		using mapped_type = typename traits_type::mapped_type;
		using value_type = typename traits_type::value_type;
		using size_type = std::uint32_t;
		using hasher = Hash;
		using key_equal = KeyEqual;

		struct BSTScatterTableEntry
		{
		public:
			BSTScatterTableEntry() = default;

			BSTScatterTableEntry(const BSTScatterTableEntry& a_rhs) :
				value(a_rhs.value),
				next(a_rhs.next)
			{}

			BSTScatterTableEntry(BSTScatterTableEntry&& a_rhs) noexcept :
				value(std::exchange(a_rhs.value, nullptr)),
				next(a_rhs.next)
			{}

			BSTScatterTableEntry& operator=(const BSTScatterTableEntry& a_rhs)
			{
				if (this != std::addressof(a_rhs)) {
					value = a_rhs.value;
					next = a_rhs.next;
				}
				return *this;
			}

			BSTScatterTableEntry& operator=(BSTScatterTableEntry&& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					value = std::move(a_rhs.value);
					next = std::exchange(a_rhs.next, nullptr);
				}
				return *this;
			}

			value_type value{};                     // 00
			BSTScatterTableEntry* next{ nullptr };  // ??
		};

		using entry_type = BSTScatterTableEntry;
		using allocator_type = Allocator<entry_type, N>;

		template <class U>
		class iterator_base :
			public boost::iterators::iterator_facade<
				iterator_base<U>,
				U,
				std::forward_iterator_tag>
		{
		private:
			using super =
				boost::iterators::iterator_facade<
					iterator_base<U>,
					U,
					std::forward_iterator_tag>;

		public:
			using difference_type = typename super::difference_type;
			using value_type = typename super::value_type;
			using pointer = typename super::pointer;
			using reference = typename super::reference;
			using iterator_category = typename super::iterator_category;

			iterator_base() noexcept = default;
			iterator_base(const iterator_base&) noexcept = default;
			iterator_base(iterator_base&&) noexcept = default;

			template <class V>  // NOLINTNEXTLINE(google-explicit-constructor)
			iterator_base(iterator_base<V> a_rhs) noexcept :
				_cur(a_rhs._cur),
				_end(a_rhs._end)
			{}

			~iterator_base() noexcept = default;

			iterator_base& operator=(const iterator_base&) noexcept = default;
			iterator_base& operator=(iterator_base&&) noexcept = default;

			template <class V>
			iterator_base& operator=(iterator_base<V> a_rhs)
			{
				_cur = a_rhs._cur;
				_end = a_rhs._end;
				return *this;
			}

		protected:
			friend class boost::iterator_core_access;

			template <class, std::uint32_t, template <class, std::uint32_t> class, class, class>
			friend struct BSTScatterTable;

			iterator_base(entry_type* a_at, entry_type* a_end) noexcept :
				_cur(a_at),
				_end(a_end)
			{
				if (!good()) {
					increment();
				}
			}

			[[nodiscard]] reference dereference() const noexcept
			{
				assert(_cur);
				return _cur->value;
			}

			template <class V>
			[[nodiscard]] bool equal(const iterator_base<V>& a_rhs) const noexcept
			{
				assert(_end == a_rhs._end);
				return _cur == a_rhs._cur;
			}

			void increment() noexcept
			{
				assert(_cur && _cur != _end);
				do {
					++_cur;
				} while (!good());
			}

		private:
			template <class>
			friend class iterator_base;

			[[nodiscard]] bool good() const noexcept { return _cur == _end || _cur->next; }

			entry_type* _cur{ nullptr };
			entry_type* _end{ nullptr };
		};

		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		BSTScatterTable() = default;

		F4_HEAP_REDEFINE_NEW(BSTScatterTable);

		[[nodiscard]] iterator begin() noexcept { return get_entries() ? make_iterator(get_entries()) : iterator{}; }
		[[nodiscard]] const_iterator begin() const noexcept { return get_entries() ? make_iterator(get_entries()) : const_iterator{}; }
		[[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] iterator end() noexcept { return get_entries() ? make_iterator(get_entries() + _capacity) : iterator{}; }
		[[nodiscard]] const_iterator end() const noexcept { return get_entries() ? make_iterator(get_entries() + _capacity) : const_iterator{}; }
		[[nodiscard]] const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] bool empty() const noexcept { return !get_entries() || _freeCount == 0; }

		[[nodiscard]] size_type size() const noexcept { return _capacity - _freeCount; }

		[[nodiscard]] size_type max_size() const noexcept { return _allocator.max_size(); }

		std::pair<iterator, bool> insert(const value_type& a_value) { return insert_impl(false, a_value); }
		std::pair<iterator, bool> insert(value_type&& a_value) { return insert_impl(false, std::move(a_value)); }

		std::pair<iterator, bool> insert_or_assign(const value_type& a_value) { return insert_impl(true, a_value); }
		std::pair<iterator, bool> insert_or_assign(value_type&& a_value) { return insert_impl(true, std::move(a_value)); }

		size_type erase(const key_type& a_key)
		{
			if (!get_entries()) {  // no entries
				return 0;
			}

			const auto entry = calc_pos(a_key);
			if (!entry->next) {  // key not in table
				return 0;
			}

			entry_type* tail = nullptr;
			while (!comp_key(get_key(entry->value), a_key)) {  // find key in table
				tail = entry;
				entry = entry->next;
				if (entry == _sentinel) {
					return 0;
				}
			}

			if (entry->next == _sentinel) {  // if no chain
				if (tail) {
					tail->next = const_cast<entry_type*>(_sentinel);
				}
				stl::destroy_at(std::addressof(entry->value));
				entry->next = nullptr;
			} else {  // else move next entry into current
				stl::construct_at(entry, std::move(*entry->next));
			}

			++_freeCount;
			return 1;
		}

		[[nodiscard]] iterator find(const key_type& a_key)
		{
			const auto entry = find_impl(a_key);
			return entry ? make_iterator(entry) : end();
		}

		[[nodiscard]] const_iterator find(const key_type& a_key) const
		{
			const auto entry = find_impl(a_key);
			return entry ? make_iterator(entry) : end();
		}

		// TODO: replace with <bit> std::bit_ceil
		void reserve(size_type a_count)
		{
			if (a_count <= _capacity) {
				return;
			}

			constexpr auto top = static_cast<std::uint32_t>(1) << 31;
			std::uint32_t leftShifts = 0;
			while ((a_count & top) == 0) {
				a_count <<= 1;
				++leftShifts;
			}

			const auto bitPos = 31 - leftShifts;
			auto newCount = static_cast<std::uint32_t>(1) << bitPos;
			if (newCount < a_count) {
				if (bitPos == 31) {
					stl::report_and_fail("reserve failed"sv);
				} else {
					newCount <<= 1;
				}
			}

			grow(newCount);
		}

		[[nodiscard]] hasher hash_function() const { return {}; }

		[[nodiscard]] key_equal key_eq() const { return {}; }

	private:
		[[nodiscard]] entry_type* find_impl(const key_type& a_key) const
		{
			if (!get_entries()) {
				return nullptr;
			}

			auto probe = calc_pos(a_key);  // try ideal pos
			if (!probe->next) {
				return nullptr;  // nothing there
			}

			do {
				if (comp_key(get_key(probe->value), a_key)) {
					return probe;
				} else {
					probe = probe->next;
				}
			} while (probe != _sentinel);  // follow chain

			return nullptr;
		}

		template <class Arg>
		[[nodiscard]] std::pair<iterator, bool> insert_impl(bool a_overwrite, Arg&& a_value)
		{
			if (!get_entries() || !_freeCount) {
				if (!grow()) {
					return { end(), false };
				}
			}

			const auto idealEntry = calc_pos(get_key(a_value));
			if (!idealEntry->next) {  // if slot empty
				stl::construct_at(std::addressof(idealEntry->value), std::forward<Arg>(a_value));
				idealEntry->next = const_cast<entry_type*>(_sentinel);
				--_freeCount;
				return { make_iterator(idealEntry), true };
			}

			for (auto iter = idealEntry; iter != _sentinel; iter = iter->next) {
				if (comp_key(get_key(iter->value), get_key(a_value))) {  // if entry already in table
					if (a_overwrite) {
						iter->value = std::forward<Arg>(a_value);
					}
					return { make_iterator(iter), false };
				}
			}

			const auto freeEntry = get_free_entry();

			auto takenIdealEntry = calc_pos(get_key(idealEntry->value));
			if (takenIdealEntry == idealEntry) {  // if entry occupying our slot would've hashed here anyway
				freeEntry->next = idealEntry->next;
				idealEntry->next = freeEntry;
				stl::construct_at(std::addressof(freeEntry->value), std::forward<Arg>(a_value));
				return { make_iterator(freeEntry), true };
			}

			while (takenIdealEntry->next != idealEntry) {  // find entry that links here
				takenIdealEntry = takenIdealEntry->next;
			}

			// move taken slot out, so we can move in
			stl::construct_at(std::addressof(freeEntry->value), std::move(idealEntry->value));
			freeEntry->next = idealEntry->next;
			takenIdealEntry->next = freeEntry;
			idealEntry->value = std::forward<Arg>(a_value);
			idealEntry->next = const_cast<entry_type*>(_sentinel);
			return { make_iterator(idealEntry), true };
		}

		[[nodiscard]] iterator make_iterator(entry_type* a_entry) noexcept
		{
			assert(get_entries() != nullptr);
			return { a_entry, get_entries() + _capacity };
		}

		[[nodiscard]] const_iterator make_iterator(entry_type* a_entry) const noexcept
		{
			assert(get_entries() != nullptr);
			return { a_entry, get_entries() + _capacity };
		}

		[[nodiscard]] std::uint32_t calc_hash(const key_type& a_key) const { return hash_function()(a_key); }

		[[nodiscard]] std::uint32_t calc_idx(const key_type& a_key) const
		{
			// capacity is always a factor of 2, so this is a faster modulo
			return calc_hash(a_key) & (_capacity - 1);
		}

		[[nodiscard]] entry_type* calc_pos(const key_type& a_key) const { return const_cast<entry_type*>(get_entries() + calc_idx(a_key)); }

		// assumes not empty
		[[nodiscard]] not_null<entry_type*> get_free_entry() noexcept
		{
			assert(!empty());
			entry_type* entry = nullptr;
			do {
				_freeIdx = (_capacity - 1) & (_freeIdx - 1);
				entry = get_entries() + _freeIdx;
			} while (entry->next);

			--_freeCount;
			return entry;
		}

		[[nodiscard]] bool comp_key(const key_type& a_lhs, const key_type& a_rhs) const { return key_eq()(a_lhs, a_rhs); }

		bool grow()
		{
			if (_capacity == (std::uint32_t)1 << 31) {
				return false;
			}

			std::uint32_t newCapacity = _capacity ? _capacity << 1 : min_size();
			return grow(newCapacity);
		}

		bool grow(std::uint32_t a_newCapacity)
		{
			const auto oldEntries = get_entries();
			auto iter = begin();
			const auto last = end();

			const auto newEntries = allocate(a_newCapacity);
			if (!newEntries) {
				return false;
			} else if (newEntries == oldEntries) {
				_capacity = a_newCapacity;
				return true;
			} else {
				_capacity = a_newCapacity;
				_freeCount = a_newCapacity;
				_freeIdx = a_newCapacity;
				set_entries(newEntries);

				while (iter != last) {
					insert(std::move(*iter));
					++iter;
				}

				deallocate(oldEntries);
				return true;
			}
		}

		[[nodiscard]] const key_type& get_key(const value_type& a_value) const
		{
			traits_type traits{};
			return traits(a_value);
		}

		[[nodiscard]] entry_type* allocate(std::size_t a_num) { return _allocator.allocate(a_num); }

		void deallocate(entry_type* a_ptr) { _allocator.deallocate(a_ptr); }

		[[nodiscard]] entry_type* get_entries() const noexcept { return _allocator.get_entries(); }

		void set_entries(entry_type* a_entries) noexcept { _allocator.set_entries(a_entries); }

		[[nodiscard]] size_type min_size() const noexcept { return _allocator.min_size(); }

		static constexpr std::uint8_t SENTINEL[] = { (std::uint8_t)0xDE, (std::uint8_t)0xAD, (std::uint8_t)0xBE, (std::uint8_t)0xEF };

		// members
		std::uint64_t _pad00{ 0 };                                                     // 00
		std::uint32_t _pad08{ 0 };                                                     // 08
		std::uint32_t _capacity{ 0 };                                                  // 0C - this must be 2^n, or else terrible things will happen
		std::uint32_t _freeCount{ 0 };                                                 // 10
		std::uint32_t _freeIdx{ 0 };                                                   // 14
		const entry_type* _sentinel{ reinterpret_cast<const entry_type*>(SENTINEL) };  // 18
		allocator_type _allocator;                                                     // 20
	};

	template <class Key, class T>
	struct BSTScatterTableTraits
	{
	public:
		using key_type = Key;
		using mapped_type = T;
		using value_type = BSTTuple<const Key, T>;

		[[nodiscard]] const key_type& operator()(const value_type& a_value) const noexcept
		{
			return a_value.first;
		}
	};

	template <class T, std::uint32_t N = 8>
	struct BSTScatterTableHeapAllocator
	{
	public:
		using entry_type = T;
		using size_type = std::uint32_t;

		BSTScatterTableHeapAllocator() noexcept = default;

		[[nodiscard]] entry_type* allocate(std::size_t a_num)
		{
			auto size = a_num * sizeof(entry_type);
			auto mem = malloc<entry_type>(size);
			std::memset(mem, 0, size);
			return mem;
		}

		void deallocate(entry_type* a_ptr) { free(a_ptr); }

		[[nodiscard]] entry_type* get_entries() const noexcept { return _entries; }

		void set_entries(entry_type* a_entries) noexcept { _entries = a_entries; }

		[[nodiscard]] size_type min_size() const noexcept { return static_cast<size_type>(1) << 3; }

		[[nodiscard]] size_type max_size() const noexcept { return static_cast<size_type>(1) << 31; }

	private:
		// members
		std::uint64_t _pad00{ 0 };        // 00 (20)
		entry_type* _entries{ nullptr };  // 08 (28)
	};
	static_assert(sizeof(BSTScatterTableHeapAllocator<void*, 8>) == 0x10);

	template <
		class Key,
		class T,
		class Hash = BSCRC32<Key>,
		class KeyEqual = std::equal_to<Key>>
	using BSTHashMap =
		BSTScatterTable<
			BSTScatterTableTraits<Key, T>,
			8,
			BSTScatterTableHeapAllocator,
			Hash,
			KeyEqual>;

	template <class Key>
	struct BSTSetTraits
	{
	public:
		using key_type = Key;
		using mapped_type = void;
		using value_type = Key;

		[[nodiscard]] const key_type& operator()(const value_type& a_value) const noexcept
		{
			return a_value;
		}
	};

	template <
		class Key,
		class Hash = BSCRC32<Key>,
		class KeyEqual = std::equal_to<Key>>
	using BSTSet =
		BSTScatterTable<
			BSTSetTraits<Key>,
			8,
			BSTScatterTableHeapAllocator,
			Hash,
			KeyEqual>;

	struct BSTStaticHashMapBase
	{
	public:
		template <class T, std::uint32_t N>
		struct Allocator
		{
		public:
			using entry_type = T;
			using size_type = std::uint32_t;

			Allocator() = default;

			[[nodiscard]] entry_type* allocate(std::size_t a_num) noexcept { return a_num <= N ? _data : 0; }

			void deallocate(entry_type* a_ptr) noexcept { return; }

			[[nodiscard]] entry_type* get_entries() const noexcept { return _entries; }

			void set_entries(entry_type* a_entries) noexcept { _entries = a_entries; }

			[[nodiscard]] size_type min_size() const noexcept { return 1; }

			[[nodiscard]] size_type max_size() const noexcept { return N; }

		private:
			// members
			entry_type _data[N]{};          // 00
			entry_type* _entries{ _data };  // ??
		};
	};

	template <
		class Key,
		class T,
		std::uint32_t N,
		class Hash = BSCRC32<Key>,
		class KeyEqual = std::equal_to<Key>>
	using BSTStaticHashMap =
		BSTScatterTable<
			BSTScatterTableTraits<Key, T>,
			N,
			BSTStaticHashMapBase::Allocator,
			Hash,
			KeyEqual>;

	template <class T, std::uint32_t N>
	class BSTScatterTableScrapAllocator
	{
	public:
		using entry_type = T;
		using size_type = std::uint32_t;

		BSTScatterTableScrapAllocator() = default;

		[[nodiscard]] entry_type* allocate(std::size_t a_num)
		{
			auto size = a_num * sizeof(entry_type);
			auto mem = static_cast<entry_type*>(_allocator->Allocate(size, 0x10));
			std::memset(mem, 0, size);
			return mem;
		}

		void deallocate(entry_type* a_ptr) { _allocator->Deallocate(a_ptr); }

		[[nodiscard]] entry_type* get_entries() const noexcept { return _entries; }

		void set_entries(entry_type* a_entries) noexcept { _entries = a_entries; }

		[[nodiscard]] size_type min_size() const noexcept { return static_cast<size_type>(1) << 3; }

		[[nodiscard]] size_type max_size() const noexcept { return static_cast<size_type>(1) << 31; }

	private:
		// members
		ScrapHeap* _allocator{ MemoryManager::GetSingleton().GetThreadScrapHeap() };  // 00
		entry_type* _entries{ nullptr };                                              // 08
	};

	template <
		class Key,
		class T,
		class Hash = BSCRC32<Key>,
		class KeyEqual = std::equal_to<Key>>
	using BSTScrapHashMap =
		BSTScatterTable<
			BSTScatterTableTraits<Key, T>,
			8,
			BSTScatterTableScrapAllocator,
			Hash,
			KeyEqual>;
}
