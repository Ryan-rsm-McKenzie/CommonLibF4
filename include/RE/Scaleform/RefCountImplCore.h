#pragma once


namespace RE
{
	namespace Scaleform
	{
		class RefCountImplCore
		{
		public:
			inline static const void* RTTI = RTTI_Scaleform__RefCountImplCore;


			RefCountImplCore();
			virtual ~RefCountImplCore() = default;	// 00

			SInt32 GetRefCount() const;
			void operator=(const RefCountImplCore&);

			FO_HEAP_REDEFINE_NEW();

		protected:
			// members
			volatile SInt32	_refCount;	// 08
			UInt32			_pad0C;		// 0C
		};
		STATIC_ASSERT(sizeof(RefCountImplCore) == 0x10);
	}
}
