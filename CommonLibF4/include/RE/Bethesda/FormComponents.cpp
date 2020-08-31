#include "RE/Bethesda/FormComponents.h"

#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/TESForms.h"
#include "RE/RTTI.h"

namespace RE
{
	const char* TESFullName::GetFullName(const TESForm* a_obj)
	{
		const auto fullName = fallout_cast<const TESFullName*>(a_obj);
		if (fullName) {
			return fullName->GetFullName();
		} else {
			REL::Relocation<BSTHashMap<const TESForm*, BGSLocalizedString>*> map{ REL::ID(226372), -0x8 };
			const auto it = map->find(a_obj);
			return it == map->end() ? "" : it->second.c_str();
		}
	}
}
