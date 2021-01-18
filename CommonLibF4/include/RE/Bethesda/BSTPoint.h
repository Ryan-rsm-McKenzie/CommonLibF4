#pragma once

namespace RE
{
	template <class T>
	class BSTPointDefaultOps
	{
	public:
	};

	extern template class BSTPointDefaultOps<std::int8_t>;
	extern template class BSTPointDefaultOps<std::uint8_t>;
	extern template class BSTPointDefaultOps<std::int16_t>;
	extern template class BSTPointDefaultOps<std::uint16_t>;
	extern template class BSTPointDefaultOps<std::int32_t>;
	extern template class BSTPointDefaultOps<std::uint32_t>;
	extern template class BSTPointDefaultOps<float>;
	extern template class BSTPointDefaultOps<double>;

	template <class T>
	class BSTPoint2Base
	{
	public:
		T x;  // 00
		T y;  // ??
	};

	extern template class BSTPoint2Base<std::int8_t>;
	extern template class BSTPoint2Base<std::uint8_t>;
	extern template class BSTPoint2Base<std::int16_t>;
	extern template class BSTPoint2Base<std::uint16_t>;
	extern template class BSTPoint2Base<std::int32_t>;
	extern template class BSTPoint2Base<std::uint32_t>;
	extern template class BSTPoint2Base<float>;
	extern template class BSTPoint2Base<double>;

	template <
		class T,
		class Ops = BSTPointDefaultOps<T>>
	class BSTPoint2 :
		public BSTPoint2Base<T>,
		public BSTPointDefaultOps<T>
	{
	public:
	};

	extern template class BSTPoint2<std::int8_t>;
	extern template class BSTPoint2<std::uint8_t>;
	extern template class BSTPoint2<std::int16_t>;
	extern template class BSTPoint2<std::uint16_t>;
	extern template class BSTPoint2<std::int32_t>;
	extern template class BSTPoint2<std::uint32_t>;
	extern template class BSTPoint2<float>;
	extern template class BSTPoint2<double>;

	template <class T>
	class BSTPoint3Base
	{
	public:
		T x;  // 00
		T y;  // ??
		T z;  // ??
	};

	extern template class BSTPoint3Base<std::int8_t>;
	extern template class BSTPoint3Base<std::uint8_t>;
	extern template class BSTPoint3Base<std::int16_t>;
	extern template class BSTPoint3Base<std::uint16_t>;
	extern template class BSTPoint3Base<std::int32_t>;
	extern template class BSTPoint3Base<std::uint32_t>;
	extern template class BSTPoint3Base<float>;
	extern template class BSTPoint3Base<double>;

	template <
		class T,
		class Ops = BSTPointDefaultOps<T>>
	class BSTPoint3 :
		public BSTPoint3Base<T>,
		public BSTPointDefaultOps<T>
	{
	public:
	};

	extern template class BSTPoint3<std::int8_t>;
	extern template class BSTPoint3<std::uint8_t>;
	extern template class BSTPoint3<std::int16_t>;
	extern template class BSTPoint3<std::uint16_t>;
	extern template class BSTPoint3<std::int32_t>;
	extern template class BSTPoint3<std::uint32_t>;
	extern template class BSTPoint3<float>;
	extern template class BSTPoint3<double>;
}
