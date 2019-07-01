#pragma once

#include "RE/TESBoundObject.h"


namespace RE
{
	class TESBoundAnimObject : public TESBoundObject
	{
	public:
		inline static const void* RTTI = RTTI_TESBoundAnimObject;


		virtual ~TESBoundAnimObject();		// 00

		// override (TESBoundObject)
		virtual void	Unk_4A() override;	// 4A - { return 1; }
		virtual void	Unk_5F() override;	// 5F
	};
	STATIC_ASSERT(sizeof(TESBoundAnimObject) == 0x68);
}
