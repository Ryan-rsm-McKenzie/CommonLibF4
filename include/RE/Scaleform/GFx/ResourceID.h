#pragma once


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class ResourceID
			{
			public:
				enum IDType : UInt32
				{
					kIndexMask = 0x0000FFFFu,
					kTypeMask = 0x0FFF0000u,

					kSWF = 0x00000,
					kStatic = 0x10000,
					kExport = 0x20000,
					kGenMask = 0x30000,

					kTypeShift = 18,

					kInvalidID = (1 << kTypeShift) | kSWF,

					kNone = 0,
					kInternalConstant = (0 << kTypeShift) | kStatic,
					kGradientImage = (1 << kTypeShift) | kStatic,
					kDynFontImage = (2 << kTypeShift) | kStatic,
					kFontImage = (1 << kTypeShift) | kExport
				};


				class HashOp
				{
				public:
					UPInt operator()(const ResourceID& a_idRef);
				};
				STATIC_ASSERT(sizeof(HashOp) == 0x1);


				ResourceID(IDType a_id);

			protected:
				UInt32 _id;	// 0
			};
			STATIC_ASSERT(sizeof(ResourceID) == 0x4);
		}
	}
}
