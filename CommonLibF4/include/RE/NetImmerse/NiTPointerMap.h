#pragma once

#include "RE/NetImmerse/NiTMapBase.h"
#include "RE/NetImmerse/NiTPointerAllocator.h"

namespace RE
{
	template <class Key, class T>
	class NiTPointerMap :
		public NiTMapBase<NiTPointerAllocator<std::size_t>, Key, T>  // 00
	{
	private:
		using super = NiTMapBase<NiTPointerAllocator<std::size_t>, Key, T>;

	public:
		using key_type = typename super::key_type;
		using mapped_type = typename super::mapped_type;
		using value_type = typename super::value_type;
		using size_type = typename super::size_type;
		using allocator_type = typename super::allocator_type;

	protected:
		value_type* malloc_value() override;            // 05
		void free_value(value_type* a_value) override;  // 06
	};
}
