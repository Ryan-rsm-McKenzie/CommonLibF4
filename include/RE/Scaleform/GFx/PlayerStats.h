#pragma once

#include "RE/Scaleform/Stats.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			enum StatMovieView
			{
				kStatMV_Default = kStatGroup_GFxMovieView,

				kStatMV_Mem,
				kStatMV_MovieClip_Mem,
				kStatMV_ActionScript_Mem,
				kStatMV_ASString_Mem,
				kStatMV_Text_Mem,
				kStatMV_XML_Mem,
				kStatMV_Other_Mem,
				kStatMV_VM,
				kStatMV_VM_VM_Mem,
				kStatMV_VM_CallFrame_Mem,
				kStatMV_VM_VTable_Mem,
				kStatMV_VM_SlotInfo_Mem,
				kStatMV_VM_SlotInfoHash_Mem,
				kStatMV_VM_CTraits_Mem,
				kStatMV_VM_Class_Mem,
				kStatMV_VM_ITraits_Mem,
				kStatMV_VM_Instance_Mem,
				kStatMV_VM_AbcFile_Mem,
				kStatMV_VM_AbcConstPool_Mem,
				kStatMV_VM_VMAbcFile_Mem,
				kStatMV_VM_Tracer_Mem,

				kStatMV_Tks,
				kStatMV_Advance_Tks,
				kStatMV_Action_Tks,
				kStatMV_Seek_Tks,
				kStatMV_Timeline_Tks,
				kStatMV_Input_Tks,
				kStatMV_Mouse_Tks,
				kStatMV_ScriptCommunication_Tks,
				kStatMV_GetVariable_Tks,
				kStatMV_SetVariable_Tks,
				kStatMV_Invoke_Tks,
				kStatMV_InvokeAction_Tks,
				kStatMV_Display_Tks,
				kStatMV_Tessellate_Tks,
				kStatMV_GradientGen_Tks,

				kStatMV_Counters,
				kStatMV_Invoke_Cnt,
				kStatMV_MCAdvance_Cnt,
				kStatMV_Tessellate_Cnt
			};
		}
	}
}
