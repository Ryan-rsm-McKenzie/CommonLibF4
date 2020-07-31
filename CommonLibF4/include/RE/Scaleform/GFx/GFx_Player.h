#pragma once

#include "RE/Scaleform/GFx/GFx_Loader.h"
#include "RE/Scaleform/GFx/GFx_Log.h"
#include "RE/Scaleform/GFx/GFx_Types.h"
#include "RE/Scaleform/Kernel/SF_RefCount.h"
#include "RE/Scaleform/Render/Render_Constants.h"
#include "RE/Scaleform/Render/Render_Context.h"
#include "RE/Scaleform/Render/Render_TreeNode.h"
#include "RE/Scaleform/Render/Render_Viewport.h"

namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class ASMovieRootBase;
			class MemoryContext;
			class Movie;
			class MovieDef;
			class Viewport;

			struct MemoryParams;

			class Viewport :
				public Render::Viewport
			{
			public:
				// members
				float scale;		// 2C
				float aspectRatio;	// 30
			};
			static_assert(sizeof(Viewport) == 0x34);

			class MemoryContext :
				public RefCountBase<MemoryContext, 2>  // 00
			{
			public:
				virtual ~MemoryContext() = default;
			};
			static_assert(sizeof(MemoryContext) == 0x10);

			struct MemoryParams
			{
			public:
				// members
				MemoryHeap::HeapDesc desc;				 // 00
				float heapLimitMultiplier;				 // 40
				std::uint32_t maxCollectionRoots;		 // 44
				std::uint32_t framesBetweenCollections;	 // 48
				std::uint32_t initialDynamicLimit;		 // 4C
				std::uint32_t runsToUpgradeGen;			 // 50
				std::uint32_t runsToCollectYoung;		 // 54
				std::uint32_t runsToCollectOld;			 // 58
			};
			static_assert(sizeof(MemoryParams) == 0x60);

			class MovieDef :
				public Resource,  // 00
				public StateBag	  // 18
			{
			public:
				enum class FileAttrFlags : std::uint32_t
				{
					kUseNetwork = 1 << 0,
					kUseActionScript3 = 1 << 3,
					kHasMetadata = 1 << 4
				};

				enum class VisitResourceMask : std::uint32_t
				{
					kNestedMovies = 1 << 15,

					kFonts = 1 << 0,
					kBitmaps = 1 << 1,
					kGradientImages = 1 << 2,
					kEditTextFields = 1 << 3,
					kSounds = 1 << 4,
					kSprite = 1 << 5,

					kAllLocalImages = (kBitmaps | kGradientImages),
					kAllImages = (kBitmaps | kGradientImages | kNestedMovies)
				};

				struct ImportVisitor
				{
				public:
					virtual ~ImportVisitor() = default;	 // 00

					// add
					virtual void Visit(MovieDef* a_parentDef, MovieDef* a_importDef, const char* a_importedMovieFilename) = 0;	// 01
				};
				static_assert(sizeof(ImportVisitor) == 0x8);

				struct ResourceVisitor :
					public FileTypeConstants  // 00
				{
				public:
					virtual ~ResourceVisitor() = default;  // 00

					// add
					virtual void Visit(MovieDef* a_movieDef, Resource* a_resource, ResourceId a_rid, const char* a_exportName) = 0;	 // 01
				};
				static_assert(sizeof(ResourceVisitor) == 0x8);

				virtual std::uint32_t GetVersion() const = 0;																																// 04
				virtual std::uint32_t GetLoadingFrame() const = 0;																															// 05
				virtual float GetWidth() const = 0;																																			// 06
				virtual float GetHeight() const = 0;																																		// 07
				virtual std::uint32_t GetFrameCount() const = 0;																															// 08
				virtual float GetFrameRate() const = 0;																																		// 09
				virtual RectF GetFrameRect() const = 0;																																		// 0A
				virtual std::uint32_t GetSWFFlags() const = 0;																																// 0B
				virtual const char* GetFileURL() const = 0;																																	// 0C
				virtual void WaitForLoadFinish(bool a_cancel = false) const = 0;																											// 0D
				virtual void WaitForFrame(std::uint32_t a_frame) const = 0;																													// 0E
				virtual FileAttrFlags GetFileAttributes() const = 0;																														// 0F
				virtual std::uint32_t GetMetadata(char* a_buff, std::uint32_t a_buffSize) const = 0;																						// 10
				virtual MemoryHeap* GetLoadDataHeap() const = 0;																															// 11
				virtual MemoryHeap* GetBindDataHeap() const = 0;																															// 12
				virtual MemoryHeap* GetImageHeap() const = 0;																																// 13
				virtual Resource* GetMovieDataResource() const = 0;																															// 14
				virtual const ExporterInfo* GetExporterInfo() const = 0;																													// 15
				virtual MemoryContext* CreateMemoryContext(const char* a_heapName, const MemoryParams& a_memParams, bool a_debugHeap) = 0;													// 16
				virtual Movie* CreateInstance1(MemoryContext* a_memContext, bool a_initFirstFrame, ActionControl* a_actionControl, Render::ThreadCommandQueue* a_queue = nullptr) = 0;		// 17
				virtual Movie* CreateInstance2(const MemoryParams& a_memParams, bool a_initFirstFrame, ActionControl* a_actionControl, Render::ThreadCommandQueue* a_queue = nullptr) = 0;	// 18
				virtual void VisitImportedMovies(ImportVisitor* a_visitor) = 0;																												// 19
				virtual void VisitResources(ResourceVisitor* a_visitor, VisitResourceMask a_visitMask = VisitResourceMask::kAllImages) = 0;													// 1A
				virtual Resource* GetResource(const char* a_exportName) const = 0;																											// 1B

				inline Movie* CreateInstance(MemoryContext* a_memContext, bool a_initFirstFrame, ActionControl* a_actionControl, Render::ThreadCommandQueue* a_queue = nullptr)
				{
					return CreateInstance1(a_memContext, a_initFirstFrame, a_actionControl, a_queue);
				}

				inline Movie* CreateInstance(const MemoryParams& a_memParams, bool a_initFirstFrame, ActionControl* a_actionControl, Render::ThreadCommandQueue* a_queue = nullptr)
				{
					return CreateInstance2(a_memParams, a_initFirstFrame, a_actionControl, a_queue);
				}
			};
			static_assert(sizeof(MovieDef) == 0x20);

			using MovieDisplayHandle = Render::DisplayHandle<Render::TreeRoot>;

			class Movie :
				public RefCountBase<Movie, 327>,  // 00
				public StateBag					  // 10
			{
			public:
				enum class SetVarType : std::int32_t
				{
					kNormal,
					kSticky,
					kPermanent
				};

				enum class SetArrayType : std::int32_t
				{
					kInt,
					kDouble,
					kFloat,
					kString,
					kStringW,
					kValue
				};

				enum class ScaleModeType : std::int32_t
				{
					kNoScale,
					kShowAll,
					kExactFit,
					kNoBorder
				};

				enum class AlignType : std::int32_t
				{
					kCenter,
					kTopCenter,
					kBottomCenter,
					kCenterLeft,
					kCenterRight,
					kTopLeft,
					kTopRight,
					kBottomLeft,
					kBottomRight
				};

				enum HE_ReturnValueType
				{
					HE_NotHandled = 0,
					HE_Handled = 1,
					HE_NoDefaultAction = 2,
					HE_Completed = (HE_Handled | HE_NoDefaultAction)
				};

				enum class HitTestType : std::int32_t
				{
					kBounds = 0,
					kShapes = 1,
					kButtonEvents = 2,
					kShapesNoInvisible = 3
				};

				enum class ReportFlags : std::uint32_t
				{
					kNone = 0,
					kShortFileNames = 1 << 0,
					kNoCircularReferences = 1 << 1,
					kSuppressOverallStats = 1 << 2,
					kAddressesForAnonymObjsOnly = 1 << 3,
					kSuppressMovieDefsStats = 1 << 4,
					kNoEllipsis = 1 << 5
				};

				enum class MakeAllVisibleFlags : std::uint32_t
				{
					kNone = 0,
					kDontScaleDown = 1 << 0,
					kScaleUp50 = 1 << 1,
					kLeftTopToZero = 1 << 2
				};

				virtual MovieDef* GetMovieDef() const = 0;																														 // 01
				virtual std::uint32_t GetCurrentFrame() const = 0;																												 // 02
				virtual bool HasLooped() const = 0;																																 // 03
				virtual void GotoFrame(std::uint32_t a_frameNumber) = 0;																										 // 04
				virtual bool GotoLabeledFrame(const char* a_label, std::int32_t a_offset = 0) = 0;																				 // 05
				virtual void SetPlayState(PlayState a_state) = 0;																												 // 06
				virtual PlayState GetPlayState() const = 0;																														 // 07
				virtual bool IsValid() = 0;																																		 // 08
				virtual void SetVisible(bool a_visible) = 0;																													 // 09
				virtual bool GetVisible() const = 0;																															 // 0A
				virtual std::uint64_t GetASTimerMs() const = 0;																													 // 0B
				virtual void SetViewport(const Viewport& a_viewDesc) = 0;																										 // 0C
				virtual void GetViewport(Viewport* a_viewDesc) const = 0;																										 // 0D
				virtual void SetViewScaleMode(ScaleModeType) = 0;																												 // 0E
				virtual ScaleModeType GetViewScaleMode() const = 0;																												 // 0F
				virtual void SetViewAlignment(AlignType) = 0;																													 // 10
				virtual AlignType GetViewAlignment() const = 0;																													 // 11
				virtual RectF GetVisibleFrameRect() const = 0;																													 // 12
				virtual RectF GetSafeRect() const = 0;																															 // 13
				virtual void SetSafeRect(const RectF& a_rect) = 0;																												 // 14
				virtual void SetEdgeAAMode(Render::EdgeAAMode a_edgeAA) = 0;																									 // 15
				virtual Render::EdgeAAMode GetEdgeAAMode() const = 0;																											 // 16
				virtual void Restart(bool a_advance0 = true) = 0;																												 // 17
				virtual float Advance(float a_deltaT, std::uint32_t a_frameCatchUpCount = 2, bool a_capture = true) = 0;														 // 18
				virtual void Capture(bool a_onChangeOnly = true) = 0;																											 // 19
				virtual const MovieDisplayHandle& GetDisplayHandle() const = 0;																									 // 1A
				virtual void SetCaptureThread(ThreadId a_captureThreadId) = 0;																									 // 1B
				virtual void ShutdownRendering(bool a_wait) = 0;																												 // 1C
				virtual bool IsShutdownRenderingComplete() const = 0;																											 // 1D
				virtual void SetPause(bool a_pause) = 0;																														 // 1E
				virtual bool IsPaused() const = 0;																																 // 1F
				virtual void SetBackgroundColor(const Render::Color a_bgColor) = 0;																								 // 20
				virtual void SetBackgroundAlpha(float a_alpha) = 0;																												 // 21
				virtual float GetBackgroundAlpha() const = 0;																													 // 22
				virtual std::uint32_t HandleEvent(const Event& a_event) = 0;																									 // 23
				virtual void GetMouseState(std::uint32_t a_mouseIndex, float* a_x, float* a_y, std::uint32_t* a_buttons) = 0;													 // 24
				virtual void NotifyMouseState(float a_x, float a_y, std::uint32_t a_buttons, std::uint32_t a_mouseIndex = 0) = 0;												 // 25
				virtual bool HitTest(float a_x, float a_y, HitTestType a_testCond = HitTestType::kShapes, std::uint32_t a_controllerIdx = 0) = 0;								 // 26
				virtual void* GetUserData() const = 0;																															 // 27
				virtual void SetUserData(void*) = 0;																															 // 28
				virtual bool IsMovieFocused() const = 0;																														 // 29
				virtual bool GetDirtyFlag(bool a_doReset = true) = 0;																											 // 2A
				virtual void SetMouseCursorCount(std::uint32_t a_num) = 0;																										 // 2B
				virtual std::uint32_t GetMouseCursorCount() const = 0;																											 // 2C
				virtual void SetControllerCount(std::uint32_t a_num) = 0;																										 // 2D
				virtual std::uint32_t GetControllerCount() const = 0;																											 // 2E
				virtual void GetStats(StatBag* a_bag, bool a_reset = true) = 0;																									 // 2F
				virtual MemoryHeap* GetHeap() const = 0;																														 // 30
				virtual void ForceCollectGarbage() = 0;																															 // 31
				virtual void SuspendGC(bool a_suspend) = 0;																														 // 32
				virtual void ScheduleGC() = 0;																																	 // 33
				virtual void PrintObjectsReport(ReportFlags a_flags = ReportFlags::kNone, Log* a_log = nullptr, const char* a_swfName = nullptr) = 0;							 // 34
				virtual RectF TranslateToScreen1(const RectF& a_pt, Matrix2F* a_userMatrix = nullptr) = 0;																		 // 35
				virtual Render::PointF TranslateToScreen2(const Render::PointF& a_pt, Matrix2F* a_userMatrix = nullptr) = 0;													 // 36
				virtual bool TranslateLocalToScreen(const char* a_pathToCharacter, const Render::PointF& a_pt, Render::PointF* a_presPt, Matrix2F* a_userMatrix = nullptr) = 0;	 // 37
				virtual bool SetControllerFocusGroup(std::uint32_t a_controllerIdx, std::uint32_t a_focusGroupIndex) = 0;														 // 38
				virtual std::uint32_t GetControllerFocusGroup(std::uint32_t a_controllerIdx) const = 0;																			 // 39
				virtual void ResetInputFocus(std::uint32_t a_controllerIdx) = 0;																								 // 3A
				virtual bool IsExitRequested() const = 0;																														 // 3B
				virtual void GetViewMatrix3D(Matrix3F*) = 0;																													 // 3C
				virtual void SetViewMatrix3D(const Matrix3F& a_matrix) = 0;																										 // 3D
				virtual void GetProjectionMatrix3D(Matrix4F*) = 0;																												 // 3E
				virtual void SetProjectionMatrix3D(const Matrix4F& a_matrix) = 0;																								 // 3F
				virtual void SetStageAutoOrients(bool a_value = true) = 0;																										 // 40
				virtual void ForceUpdateImages() = 0;																															 // 41
				virtual void MakeAreaVisible(const Render::RectF& a_screenRect, const Render::RectF& a_box, MakeAllVisibleFlags a_flags = MakeAllVisibleFlags::kNone) = 0;		 // 42
				virtual void RestoreViewport() = 0;																																 // 43

				inline void Release()
				{
					using func_t = decltype(&Movie::Release);
					REL::Relocation<func_t> func{ REL::ID(404814) };
					return func(this);
				}

				inline RectF TranslateToScreen(const RectF& a_pt, Matrix2F* a_userMatrix = nullptr)
				{
					return TranslateToScreen1(a_pt, a_userMatrix);
				}

				inline Render::PointF TranslateToScreen(const Render::PointF& a_pt, Matrix2F* a_userMatrix = nullptr)
				{
					return TranslateToScreen2(a_pt, a_userMatrix);
				}

				// members
				Ptr<ASMovieRootBase> asMovieRoot;  // 18
			};
			static_assert(sizeof(Movie) == 0x20);
		}
	}
}
