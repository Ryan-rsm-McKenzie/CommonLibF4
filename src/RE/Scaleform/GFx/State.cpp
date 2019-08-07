#include "RE/Scaleform/GFx/State.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			State::State(StateType a_state) :
				_type(a_state),
				_pad14(0)
			{}


			auto State::GetStateType() const
				-> StateType
			{
				return _type;
			}
		}
	}
}
