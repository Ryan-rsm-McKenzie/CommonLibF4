#pragma once


namespace RE
{
	namespace Scaleform
	{
		class Lock
		{
		public:
			class Locker
			{
			public:
				Locker(Lock& a_lock);
				~Locker();


				// members
				Lock* _lock;	// 0
			};
			STATIC_ASSERT(sizeof(Locker) == 0x8);


			void lock();
			void unlock();


			// members
			CRITICAL_SECTION cs;	// 00
		};
		STATIC_ASSERT(sizeof(Lock) == 0x28);
	}
}
