#pragma once

namespace RE::Scaleform
{
	class Lock;

	template <class T>
	class AtomicValueBase
	{
	public:
		// members
		volatile T value;  // 0
	};
	//static_assert(sizeof(AtomicValueBase<std::int32_t>) == 0x4);

	template <class T>
	class AtomicInt :
		public AtomicValueBase<T>  // 0
	{
	public:
	};
	//static_assert(sizeof(AtomicInt<std::int32_t>) == 0x4);

	class Lock
	{
	public:
		// members
		WinAPI::CRITICAL_SECTION cs;  // 00
	};
	static_assert(sizeof(Lock) == 0x28);
}
