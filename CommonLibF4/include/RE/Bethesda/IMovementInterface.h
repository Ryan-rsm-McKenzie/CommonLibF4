#pragma once

#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/NetImmerse/NiPoint3.h"

namespace RE
{
	class BSPathingLocation;
	class BSPathingRequest;
	class IMovementParameters;

	namespace Movement
	{
		struct MaxSpeeds;
	}

	struct __declspec(novtable) IMovementInterface
	{
	public:
		static constexpr auto RTTI{ RTTI::IMovementInterface };
		static constexpr auto VTABLE{ VTABLE::IMovementInterface };

		virtual ~IMovementInterface() = default;  // 00
	};
	static_assert(sizeof(IMovementInterface) == 0x8);

	struct __declspec(novtable) IMovementState :
		public IMovementInterface  // 0
	{
	public:
		static constexpr auto RTTI{ RTTI::IMovementState };
		static constexpr auto VTABLE{ VTABLE::IMovementState };

		enum class CHARACTER_STATE;

		// add
		virtual std::uint32_t DoGetNumericID() const = 0;                                                            // 01
		virtual void DoGetPathingLocation(BSPathingLocation& a_retLocation) const = 0;                               // 02
		virtual void DoGetLocation(NiPoint3& a_retLocation) const = 0;                                               // 03
		virtual void DoGetEulerAngles(NiPoint3& a_retAngles) const = 0;                                              // 04
		virtual float DoGetMovementSpeed() const = 0;                                                                // 05
		virtual float DoGetAnimationSpeed() const = 0;                                                               // 06
		virtual float DoGetCurrentSpeed() const = 0;                                                                 // 07
		virtual void DoGetRotationSpeed(NiPoint3& a_outRotationSpeed) const = 0;                                     // 08
		virtual void DoGetMovementRotation(NiPoint3& a_retMovementRotation) const = 0;                               // 09
		virtual bool DoGetCurrentMaxSpeeds(Movement::MaxSpeeds& a_retMaxSpeeds) const = 0;                           // 0A
		virtual float DoGetMovementRadius() const = 0;                                                               // 0B
		virtual float DoGetMovementWidth() const = 0;                                                                // 0C
		virtual float DoGetMovementLength() const = 0;                                                               // 0D
		virtual float DoGetMovementHeight() const = 0;                                                               // 0E
		virtual float DoGetMovementPitch() const = 0;                                                                // 0F
		virtual float DoGetLookingHeight() const = 0;                                                                // 10
		virtual float DoGetPathingRadius() const = 0;                                                                // 11
		virtual bool DoMakeDefaultMovementParameters(BSTSmartPointer<IMovementParameters>& a_parameters) const = 0;  // 12
		virtual const IMovementParameters& DoGetDefaultMovementParameters() const = 0;                               // 13
		virtual float DoGetFlightAngleGain() const = 0;                                                              // 14
		virtual CHARACTER_STATE DoGetCharacterState() const = 0;                                                     // 15
		virtual bool DoGetUseVelocityObstacles() const = 0;                                                          // 16
		virtual std::uint32_t DoGetCollisionFilter() const = 0;                                                      // 17
		virtual bool DoCanRotate() const = 0;                                                                        // 18
		virtual bool DoUpdatePathingRequest(const BSTSmartPointer<BSPathingRequest>& a_request) const = 0;           // 19
		virtual void DoGetFaceTargetSource(NiPoint3& a_location, NiPoint3& a_orientation) const = 0;                 // 1A
		virtual bool DoGetFaceTargetAllowRoll() const = 0;                                                           // 1B
		virtual bool DoShouldDecelerateToStop(float a_currentSpeed, float& a_nonDecelerateStopDistance) const = 0;   // 1C
		virtual void DoGetMaxAngles(NiPoint3& a_maxAngles) const = 0;                                                // 1D
		virtual void DoGetLookingLocation(NiPoint3& a_location) const = 0;                                           // 1E
		virtual void DoGetSprinting() const = 0;                                                                     // 1F
		virtual bool DoIsHovering() const = 0;                                                                       // 20
	};
	static_assert(sizeof(IMovementState) == 0x8);

	struct MovementData
	{
	public:
		// members
		NiPoint3A movementRotation;  // 00
		NiPoint3A rotationSpeed;     // 10
		float movementSpeed;         // 20
	};
	static_assert(sizeof(MovementData) == 0x30);

	struct PlayerControlsMovementData :
		public MovementData  // 00
	{
	public:
		// members
		NiPoint3A targetAngle;  // 30
	};
	static_assert(sizeof(PlayerControlsMovementData) == 0x40);

	struct __declspec(novtable) IMovementPlayerControls :
		public IMovementInterface  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::IMovementPlayerControls };
		static constexpr auto VTABLE{ VTABLE::IMovementPlayerControls };

		// add
		virtual void GetControllerOutput(std::uint32_t a_numericID, PlayerControlsMovementData& a_normalizedOutputData) = 0;  // 01
	};
	static_assert(sizeof(IMovementPlayerControls) == 0x8);

	class __declspec(novtable) IMovementPlayerControlsFilter :
		public IMovementInterface  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::IMovementPlayerControlsFilter };
		static constexpr auto VTABLE{ VTABLE::IMovementPlayerControlsFilter };

		// add
		virtual void FilterControllerOutput(const MovementData& a_previousFrameData, MovementData& a_inOutData, float a_timeDelta) const = 0;  // 01
		virtual bool ShouldPlayLargeDeltas() const = 0;                                                                                        // 02
		virtual bool IsInCombatStance() const = 0;                                                                                             // 03
		virtual bool DampenRotationInput() const = 0;                                                                                          // 04
		virtual bool DampenInput(float& a_acceleration, float& a_deceleration) const = 0;                                                      // 05
		virtual bool IsInThirdPerson() const = 0;                                                                                              // 06
		virtual void FilterDampenedOutput(const MovementData&, MovementData& a_inOutData) const = 0;                                           // 07
		virtual bool ForceWalkBeforeRun() const = 0;                                                                                           // 08
		virtual float GetNormalizedAngleAccelerationMultiplier() const = 0;                                                                    // 09
	};
	static_assert(sizeof(IMovementPlayerControlsFilter) == 0x8);
}
