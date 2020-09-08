#include "RE/Bethesda/Settings.h"

namespace RE
{
	template class SettingT<GameSettingCollection>;
	static_assert(sizeof(SettingT<GameSettingCollection>) == 0x18);

	template class SettingT<INIPrefSettingCollection>;
	static_assert(sizeof(SettingT<INIPrefSettingCollection>) == 0x18);

	template class SettingT<INISettingCollection>;
	static_assert(sizeof(SettingT<INISettingCollection>) == 0x18);

	template class SettingT<LipSynchroSettingCollection>;
	static_assert(sizeof(SettingT<LipSynchroSettingCollection>) == 0x18);

	template class SettingT<RegSettingCollection>;
	static_assert(sizeof(SettingT<RegSettingCollection>) == 0x18);

	template class SettingCollection<Setting>;
	static_assert(sizeof(SettingCollection<Setting>) == 0x118);

	template class SettingCollectionMap<Setting>;
	static_assert(sizeof(SettingCollectionMap<Setting>) == 0x138);

	template class SettingCollectionList<Setting>;
	static_assert(sizeof(SettingCollectionList<Setting>) == 0x128);
}
