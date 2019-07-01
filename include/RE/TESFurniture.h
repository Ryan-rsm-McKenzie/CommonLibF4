#pragma once

#include "RE/BGSAttachParentArray.h"
#include "RE/TESObjectACTI.h"


namespace RE
{
	class TESFurniture : public TESObjectACTI
	{
	public:
		inline static const void* RTTI = RTTI_TESFurniture;


		enum class Flag : UInt32
		{
			kNone = 0,
			kInteractionPoint0 = 1 << 0,
			kInteractionPoint1 = 1 << 1,
			kInteractionPoint2 = 1 << 2,
			kInteractionPoint3 = 1 << 3,
			kInteractionPoint4 = 1 << 4,
			kInteractionPoint5 = 1 << 5,
			kInteractionPoint6 = 1 << 6,
			kInteractionPoint7 = 1 << 7,
			kInteractionPoint8 = 1 << 8,
			kInteractionPoint9 = 1 << 9,
			kInteractionPoint10 = 1 << 10,
			kInteractionPoint11 = 1 << 11,
			kInteractionPoint12 = 1 << 12,
			kInteractionPoint13 = 1 << 13,
			kInteractionPoint14 = 1 << 14,
			kInteractionPoint15 = 1 << 15,
			kInteractionPoint16 = 1 << 16,
			kInteractionPoint17 = 1 << 17,
			kInteractionPoint18 = 1 << 18,
			kInteractionPoint19 = 1 << 19,
			kInteractionPoint20 = 1 << 20,
			kInteractionPoint21 = 1 << 21,
			kAllowAwakeSound = 1 << 22,
			kEnterWithWeaponDrawn = 1 << 23,
			kPlayAnimWhenFull = 1 << 24,
			kDisablesActivation = 1 << 25,
			kIsPerch = 1 << 26,
			kMustExitToTalk = 1 << 27,
			kUseStaticAvoidNode = 1 << 28,
			kHasModel = 1 << 30
		};


		struct Marker
		{
			float	offsetX;	// 00
			float	offsetY;	// 04
			float	offsetZ;	// 08
		};
		//STATIC_ASSERT(sizeof(Marker) == 0x);


		virtual ~TESFurniture();			// 00

		// override (TESObjectACTI)
		virtual void	Unk_07() override;	// 07
		virtual void	Unk_08() override;	// 08
		virtual void	Unk_09() override;	// 09
		virtual void	Unk_16() override;	// 16
		virtual void	Unk_22() override;	// 22
		virtual void	Unk_3F() override;	// 3F
		virtual void	Unk_40() override;	// 40
		virtual void	Unk_5E() override;	// 5E - { return TESBoundObject::Unk_5E(); }
		virtual void	Unk_60() override;	// 60
		virtual void	Unk_61() override;	// 61


		// members
		UInt64					unk140;				// 140
		BSTArray<void*>			unk148;				// 148
		BGSAttachParentArray	unk160;				// 160
		UInt32					unk178;				// 178
		Flag					flags;				// 17C - MNAM
		UInt64					unk180;				// 180
		BSTArray<Marker>		markerParameters;	// 188 - SNAM
	};
	STATIC_ASSERT(sizeof(TESFurniture) == 0x1A0);
}
