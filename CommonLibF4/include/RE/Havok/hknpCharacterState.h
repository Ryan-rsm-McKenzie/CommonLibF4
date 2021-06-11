#pragma once

#include "RE/Havok/hkReferencedObject.h"

namespace RE
{
	class hknpCharacterContext;

	struct hknpCharacterInput;
	struct hknpCharacterOutput;

	class __declspec(novtable) hknpCharacterState :
		public hkReferencedObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpCharacterState };
		static constexpr auto VTABLE{ VTABLE::hknpCharacterState };

		enum class hknpCharacterStateType
		{
			kOnGround,
			kJumping,
			kInAir,
			kClimbing,
			kFlying
		};

		// add
		virtual hknpCharacterStateType GetType() = 0;                                                     // 04
		virtual void Update(hknpCharacterContext&, const hknpCharacterInput&, hknpCharacterOutput&) = 0;  // 05
		virtual void Change(hknpCharacterContext&, const hknpCharacterInput&, hknpCharacterOutput&) = 0;  // 06
		virtual void EnterState(
			[[maybe_unused]] hknpCharacterContext& a_context,
			[[maybe_unused]] hknpCharacterStateType a_prevState,
			[[maybe_unused]] const hknpCharacterInput& a_input,
			[[maybe_unused]] hknpCharacterOutput& a_output) { return; }  // 07
		virtual void LeaveState(
			[[maybe_unused]] hknpCharacterContext& a_context,
			[[maybe_unused]] hknpCharacterStateType a_nextState,
			[[maybe_unused]] const hknpCharacterInput& a_input,
			[[maybe_unused]] hknpCharacterOutput& a_output) { return; }  // 08
	};
	static_assert(sizeof(hknpCharacterState) == 0x10);
}
