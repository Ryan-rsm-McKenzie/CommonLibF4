#pragma once

#include <cassert>


namespace RE
{
	namespace Scaleform
	{
		template <class Child, class Parent>
		class SysAllocBase_SingletonSupport : public Parent
		{
		public:
			struct SysAllocContainer
			{
				SysAllocContainer() :
					initialized(false)
				{}


				// members
				UPInt	data[(sizeof(Child) + sizeof(UPInt) - 1) / sizeof(UPInt)];	// 00 - forcing alignment?
				bool	initialized;												// ??
			};


			SysAllocBase_SingletonSupport() :
				_container(0)
			{}


			virtual bool ShutdownHeapEngine()	// ??
			{
				bool hasNoLeaks = Parent::ShutdownHeapEngine();
				if (_container) {
					_container->initialized = false;
					((Parent*)this)->~Parent();
					_container = 0;
				}
				return hasNoLeaks;
			}


			static Parent* InitSystemSingleton()
			{
				static SysAllocContainer container;
				assert(container.initialized == false);

				auto result = ::new((void*)container.data) Child{};
				result->_container = &container;
				container.initialized = true;

				return result;
			}


			// members
			SysAllocContainer* _container;	// ??
		};
		// size == sizeof(Parent) + 0x8
	}
}
