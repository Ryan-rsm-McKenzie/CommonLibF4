#pragma once

namespace RE
{
	class TESObjectREFR;

	namespace SplineUtils
	{
		inline void DisconnectSpline(TESObjectREFR& a_spline)
		{
			using func_t = decltype(&DisconnectSpline);
			REL::Relocation<func_t> func{ REL::ID(750682) };
			return func(a_spline);
		}
	}
}
