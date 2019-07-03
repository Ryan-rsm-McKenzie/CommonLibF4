#pragma once

#include <cstdarg>

#include "RE/Scaleform/GFx/ASSupport.h"
#include "RE/Scaleform/GFx/FocusMovedType.h"
#include "RE/Scaleform/GFx/Movie.h"
#include "RE/Scaleform/GFx/PlayerStats.h"
#include "RE/Scaleform/Render/Point.h"
#include "RE/Scaleform/Ptr.h"
#include "RE/Scaleform/RefCountBase.h"


namespace RE
{
	namespace Scaleform
	{
		template <class T> class ArrayPOD;
		class Log;
		class String;


		namespace Render
		{
			namespace Text
			{
				class Allocator;
			}
		}


		namespace GFx
		{
			class AppLifecycleEvent;
			class ASString;
			class ASStringManager;
			class DisplayObject;
			class DisplayObjContainer;
			class EventID;
			class FunctionHandler;
			class InputEventsQueueEntry;
			class LoadQueueEntry;
			class LoadStates;
			class MouseState;
			class MovieDefImpl;
			class MovieDefRootNode;
			class MovieImpl;
			class OrientationEvent;
			class Value;
			struct ProcessFocusKeyInfo;


			class ASMovieRootBase : public RefCountBase<ASMovieRootBase, kStatMV_Other_Mem>
			{
			public:

				ASMovieRootBase(ASSupport* a_asSupport);
				virtual ~ASMovieRootBase() = default;																																																			// 00

