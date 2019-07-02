#pragma once


namespace RE
{
	struct AllocInfo
	{
		UInt32 StatID;	// 0
	};
	STATIC_ASSERT(sizeof(AllocInfo) == 0x4);
}
