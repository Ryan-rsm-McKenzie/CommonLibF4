#include "RE/Condition.h"


namespace RE
{
	Condition::operator bool() const
	{
		return root != 0;
	}
}
