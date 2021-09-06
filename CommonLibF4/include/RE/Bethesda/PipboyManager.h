#pragma once

#include "RE/Bethesda/BGSInventoryInterface.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSInputEventUser.h"
#include "RE/Bethesda/BSPointerHandle.h"
#include "RE/Bethesda/BSSoundHandle.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTPoint.h"
#include "RE/Bethesda/BSTSingleton.h"
#include "RE/Bethesda/Inventory3DManager.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class BGSNote;
	class BGSTerminal;
	class BSTriShape;
	class TESBoundObject;

	class IsPipboyActiveEvent :
		public BSTValueEvent<bool>  // 0
	{
	public:
	};
	static_assert(sizeof(IsPipboyActiveEvent) == 0x2);

	class PipboyRadioController
	{
	public:
		// members
		float chaseStation;  // 0
	};
	static_assert(sizeof(PipboyRadioController) == 0x4);

	struct BSAnimationGraphEvent;

	class __declspec(novtable) PipboyManager :
		public BSTSingletonSDM<PipboyManager>,       // 018
		public BSTEventSink<BSAnimationGraphEvent>,  // 000
		public BSInputEventUser                      // 008
	{
	public:
		static constexpr auto RTTI{ RTTI::PipboyManager };
		static constexpr auto VTABLE{ VTABLE::PipboyManager };

		enum class LOWER_REASON : std::int32_t
		{
			kNone,
			kBook,
			kPerkGrid,
			kInspect
		};

		[[nodiscard]] static PipboyManager* GetSingleton()
		{
			REL::Relocation<PipboyManager**> singleton{ REL::ID(553234) };
			return *singleton;
		}

		void RefreshPipboyRenderSurface()
		{
			using func_t = decltype(&PipboyManager::RefreshPipboyRenderSurface);
			REL::Relocation<func_t> func{ REL::ID(81339) };
			return func(this);
		}

		void UpdateCursorConstraint(bool a_enable)
		{
			using func_t = decltype(&PipboyManager::UpdateCursorConstraint);
			REL::Relocation<func_t> func{ REL::ID(900802) };
			return func(this, a_enable);
		}

		// members
		BSSoundHandle pipboyHumSound;                                 //
		BSTPoint2<float> inputVector;                                 //
		BSTPoint2<float> newInput;                                    //
		NiPointer<BSTriShape> debugModeGeom;                          //
		Inventory3DManager modelManager;                              //
		BGSNote* holotapeToLoad;                                      //
		BGSTerminal* terminalToLoad;                                  //
		BSFixedString menuToOpen;                                     //
		BSFixedString openAnimEvent;                                  //
		BSFixedString closeAnimEvent;                                 //
		stl::enumeration<LOWER_REASON, std::int32_t> loweringReason;  //
		PipboyRadioController radioController;                        //
		TESBoundObject* itemAnimOnClose;                              //
		ObjectRefHandle fastTravelLocation;                           //
		InventoryInterface::Handle inspectRequestItem;                //
		std::uint32_t inspectRequestStack;                            //
		bool pipboyExamineMode;                                       //
		bool pipboyExamineDirtyFlag;                                  //
		bool pipboyOpening;                                           //
		bool pipboyClosing;                                           //
		BSTValueEventSource<IsPipboyActiveEvent> pipboyActive;        //
		bool ignoreOpeningFlag;                                       //
		bool autoSaveOnClose;                                         //
		bool pipboyMenuCloseQueued;                                   //
		bool pipboyRaising;                                           //
		bool wasMotionBlurActive;                                     //
		bool wasPipboyLightActive;                                    //
	};
	static_assert(sizeof(PipboyManager) == 0x1F0);
}
