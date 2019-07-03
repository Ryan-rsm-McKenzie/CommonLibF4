#pragma once

#include <cassert>

#include "RE/Scaleform/GFx/FileTypeConstants.h"
#include "RE/Scaleform/GFx/State.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class StateBag : public FileTypeConstants
			{
			protected:
				// add
				virtual StateBag* GetStateBagImpl() const;																			// 00

			public:
				virtual ~StateBag() = default;																						// 01

				virtual void	SetState(State::StateType a_stateType, State* a_state);												// 02
				virtual State*	GetStateAddRef(State::StateType a_stateType) const;													// 03
				virtual void	GetStatesAddRef(State** a_stateList, const State::StateType* a_stateTypes, UInt32 a_count) const;	// 04
			};
			STATIC_ASSERT(sizeof(StateBag) == 0x8);
		}
	}
}
