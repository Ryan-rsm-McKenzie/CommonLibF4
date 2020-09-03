#pragma once

namespace RE
{
	class hkVector4f
	{
	public:
		__m128 quad;  // 00
	};
	static_assert(sizeof(hkVector4f) == 0x10);
}
