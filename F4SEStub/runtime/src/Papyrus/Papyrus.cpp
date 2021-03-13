#include "Papyrus/Papyrus.h"

#include "Papyrus/Actor.h"
#include "Papyrus/ActorBase.h"
#include "Papyrus/Armor.h"
#include "Papyrus/ArmorAddon.h"
#include "Papyrus/Cell.h"
#include "Papyrus/Component.h"
#include "Papyrus/ConstructibleObject.h"
#include "Papyrus/DefaultObject.h"
#include "Papyrus/EncounterZone.h"
#include "Papyrus/EquipSlot.h"
#include "Papyrus/F4SE.h"
#include "Papyrus/Form.h"
#include "Papyrus/Game.h"
#include "Papyrus/HeadPart.h"
#include "Papyrus/Input.h"
#include "Papyrus/InstanceData.h"
#include "Papyrus/Location.h"
#include "Papyrus/MatSwap.h"
#include "Papyrus/Math.h"
#include "Papyrus/MiscObject.h"
#include "Papyrus/ObjectMod.h"
#include "Papyrus/ObjectReference.h"
#include "Papyrus/Perk.h"
#include "Papyrus/ScriptObject.h"
#include "Papyrus/UI.h"
#include "Papyrus/Utility.h"
#include "Papyrus/WaterType.h"
#include "Papyrus/Weapon.h"

#undef BIND

namespace Papyrus
{
	bool F4SEAPI Bind(RE::BSScript::IVirtualMachine* a_vm)
	{
		if (!a_vm) {
			return false;
		}

		Actor::Bind(*a_vm);
		ActorBase::Bind(*a_vm);
		Armor::Bind(*a_vm);
		ArmorAddon::Bind(*a_vm);
		Cell::Bind(*a_vm);
		Component::Bind(*a_vm);
		ConstructibleObject::Bind(*a_vm);
		DefaultObject::Bind(*a_vm);
		EncounterZone::Bind(*a_vm);
		EquipSlot::Bind(*a_vm);
		F4SE::Bind(*a_vm);
		Form::Bind(*a_vm);
		Game::Bind(*a_vm);
		HeadPart::Bind(*a_vm);
		Input::Bind(*a_vm);
		InstanceData::Bind(*a_vm);
		Location::Bind(*a_vm);
		MatSwap::Bind(*a_vm);
		Math::Bind(*a_vm);
		MiscObject::Bind(*a_vm);
		ObjectMod::Bind(*a_vm);
		ObjectReference::Bind(*a_vm);
		Perk::Bind(*a_vm);
		ScriptObject::Bind(*a_vm);
		UI::Bind(*a_vm);
		Utility::Bind(*a_vm);
		WaterType::Bind(*a_vm);
		Weapon::Bind(*a_vm);

		logger::info("bound all scripts"sv);
		return true;
	}
}
