#pragma once

namespace RE::BSBTreeFile
{
	template <class Key, std::size_t PAGE_SIZE>
	struct PageBasics
	{
	public:
		using key_type = Key;

		struct InteriorNode;
	};

	template <class T, class Key, std::size_t PAGE_SIZE>
	struct PGFSEDL :
		public PageBasics<Key, PAGE_SIZE>
	{
	public:
		using key_type = Key;

		struct LeafNode;
	};

	template <class Pager, class Impl, std::size_t MAX_DEPTH>
	class BPTree :
		public Impl  // 00
	{
	public:
		class PagePtr
		{
		public:
			// members
			union
			{
				typename Impl::InteriorNode* interior;
				typename Impl::LeafNode* leaf;
				void* ptr = nullptr;
			};  // 0
		};
		// static_assert(sizeof(PagePtr) == 0x8);

		struct Cursor
		{
		public:
			struct PageEntry
			{
			public:
				// members
				PagePtr page = {};            // 00
				std::uint64_t pageIndex = 0;  // 08
			};
			// static_assert(sizeof(PageEntry) == 0x10);

			// members
			PageEntry pages[MAX_DEPTH] = {};          // 00
			std::uint32_t positions[MAX_DEPTH] = {};  // ??
			std::uint32_t depth = 0;                  // ??
		};

		// members
		Pager* fpol = nullptr;            // 00
		PagePtr* root = nullptr;          // 18
		std::uint64_t rootPageIndex = 0;  // 10
		std::uint32_t active = 0;         // 18
		std::uint32_t depth = 0;          // 1C
	};
	// static_assert(sizeof(BPTree) == 0x20);
}
