#pragma once

namespace RE
{
	struct BSIntrusiveRefCounted
	{
	public:
		constexpr BSIntrusiveRefCounted() noexcept {}  // intentional

		std::uint32_t DecRef()
		{
			stl::atomic_ref myRefCount{ refCount };
			return --myRefCount;
		}

		std::uint32_t IncRef()
		{
			stl::atomic_ref myRefCount{ refCount };
			return ++myRefCount;
		}

		[[nodiscard]] constexpr std::uint32_t QRefCount() const noexcept { return refCount; }

		// members
		std::uint32_t refCount{ 0 };  // 0
	};
	static_assert(sizeof(BSIntrusiveRefCounted) == 0x4);
}
