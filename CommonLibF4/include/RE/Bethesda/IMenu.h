#pragma once

#include "RE/Bethesda/Atomic.h"
#include "RE/Bethesda/BGSCreatedObjectManager.h"
#include "RE/Bethesda/BGSInventoryItem.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSInputEventUser.h"
#include "RE/Bethesda/BSPointerHandle.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTInterpolator.h"
#include "RE/Bethesda/BSTOptional.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTTuple.h"
#include "RE/Bethesda/SWFToCodeFunctionHandler.h"
#include "RE/Bethesda/TESForms.h"
#include "RE/Bethesda/UIMessage.h"
#include "RE/Bethesda/UserEvents.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiMatrix3.h"
#include "RE/NetImmerse/NiPoint2.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiQuaternion.h"
#include "RE/NetImmerse/NiRect.h"

namespace RE
{
	namespace Workshop
	{
		struct BuildableAreaEvent;
		struct PlacementStatusEvent;
	}

	class BSGFxShaderFXTarget;
	class ButtonHintBar;
	class ExtraDataList;
	class NiAVObject;
	class TESBoundObject;
	class TESForm;
	class TESObjectREFR;
	class UserEventEnabledEvent;
	class WorkshopMenuGeometry;

	struct LoadedInventoryModel;
	struct PickRefUpdateEvent;

	enum class MENU_RENDER_CONTEXT : std::int32_t
	{
		kMenuDelete,
		kPreDisplay,
		kRenderScreenspace,
		kRenderCopyQuads,
		kRenderImagespace,
		kEnsureDisplayMenuCalled,
		kPostDisplay
	};

	enum class UI_MENU_FLAGS : std::uint32_t
	{
		kPausesGame = 1 << 0,
		kAlwaysOpen = 1 << 1,
		kUsesCursor = 1 << 2,
		kUsesMenuContext = 1 << 3,
		kModal = 1 << 4,
		kFreezeFrameBackground = 1 << 5,
		kOnStack = 1 << 6,
		kDisablePauseMenu = 1 << 7,
		kRequiresUpdate = 1 << 8,
		kTopmostRenderedMenu = 1 << 9,
		kUpdateUsesCursor = 1 << 10,
		kAllowSaving = 1 << 11,
		kRendersOffscreenTargets = 1 << 12,
		kInventoryItemMenu = 1 << 13,
		kDontHideCursorWhenTopmost = 1 << 14,
		kCustomRendering = 1 << 15,
		kAssignCursorToRenderer = 1 << 16,
		kApplicationMenu = 1 << 17,
		kHasButtonBar = 1 << 18,
		kIsTopButtonBar = 1 << 19,
		kAdvancesUnderPauseMenu = 1 << 20,
		kRendersUnderPauseMenu = 1 << 21,
		kUsesBlurredBackground = 1 << 22,
		kCompanionAppAllowed = 1 << 23,
		kFreezeFramePause = 1 << 24,
		kSkipRenderDuringFreezeFrameScreenshot = 1 << 25,
		kLargeScaleformRenderCacheMode = 1 << 26,
		kUsesMovementToDirection = 1 << 27
	};

