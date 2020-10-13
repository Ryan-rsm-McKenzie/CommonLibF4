#pragma once

namespace RE
{
	template <class T>
	class hkRefPtr
	{
	public:
		~hkRefPtr() noexcept {}  // intentional

		T* _ptr;
	};
}
