#pragma once


namespace RE
{
	namespace Scaleform
	{
		template <class T>
		class AtomicValueBase
		{
		public:
			volatile T value;
		};
	}
}