	class IMenu :
		public SWFToCodeFunctionHandler,  // 00
		public BSInputEventUser           // 10
	{
	public:
		static constexpr auto RTTI{ RTTI::IMenu };
		static constexpr auto VTABLE{ VTABLE::IMenu };

		using SWFToCodeFunctionHandler::operator new;
		using SWFToCodeFunctionHandler::operator delete;

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~IMenu()  // 00
		{
			if (uiMovie) {
				const auto id = Scaleform::GetCurrentThreadId();
				uiMovie->SetCaptureThread(id);

				const auto heap = uiMovie->GetHeap();
				if (heap) {
					heap->AssignToCurrentThread();
				}
			}
		}

		// override (BSInputEventUser)
		bool ShouldHandleEvent(const InputEvent* a_event) override  // 01
		{
			using func_t = decltype(&IMenu::ShouldHandleEvent);
			REL::Relocation<func_t> func{ REL::ID(1241790) };
			return func(this, a_event);
		}

		void HandleEvent(const ButtonEvent* a_event) override  // 08
		{
			if (menuObj.IsObject()) {
				using func_t = decltype(&IMenu::HandleEvent);
				REL::Relocation<func_t> func{ REL::ID(1414130) };
				return func(this, a_event);
			}
		}

		// add
		virtual UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message)  // 03
		{
			switch (*a_message.type) {
			case UI_MESSAGE_TYPE::kShow:
			case UI_MESSAGE_TYPE::kHide:
				return UI_MESSAGE_RESULTS::kHandled;
			case UI_MESSAGE_TYPE::kScaleformEvent:
				return ProcessScaleformEvent(uiMovie.get(), a_message.QData());
			case UI_MESSAGE_TYPE::kUpdateController:
				RefreshPlatform();
				return UI_MESSAGE_RESULTS::kPassOn;
			default:
				return UI_MESSAGE_RESULTS::kPassOn;
			}
		}

		virtual void AdvanceMovie(float a_timeDelta, [[maybe_unused]] std::uint64_t a_time)  // 04
		{
			if (uiMovie) {
				DoAdvanceMovie(a_timeDelta);
				hasDoneFirstAdvanceMovie = true;
			}
		}

		virtual void PreDisplay() { return; }   // 05
		virtual void PostDisplay() { return; }  // 06

		virtual bool PassesRenderConditionText(MENU_RENDER_CONTEXT a_reason, const BSFixedString& a_customRendererName) const  // 07
		{
			using func_t = decltype(&IMenu::PassesRenderConditionText);
			REL::Relocation<func_t> func{ REL::ID(937304) };
			return func(this, a_reason, a_customRendererName);
		}

		virtual void SetIsTopButtonBar([[maybe_unused]] bool a_isTopButtonBar) { return; }  // 08

		virtual void OnMenuStackChanged(const BSFixedString& a_topMenuName, bool a_passesTopMenuTest)  // 09
		{
			const bool topMenuTest = a_passesTopMenuTest || (a_topMenuName == "PauseMenu"sv && RendersUnderPauseMenu());
			if (passesTopMenuTest != topMenuTest) {
				passesTopMenuTest = topMenuTest;
				OnMenuDisplayStateChanged();
			}
		}

		virtual void OnMenuDisplayStateChanged() { return; }  // 0A

		virtual void OnAddedToMenuStack()  // 0B
		{
			menuFlags.set(UI_MENU_FLAGS::kOnStack);
			OnMenuDisplayStateChanged();
		}

		virtual void OnRemovedFromMenuStack()  // 0C
		{
			menuFlags.reset(UI_MENU_FLAGS::kOnStack);
			OnMenuDisplayStateChanged();
		}

		virtual bool CanAdvanceMovie(bool a_pauseMenuShowing)  // 0D
		{
			return !a_pauseMenuShowing || depthPriority > 10 || AdvancesUnderPauseMenu();
		}

		virtual bool CanHandleWhenDisabled([[maybe_unused]] const ButtonEvent* a_event) { return false; }                      // 0E
		virtual bool OnButtonEventRelease([[maybe_unused]] const BSFixedString& a_eventName) { return false; }                 // 0F
		virtual bool CacheShaderFXQuadsForRenderer_Impl() { return false; }                                                    // 10
		virtual void TransferCachedShaderFXQuadsForRenderer([[maybe_unused]] const BSFixedString& a_rendererName) { return; }  // 11
		virtual void SetViewportRect([[maybe_unused]] const NiRect<float>& a_viewportRect) { return; }                         // 12

		[[nodiscard]] constexpr bool AdvancesUnderPauseMenu() const noexcept { return menuFlags.all(UI_MENU_FLAGS::kAdvancesUnderPauseMenu); }

