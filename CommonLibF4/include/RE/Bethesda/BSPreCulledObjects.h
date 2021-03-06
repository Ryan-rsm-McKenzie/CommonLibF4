#pragma once

namespace RE
{
	class BSCullingGroup;
	class NiAVObject;

	struct BSPreCulledObjects
	{
	public:
		struct ObjectRecord
		{
		public:
			// members
			NiAVObject* obj{ nullptr };  // 00
			std::uint32_t flags{ 0 };    // 08
		};
		static_assert(sizeof(ObjectRecord) == 0x10);
	};
	static_assert(std::is_empty_v<BSPreCulledObjects>);
}
