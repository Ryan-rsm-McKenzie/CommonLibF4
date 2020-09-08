#pragma once

#include "RE/Bethesda/BSTTuple.h"

namespace RE
{
	template <class Key, class T>
	class BSTBTree
	{
	public:
		using key_type = Key;
		using mapped_type = T;
		using value_type = BSTTuple<const key_type, mapped_type>;

		// traverse entries using a leftmost binary search
		//	index nodes with with index of lower bound, iff entry is not found at this level
		// nodes are always allocated as powers of 2
		//	maybe std::bit_ceil(sizeof(node_type)) ?
		struct node_type
		{
		public:
			// members
			value_type entries[4];			 // 00
			node_type* nodes[5]{ nullptr };	 // ??
			std::uint32_t usedEntries{ 0 };	 // ??
		};

	private:
		template <class T>
		class iterator_base :
			public boost::iterators::iterator_facade<
				iterator_base<T>,
				T,
				std::forward_iterator_tag>
		{
		private:
			using super =
				boost::iterators::iterator_facade<
					iterator_base<T>,
					T,
					std::forward_iterator_tag>;

		public:
			using difference_type = typename super::difference_type;
			using value_type = typename super::value_type;
			using pointer = typename super::pointer;
			using reference = typename super::reference;
			using iterator_category = typename super::iterator_category;

			iterator_base() noexcept = default;

			template <class U>
			iterator_base(const iterator_base<U>& a_rhs) :
				_queued(a_rhs._queued),
				_cur(a_rhs._cur),
				_pos(a_rhs._pos)
			{}

			template <class U>
			iterator_base(iterator_base<U>&& a_rhs) noexcept :
				_queued(std::move(a_rhs._queued)),
				_cur(a_rhs._cur),
				_pos(a_rhs._pos)
			{
				a_rhs._cur = nullptr;
				a_rhs._pos = 0;
			}

			~iterator_base() noexcept = default;

			template <class U>
			iterator_base& operator=(const iterator_base<U>& a_rhs)
			{
				if (this != std::addressof(a_rhs)) {
					_queued = a_rhs._queued;
					_cur = a_rhs._cur;
					_pos = a_rhs._pos;
				}
				return *this;
			}

			template <class U>
			iterator_base& operator=(iterator_base<U>&& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					_queued = std::move(a_rhs._queued);
					_cur = a_rhs._cur;
					_pos = a_rhs._pos;

					a_rhs._cur = nullptr;
					a_rhs._pos = 0;
				}
				return *this;
			}

		protected:
			friend class boost::iterator_core_access;

			template <class, class>
			friend class BSTBTree;

			iterator_base(node_type* a_node) noexcept
			{
				if (a_node && a_node->usedEntries > 0) {
					_cur = a_node;
					push_level();
				}
			}

			[[nodiscard]] reference dereference() const noexcept { return _cur->entries[_pos]; }

			template <class U>
			[[nodiscard]] bool equal(const iterator_base<U>& a_rhs) const noexcept
			{
				return _cur == nullptr && a_rhs._cur == nullptr;
			}

			void increment() noexcept
			{
				assert(_cur != nullptr);
				if (++_pos >= _cur->usedEntries) {
					_cur = nullptr;
					_pos = 0;
					if (!_queued.empty()) {
						_cur = _queued.top();
						_queued.pop();
						push_level();
					}
				}
			}

		private:
			void push_level()
			{
				for (std::uint32_t i = 0; i <= _cur->usedEntries; ++i) {
					if (const auto node = _cur->nodes[i];
						node && node->usedEntries > 0) {
						_queued.push(node);
					}
				}
			}

			std::stack<node_type*> _queued;
			node_type* _cur{ nullptr };
			std::uint32_t _pos{ 0 };
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		[[nodiscard]] iterator begin() noexcept { return { _root }; }
		[[nodiscard]] const_iterator begin() const noexcept { return { _root }; }
		[[nodiscard]] const_iterator cbegin() const noexcept { return { _root }; }

		[[nodiscard]] iterator end() noexcept { return {}; }
		[[nodiscard]] const_iterator end() const noexcept { return {}; }
		[[nodiscard]] const_iterator cend() const noexcept { return {}; }

	private:
		std::uint64_t pad{ 0 };				// 00
		std::uint32_t _activeEntry{ 0 };	// 08
		std::uint32_t _allocatedSize{ 0 };	// 0C
		node_type* _root{ nullptr };		// 10
		node_type* _availNodes{ nullptr };	// 18
	};
}
