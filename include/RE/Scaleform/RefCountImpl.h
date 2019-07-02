#pragma once

#include "RE/Scaleform/RefCountImplCore.h"


namespace RE
{
	namespace Scaleform
	{
		class RefCountImpl : public RefCountImplCore
		{
		public:
			inline static const void* RTTI = RTTI_Scaleform__RefCountImpl;


			virtual ~RefCountImpl() = default;	// 00

			void	AddRef();
			void	Release();
		};
		STATIC_ASSERT(sizeof(RefCountImpl) == 0x10);
	}
}
