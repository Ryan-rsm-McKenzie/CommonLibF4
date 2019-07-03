#include "RE/Scaleform/GFx/ResourceID.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			UPInt ResourceID::HashOp::operator()(const ResourceID& a_idRef)
			{
				return (a_idRef._id ^ (a_idRef._id >> (16 - 8)));
			}


			ResourceID::ResourceID(IDType a_id) :
				_id(a_id)
			{}
		}
	}
}
