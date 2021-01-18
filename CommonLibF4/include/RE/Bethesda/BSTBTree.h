#pragma once

#include "RE/Bethesda/BSTTuple.h"

namespace RE
{
	template <
		class Key,
		class T,
		class Compare = std::less<>>
	class BSTBTree
	{
	public:
		using key_type = Key;
		using mapped_type = T;
		using value_type = BSTTuple<const key_type, mapped_type>;
		using size_type = std::uint32_t;
		using key_compare = Compare;

		static_assert(std::is_empty_v<key_compare>, "compare object must be stateless");

		// traverse entries using a leftmost binary search
		//	index nodes with with index of lower bound, iff entry is not found at this level
		// nodes are always allocated as powers of 2
		//	maybe std::bit_ceil(sizeof(node_type)) ?
		struct node_type
		{
		public:
			using iterator = value_type*;
			using const_iterator = const value_type*;

			[[nodiscard]] iterator begin() noexcept { return entries; }
			[[nodiscard]] const_iterator begin() const noexcept { return entries; }
			[[nodiscard]] const_iterator cbegin() const noexcept { return entries; }

			[[nodiscard]] iterator end() noexcept { return entries + usedEntries; }
			[[nodiscard]] const_iterator end() const noexcept { return entries + usedEntries; }
			[[nodiscard]] const_iterator cend() const noexcept { return entries + usedEntries; }

			// members
			value_type entries[4];           // 00
			node_type* nodes[5]{ nullptr };  // ??
			size_type usedEntries{ 0 };      // ??
		};

	private:
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

			template <class V>
			iterator_base(const iterator_base<V>& a_rhs)  //
				requires(std::convertible_to<typename iterator_base<V>::reference, reference>) :
				_queued(a_rhs._queued),
				_cur(a_rhs._cur),
				_pos(a_rhs._pos)
			{}

			template <class V>
			iterator_base(iterator_base<V>&& a_rhs) noexcept  //
				requires(std::convertible_to<typename iterator_base<V>::reference, reference>) :
				_queued(std::move(a_rhs._queued)),
				_cur(std::exchange(a_rhs._cur, nullptr)),
				_pos(std::exchange(a_rhs._pos, 0))
			{}

			~iterator_base() noexcept = default;

			template <class V>
			iterator_base& operator=(const iterator_base<V>& a_rhs)  //
				requires(std::convertible_to<typename iterator_base<V>::reference, reference>)
			{
				if (this != std::addressof(a_rhs)) {
					_queued = a_rhs._queued;
					_cur = a_rhs._cur;
					_pos = a_rhs._pos;
				}
				return *this;
			}

			template <class V>
			iterator_base& operator=(iterator_base<V>&& a_rhs) noexcept  //
				requires(std::convertible_to<typename iterator_base<V>::reference, reference>)
			{
				if (this != std::addressof(a_rhs)) {
					_queued = std::move(a_rhs._queued);
					_cur = std::exchange(a_rhs._cur, nullptr);
					_pos = std::exchange(a_rhs._pos, 0);
				}
				return *this;
			}

			[[nodiscard]] reference operator*() const noexcept
			{
				assert(_cur != nullptr);
				assert(_pos < _cur->usedEntries);
				return _cur->entries[_pos];
			}

			template <class V>
			[[nodiscard]] bool operator==(const iterator_base<V>& a_rhs) const noexcept
			{
				return _cur == nullptr && a_rhs._cur == nullptr;
			}

			using super::operator++;

			void operator++() noexcept
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

		protected:
			template <class, class, class>
			friend class BSTBTree;

			explicit iterator_base(node_type* a_node) noexcept :
				iterator_base(a_node, 0)
			{}

			iterator_base(node_type* a_node, size_type a_pos) noexcept :
				_pos(a_pos)
			{
				if (a_node && a_node->usedEntries > 0) {
					_cur = a_node;
					push_level();
				}
			}

		private:
			template <class>
			friend class iterator_base;

			void push_level()
			{
				for (size_type i = 0; i <= _cur->usedEntries; ++i) {
					if (const auto node = _cur->nodes[i];
						node && node->usedEntries > 0) {
						_queued.push(node);
					}
				}
			}

			std::stack<node_type*> _queued;
			node_type* _cur{ nullptr };
			size_type _pos{ 0 };
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		[[nodiscard]] iterator begin() noexcept { return iterator{ _root }; }
		[[nodiscard]] const_iterator begin() const noexcept { return const_iterator{ _root }; }
		[[nodiscard]] const_iterator cbegin() const noexcept { return const_iterator{ _root }; }

		[[nodiscard]] iterator end() noexcept { return {}; }
		[[nodiscard]] const_iterator end() const noexcept { return {}; }
		[[nodiscard]] const_iterator cend() const noexcept { return {}; }

		[[nodiscard]] iterator find(const key_type& a_key) { return do_find<iterator>(a_key); }
		[[nodiscard]] const_iterator find(const key_type& a_key) const { return do_find<const_iterator>(a_key); }

		template <class K>
		[[nodiscard]] iterator find(const K& a_key)  //
			requires(stl::transparent_comparator<BSTBTree, K>)
		{
			return do_find<iterator>(a_key);
		}

		template <class K>
		[[nodiscard]] const_iterator find(const K& a_key) const  //
			requires(stl::transparent_comparator<BSTBTree, K>)
		{
			return do_find<const_iterator>(a_key);
		}

		[[nodiscard]] key_compare key_comp() const { return key_compare{}; }

	private:
		template <class Iter, class K>
		[[nodiscard]] Iter do_find(const K& a_key) const
		{
			auto node = _root;
			while (node) {
				const auto it = std::lower_bound(
					node->begin(),
					node->end(),
					a_key,
					[&](const value_type& a_lhs, const key_type& a_rhs) {
						return key_comp()(a_lhs.first, a_rhs);
					});
				if (it != node->end()) {
					const auto pos = static_cast<size_type>(it - node->begin());
					if (!key_comp()(a_key, it->first)) {
						return Iter(node, pos);
					} else {
						node = node->nodes[pos];
					}
				} else {
					node = node->nodes[node->usedEntries];
				}
			}

			return Iter();
		}

		std::uint64_t pad{ 0 };             // 00
		size_type _activeEntry{ 0 };        // 08
		size_type _allocatedSize{ 0 };      // 0C
		node_type* _root{ nullptr };        // 10
		node_type* _availNodes{ nullptr };  // 18
	};
}