		void DoAdvanceMovie(float a_timeDelta)
		{
			++advanceWithoutRenderCount;
			uiMovie->Advance(a_timeDelta);
		}

		[[nodiscard]] bool IsMenuDisplayEnabled() const noexcept
		{
			return passesTopMenuTest && menuCanBeVisible;
		}

		void OnSetSafeRect()
		{
			using func_t = decltype(&IMenu::RefreshPlatform);
			REL::Relocation<func_t> func{ REL::ID(964859) };
			return func(this);
		}

		[[nodiscard]] bool OnStack() const noexcept { return menuFlags.all(UI_MENU_FLAGS::kOnStack); }

		UI_MESSAGE_RESULTS ProcessScaleformEvent(Scaleform::GFx::Movie* a_movie, const IUIMessageData* a_data)
		{
			using func_t = decltype(&IMenu::ProcessScaleformEvent);
			REL::Relocation<func_t> func{ REL::ID(150211) };
			return func(this, a_movie, a_data);
		}

		void RefreshPlatform()
		{
			using func_t = decltype(&IMenu::RefreshPlatform);
			REL::Relocation<func_t> func{ REL::ID(1071829) };
			return func(this);
		}

		[[nodiscard]] constexpr bool RendersUnderPauseMenu() const noexcept { return menuFlags.all(UI_MENU_FLAGS::kRendersUnderPauseMenu); }

		void SetMenuCodeObject(Scaleform::GFx::Movie& a_movie, stl::zstring a_menuObjPath)
		{
			a_movie.GetVariable(std::addressof(menuObj), a_menuObjPath.data());
			RegisterCodeObject(a_movie, menuObj);
		}

		void UpdateFlag(UI_MENU_FLAGS a_flag, bool a_set) noexcept
		{
			if (a_set) {
				menuFlags.set(a_flag);
			} else {
				menuFlags.reset(a_flag);
			}
		}

