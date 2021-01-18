#include "RE/Bethesda/BSTPoint.h"

namespace RE
{
	template class BSTPointDefaultOps<std::int8_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::int8_t>>);

	template class BSTPointDefaultOps<std::uint8_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::uint8_t>>);

	template class BSTPointDefaultOps<std::int16_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::int16_t>>);

	template class BSTPointDefaultOps<std::uint16_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::uint16_t>>);

	template class BSTPointDefaultOps<std::int32_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::int32_t>>);

	template class BSTPointDefaultOps<std::uint32_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::uint32_t>>);

	template class BSTPointDefaultOps<float>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<float>>);

	template class BSTPointDefaultOps<double>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<double>>);

	template class BSTPoint2Base<std::int8_t>;
	static_assert(sizeof(BSTPoint2Base<std::int8_t>) == 0x2);

	template class BSTPoint2Base<std::uint8_t>;
	static_assert(sizeof(BSTPoint2Base<std::uint8_t>) == 0x2);

	template class BSTPoint2Base<std::int16_t>;
	static_assert(sizeof(BSTPoint2Base<std::int16_t>) == 0x4);

	template class BSTPoint2Base<std::uint16_t>;
	static_assert(sizeof(BSTPoint2Base<std::uint16_t>) == 0x4);

	template class BSTPoint2Base<std::int32_t>;
	static_assert(sizeof(BSTPoint2Base<std::int32_t>) == 0x8);

	template class BSTPoint2Base<std::uint32_t>;
	static_assert(sizeof(BSTPoint2Base<std::uint32_t>) == 0x8);

	template class BSTPoint2Base<float>;
	static_assert(sizeof(BSTPoint2Base<float>) == 0x8);

	template class BSTPoint2Base<double>;
	static_assert(sizeof(BSTPoint2Base<double>) == 0x10);

	template class BSTPoint2<std::int8_t>;
	static_assert(sizeof(BSTPoint2<std::int8_t>) == 0x2);

	template class BSTPoint2<std::uint8_t>;
	static_assert(sizeof(BSTPoint2<std::uint8_t>) == 0x2);

	template class BSTPoint2<std::int16_t>;
	static_assert(sizeof(BSTPoint2<std::int16_t>) == 0x4);

	template class BSTPoint2<std::uint16_t>;
	static_assert(sizeof(BSTPoint2<std::uint16_t>) == 0x4);

	template class BSTPoint2<std::int32_t>;
	static_assert(sizeof(BSTPoint2<std::int32_t>) == 0x8);

	template class BSTPoint2<std::uint32_t>;
	static_assert(sizeof(BSTPoint2<std::uint32_t>) == 0x8);

	template class BSTPoint2<float>;
	static_assert(sizeof(BSTPoint2<float>) == 0x8);

	template class BSTPoint2<double>;
	static_assert(sizeof(BSTPoint2<double>) == 0x10);

	template class BSTPoint3Base<std::int8_t>;
	static_assert(sizeof(BSTPoint3Base<std::int8_t>) == 0x3);

	template class BSTPoint3Base<std::uint8_t>;
	static_assert(sizeof(BSTPoint3Base<std::uint8_t>) == 0x3);

	template class BSTPoint3Base<std::int16_t>;
	static_assert(sizeof(BSTPoint3Base<std::int16_t>) == 0x6);

	template class BSTPoint3Base<std::uint16_t>;
	static_assert(sizeof(BSTPoint3Base<std::uint16_t>) == 0x6);

	template class BSTPoint3Base<std::int32_t>;
	static_assert(sizeof(BSTPoint3Base<std::int32_t>) == 0xC);

	template class BSTPoint3Base<std::uint32_t>;
	static_assert(sizeof(BSTPoint3Base<std::uint32_t>) == 0xC);

	template class BSTPoint3Base<float>;
	static_assert(sizeof(BSTPoint3Base<float>) == 0xC);

	template class BSTPoint3Base<double>;
	static_assert(sizeof(BSTPoint3Base<double>) == 0x18);

	template class BSTPoint3<std::int8_t>;
	static_assert(sizeof(BSTPoint3<std::int8_t>) == 0x3);

	template class BSTPoint3<std::uint8_t>;
	static_assert(sizeof(BSTPoint3<std::uint8_t>) == 0x3);

	template class BSTPoint3<std::int16_t>;
	static_assert(sizeof(BSTPoint3<std::int16_t>) == 0x6);

	template class BSTPoint3<std::uint16_t>;
	static_assert(sizeof(BSTPoint3<std::uint16_t>) == 0x6);

	template class BSTPoint3<std::int32_t>;
	static_assert(sizeof(BSTPoint3<std::int32_t>) == 0xC);

	template class BSTPoint3<std::uint32_t>;
	static_assert(sizeof(BSTPoint3<std::uint32_t>) == 0xC);

	template class BSTPoint3<float>;
	static_assert(sizeof(BSTPoint3<float>) == 0xC);

	template class BSTPoint3<double>;
	static_assert(sizeof(BSTPoint3<double>) == 0x18);
}
