#pragma once

namespace RE
{
	struct BSPointerAllocator
	{
	public:
	};
	static_assert(std::is_empty_v<BSPointerAllocator>);

	template <class T>
	class NiTPointerAllocator :
		public BSPointerAllocator  // 0
	{
	public:
	};
}
