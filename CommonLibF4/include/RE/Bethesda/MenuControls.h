#pragma once

#include "RE/Bethesda/BSInputEventReceiver.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTSingleton.h"

namespace RE
{
	class BSInputEventUser;

	struct CameraZoomHandler;
	struct ClickHandler;
	struct DisconnectHandler;
	struct GFxConvertHandler;
	struct MenuOpenHandler;
	struct PipboyHandler;
	struct QuickSaveLoadHandler;
	struct ScreenshotHandler;

	class MenuControls :
		public BSInputEventReceiver,          // 00
		public BSTSingletonSDM<MenuControls>  // 10
	{
	public:
		[[nodiscard]] static MenuControls* GetSingleton()
		{
			REL::Relocation<MenuControls**> singleton{ REL::ID(520890) };
			return *singleton;
		}

		// members
		BSTArray<BSInputEventUser*> handlers;        // 18
		GFxConvertHandler* convertHandler;           // 30
		DisconnectHandler* disconnectHandler;        // 38
		ClickHandler* clickHandler;                  // 40
		QuickSaveLoadHandler* quickSaveLoadHandler;  // 48
		MenuOpenHandler* menuOpenHandler;            // 50
		ScreenshotHandler* screenshotHandler;        // 58
		CameraZoomHandler* cameraZoomHandler;        // 60
		PipboyHandler* pipboyHandler;                // 68
	};
	static_assert(sizeof(MenuControls) == 0x70);
}
