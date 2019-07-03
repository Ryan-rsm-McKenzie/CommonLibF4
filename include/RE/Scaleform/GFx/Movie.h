#pragma once

#include <cstdarg>

#include "RE/Scaleform/GFx/PlayerStats.h"
#include "RE/Scaleform/GFx/PlayState.h"
#include "RE/Scaleform/GFx/StateBag.h"
#include "RE/Scaleform/Render/Color.h"
#include "RE/Scaleform/Render/Constants.h"
#include "RE/Scaleform/Render/Matrix2x4.h"
#include "RE/Scaleform/Render/Matrix3x4.h"
#include "RE/Scaleform/Render/Matrix4x4.h"
#include "RE/Scaleform/Render/Point.h"
#include "RE/Scaleform/Render/Rect.h"
#include "RE/Scaleform/Ptr.h"
#include "RE/Scaleform/RefCountBase.h"
#include "RE/Scaleform/ThreadID.h"


namespace RE
{
	namespace Scaleform
	{
		class Log;
		class StatBag;


		namespace Render
		{
			template <class T> class DisplayHandle;
			class TreeRoot;
			using MovieDisplayHandle = DisplayHandle<TreeRoot>;
		}


		namespace GFx
		{
			class ASMovieRootBase;
			class Event;
			class FunctionHandler;
			class MovieDef;
			class Value;
			class Viewport;


