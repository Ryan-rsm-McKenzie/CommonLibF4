#pragma once

#include "RE/Scaleform/GFx/ResourceKey.h"
#include "RE/Scaleform/AtomicInt.h"
#include "RE/Scaleform/NewOverrideBase.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class ResourceLibBase;
			class ResourceReport;


			class Resource : public NewOverrideBase<kStat_Default_Mem>
			{
			public:
				enum class ResourceType : UInt32
				{
					kCharacterDef_Bit = 0x0080,

					kNone = 0,
					kImage,
					kFont,
					kMovieDef,
					kSoundSample,

					kMovieDataDef = kCharacterDef_Bit | 0,
					kButtonDef,
					kTextDef,
					kEditTextDef,
					kSpriteDef,
					kShapeDef,
					kVideoDef,

					kTypeCode_Mask = 0xFF00,
					kTypeCode_Shift = 8
				};


				enum class ResourceUse : UInt32
				{
					kNone = 0,
					kBitmap = 1,
					kGradient = 2,
					kFontTexture = 3,
					kSoundSample = 4,
					kTypeCode_Mask = 0xFF
				};


				// add
				virtual ResourceKey		GetKey();						// 00
				virtual UInt32			GetResourceTypeCode() const;	// 01
				virtual ResourceReport*	GetResourceReport();			// 02

				static UInt32 MakeTypeCode(ResourceType a_type, ResourceUse a_use = ResourceUse::kNone);

			protected:
				AtomicInt<SInt32>	_refCount;	// 08
				UInt32				_pad0C;		// 0C
				ResourceLibBase*	_lib;		// 10
			};
			STATIC_ASSERT(sizeof(Resource) == 0x18);
		}
	}
}
