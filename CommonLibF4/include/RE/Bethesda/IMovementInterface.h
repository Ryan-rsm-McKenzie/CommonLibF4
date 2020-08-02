#pragma once

#include "RE/NetImmerse/NiPoint3.h"

namespace RE
{
	struct MovementData
	{
	public:
		// members
		NiPoint3A movementRotation;	 // 00
		NiPoint3A rotationSpeed;	 // 10
		float movementSpeed;		 // 20
	};
	static_assert(sizeof(MovementData) == 0x30);

	class IMovementInterface
	{
	public:
		static constexpr auto RTTI{ RTTI_IMovementInterface };

		virtual ~IMovementInterface();	// 00
	};
	static_assert(sizeof(IMovementInterface) == 0x8);

	struct PlayerControlsMovementData :
		public MovementData	 // 00
	{
	public:
		// members
		NiPoint3A targetAngle;	// 30
	};
	static_assert(sizeof(PlayerControlsMovementData) == 0x40);

	class IMovementPlayerControls :
		public IMovementInterface  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_IMovementPlayerControls };

		// add
		virtual void GetControllerOutput(std::uint32_t a_numericID, PlayerControlsMovementData& a_normalizedOutputData) = 0;  // 01
	};
	static_assert(sizeof(IMovementPlayerControls) == 0x8);
}
