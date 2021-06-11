#pragma once

#include "RE/Havok/hkBaseTypes.h"
#include "RE/Havok/hkReferencedObject.h"
#include "RE/Havok/hkVector4.h"
#include "RE/Havok/hknpCharacterState.h"

namespace RE
{
	class hknpCharacterStateManager;

	class __declspec(novtable) hknpCharacterContext :
		public hkReferencedObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpCharacterContext };
		static constexpr auto VTABLE{ VTABLE::hknpCharacterContext };

		enum class CharacterType
		{
			kProxy,
			kRigidBody
		};

		// members
		stl::enumeration<CharacterType, std::int32_t> characterType;                               // 10
		hknpCharacterStateManager* stateManager;                                                   // 18
		stl::enumeration<hknpCharacterState::hknpCharacterStateType, std::int32_t> currentState;   // 20
		stl::enumeration<hknpCharacterState::hknpCharacterStateType, std::int32_t> previousState;  // 24
		hkBool filterEnable;                                                                       // 28
		float maxLinearAcceleration;                                                               // 2C
		float maxLinearSpeed;                                                                      // 30
		float gain;                                                                                // 34
		hkVector4f previousSurfaceVelocity;                                                        // 40
		std::int32_t numUpdatesInCurrentState;                                                     // 50
	};
	static_assert(sizeof(hknpCharacterContext) == 0x60);
}
