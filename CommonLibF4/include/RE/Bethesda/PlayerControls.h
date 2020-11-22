#pragma once

#include "RE/Bethesda/BSInputEventReceiver.h"
#include "RE/Bethesda/BSInputEventUser.h"
#include "RE/Bethesda/BSPointerHandle.h"
#include "RE/Bethesda/BSSpring.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTSingleton.h"
#include "RE/Bethesda/IMovementInterface.h"
#include "RE/NetImmerse/NiPoint2.h"
#include "RE/NetImmerse/NiPoint3.h"

namespace RE
{
	class MenuModeChangeEvent;
	class MenuOpenCloseEvent;
	class QuickContainerStateEvent;
	class UserEventEnabledEvent;

	struct ActivateHandler;
	struct AttackBlockHandler;
	struct AutoMoveHandler;
	struct GrabRotationHandler;
	struct JumpHandler;
	struct LookHandler;
	struct MeleeThrowHandler;
	struct MovementHandler;
	struct ReadyWeaponHandler;
	struct RunHandler;
	struct SneakHandler;
	struct SprintHandler;
	struct TESFurnitureEvent;
	struct TogglePOVHandler;
	struct ToggleRunHandler;

	struct PlayerControlsData
	{
	public:
		// members
		NiPoint2 moveInputVec;                                // 00
		NiPoint2 lookInputVec;                                // 08
		NiPoint2 lookInputVecNormalized;                      // 10
		NiPoint2 prevMoveVec;                                 // 18
		NiPoint2 prevLookVec;                                 // 20
		BSSpring::SpringState<NiPoint3> rotationSpeedSpring;  // 28
		bool autoMove;                                        // 44
		bool running;                                         // 45
		bool togglePOV;                                       // 46
		bool vanityModeEnabled;                               // 47
		bool checkHeldStates;                                 // 48
		bool setupHeldStatesForRelease;                       // 49
	};
	static_assert(sizeof(PlayerControlsData) == 0x4C);

	class PlayerInputHandler :
		public BSInputEventUser  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::PlayerInputHandler };
		static constexpr auto VTABLE{ VTABLE::PlayerInputHandler };

		explicit constexpr PlayerInputHandler(PlayerControlsData& a_data) noexcept :
			data(a_data)
		{}

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~PlayerInputHandler() = default;  // 00

		// add
		virtual void PerFrameUpdate() { return; };  // 09

		// members
		PlayerControlsData& data;        // 10
		bool inQuickContainer{ false };  // 18
	};
	static_assert(sizeof(PlayerInputHandler) == 0x20);

	class HeldStateHandler :
		public PlayerInputHandler  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::HeldStateHandler };
		static constexpr auto VTABLE{ VTABLE::HeldStateHandler };

		explicit constexpr HeldStateHandler(PlayerControlsData& a_data) noexcept :
			PlayerInputHandler(a_data)
		{}

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~HeldStateHandler() = default;  // 00

		// add
		virtual void UpdateHeldStateActive(const ButtonEvent* a_event)  // 10
		{
			heldStateActive = a_event && (a_event->value != 0.0F || a_event->heldDownSecs < 0.0F);
		}

		virtual void SetHeldStateActive(bool a_flag) { heldStateActive = a_flag; }  // 11

		// members
		bool heldStateActive{ false };      // 20
		bool triggerReleaseEvent{ false };  // 21
	};
	static_assert(sizeof(HeldStateHandler) == 0x28);

	class __declspec(novtable) PlayerControls :
		BSInputEventReceiver,                    // 000
		BSTEventSink<MenuOpenCloseEvent>,        // 010
		BSTEventSink<MenuModeChangeEvent>,       // 018
		BSTEventSink<TESFurnitureEvent>,         // 020
		BSTEventSink<UserEventEnabledEvent>,     // 028
		IMovementPlayerControls,                 // 030
		BSTEventSink<QuickContainerStateEvent>,  // 038
		BSTSingletonSDM<PlayerControls>          // 040
	{
	public:
		static constexpr auto RTTI{ RTTI::PlayerControls };
		static constexpr auto VTABLE{ VTABLE::PlayerControls };

		static PlayerControls* GetSingleton()
		{
			REL::Relocation<PlayerControls**> singleton{ REL::ID(544871) };
			return *singleton;
		}

		void RegisterHandler(PlayerInputHandler* a_handler) { DoRegisterHandler(a_handler, false); }
		void RegisterHandler(HeldStateHandler* a_handler) { DoRegisterHandler(a_handler, true); }

		// members
		PlayerControlsData data;                        // 044
		BSTArray<PlayerInputHandler*> handlers;         // 090
		BSTArray<HeldStateHandler*> heldStateHandlers;  // 0A8
		std::uint32_t topGraphPoint[3];                 // 0C0
		float graphPoints[3][10][2];                    // 0CC
		BSTArray<ActorHandle> actionInterestedActors;   // 1C0
		BSSpinLock actorArraySpinLock;                  // 1D8
		MovementHandler* movementHandler;               // 1E0
		LookHandler* lookHandler;                       // 1E8
		SprintHandler* sprintHandler;                   // 1F0
		ReadyWeaponHandler* readyWeaponHandler;         // 1F8
		AutoMoveHandler* autoMoveHandler;               // 200
		ToggleRunHandler* toggleRunHandler;             // 208
		ActivateHandler* activateHandler;               // 210
		JumpHandler* jumpHandler;                       // 218
		AttackBlockHandler* attackHandler;              // 220
		RunHandler* runHandler;                         // 228
		SneakHandler* sneakHandler;                     // 230
		TogglePOVHandler* togglePOVHandler;             // 238
		MeleeThrowHandler* meleeThrowHandler;           // 240
		GrabRotationHandler* grabRotationHandler;       // 248
		bool notifyingHandlers;                         // 250
		bool blockPlayerInput;                          // 251
		float cameraAutoRotationX;                      // 254
		float cameraAutoRotationY;                      // 258

	private:
		void DoRegisterHandler(PlayerInputHandler* a_handler, bool a_isHeldStateHandler)
		{
			using func_t = decltype(&PlayerControls::DoRegisterHandler);
			REL::Relocation<func_t> func{ REL::ID(177801) };
			return func(this, a_handler, a_isHeldStateHandler);
		}
	};
	static_assert(sizeof(PlayerControls) == 0x260);
}
