#include "RE/Scaleform/GFx/StateBag.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			StateBag* StateBag::GetStateBagImpl() const
			{
				return 0;
			}


			void StateBag::SetState(State::StateType a_stateType, State* a_state)
			{
				auto stateBag = GetStateBagImpl();
				assert((a_state == 0) ? true : (a_state->GetStateType() == a_stateType));
				if (stateBag) {
					stateBag->SetState(a_stateType, a_state);
				}
			}


			State* StateBag::GetStateAddRef(State::StateType a_stateType) const
			{
				auto stateBag = GetStateBagImpl();
				return stateBag ? stateBag->GetStateAddRef(a_stateType) : 0;
			}


			void StateBag::GetStatesAddRef(State** a_stateList, const State::StateType* a_stateTypes, UInt32 a_count) const
			{
				auto stateBag = GetStateBagImpl();
				if (stateBag) {
					stateBag->GetStatesAddRef(a_stateList, a_stateTypes, a_count);
				}
			}
		}
	}
}
