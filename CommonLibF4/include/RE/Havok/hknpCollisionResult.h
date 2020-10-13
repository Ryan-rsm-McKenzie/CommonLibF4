#pragma once

#include "RE/Havok/hkBaseTypes.h"
#include "RE/Havok/hkVector4.h"
#include "RE/Havok/hknpBodyId.h"
#include "RE/Havok/hknpMaterialId.h"

namespace RE
{
	struct hknpCollisionQueryType
	{
	public:
		enum class Enum;
	};

	struct hknpCollisionResult
	{
	public:
		struct BodyInfo
		{
		public:
			// members
			hknpBodyId m_bodyId;                                 // 00
			hknpMaterialId m_shapeMaterialId;                    // 04
			hkPadSpu<std::uint32_t> m_shapeKey;                  // 08
			hkPadSpu<std::uint32_t> m_shapeCollisionFilterInfo;  // 0C
			hkPadSpu<std::size_t> m_shapeUserData;               // 10
		};
		static_assert(sizeof(BodyInfo) == 0x18);

		// members
		hkVector4f position;                                                     // 00
		hkVector4f normal;                                                       // 10
		hkPadSpu<float> fraction;                                                // 20
		BodyInfo queryBodyInfo;                                                  // 28
		BodyInfo hitBodyInfo;                                                    // 40
		stl::enumeration<hknpCollisionQueryType::Enum, std::int32_t> queryType;  // 58
		hkPadSpu<std::uint32_t> hitResult;                                       // 5C
	};
	static_assert(sizeof(hknpCollisionResult) == 0x60);
}