		// members
		Scaleform::GFx::Value menuObj;                                                                                     // 20
		Scaleform::Ptr<Scaleform::GFx::Movie> uiMovie;                                                                     // 40
		BSFixedString customRendererName;                                                                                  // 48
		BSFixedString menuName;                                                                                            // 50
		stl::enumeration<UI_MENU_FLAGS, std::uint32_t> menuFlags;                                                          // 58
		BSTAtomicValue<std::uint32_t> advanceWithoutRenderCount{ 0 };                                                      // 5C
		bool passesTopMenuTest{ true };                                                                                    // 60
		bool menuCanBeVisible{ true };                                                                                     // 61
		bool hasQuadsForCumstomRenderer{ false };                                                                          // 62
		bool hasDoneFirstAdvanceMovie{ false };                                                                            // 63
		std::int8_t depthPriority{ 6 };                                                                                    // 64
		stl::enumeration<UserEvents::INPUT_CONTEXT_ID, std::int32_t> inputContext{ UserEvents::INPUT_CONTEXT_ID::kNone };  // 68
	};
	static_assert(sizeof(IMenu) == 0x70);

	struct UIShaderColors
	{
	public:
		enum class Flags
		{
			kBackgroundQuad = 1u << 0,
			kColorMultiplier = 1u << 1,
			kVerticalGradient = 1u << 2,
			kUseAlphaForDropshadow = 1u << 3
		};

		// members
		NiRect<float> backgroundQuad;                          // 00
		NiColorA backgroundColor;                              // 10
		NiColorA colorMultipliers;                             // 20
		float colorBrightness;                                 // 30
		stl::enumeration<Flags, std::uint32_t> enabledStates;  // 34
	};
	static_assert(sizeof(UIShaderColors) == 0x38);

	struct alignas(0x10) UIShaderFXInfo
	{
	public:
		// members
		NiRect<float> renderQuad;  // 00
		UIShaderColors shaderFX;   // 10
	};
	static_assert(sizeof(UIShaderFXInfo) == 0x50);

	class HUDModeType
	{
	public:
		// members
		BSFixedString modeString;  // 0
	};
	static_assert(sizeof(HUDModeType) == 0x8);

	// TODO
	class GameMenuBase :
		public IMenu  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::GameMenuBase };
		static constexpr auto VTABLE{ VTABLE::GameMenuBase };

		// override (IMenu)
		void SetIsTopButtonBar(bool a_isTopButtonBar) override  // 08
		{
			using func_t = decltype(&IMenu::SetIsTopButtonBar);
			REL::Relocation<func_t> func{ REL::ID(1367353) };
			return func(this, a_isTopButtonBar);
		}

		void OnMenuDisplayStateChanged() override  // 0A
		{
			using func_t = decltype(&IMenu::OnMenuDisplayStateChanged);
			REL::Relocation<func_t> func{ REL::ID(1274450) };
			return func(this);
		}

		void OnAddedToMenuStack() override  // 0B
		{
			using func_t = decltype(&IMenu::OnAddedToMenuStack);
			REL::Relocation<func_t> func{ REL::ID(210529) };
			return func(this);
		}

		void OnRemovedFromMenuStack() override  // 0C
		{
			using func_t = decltype(&IMenu::OnRemovedFromMenuStack);
			REL::Relocation<func_t> func{ REL::ID(383045) };
			return func(this);
		}

		bool CacheShaderFXQuadsForRenderer_Impl() override  // 10
		{
			using func_t = decltype(&IMenu::CacheShaderFXQuadsForRenderer_Impl);
			REL::Relocation<func_t> func{ REL::ID(863029) };
			return func(this);
		}

		void TransferCachedShaderFXQuadsForRenderer(const BSFixedString& a_rendererName) override  // 11
		{
			using func_t = decltype(&IMenu::TransferCachedShaderFXQuadsForRenderer);
			REL::Relocation<func_t> func{ REL::ID(65166) };
			return func(this, a_rendererName);
		}

		void SetViewportRect(const NiRect<float>& a_viewportRect) override  // 12
		{
			using func_t = decltype(&IMenu::SetViewportRect);
			REL::Relocation<func_t> func{ REL::ID(1554334) };
			return func(this, a_viewportRect);
		}

		// add
		virtual void AppendShaderFXInfos(BSTAlignedArray<UIShaderFXInfo>& a_colorFXInfos, BSTAlignedArray<UIShaderFXInfo>& a_backgroundFXInfos) const  // 13
		{
			using func_t = decltype(&GameMenuBase::AppendShaderFXInfos);
			REL::Relocation<func_t> func{ REL::ID(583584) };
			return func(this, a_colorFXInfos, a_backgroundFXInfos);
		}

		// members
		BSTArray<BSGFxShaderFXTarget*> shaderFXObjects;           // 70
		msvc::unique_ptr<BSGFxShaderFXTarget> filterHolder;       // 88
		msvc::unique_ptr<ButtonHintBar> buttonHintBar;            // 90
		BSTAlignedArray<UIShaderFXInfo> cachedColorFXInfos;       // 98
		BSTAlignedArray<UIShaderFXInfo> cachedBackgroundFXInfos;  // B0
		BSReadWriteLock cachedQuadsLock;                          // C8
		BSTOptional<HUDModeType> menuHUDMode;                     // D0
	};
	static_assert(sizeof(GameMenuBase) == 0xE0);

	struct Rumble
	{
	public:
		struct AutoRumblePause
		{
		public:
		};
		static_assert(std::is_empty_v<AutoRumblePause>);
	};
	static_assert(std::is_empty_v<Rumble>);

	struct __declspec(novtable) Console :
		public GameMenuBase  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::Console };
		static constexpr auto VTABLE{ VTABLE::Console };
		static constexpr auto MENU_NAME{ "Console"sv };

		[[nodiscard]] static decltype(auto) GetCurrentPickIndex()
		{
			REL::Relocation<std::int32_t*> currentPickIndex{ REL::ID(1407033) };
			return *currentPickIndex;
		}

		[[nodiscard]] static decltype(auto) GetPickRef()
		{
			REL::Relocation<ObjectRefHandle*> ref{ REL::ID(170742) };
			return *ref;
		}

		[[nodiscard]] static decltype(auto) GetPickRefs()
		{
			REL::Relocation<BSTArray<ObjectRefHandle>*> pickRefs{ REL::ID(875116) };
			return *pickRefs;
		}

		[[nodiscard]] static ObjectRefHandle GetCurrentPickREFR()
		{
			const auto idx = GetCurrentPickIndex();
			const auto& refs = GetPickRefs();
			return 0 <= idx && static_cast<std::size_t>(idx) < refs.size() ?
                       refs[static_cast<std::size_t>(idx)] :
                       ObjectRefHandle{};
		}

		void SetCurrentPickREFR(stl::not_null<ObjectRefHandle*> a_refr)
		{
			using func_t = decltype(&Console::SetCurrentPickREFR);
			REL::Relocation<func_t> func{ REL::ID(79066) };
			return func(this, a_refr);
		}

		// members
		Rumble::AutoRumblePause* rumbleLock;  // E0
		bool minimized;                       // E8
	};
	static_assert(sizeof(Console) == 0xF0);

	struct BaseLoadedInventoryModel
	{
	public:
		// members
		CreatedObjPtr<TESForm> itemBase;  // 00
		TESBoundObject* modelObj;         // 08
		NiPointer<NiAVObject> model;      // 10
		NiPoint2 panMinima;               // 18
		NiPoint2 panMaxima;               // 20
		float initialDistance;            // 28
		float boundRadius;                // 2C
		float horizontalBound;            // 30
		float verticalBound;              // 34
		float verticalBoundOffset;        // 38
	};
	static_assert(sizeof(BaseLoadedInventoryModel) == 0x40);

	struct DisplayItemModel :
		public BaseLoadedInventoryModel  // 00
	{
	public:
		// members
		float itemRotation;         // 40
		std::uint32_t uniqueIndex;  // 44
		std::uint16_t column;       // 48
		std::uint16_t index;        // 4A
		std::uint16_t row;          // 4C
	};
	static_assert(sizeof(DisplayItemModel) == 0x50);

	namespace nsInventory3DManager
	{
		class NewInventoryMenuItemLoadTask;
	}

	class __declspec(novtable) Inventory3DManager :
		public BSInputEventUser  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::Inventory3DManager };
		static constexpr auto VTABLE{ VTABLE::Inventory3DManager };

		// members
		bool useBoundForScale: 1;                                                // 010:0
		bool startedZoomThisFrame: 1;                                            // 010:1
		bool useStoredModelPosition: 1;                                          // 010:2
		bool rotating: 1;                                                        // 010:3
		bool modelPositionInScreenCoords: 1;                                     // 010:4
		bool centerOnBoundCenter: 1;                                             // 010:5
		NiPoint3 modelPosition;                                                  // 014
		float modelScale;                                                        // 020
		alignas(0x10) BSTArray<LoadedInventoryModel> loadedModels;               // 030
		NiPoint3 initialPosition;                                                // 048
		NiPoint3 storedPostion;                                                  // 054
		NiMatrix3 initialRotation;                                               // 060
		NiQuaternion storedRotation;                                             // 090
		NiPoint2 previousInput;                                                  // 0A0
		NiPointer<nsInventory3DManager::NewInventoryMenuItemLoadTask> loadTask;  // 0A8
		TESObjectREFR* tempRef;                                                  // 0B0
		BSTSmartPointer<ExtraDataList> originalExtra;                            // 0B8
		BSFixedString str3DRendererName;                                         // 0C0
		BGSInventoryItem queuedDisplayItem;                                      // 0C8
		std::uint32_t itemExtraIndex;                                            // 0D8
		TESForm* itemBase;                                                       // 0E0
		std::int8_t disableInputUserCount;                                       // 0E8
		BSTSet<BSFixedString> disableRendererUsers;                              // 0F0
		float storedXRotation;                                                   // 120
		float zoomDirection;                                                     // 124
		float zoomProgress;                                                      // 128
		float minZoomModifier;                                                   // 12C
		float maxZoomModifier;                                                   // 130
		std::uint32_t hightlightedPart;                                          // 134
		bool queueShowItem;                                                      // 138
		bool mouseRotation;                                                      // 139
		bool prevUsesCursorFlag;                                                 // 13A
		bool prevUpdateUsesCursorFlag;                                           // 13B
		bool addedLightsToScene;                                                 // 13C
	};
	static_assert(sizeof(Inventory3DManager) == 0x140);

	class __declspec(novtable) WorkshopMenu :
		public GameMenuBase,                                 // 000
		public BSTEventSink<UserEventEnabledEvent>,          // 0E0
		public BSTEventSink<Workshop::BuildableAreaEvent>,   // 0E8
		public BSTEventSink<PickRefUpdateEvent>,             // 0F0
		public BSTEventSink<Workshop::PlacementStatusEvent>  // 0F8
	{
	public:
		static constexpr auto RTTI{ RTTI::WorkshopMenu };
		static constexpr auto VTABLE{ VTABLE::WorkshopMenu };
		static constexpr auto MENU_NAME{ "WorkshopMenu"sv };

		class FXWorkshopMenu;

		struct IconBG
		{
		public:
			BSTAlignedArray<UIShaderFXInfo> cachedColorFXInfos;       // 00
			BSTAlignedArray<UIShaderFXInfo> cachedBackgroundFXInfos;  // 18
			BSReadWriteLock cachedQuadsLock;                          // 30
		};
		static_assert(sizeof(IconBG) == 0x38);

		// members
		BSTArray<NiPoint3> item3DPositions[4];                                                                          // 100
		BSTArray<BSTTuple<DisplayItemModel, TESObjectREFR*>> displayItemModels;                                         // 160
		IconBG iconBG;                                                                                                  // 178
		Inventory3DManager inv3DModelManager;                                                                           // 1B0
		BSTArray<BSTTuple<NiPointer<nsInventory3DManager::NewInventoryMenuItemLoadTask>, NiPoint3>> loadTasks;          // 2F0
		BSTInterpolator<float, EaseOutInterpolator, GetCurrentPositionFunctor> upDownGlassAnimationInterpolator;        // 308
		BSTInterpolator<float, EaseOutInterpolator, GetCurrentPositionFunctor> leftRightGlassAnimationInterpolator[4];  // 320
		BSTSmartPointer<WorkshopMenuGeometry> displayGeometry;                                                          // 380
		BSFixedString dpadInput;                                                                                        // 388
		BGSListForm includeList;                                                                                        // 390
		BGSListForm excludeList;                                                                                        // 3D8
		long double lastBudget;                                                                                         // 420
		std::uint16_t topMenuCount;                                                                                     // 428
		bool inputAdjustMode;                                                                                           // 42A
		bool verticalAdjustment;                                                                                        // 42B
		bool disableAdjustOnThumbEvent;                                                                                 // 42C
		bool initialized;                                                                                               // 42D
		bool inEditMode;                                                                                                // 42E
		bool electricalDevice;                                                                                          // 42F
		bool useMovementAsDirectional;                                                                                  // 430
		bool motionBlurActive;                                                                                          // 431
		bool exitDebounce;                                                                                              // 432
		msvc::unique_ptr<FXWorkshopMenu> workshopMenuBase;                                                              // 438
	};
	static_assert(sizeof(WorkshopMenu) == 0x440);
}