			class Movie :
				public RefCountBase<Movie, kStatMV_Other_Mem>,	// 00
				public StateBag									// 10
			{
			public:
				enum class SetVarType : UInt32
				{
					kNormal,
					kSticky,
					kPermanent
				};


				enum class ReportFlags : UInt32
				{
					kNone = 0,
					kShortFileNames = 1 << 0,
					kNoCircularReferences = 1 << 1,
					kSuppressOverallStats = 1 << 2,
					kAddressesForAnonymObjsOnly = 1 << 3,
					kSuppressMovieDefsStats = 1 << 4,
					kNoEllipsis = 1 << 5
				};


				enum HEReturnType
				{
					kNotHandled = 0,
					kHandled = 1,
					kNoDefaultAction = 2,
					kCompleted = (kHandled | kNoDefaultAction)
				};


				enum class HitTestType : UInt32
				{
					kBounds = 0,
					kShapes = 1,
					kButtonEvents = 2,
					kShapesNoInvisible = 3
				};


				enum class AlignType : UInt32
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


				enum class ScaleModeType : UInt32
				{
					kNoScale,
					kShowAll,
					kExactFit,
					kNoBorder
				};


				enum class MakeAreaVisibleFlag : UInt32
				{
					kNone = 0,
					kDontScaleDown = 1 << 0,
					kScaleUp50 = 1 << 1,
					kLeftTopToZero = 1 << 2
				};


				enum class SetArrayType : UInt32
				{
					kInt,
					kDouble,
					kFloat,
					kString,
					kStringW,
					kValue
				};


				virtual ~Movie();																																														// 00


				virtual MovieDef*							GetMovieDef() const = 0;																																	// 01
				virtual UInt32								GetCurrentFrame() const = 0;																																// 02
				virtual bool								HasLooped() const = 0;																																		// 03
				virtual void								GotoFrame(UInt32 a_frameNumber) = 0;																														// 04
				virtual bool								GotoLabeledFrame(const char* a_label, SInt32 a_offset = 0) = 0;																								// 05
				virtual void								SetPlayState(PlayState a_state) = 0;																														// 06
				virtual PlayState							GetPlayState() const = 0;																																	// 07
				virtual void								SetVisible(bool a_visible) = 0;																																// 08
				virtual bool								GetVisible() const = 0;																																		// 09
				virtual UInt64								GetASTimerMs() const = 0;																																	// 0A
				virtual void								SetViewport(const Viewport& a_viewDesc) = 0;																												// 0B
				virtual void								GetViewport(Viewport* a_viewDesc) const = 0;																												// 0C
				virtual void								SetViewScaleMode(ScaleModeType a_type) = 0;																													// 0D
				virtual ScaleModeType						GetViewScaleMode() const = 0;																																// 0E
				virtual void								SetViewAlignment(AlignType a_type) = 0;																														// 0F
				virtual AlignType							GetViewAlignment() const = 0;																																// 10
				virtual Render::RectF						GetVisibleFrameRect() const = 0;																															// 11
				virtual Render::RectF						GetSafeRect() const = 0;																																	// 12
				virtual void								SetSafeRect(const Render::RectF& a_rect) = 0;																												// 13
				virtual void								SetEdgeAAMode(Render::EdgeAAMode a_edgeAA) = 0;																												// 14
				virtual Render::EdgeAAMode					GetEdgeAAMode() const = 0;																																	// 15
				virtual void								Restart(bool a_advance0 = true) = 0;																														// 16
				virtual float								Advance(float a_deltaT, UInt32 a_frameCatchUpCount = 2, bool a_capture = true) = 0;																			// 17
				virtual void								Capture(bool a_onChangeOnly = true) = 0;																													// 18
				virtual const Render::MovieDisplayHandle&	GetDisplayHandle() const = 0;																																// 19
				virtual void								SetCaptureThread(ThreadID a_captureThreadID) = 0;																											// 1A
				virtual void								ShutdownRendering(bool a_wait) = 0;																															// 1B
				virtual bool								IsShutdownRenderingComplete() const = 0;																													// 1C
				virtual void								SetPause(bool a_pause) = 0;																																	// 1D
				virtual bool								IsPaused() const = 0;																																		// 1E
				virtual void								SetBackgroundColor(const Render::Color a_bgColor) = 0;																										// 1F
				virtual void								SetBackgroundAlpha(float a_alpha) = 0;																														// 20
				virtual float								GetBackgroundAlpha() const = 0;																																// 21
				virtual UInt32								HandleEvent(const Event& a_event) = 0;																														// 22
				virtual void								GetMouseState(UInt32 a_mouseIndex, float* a_x, float* a_y, UInt32* a_buttons) = 0;																			// 23
				virtual void								NotifyMouseState(float a_x, float a_y, UInt32 a_buttons, UInt32 a_mouseIndex = 0) = 0;																		// 24
				virtual bool								HitTest(float a_x, float a_y, HitTestType a_testCond = HitTestType::kShapes, UInt32 a_controllerIdx = 0) = 0;												// 25
				virtual void*								GetUserData() const = 0;																																	// 26
				virtual void								SetUserData(void* a_userData) = 0;																															// 27
				virtual bool								IsMovieFocused() const = 0;																																	// 28
				virtual bool								GetDirtyFlag(bool a_doReset = true) = 0;																													// 29
				virtual void								SetMouseCursorCount(UInt32 a_count) = 0;																													// 2A
				virtual UInt32								GetMouseCursorCount() const = 0;																															// 2B
				virtual void								SetControllerCount(UInt32 a_count) = 0;																														// 2C
				virtual UInt32								GetControllerCount() const = 0;																																// 2D
				virtual void								GetStats(StatBag* a_bag, bool a_reset = true) = 0;																											// 2E
				virtual MemoryHeap*							GetHeap() const = 0;																																		// 2F
				virtual void								ForceCollectGarbage() = 0;																																	// 30
				virtual void								SuspendGC(bool a_suspend) = 0;																																// 31
				virtual void								ScheduleGC() = 0;																																			// 32
				virtual void								PrintObjectsReport(ReportFlags a_flags = ReportFlags::kNone, Log* a_log = 0, const char* a_swfName = 0) = 0;												// 33
				virtual Render::PointF						TranslateToScreen(const Render::PointF& a_point, Render::Matrix2F* a_userMatrix = 0) = 0;																	// 34
				virtual Render::RectF						TranslateToScreen(const Render::RectF& a_rect, Render::Matrix2F* a_userMatrix = 0) = 0;																		// 35
				virtual bool								TranslateLocalToScreen(const char* a_pathToCharacter, const Render::PointF& a_point, Render::PointF* a_presPoint, Render::Matrix2F* a_userMatrix = 0) = 0;	// 36
				virtual bool								SetControllerFocusGroup(UInt32 a_controllerIdx, UInt32 a_focusGroupIndex) = 0;																				// 37
				virtual UInt32								GetControllerFocusGroup(UInt32 a_controllerIdx) const = 0;																									// 38
				virtual void								ResetInputFocus(UInt32 a_controllerIdx) = 0;																												// 39
				virtual bool								IsExitRequested() const = 0;																																// 3A
				virtual void								GetViewMatrix3D(Render::Matrix3F* a_matrix) = 0;																											// 3B
				virtual void								SetViewMatrix3D(const Render::Matrix3F& a_matrix) = 0;																										// 3C
				virtual void								GetProjectionMatrix3D(Render::Matrix4F* a_matrix) = 0;																										// 3D
				virtual void								SetProjectionMatrix3D(const Render::Matrix4F& a_matrix) = 0;																								// 3E
				virtual void								SetStageAutoOrients(bool a_val = true) = 0;																													// 3F
				virtual void								ForceUpdateImages() = 0;																																	// 40
				virtual void								MakeAreaVisible(const Render::RectF& a_screenRect, const Render::RectF& a_box, MakeAreaVisibleFlag a_flags = MakeAreaVisibleFlag::kNone) = 0;				// 41
				virtual void								RestoreViewport() = 0;																																		// 42

				static float GetRenderPixelScale();

				UInt32	GetFrameCount() const;
				float	GetFrameRate() const;
				SInt32	GetAVMVersion() const;
				bool	IsAvailable(const char* a_pathToVar) const;
				void	CreateString(Value* a_value, const char* a_string);
				void	CreateStringW(Value* a_value, const wchar_t* a_string);
				void	CreateObject(Value* a_value, const char* a_className = 0, const Value* a_args = 0, UInt32 a_numArgs = 0);
				void	CreateArray(Value* a_value);
				void	CreateFunction(Value* a_value, FunctionHandler* a_fc, void* a_userData = 0);
				bool	SetVariable(const char* a_pathToVar, const Value& a_value, SetVarType a_setType = SetVarType::kSticky);
				bool	GetVariable(Value* a_val, const char* a_pathToVar) const;
				bool	SetVariable(const char* a_pathToVar, const char* a_value, SetVarType a_setType = SetVarType::kSticky);
				bool	SetVariable(const char* a_pathToVar, const wchar_t* a_value, SetVarType a_setType = SetVarType::kSticky);
				bool	SetVariableDouble(const char* a_pathToVar, double a_value, SetVarType a_setType = SetVarType::kSticky);
				double	GetVariableDouble(const char* a_pathToVar) const;
				bool	SetVariableArray(SetArrayType a_type, const char* a_pathToVar, UInt32 a_index, const void* a_data, UInt32 a_count, SetVarType a_setType = SetVarType::kSticky);
				bool	SetVariableArraySize(const char* a_pathToVar, UInt32 a_count, SetVarType a_setType = SetVarType::kSticky);
				UInt32	GetVariableArraySize(const char* a_pathToVar);
				bool	GetVariableArray(SetArrayType a_type, const char* a_pathToVar, UInt32 a_index, void* a_data, UInt32 a_count);
				bool	SetVariableArray(const char* a_pathToVar, UInt32 a_index, const Value* a_data, UInt32 a_count, SetVarType a_setType = SetVarType::kSticky);
				bool	GetVariableArray(const char* a_pathToVar, UInt32 a_index, Value* a_data, UInt32 a_count);
				bool	Invoke(const char* a_pathToMethod, Value* a_result, const Value* a_args, UInt32 a_numArgs);
				bool	Invoke(const char* a_pathToMethod, Value* a_result, const char* a_argFmt, ...);
				bool	InvokeArgs(const char* a_pathToMethod, Value* a_result, const char* a_argFmt, std::va_list a_args);
				bool	Invoke(const char* a_pathToMethod, const char* a_argFmt, ...);
				void	SetExternalInterfaceRetVal(const Value& a_val);
				void	Release();

			protected:
				// members
				Ptr<ASMovieRootBase> _asMovieRoot;	// 18
			};
			STATIC_ASSERT(sizeof(Movie) == 0x20);
		}
	}
}
