#include "RE/Scaleform/GFx/Resource.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			ResourceKey Resource::GetKey()
			{
				return ResourceKey();
			}


			UInt32 Resource::GetResourceTypeCode() const
			{
				return MakeTypeCode(ResourceType::kNone);
			}


			ResourceReport* Resource::GetResourceReport()
			{
				return 0;
			}


			UInt32 Resource::MakeTypeCode(ResourceType a_type, ResourceUse a_use)
			{
				return to_underlying(static_cast<ResourceUse>(a_type << ResourceType::kTypeCode_Shift) | a_use);
			}
		}
	}
}
