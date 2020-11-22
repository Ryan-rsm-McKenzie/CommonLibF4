#pragma once

#include "RE/Scaleform/Kernel/SF_Memory.h"

namespace RE::Scaleform
{
	template <std::int32_t>
	class AllocatorBaseGH
	{
	public:
	};
	//static_assert(std::is_empty_v<AllocatorBaseGH<0>>);

	template <class T>
	class ConstructorMov
	{
	public:
	};
	//static_assert(std::is_empty_v<ConstructorMov<void*>>);

	template <class T, std::int32_t SID = 2>
	struct AllocatorGH :
		public AllocatorBaseGH<SID>,  // 0
		public ConstructorMov<T>      // 1
	{
	public:
	};
	//static_assert(std::is_empty_v<AllocatorGH<void*>>);
}
