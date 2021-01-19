#include "Papyrus/Papyrus.h"

#define BIND(a_method, ...) a_vm.BindNativeMethod(obj, #a_method##sv, a_method __VA_OPT__(, ) __VA_ARGS__)

namespace Papyrus
{
	using RE::BSScript::structure_wrapper;
	using Severity = RE::BSScript::ErrorLogger::Severity;
}

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
		//InstanceData::Bind(*a_vm);
		Location::Bind(*a_vm);
		Math::Bind(*a_vm);
		MatSwap::Bind(*a_vm);

		logger::info("bound all scripts"sv);
		return true;
	}
}
