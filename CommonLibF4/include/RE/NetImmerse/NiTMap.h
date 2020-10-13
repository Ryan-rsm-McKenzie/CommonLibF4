#pragma once

#include "RE/NetImmerse/NiTDefaultAllocator.h"
#include "RE/NetImmerse/NiTMapBase.h"

namespace RE
{
	template <class Key, class T>
	class NiTMap :
		public NiTMapBase<DFALL<NiTMapItem<Key, T>>, Key, T>  // 00
	{
	private:
		using super = NiTMapBase<DFALL<NiTMapItem<Key, T>>, Key, T>;

	public:
		using key_type = typename super::key_type;
		using mapped_type = typename super::mapped_type;
		using value_type = typename super::value_type;
		using size_type = typename super::size_type;
		using allocator_type = typename super::allocator_type;

	protected:
		value_type* malloc_value() override { return new value_type(); };   // 05
		void free_value(value_type* a_value) override { delete a_value; };  // 06
	};
}
