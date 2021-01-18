#pragma once

namespace RE
{
	namespace UserEvents
	{
		enum class USER_EVENT_FLAG
		{
			kAll = static_cast<std::underlying_type_t<USER_EVENT_FLAG>>(-1),

			kMovement = 1 << 0,
			kLooking = 1 << 1,
			kActivate = 1 << 2,
			kMenu = 1 << 3,
			kConsole = 1 << 4,
			kPOVSwitch = 1 << 5,
			kFighting = 1 << 6,
			kSneaking = 1 << 7,
			kMainFour = 1 << 8,
			kWheelZoom = 1 << 9,
			kJumping = 1 << 10,
			kVATS = 1 << 11
		};

		enum class INPUT_CONTEXT_ID
		{
			kMainGameplay = 0,
			kBasicMenuNav,
			kThumbNav,
			kVirtualController,
			kCursor,
			kLThumbCursor,
			kConsole,
			kDebugText,
			kBook,
			kDebugOverlay,
			kTFC,
			kDebugMap,
			kLockpick,
			kVATS,
			kVATSPlayback,
			kMultiActivate,
			kWorkshop,
			kScope,
			kSitWait,
			kLooksMenu,
			kWorkshopAddendum,
			kPauseMenu,
			kLevelupMenu,
			kLevelupMenuPrevNext,
			kMainMenu,
			kQuickContainerMenu,
			kSpecialActivateRollover,
			kTwoButtonRollover,
			kQuickContainerMenuPerk,
			kVertiBird,
			kPlayBinkMenu,
			kRobotModAddendum,
			kCreationClub,

			kTotal,

			kNone
		};

		enum class SENDER_ID
		{
			kNone,
			kGameplay,
			kMenu,
			kScript
		};
	}
}
