#pragma once


namespace RE
{
	namespace Scaleform
	{
		enum StatBasicValues : UInt32
		{
			kStatGroup_Default = 0,
			kStatGroup_Core = 16,

			kStat_Mem = kStatGroup_Default + 1,
			kStat_Default_Mem = kStat_Mem + 1,

			kStatHeap_Start = kStatGroup_Core,

			kStat_MaxID = 64 << 6,
			kStat_EntryCount = 512,

			kHeapID_Default = 1
		};


		enum StatGroup : UInt32
		{
			kStatGroup_Renderer = 1 << 6,
			kStatGroup_RenderGen = 2 << 6,
			kStatGroup_GFxFontCache = 3 << 6,
			kStatGroup_GFxMovieData = 4 << 6,
			kStatGroup_GFxMovieView = 5 << 6,
			kStatGroup_GFxRenderCache = 6 << 6,
			kStatGroup_GFxPlayer = 7 << 6,
			kStatGroup_GFxIME = 8 << 6,
			kStatGroup_GFxAmp = 9 << 6,

			kStat_Image_Mem = kStat_Default_Mem + 1,
			//kStat_Sound_Mem,
			kStat_String_Mem,
			//kStat_Video_Mem,

			kStat_Debug_Mem,
			kStat_DebugHUD_Mem,
			kStat_DebugTracker_Mem,
			kStat_StatBag_Mem,
		};


		enum HeapID : UInt32
		{
			kHeapID_Global = kHeapID_Default,
			kHeapID_MovieDef,
			kHeapID_MovieView,
			kHeapID_MovieData,
			kHeapID_Images,
			kHeapID_OtherHeaps,
			kHeapID_HUDHeaps,
			kHeapID_Video,
		};
	}
}
