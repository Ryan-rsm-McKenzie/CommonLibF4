#include "RE/Scaleform/GFx/CharacterDef.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			CharacterDef::CharacterDef()
				: _id(ResourceID::kInvalidID)
			{}


			bool CharacterDef::DefPointTestLocal(const Render::PointF& a_pt, bool a_testShape, const DisplayObjectBase* a_inst) const
			{
				return false;
			}


			Render::RectF CharacterDef::GetBoundsLocal() const
			{
				return Render::RectF();
			}


			Render::RectF CharacterDef::GetRectBoundsLocal() const
			{
				return Render::RectF();
			}


			UInt32 CharacterDef::GetVersion() const
			{
				return 0;
			}
		}
	}
}
