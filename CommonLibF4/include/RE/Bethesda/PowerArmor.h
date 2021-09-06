#pragma once

namespace RE
{
	class Actor;

	namespace PowerArmor
	{
		[[nodiscard]] inline bool ActorInPowerArmor(const Actor& a_actor)
		{
			using func_t = decltype(&ActorInPowerArmor);
			REL::Relocation<func_t> func{ REL::ID(1176757) };
			return func(a_actor);
		}
	}
}
