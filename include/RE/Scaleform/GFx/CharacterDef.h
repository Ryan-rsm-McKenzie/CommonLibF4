#pragma once

#include "RE/Scaleform/GFx/Resource.h"
#include "RE/Scaleform/GFx/ResourceID.h"
#include "RE/Scaleform/Render/Rect.h"
#include "RE/Scaleform/Render/Point.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class DisplayContext;
			class DisplayObjectBase;


			class CharacterDef : public Resource
			{
			public:
				enum class CharacterDefType : UInt32
				{
					kUnknown,
					kShape,
					kMovieData,
					kSprite,
					kTextField,
					kStaticText,
					kButton,
					kVideo,
					kBitmap,

					kEmptySprite
				};


				enum
				{
					kEmptyMovieClip = ResourceID::IDType::kInternalConstant | 1,
					kEmptyTextField = ResourceID::IDType::kInternalConstant | 2,
					kEmptyButton = ResourceID::IDType::kInternalConstant | 3,
					kEmptyShape = ResourceID::IDType::kInternalConstant | 4,
					kEmptyVideo = ResourceID::IDType::kInternalConstant | 5,
					kImageMovieDef_ImageResource = 0,
					kImageMovieDef_ShapeDef = 1
				};


				CharacterDef();
				virtual ~CharacterDef() = default;																												// 03

				// add
				virtual CharacterDefType	GetType() const = 0;																								// 04
				virtual void				Display(DisplayContext& a_context, DisplayObjectBase* a_instanceInfo);												// 05
				virtual bool				DefPointTestLocal(const Render::PointF& a_pt, bool a_testShape = false, const DisplayObjectBase* a_inst = 0) const;	// 06
				virtual Render::RectF		GetBoundsLocal() const;																								// 07
				virtual Render::RectF		GetRectBoundsLocal() const;																							// 08
				virtual UInt32				GetVersion() const;																									// 09

			protected:
				ResourceID	_id;	// 18
				UInt32		_pad0C;	// 1C
			};
			STATIC_ASSERT(sizeof(CharacterDef) == 0x20);
		}
	}
}
