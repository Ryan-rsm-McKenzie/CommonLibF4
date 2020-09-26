#pragma once

namespace RE
{
	template <class E, class U>
	using hkFlags = stl::enumeration<E, U>;

	template <class T>
	class hkPadSpu
	{
	public:
		~hkPadSpu() noexcept {}	 // intentional

		// members
		T storage;
	};

	enum class hkResultEnum
	{
		kSuccess,
		kFailure
	};

	struct hkResult
	{
	public:
		~hkResult() noexcept {}	 // intentional

		// members
		hkResultEnum e;	 // 0
	};
	static_assert(sizeof(hkResult) == 0x4);
}
