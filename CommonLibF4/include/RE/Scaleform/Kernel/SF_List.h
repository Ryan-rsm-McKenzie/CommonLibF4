#pragma once

namespace RE::Scaleform
{
	template <class T>
	struct ListNode
	{
	public:
		// members
		T* prev;  // 00
		T* next;  // 08
	};
	//static_assert(sizeof(ListNode<void*>) == 0x10);

	template <class T, class B = T>
	class List
	{
	public:
		// members
		ListNode<B> root;  // 00
	};
	//static_assert(sizeof(List<void*>) == 0x10);

	template <class T, class Accessor>
	class List2
	{
	public:
		// members
		T root;  // 00
	};
}
