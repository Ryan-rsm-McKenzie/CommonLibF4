#pragma once

namespace RE::BSSystemFileStreamer
{
	inline void UncacheAll(bool a_block)
	{
		using func_t = decltype(&UncacheAll);
		REL::Relocation<func_t> func{ REL::ID(40925) };
		return func(a_block);
	}
}
