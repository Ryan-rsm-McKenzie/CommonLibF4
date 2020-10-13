#pragma once

namespace RE
{
	template <class T>
	class NiRect
	{
	public:
		// members
		T left;    // 00
		T right;   // ??
		T top;     // ??
		T bottom;  // ??
	};

	extern template class NiRect<float>;
	extern template class NiRect<std::int32_t>;
	extern template class NiRect<std::uint32_t>;
}
