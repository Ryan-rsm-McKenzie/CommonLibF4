#pragma once

#define BIND(a_method, ...) a_vm.BindNativeMethod(obj, #a_method##sv, a_method __VA_OPT__(, ) __VA_ARGS__)

namespace Papyrus
{
	using RE::BSScript::structure_wrapper;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto GetReferenceData(const RE::GameScript::RefrOrInventoryObj& a_data)
		-> std::optional<std::pair<RE::TESBoundObject*, RE::BSTSmartPointer<RE::ExtraDataList>>>
	{
		if (a_data.Reference()) {
			const auto ref = a_data.Reference();
			return std::make_pair(ref->GetObjectReference(), ref->extraList);
		} else if (a_data.Container() && a_data.UniqueID()) {
			const auto cont = a_data.Container();
			const auto uniqueID = a_data.UniqueID();
			if (const auto inv = cont->inventoryList; inv) {
				const RE::BSAutoReadLock l{ inv->rwLock };
				for (const auto& item : inv->data) {
					for (auto stack = item.stackData.get(); stack; stack = stack->nextStack.get()) {
						const auto xID =
							stack->extra ?
                                stack->extra->GetByType<RE::ExtraUniqueID>() :
                                nullptr;
						if (xID && xID->uniqueID == uniqueID) {
							return std::make_pair(item.object, stack->extra);
						}
					}
				}
			}
		}

		return std::nullopt;
	}
}
