#pragma once


namespace RE
{
	namespace Scaleform
	{
		template <class T>
		struct ListNode
		{
			// members
			T*	prev;	// 00
			T*	next;	// 08
		};
		STATIC_ASSERT(sizeof(ListNode<void*>) == 0x10);
	}
}