				// add
				virtual void						SetMovie(MovieImpl* a_movie);																																												// 01
				virtual void						AdvanceFrame(bool a_nextFrame) = 0;																																											// 02
				virtual void						ChangeMouseCursorType(UInt32 a_mouseIdx, UInt32 a_newCursorType) = 0;																																		// 03
				virtual bool						CheckAvm() = 0;																																																// 04
				virtual void						ClearDisplayList() = 0;																																														// 05
				virtual MovieDefRootNode*			CreateMovieDefRootNode(MemoryHeap* a_heap, MovieDefImpl* a_defImpl, bool a_importFlag = false) = 0;																											// 06
				virtual void						DoActions() = 0;																																															// 07
				virtual InteractiveObject*			FindTarget(const ASString& a_path) const = 0;																																								// 08
				virtual void						ForceCollect() = 0;																																															// 09
				virtual void						ForceEmergencyCollect() = 0;																																												// 0A
				virtual void						SuspendGC(bool suspend) = 0;																																												// 0B
				virtual void						ScheduleGC() = 0;																																															// 0C
				virtual void						GenerateMouseEvents(UInt32 a_mouseIndex) = 0;																																								// 0D
				virtual void						GenerateTouchEvents(UInt32 a_mouseStateIndex);																																								// 0E
				virtual void						GenerateGestureEvents(InteractiveObject* a_topmost, UInt32 a_phase, const Render::PointF& a_pos, const Render::PointF& a_offset, const Render::PointF& a_scale, float a_rotation, UInt32 a_gestureMask);	// 0F
				virtual DisplayObjContainer*		GetRootMovie(DisplayObject* a_dObj = 0) const = 0;																																							// 10
				virtual bool						Init(MovieDefImpl* a_movieDef) = 0;																																											// 11
				virtual void						NotifyMouseEvent(const InputEventsQueueEntry* a_queueEntry, const MouseState& a_mouseState, SInt32 a_mouseIndex) = 0;																						// 12
				virtual void						NotifyOnResize() = 0;																																														// 13
				virtual void						NotifyQueueSetFocus(InteractiveObject* a_ch, UInt32 a_controllerIdx, FocusMovedType a_fmt) = 0;																												// 14
				virtual void						NotifyTransferFocus(InteractiveObject* a_curFocused, InteractiveObject* a_newFocus, UInt32 a_controllerIdx) = 0;																							// 15
				virtual bool						NotifyOnFocusChange(InteractiveObject* a_curFocused, InteractiveObject* a_toBeFocused, UInt32 a_controllerIdx, FocusMovedType a_fmt, ProcessFocusKeyInfo* a_focusKeyInfo = 0) = 0;							// 16
				//virtual void						NotifyGamePadAnalogEvent(const EventID* a_id) { return; }																																					//
				virtual void						OnMovieFocus(bool a_set) = 0;																																												//
				virtual void						OnNextFrame() = 0;																																															//
				virtual void						OnDeviceOrientationChanged(const OrientationEvent& a_event);																																				//
				virtual void						OnAppLifecycleEvent(const AppLifecycleEvent& a_event);																																						//
				virtual void						PrintObjectsReport(UInt32 a_flags = 0, Log* a_log = 0, const char* a_swfName = 0);																															//
				virtual void						ProcessLoadQueueEntry(LoadQueueEntry* a_entry, LoadStates* a_ls) = 0;																																		//
				virtual void						ProcessLoadVarsMT(LoadQueueEntry* a_entry, LoadStates* a_ls, const String& a_data, UPInt a_fileLen, bool a_succeeded) = 0;																					//
				virtual void						ProcessLoadBinaryMT(LoadQueueEntry* a_entry, LoadStates* a_ls, const ArrayPOD<UInt8>& a_data, UPInt a_fileLen, bool a_succeeded);																			//
				virtual void						RegisterAuxASClasses() = 0;																																													//
				virtual void						ResolveStickyVariables(InteractiveObject* a_character) = 0;																																					//
				virtual void						SetExternalInterfaceRetVal(const Value& a_val) = 0;																																							//
				virtual void						SetMemoryParams(UInt32 a_frameBetweenCollections, UInt32 a_maxRootCount) = 0;																																//
				virtual void						Shutdown() = 0;																																																//
				virtual void						CreateString(Value* a_value, const char* a_string) = 0;																																						//
				virtual void						CreateStringW(Value* a_value, const wchar_t* a_string) = 0;																																					//
				virtual void						CreateObject(Value* a_value, const char* a_className = 0, const Value* a_args = 0, UInt32 a_numArgs = 0) = 0;																								//
				virtual void						CreateArray(Value* a_value) = 0;																																											//
				virtual void						CreateFunction(Value* a_value, FunctionHandler* a_fc, void* a_userData = 0) = 0;																															//
				virtual bool						SetVariable(const char* a_pathToVar, const Value& a_value, Movie::SetVarType a_setType = Movie::SetVarType::kSticky) = 0;																					//
				virtual bool						GetVariable(Value* a_val, const char* a_pathToVar) const = 0;																																				//
				virtual bool						SetVariableArray(Movie::SetArrayType a_type, const char* a_pathToVar, UInt32 a_index, const void* a_data, UInt32 a_count, Movie::SetVarType a_setType = Movie::SetVarType::kSticky) = 0;					//
				virtual bool						SetVariableArraySize(const char* a_pathToVar, UInt32 a_count, Movie::SetVarType a_setType = Movie::SetVarType::kSticky) = 0;																				//
				virtual UInt32						GetVariableArraySize(const char* a_pathToVar) = 0;																																							//
				virtual bool						GetVariableArray(Movie::SetArrayType a_type, const char* a_pathToVar, UInt32 a_index, void* a_data, UInt32 a_count) = 0;																					//
				virtual bool						IsAvailable(const char* a_pathToVar) const = 0;																																								//
				virtual bool						Invoke(const char* a_pathToMethod, Value* a_result, const Value* a_args, UInt32 a_numArgs) = 0;																												//
				virtual bool						Invoke(const char* a_pathToMethod, Value* a_result, const char* a_argFmt, ...) = 0;																															//
				virtual bool						InvokeArgs(const char* a_pathToMethod, Value* a_result, const char* a_argFmt, std::va_list a_args) = 0;																										//
				virtual MemoryContext*				GetMemoryContext() const = 0;																																												//
				virtual ASStringManager*			GetStringManager() const = 0;																																												//
				virtual Render::Text::Allocator*	GetTextAllocator() = 0;																																														//

				SInt32		GetAVMVersion() const;
				ASSupport*	GetASSupport() const;
				MovieImpl*	GetMovieImpl() const;

			protected:
				// members
				MovieImpl*		_movieImpl;		// 10
				Ptr<ASSupport>	_asSupport;		// 18
				UInt8			_avmVersion;	// 20
			};
			STATIC_ASSERT(sizeof(ASMovieRootBase) == 0x28);
		}
	}
}
