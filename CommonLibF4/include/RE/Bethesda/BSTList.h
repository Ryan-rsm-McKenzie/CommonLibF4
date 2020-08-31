#pragma once

#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	// forward list
	template <class T>
	class BSSimpleList
	{
	public:
		using value_type = T;
		using size_type = std::uint32_t;
		using reference = value_type&;
		using const_reference = const value_type&;

		struct Node
		{
		public:
			Node() = default;

			Node(value_type a_value, Node* a_next) :
				item(a_value),
				next(a_next)
			{}

			Node(const Node& a_rhs) :
				item(a_rhs.item),
				next(a_rhs.next)
			{}

			Node(Node&& a_rhs) :
				item(std::move(a_rhs.item)),
				next(std::move(a_rhs.next))
			{
				a_rhs.next = nullptr;
			}

			Node(const value_type& a_value) :
				item(a_value),
				next(nullptr)
			{}

			Node(value_type&& a_value) :
				item(std::move(a_value)),
				next(nullptr)
			{}

			~Node() = default;

			Node& operator=(const Node& a_rhs)
			{
				if (this != std::addressof(a_rhs)) {
					item = a_rhs.item;
					next = a_rhs.next;
				}
				return *this;
			}

			Node& operator=(Node&& a_rhs)
			{
				if (this != std::addressof(a_rhs)) {
					item = std::move(a_rhs.item);

					next = std::move(a_rhs.next);
					a_rhs.next = nullptr;
				}
				return *this;
			}

			F4_HEAP_REDEFINE_NEW(Node);

			// members
			value_type item{};				  // 00
			observer<Node*> next{ nullptr };  // ??
		};

		template <class U>
		class iterator_base
		{
		public:
			using difference_type = std::ptrdiff_t;
			using value_type = U;
			using pointer = U*;
			using reference = U&;
			using iterator_category = std::forward_iterator_tag;

			constexpr iterator_base() noexcept = default;
			constexpr iterator_base(const iterator_base&) noexcept = default;

			constexpr iterator_base(iterator_base&& a_rhs) noexcept :
				_cur(std::move(a_rhs._cur))
			{
				a_rhs._cur = nullptr;
			}

			constexpr iterator_base(Node* a_node) noexcept :
				_cur(a_node)
			{}

			~iterator_base() noexcept { _cur = nullptr; }

			constexpr iterator_base& operator=(const iterator_base&) noexcept = default;

			constexpr iterator_base& operator=(iterator_base&& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					_cur = std::move(a_rhs._cur);
					a_rhs._cur = nullptr;
				}
				return *this;
			}

			[[nodiscard]] constexpr reference operator*() const noexcept { return _cur->item; }
			[[nodiscard]] constexpr pointer operator->() const noexcept { return std::addressof(_cur->item); }

			[[nodiscard]] constexpr bool operator==(const iterator_base& a_rhs) const noexcept { return _cur == a_rhs._cur; }
			[[nodiscard]] constexpr bool operator!=(const iterator_base& a_rhs) const noexcept { return !(*this == a_rhs); }

			// prefix
			constexpr iterator_base& operator++() noexcept
			{
				assert(_cur);
				_cur = _cur->next;
				return *this;
			}

			// postfix
			[[nodiscard]] constexpr iterator_base operator++(int) noexcept
			{
				iterator_base tmp(*this);
				++(*this);
				return tmp;
			}

		protected:
			friend class BSSimpleList<T>;

			[[nodiscard]] constexpr Node* get_current() noexcept { return _cur; }
			[[nodiscard]] constexpr const Node* get_current() const noexcept { return _cur; }

			[[nodiscard]] constexpr bool comes_before(const iterator_base& a_rhs) const noexcept
			{
				for (auto iter = _cur; iter; iter = iter->next) {
					if (iter == a_rhs._cur) {
						return true;
					}
				}
				return false;
			}

		private:
			observer<Node*> _cur{ nullptr };
		};

		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		BSSimpleList() = default;

		BSSimpleList(const BSSimpleList& a_rhs)
		{
			copy_from(a_rhs);
		}

		BSSimpleList(BSSimpleList&& a_rhs) :
			_listHead(std::move(a_rhs._listHead))
		{}

		~BSSimpleList() { clear(); }

		BSSimpleList& operator=(const BSSimpleList& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				clear();
				copy_from(a_rhs);
			}
			return *this;
		}

		BSSimpleList& operator=(BSSimpleList&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				clear();
				_listHead = std::move(a_rhs._listHead);
			}
			return *this;
		}

		F4_HEAP_REDEFINE_NEW(BSSimpleList<value_type>);

		[[nodiscard]] reference front()
		{
			assert(!empty());
			return *begin();
		}

		[[nodiscard]] const_reference front() const
		{
			assert(!empty());
			return *begin();
		}

		[[nodiscard]] iterator begin() { return empty() ? end() : iterator(get_head()); }
		[[nodiscard]] const_iterator begin() const { return empty() ? end() : const_iterator(get_head()); }
		[[nodiscard]] const_iterator cbegin() const { return begin(); }

		[[nodiscard]] constexpr iterator end() noexcept { return iterator(nullptr); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return const_iterator(nullptr); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] bool empty() const { return !_listHead.next && !_listHead.item; }

		void clear()
		{
			erase_after_impl(get_head(), nullptr);
			if (static_cast<bool>(_listHead.item)) {
				stl::destroy_at(std::addressof(_listHead.item));
			}
		}

		iterator insert_after(const_iterator a_pos, const_reference a_value)
		{
			const auto node = new Node(a_value);
			return insert_after_impl(
				a_pos.get_current(),
				std::make_pair(node, node));
		}

		iterator insert_after(const_iterator a_pos, value_type&& a_value)
		{
			const auto node = new Node(std::move(a_value));
			return insert_after_impl(
				a_pos.get_current(),
				std::make_pair(node, node));
		}

		iterator insert_after(const_iterator a_pos, size_type a_count, const_reference a_value)
		{
			if (a_count <= 0) {
				return a_pos;
			}

			return insert_after_impl(
				a_pos.get_current(),
				alloc_copies(a_count, a_value));
		}

		iterator erase_after(const_iterator a_pos)
		{
			if (a_pos == cend()) {
				return end();
			}

			const auto node = a_pos.get_current();
			erase_after_impl(node, node->next);
			return node->next;
		}

		iterator erase_after(const_iterator a_first, const_iterator a_last)
		{
			assert(a_first.comes_before(a_last));

			const auto head = a_first.get_current();
			const auto tail = a_last.get_current();

			erase_after_impl(head, tail);
			return tail;
		}

		void push_front(const_reference a_value) { emplace_front_impl(a_value); }
		void push_front(value_type&& a_value) { emplace_front_impl(std::move(a_value)); }

		template <class... Args>
		reference emplace_front(Args&&... a_args)
		{
			emplace_front_impl(std::forward<Args>(a_args)...);
			return front();
		}

		void pop_front()
		{
			assert(!empty());

			stl::destroy_at(std::addressof(_listHead.item));
			auto node = _listHead.next;
			if (node) {
				_listHead.next = node->next;
				stl::construct_at(std::addressof(_listHead.item), std::move(node->item));
				delete node;
			}
		}

		void resize(size_type a_count) { resize(a_count, value_type{}); }
		void resize(size_type a_count, const value_type& a_value) { resize_impl(a_count, a_value); }

	protected:
		[[nodiscard]] constexpr Node* get_head() noexcept { return std::addressof(_listHead); }
		[[nodiscard]] constexpr const Node* get_head() const noexcept { return std::addressof(_listHead); }

		[[nodiscard]] std::pair<Node*, Node*> alloc_copies(size_type a_count, const_reference a_value)
		{
			assert(a_count > 0);

			const auto head = new Node(a_value);
			auto tail = head;
			for (size_type i = 1; i < a_count; ++i) {
				tail->next = new Node(a_value);
				tail = tail->next;
			}

			return std::make_pair(head, tail);
		}

		void copy_from(const BSSimpleList& a_rhs)
		{
			auto lhs = get_head();
			auto rhs = a_rhs.get_head();

			lhs->item = rhs->item;
			while (rhs->next) {
				rhs = rhs->next;
				lhs->next = new Node(rhs->item);
				lhs = lhs->next;
			}
		}

		[[nodiscard]] Node* insert_after_impl(Node* a_pos, std::pair<Node*, Node*> a_values)
		{
			const auto [head, tail] = a_values;

			assert(a_pos);
			assert(head && tail);

			tail->next = a_pos->next;
			a_pos->next = head;
			return tail;
		}

		void erase_after_impl(Node* a_head, Node* a_tail)
		{
			if (a_head && a_head != a_tail) {
				auto iter = a_head->next;
				auto tmp = iter;
				while (iter != a_tail) {
					tmp = iter;
					iter = iter->next;
					delete tmp;
				}
				a_head->next = a_tail;
			}
		}

		template <class... Args>
		void emplace_front_impl(Args&&... a_args)
		{
			if (static_cast<bool>(_listHead.item)) {
				_listHead.next = new Node(std::move(_listHead));
			}

			stl::destroy_at(std::addressof(_listHead.item));
			stl::construct_at(std::addressof(_listHead.item), std::forward<Args>(a_args)...);
		}

		void resize_impl(size_type a_count, const_reference a_value)
		{
			if (a_count <= 0) {
				clear();
			}

			auto iter = begin();
			const auto last = end();
			size_type elems = 1;
			while (iter != last && elems != a_count) {
				++iter;
				++elems;
			}

			if (elems < a_count) {
				// need to grow
				insert_after(iter, a_count - elems, a_value);
			} else if (iter != last) {
				// need to shrink
				erase_after(iter, last);
			} else {
				// already required size
			}
		}

		// members
		Node _listHead{};  // 00

		// T				_item;	// 00
		// BSSimpleList<T>* _next;	// ??
	};
}
