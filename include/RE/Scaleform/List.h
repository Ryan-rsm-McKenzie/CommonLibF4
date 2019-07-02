#pragma once

#include "RE/Scaleform/ListNode.h"


namespace RE
{
	namespace Scaleform
	{
		template <class T, class Base = T>
		class List
		{
		public:
			ListNode<Base> root;	// 00
		};
		STATIC_ASSERT(sizeof(List<void*>) == 0x10);
	}
}
