#pragma once

#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	// forward list
	template <class T>
	class BSSimpleList
	{
	public:
		using size_type = std::size_t;
		using difference_type = std::uint32_t;
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;

	private:
		struct node_type
		{
		public:
			F4_HEAP_REDEFINE_NEW(node_type);

			value_type value{};
			node_type* next{ nullptr };
		};

		template <class U>
		class iterator_base :
			public boost::stl_interfaces::iterator_interface<
				iterator_base<U>,
				std::forward_iterator_tag,
				U>
		{
		private:
			using super =
				boost::stl_interfaces::iterator_interface<
					iterator_base<U>,
					std::forward_iterator_tag,
					U>;

		public:
			using difference_type = typename super::difference_type;
			using value_type = typename super::value_type;
			using pointer = typename super::pointer;
			using reference = typename super::reference;
			using iterator_category = typename super::iterator_category;

			iterator_base() noexcept = default;
			iterator_base(const iterator_base&) noexcept = default;
			iterator_base(iterator_base&&) noexcept = default;

			template <
				class V,
				std::enable_if_t<
					std::is_convertible_v<
						typename iterator_base<V>::reference,
						reference>,
					int> = 0>
			iterator_base(iterator_base<V> a_rhs) noexcept :
				_proxy(a_rhs._proxy),
				_cur(a_rhs._cur)
			{}

			iterator_base& operator=(const iterator_base&) noexcept = default;
			iterator_base& operator=(iterator_base&&) noexcept = default;

			template <
				class V,
				std::enable_if_t<
					std::is_convertible_v<
						typename iterator_base<V>::reference,
						reference>,
					int> = 0>
			iterator_base& operator=(iterator_base<V> a_rhs) noexcept
			{
				_cur = a_rhs._cur;
				return *this;
			}

			[[nodiscard]] reference operator*() noexcept
			{
				assert(_cur && _cur != nullptr);
				return get()->value;
			}

			iterator_base& operator++() noexcept
			{
				if (_cur) {
					assert(_cur != nullptr);
					_cur = get()->next;
				} else {
					*this = _proxy->begin();
				}
				return *this;
			}

			using super::operator++;

			template <class V>
			[[nodiscard]] bool operator==(const iterator_base<V>& a_rhs) noexcept
			{
				assert(_proxy == a_rhs._proxy);
				return _cur == a_rhs._cur;
			}

			template <class V>
			[[nodiscard]] bool operator!=(const iterator_base<V>& a_rhs) noexcept
			{
				return !(*this == a_rhs);
			}

		protected:
			template <class>
			friend class BSSimpleList;

			iterator_base(BSSimpleList<T>* a_proxy, std::optional<node_type*> a_cur) noexcept :
				_proxy(a_proxy),
				_cur(a_cur)
			{}

			[[nodiscard]] node_type* get() const noexcept
			{
				assert(_cur);
				return _cur.value();
			}

			[[nodiscard]] auto make_mutable() const noexcept { return iterator_base<std::remove_const_t<value_type>>{ _proxy, _cur }; }

		private:
			BSSimpleList<T>* _proxy{ nullptr };
			std::optional<node_type*> _cur{ nullptr };
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		// 1)
		BSSimpleList() = default;

		// 4)
		explicit BSSimpleList(size_type a_count) { assign(a_count, value_type{}); }

		// 5)
		template <class InputIt>
		BSSimpleList(InputIt a_first, InputIt a_last)
		{
			assign(a_first, a_last);
		}

		// 6)
		BSSimpleList(const BSSimpleList& a_rhs) { assign(a_rhs.begin(), a_rhs.end()); }

		// 8)
		BSSimpleList(BSSimpleList&& a_rhs) noexcept :
			_root(std::exchange(a_rhs._root, node_type{}))
		{}

		// 10)
		explicit BSSimpleList(std::initializer_list<value_type> a_init) { assign(a_init.begin(), a_init.end()); }

		~BSSimpleList() { clear(); }

		BSSimpleList& operator=(const BSSimpleList& a_rhs)
		{
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		BSSimpleList& operator=(BSSimpleList&& a_rhs) noexcept
		{
			clear();
			_root = std::exchange(a_rhs._root, node_type{});
			return *this;
		}

		BSSimpleList& operator=(std::initializer_list<value_type> a_init)
		{
			assign(a_init.begin(), a_init.end());
			return *this;
		}

		F4_HEAP_REDEFINE_NEW(BSSimpleList<T>);

		// 1)
		void assign(size_type a_count, const_reference a_value)
		{
			clear();
			insert_after(cbefore_begin(), a_count, a_value);
		}

		// 2)
		template <class InputIt>
		void assign(InputIt a_first, InputIt a_last)
		{
			clear();
			insert_after(cbefore_begin(), std::move(a_first), std::move(a_last));
		}

		// 3)
		void assign(std::initializer_list<T> a_ilist) { assign(a_ilist.begin(), a_ilist.end()); }

		// 1)
		[[nodiscard]] reference front() noexcept
		{
			assert(!empty());
			return *begin();
		}

		// 2)
		[[nodiscard]] const_reference front() const noexcept { return mutable_reference().front(); }

		[[nodiscard]] iterator before_begin() noexcept { return iterator{ this, std::nullopt }; }
		[[nodiscard]] const_iterator before_begin() const noexcept { return mutable_reference().before_begin(); }
		[[nodiscard]] const_iterator cbefore_begin() const noexcept { return before_begin(); }

		[[nodiscard]] iterator begin() noexcept { return !empty() ? iterator{ this, std::addressof(_root) } : end(); }
		[[nodiscard]] const_iterator begin() const noexcept { mutable_reference().begin(); }
		[[nodiscard]] const_iterator cbegin() const noexcept { begin(); }

		[[nodiscard]] iterator end() noexcept { return iterator{ this, nullptr }; }
		[[nodiscard]] const_iterator end() const noexcept { return mutable_reference().end(); }
		[[nodiscard]] const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] bool empty() const noexcept { return !_root.next && !_root.value; }

		void clear() noexcept { erase_after(cbefore_begin(), cend()); }

		// 1)
		iterator insert_after(const_iterator a_pos, const_reference a_value) { return emplace_after(a_pos, a_value); }

		// 2)
		iterator insert_after(const_iterator a_pos, value_type&& a_value) { return emplace_after(a_pos, std::move(a_value)); }

		// 3)
		iterator insert_after(const_iterator a_pos, size_type a_count, const_reference a_value)
		{
			const auto gen = [&]() noexcept -> const_reference { return a_value; };
			return insert_after(
				a_pos,
				stl::counted_function_iterator{ gen, a_count },
				stl::counted_function_iterator<decltype(gen)>{});
		}

		// 4)
		template <class InputIt>
		iterator insert_after(const_iterator a_pos, InputIt a_first, InputIt a_last)
		{
			const auto [first, last] = allocate_range(std::move(a_first), std::move(a_last));
			return insert_range(a_pos, first, last);
		}

		// 5)
		iterator insert_after(const_iterator a_pos, std::initializer_list<T> a_ilist)
		{
			return insert_after(
				a_pos,
				a_ilist.begin(),
				a_ilist.end());
		}

		template <class... Args>
		iterator emplace_after(const_iterator a_pos, Args&&... a_args)
		{
			const auto node = new node_type{ { std::forward<Args>(a_args)... }, nullptr };
			return insert_range(a_pos, node, node);
		}

		// 1)
		iterator erase_after(const_iterator a_pos) { return erase_after(a_pos, ++a_pos); }

		// 2)
		iterator erase_after(const_iterator a_first, const_iterator a_last)
		{
			assert(a_first != cend());
			if (a_first != a_last) {
				const auto delRange = [](node_type* a_first, node_type* a_last) {
					while (a_first != a_last) {
						auto prev = a_first;
						a_first = a_first->next;
						delete prev;
					}
				};

				if (a_first == cbefore_begin()) {
					delRange(_root.next, a_last.get());
					if (a_last == cend()) {
						_root = node_type{};
					} else {
						// invalidates a_last, nonconforming
						_root = std::move(*a_last.get());
						delete a_last.get();
						return begin();
					}
				} else {
					delRange(a_first.get()->next, a_last.get());
					a_first.get()->next = a_last.get();
				}
			}

			return a_last.make_mutable();
		}

		// 1)
		void push_front(const_reference a_value) { emplace_front(a_value); }

		// 2)
		void push_front(value_type&& a_value) { emplace_front(std::move(a_value)); }

		template <class... Args>
		reference emplace_front(Args&&... a_args)
		{
			return *emplace_after(cbefore_begin(), std::forward<Args>(a_args)...);
		}

		void pop_front() { erase_after(cbefore_begin()); }

		// 1)
		void resize(size_type a_count) { resize(a_count, value_type{}); }

		// 2)
		void resize(size_type a_count, const value_type& a_value)
		{
			size_type n = static_cast<size_type>(-1);
			auto iter = cbefore_begin();
			const_iterator prev;
			while (++n != a_count) {
				prev = iter;
				if (++iter == cend()) {
					break;
				}
			}

			if (iter != cend()) {
				assert(n == a_count);
				erase_after(iter, cend());
			} else {
				assert(n != a_count);
				insert_after(prev, a_count - n, a_value);
			}
		}

		void swap(BSSimpleList& a_rhs)
		{
			using std::swap;
			swap(_root.value, a_rhs._root.value);
			swap(_root.next, a_rhs._root.next);
		}

	private:
		template <class InputIt>
		[[nodiscard]] static std::pair<node_type*, node_type*> allocate_range(InputIt a_first, InputIt a_last)
		{
			std::pair<node_type*, node_type*> range{ nullptr, nullptr };
			if (a_first != a_last) {
				range.first = new node_type{ *a_first };
				++a_first;

				range.second = range.first;
				for (; a_first != a_last; ++a_first) {
					range.second->next = new node_type{ *a_first };
					range.second = range.second->next;
				}
			}

			return range;
		}

		// assumes ownership of given range
		[[nodiscard]] iterator insert_range(const_iterator a_pos, node_type* a_first, node_type* a_last)
		{
			assert(a_pos != cend());
			if (a_first == nullptr) {
				assert(a_last == nullptr);
				return a_pos.make_mutable();
			} else {
				assert(a_last != nullptr);

				if (a_pos == cbefore_begin()) {
					if (_root.value) {
						_root.next = new node_type{ std::move(_root.value), _root.next };
					}

					a_last->next = _root.next;
					_root = std::move(*a_first);
					delete a_first;
				} else {
					a_last->next = a_pos.get()->next;
					a_pos.get()->next = a_first;
				}

				return iterator{ this, a_last };
			}
		}

		[[nodiscard]] BSSimpleList<T>& mutable_reference() const noexcept { return const_cast<BSSimpleList<T>&>(*this); }

		node_type _root;
	};

	template <class T>
	void swap(BSSimpleList<T>& a_lhs, BSSimpleList<T>& a_rhs)
	{
		a_lhs.swap(a_rhs);
	}
}
