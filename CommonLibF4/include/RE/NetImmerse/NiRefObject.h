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

		// members
		std::uint32_t refCount;	 // 08
	};
	static_assert(sizeof(NiRefObject) == 0x10);
}
