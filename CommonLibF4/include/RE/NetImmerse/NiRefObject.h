#pragma once

namespace RE
{
	class NiRefObject
	{
	public:
		static constexpr auto RTTI{ RTTI_NiRefObject };

		virtual ~NiRefObject();	 // 00

		// add
		virtual void DeleteThis() { delete this; }	// 01

		std::uint32_t DecRefCount()
		{
			stl::atomic_ref myRefCount{ refCount };
			const auto newRefCount = --myRefCount;
			if (newRefCount == 0) {
				DeleteThis();
			}
			return newRefCount;
		}

		std::uint32_t IncRefCount()
		{
			stl::atomic_ref myRefCount{ refCount };
			return ++myRefCount;
		}

		// members
		std::uint32_t refCount;	 // 08
	};
	static_assert(sizeof(NiRefObject) == 0x10);
}
