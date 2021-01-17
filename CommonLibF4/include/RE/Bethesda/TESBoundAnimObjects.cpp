#include "RE/Bethesda/TESBoundAnimObjects.h"

#include "RE/Bethesda/PlayerCharacter.h"

namespace RE
{
	bool TESNPC::UsingAlternateHeadPartList() const
	{
		if (const auto player = PlayerCharacter::GetSingleton(); IsPlayer() && player) {
			const auto& map = GetAlternateHeadPartListMap();
			return player->charGenRace && player->charGenRace != formRace && map.contains(player->GetNPC());
		} else {
			return originalRace && originalRace != formRace;
		}
	}
}
