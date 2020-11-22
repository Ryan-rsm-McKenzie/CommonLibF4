#pragma once

#include "RE/Scaleform/GFx/GFx_Player.h"

namespace RE::Scaleform
{
	class String;

	template <class>
	class ArrayPOD;

	namespace Render::Text
	{
		class Allocator;
	}

	namespace GFx
	{
		class AccelerometerEvent;
		class AmpMovieObjectDesc;
		class AppLifecycleEvent;
		class ASString;
		class ASStringManager;
		class ASSupport;
		class DisplayObjContainer;
		class DisplayObject;
		class EventId;
		class GeolocationEvent;
		class InputEventsQueueEntry;
		class InteractiveObject;
		class LoadQueueEntry;
		class LoadStates;
		class MouseState;
		class MovieDefImpl;
		class MovieDefRootNode;
		class MovieImpl;
		class OrientationEvent;

		struct ProcessFocusKeyInfo;

		class __declspec(novtable) ASMovieRootBase :
			public RefCountBase<ASMovieRootBase, 327>  // 00
		{
		public:
			// add
			virtual void SetMovie(MovieImpl* a_movie) { movieImpl = a_movie; }                                                     // 01
			virtual void AdvanceFrame(bool a_nextFrame) = 0;                                                                       // 02
			virtual void ChangeMouseCursorType(std::uint32_t a_mouseIdx, std::uint32_t a_newCursorType) = 0;                       // 03
			virtual bool CheckAvm() = 0;                                                                                           // 04
			virtual void ClearDisplayList() = 0;                                                                                   // 05
			virtual MovieDefRootNode* CreateMovieDefRootNode(MemoryHeap* a_heap, MovieDefImpl* a_defImpl, bool a_importFlag) = 0;  // 06
			virtual void DoActions() = 0;                                                                                          // 07
			virtual InteractiveObject* FindTarget(const ASString& a_path) const = 0;                                               // 08
			virtual void ForceCollect() = 0;                                                                                       // 09
			virtual void ForceEmergencyCollect() = 0;                                                                              // 0A
			virtual void SuspendGC(bool a_suspend) = 0;                                                                            // 0B
			virtual void ScheduleGC() = 0;                                                                                         // 0C
			virtual void GenerateMouseEvents(std::uint32_t mouseIndex) = 0;                                                        // 0D
			virtual void GenerateTouchEvents([[maybe_unused]] std::uint32_t a_mouseStateIndex) { return; }                         // 0E

			virtual void GenerateGestureEvents(  // 0F
				[[maybe_unused]] InteractiveObject* a_topmost,
				[[maybe_unused]] std::uint32_t a_phase,
				[[maybe_unused]] const PointF& a_pos,
				[[maybe_unused]] const PointF& a_offset,
				[[maybe_unused]] const PointF& a_scale,
				[[maybe_unused]] float a_rotation,
				[[maybe_unused]] std::uint32_t a_gestureMask)
			{}

			virtual DisplayObjContainer* GetRootMovie(DisplayObject* dobj = nullptr) const = 0;                                                                                                                           // 10
			virtual bool Init(MovieDefImpl* a_movieDef) = 0;                                                                                                                                                              // 11
			virtual void NotifyMouseEvent(const InputEventsQueueEntry* a_qe, const MouseState& a_ms, std::int32_t a_mi) = 0;                                                                                              // 12
			virtual void NotifyOnResize() = 0;                                                                                                                                                                            // 13
			virtual void NotifyQueueSetFocus(InteractiveObject* a_ch, std::uint32_t a_controllerIdx, FocusMovedType a_fmt) = 0;                                                                                           // 14
			virtual void NotifyTransferFocus(InteractiveObject* a_curFocused, InteractiveObject* a_newFocus, std::uint32_t a_controllerIdx) = 0;                                                                          // 15
			virtual bool NotifyOnFocusChange(InteractiveObject* a_curFocused, InteractiveObject* a_toBeFocused, std::uint32_t a_controllerIdx, FocusMovedType a_fmt, ProcessFocusKeyInfo* a_focusKeyInfo = nullptr) = 0;  // 16
			virtual void NotifyGamePadAnalogEvent([[maybe_unused]] const EventId* a_id) { return; }                                                                                                                       // 17
			virtual void NotifyStatusEvent([[maybe_unused]] const EventId* a_id) { return; }                                                                                                                              // 18
			virtual void NotifyAccelerometerEvent([[maybe_unused]] const EventId* a_id, [[maybe_unused]] std::int32_t a_evtIDAcc) { return; }                                                                             // 19
			virtual void NotifyGeolocationEvent([[maybe_unused]] const EventId* a_id, [[maybe_unused]] std::int32_t a_evtIDGeo) { return; }                                                                               // 1A
			virtual void OnMovieFocus(bool a_set) = 0;                                                                                                                                                                    // 1B
			virtual void OnNextFrame() = 0;                                                                                                                                                                               // 1C
			virtual void OnDeviceOrientationChanged([[maybe_unused]] const OrientationEvent&) { return; }                                                                                                                 // 1D
			virtual void OnAppLifecycleEvent([[maybe_unused]] const AppLifecycleEvent&) { return; }                                                                                                                       // 1E
			virtual void OnAccelerometerEvent([[maybe_unused]] const AccelerometerEvent&) { return; }                                                                                                                     // 1F
			virtual void OnGeolocationEvent([[maybe_unused]] const GeolocationEvent&) { return; }                                                                                                                         // 20
			virtual void PrintObjectsReport([[maybe_unused]] std::uint32_t a_flags = 0, [[maybe_unused]] Log* a_log = nullptr, [[maybe_unused]] const char* a_swfName = nullptr) { return; }                              // 21
			virtual void GetObjectsTree([[maybe_unused]] Array<Ptr<AmpMovieObjectDesc>>* a_rootObjects, [[maybe_unused]] MemoryHeap* a_heap) { return; }                                                                  // 22
			virtual AmpMovieObjectDesc* GetDisplayObjectsTree([[maybe_unused]] MemoryHeap* a_heap) { return nullptr; }                                                                                                    // 23
			virtual void ProcessLoadQueueEntry(GFx::LoadQueueEntry* a_entry, LoadStates* a_ls) = 0;                                                                                                                       // 24
			virtual void ProcessLoadVarsMT(GFx::LoadQueueEntry* a_entry, LoadStates* a_ls, const String& a_data, std::size_t a_fileLen, bool a_succeeded) = 0;                                                            // 25

			virtual void ProcessLoadBinaryMT(  // 26
				[[maybe_unused]] GFx::LoadQueueEntry* a_entry,
				[[maybe_unused]] LoadStates* a_ls,
				[[maybe_unused]] const ArrayPOD<std::byte>& a_data,
				[[maybe_unused]] std::size_t a_fileLen,
				[[maybe_unused]] bool a_succeeded)
			{}

			virtual void RegisterAuxASClasses() = 0;                                                                                                                                                                             // 27
			virtual void ResolveStickyVariables(InteractiveObject* a_character) = 0;                                                                                                                                             // 28
			virtual void SetExternalInterfaceRetVal(const GFx::Value&) = 0;                                                                                                                                                      // 29
			virtual void SetMemoryParams(std::uint32_t a_frameBetweenCollections, std::uint32_t a_maxRootCount) = 0;                                                                                                             // 2A
			virtual void Shutdown() = 0;                                                                                                                                                                                         // 2B
			virtual void CreateString(GFx::Value* a_value, const char* a_string) = 0;                                                                                                                                            // 2C
			virtual void CreateStringW(GFx::Value* a_value, const wchar_t* a_string) = 0;                                                                                                                                        // 2D
			virtual void CreateObject(GFx::Value* a_value, const char* a_className = nullptr, const GFx::Value* a_args = nullptr, std::uint32_t a_numArgs = 0) = 0;                                                              // 2E
			virtual void CreateArray(GFx::Value* a_value) = 0;                                                                                                                                                                   // 2F
			virtual void CreateFunction(GFx::Value* a_value, GFx::FunctionHandler* a_fc, void* a_userData = nullptr) = 0;                                                                                                        // 30
			virtual bool SetVariable(const char* a_pathToVar, const GFx::Value& a_value, Movie::SetVarType a_setType = Movie::SetVarType::kSticky) = 0;                                                                          // 31
			virtual bool GetVariable(GFx::Value* a_val, const char* a_pathToVar) const = 0;                                                                                                                                      // 32
			virtual bool SetVariableArray(Movie::SetArrayType a_type, const char* a_pathToVar, std::uint32_t a_index, const void* a_data, std::uint32_t a_count, Movie::SetVarType a_setType = Movie::SetVarType::kSticky) = 0;  // 33
			virtual bool SetVariableArraySize(const char* a_pathToVar, std::uint32_t a_count, Movie::SetVarType a_setType = Movie::SetVarType::kSticky) = 0;                                                                     // 35
			virtual std::uint32_t GetVariableArraySize(const char* a_pathToVar) = 0;                                                                                                                                             // 34
			virtual bool GetVariableArray(Movie::SetArrayType a_type, const char* a_pathToVar, std::uint32_t a_index, void* a_data, std::uint32_t a_count) = 0;                                                                  // 36
			virtual bool IsAvailable(const char* ppathToVar) const = 0;                                                                                                                                                          // 37
			virtual bool Invoke(const char* a_pathToMethod, GFx::Value* a_result, const GFx::Value* a_args, std::uint32_t a_numArgs) = 0;                                                                                        // 39
			virtual bool Invoke(const char* a_pathToMethod, GFx::Value* a_result, const char* a_argFmt, ...) = 0;                                                                                                                // 38
			virtual bool InvokeArgs(const char* a_pathToMethod, GFx::Value* a_result, const char* a_argFmt, std::va_list a_args) = 0;                                                                                            // 3A
			virtual MemoryContext* GetMemoryContext() const = 0;                                                                                                                                                                 // 3B
			virtual ASStringManager* GetStringManager() const = 0;                                                                                                                                                               // 3C
			virtual Render::Text::Allocator* GetTextAllocator() = 0;                                                                                                                                                             // 3D
			virtual void BroadcastGeolocationStatusEvent(const EventId* a_id) = 0;                                                                                                                                               // 3E

			// members
			MovieImpl* movieImpl;      // 10
			Ptr<ASSupport> asSupport;  // 18
			std::uint8_t avmVersion;   // 20
		};
		static_assert(sizeof(ASMovieRootBase) == 0x28);
	}
}
