#include "RE/Bethesda/BSExtraData.h"

#include "RE/Bethesda/BGSMod.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/TESBoundObjects.h"

namespace RE
{
	ExtraInstanceData::ExtraInstanceData() :
		ExtraInstanceData(nullptr, nullptr)
	{}

	ExtraInstanceData::ExtraInstanceData(const TESBoundObject* a_base, BSTSmartPointer<TBO_InstanceData> a_data) :
		BSExtraData(TYPE),
		base(a_base),
		data(std::move(a_data))
	{
		stl::emplace_vtable(this);
	}

	void BGSObjectInstanceExtra::CreateBaseInstanceData(const TESBoundObject& a_object, BSTSmartPointer<TBO_InstanceData>& a_instanceData) const
	{
		if (values && itemIndex != static_cast<std::uint16_t>(-1)) {
			a_object.ApplyMods(a_instanceData, this);
		}
	}

	std::span<BGSMod::ObjectIndexData> BGSObjectInstanceExtra::GetIndexData() const noexcept
	{
		return values->GetBuffer<BGSMod::ObjectIndexData>(0);
	}
}
