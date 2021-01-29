#pragma once

#include "RE/NetImmerse/NiPoint2.h"

namespace RE
{
	class EaseOutInterpolator
	{
	public:
	};
	static_assert(std::is_empty_v<EaseOutInterpolator>);

	template <class T>
	class GetCurrentPositionFunctor
	{
	public:
	};

	extern template class GetCurrentPositionFunctor<float>;

	template <
		class T,
		class Interpolator,
		template <class> class GetCurrent>
	class BSTInterpolator
	{
	public:
		Interpolator interpolate;  // 00
		GetCurrent<T> getCurr;     // ??
		T start;                   // ??
		T finish;                  // ??
		float duration;            // ??
		float startTime;           // ??
		bool finished;             // ??
	};

	extern template class BSTInterpolator<float, EaseOutInterpolator, GetCurrentPositionFunctor>;
}
