#include "RE/Bethesda/FormComponents.h"

#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/FormUtil.h"
#include "RE/Bethesda/TESForms.h"

namespace RE
{
	std::string_view TESFullName::GetFullName(const TESForm& a_obj, bool a_strict)
	{
		if (const auto fullName = a_obj.As<TESFullName>(); fullName) {
			const auto name = fullName->GetFullName();
			return name ? name : ""sv;
		} else {
			if (a_strict) {
				switch (a_obj.GetFormType()) {
				case ENUM_FORM_ID::kKYWD:  // BGSKeyword
				case ENUM_FORM_ID::kLCRT:  // BGSLocationRefType
				case ENUM_FORM_ID::kAACT:  // BGSAction
				case ENUM_FORM_ID::kLIGH:  // TESObjectLIGH
				case ENUM_FORM_ID::kSTAT:  // TESObjectSTAT
				case ENUM_FORM_ID::kSCOL:  // BGSStaticCollection
				case ENUM_FORM_ID::kMSTT:  // BGSMovableStatic
				case ENUM_FORM_ID::kFLST:  // BGSListForm
					break;
				default:
					return ""sv;
				}
			}

			const auto& map = GetSparseFullNameMap();
			const auto it = map.find(std::addressof(a_obj));
			return it != map.end() ? it->second : ""sv;
		}
	}
}
