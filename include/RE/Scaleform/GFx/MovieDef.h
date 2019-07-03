#pragma once

#include "RE/Scaleform/GFx/Resource.h"
#include "RE/Scaleform/GFx/ResourceID.h"
#include "RE/Scaleform/GFx/StateBag.h"
#include "RE/Scaleform/Render/Rect.h"

#undef GetFileAttributes


namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			class ThreadCommandQueue;
		}


		namespace GFx
		{
			class ActionControl;
			class MemoryContext;
			class Movie;
			struct ExporterInfo;
			struct MemoryParams;


			class MovieDef :
				public Resource,	// 00
				public StateBag		// 18
			{
			public:
				enum class FileAttrFlags : UInt32
				{
					kUseNetwork = 1 < 0,
					kUseActionScript3 = 1 << 3,
					kHasMetadata = 1 << 4
				};


				enum class VisitResourceMask : UInt32
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
					virtual ~ImportVisitor() = default;																			// 00

					// add
					virtual void Visit(MovieDef* a_parentDef, MovieDef* a_importDef, const char* a_importedMovieFilename) = 0;	// 01
				};
				STATIC_ASSERT(sizeof(ImportVisitor) == 0x8);


				struct ResourceVisitor : public FileTypeConstants
				{
					virtual ~ResourceVisitor() = default;																			// 00

					// add
					virtual void Visit(MovieDef* a_movieDef, Resource* a_resource, ResourceID a_id, const char* a_exportName) = 0;	// 01
				};
				STATIC_ASSERT(sizeof(ResourceVisitor) == 0x8);


				virtual UInt32				GetVersion() const = 0;																																	// 03
				virtual UInt32				GetLoadingFrame() const = 0;																															// 04
				virtual float				GetWidth() const = 0;																																	// 05
				virtual float				GetHeight() const = 0;																																	// 06
				virtual UInt32				GetFrameCount() const = 0;																																// 07
				virtual float				GetFrameRate() const = 0;																																// 08
				virtual Render::RectF		GetFrameRect() const = 0;																																// 09
				virtual UInt32				GetSWFFlags() const = 0;																																// 0A
				virtual const char*			GetFileURL() const = 0;																																	// 0B
				virtual void				WaitForLoadFinish(bool a_cancel = false) const = 0;																										// 0C
				virtual void				WaitForFrame(UInt32 a_frame) const = 0;																													// 0D
				virtual FileAttrFlags		GetFileAttributes() const = 0;																															// 0E
				virtual UInt32				GetMetadata(char* a_buff, UInt32 a_buffSize) const = 0;																									// 0F
				virtual MemoryHeap*			GetLoadDataHeap() const = 0;																															// 10
				virtual MemoryHeap*			GetBindDataHeap() const = 0;																															// 11
				virtual MemoryHeap*			GetImageHeap() const = 0;																																// 12
				virtual Resource*			GetMovieDataResource() const = 0;																														// 13
				virtual const ExporterInfo*	GetExporterInfo() const = 0;																															// 14
				virtual MemoryContext*		CreateMemoryContext(const char* a_heapName, const MemoryParams& a_memParams, bool a_debugHeap) = 0;														// 15
				virtual Movie*				CreateInstance(const MemoryParams& a_memParams, bool a_initFirstFrame, ActionControl* a_actionControl, Render::ThreadCommandQueue* a_queue = 0) = 0;	// 16
				virtual Movie*				CreateInstance(MemoryContext* a_memContext, bool a_initFirstFrame, ActionControl* a_actionControl, Render::ThreadCommandQueue* a_queue = 0) = 0;		// 17
				virtual void				VisitImportedMovies(ImportVisitor* a_visitor) = 0;																										// 18
				virtual void				VisitResources(ResourceVisitor* a_visitor, VisitResourceMask a_visitMask = VisitResourceMask::kAllImages) = 0;											// 19
				virtual Resource*			GetResource(const char* a_exportName) const = 0;																										// 1A

				Movie* CreateInstance(bool a_initFirstFrame = false, UPInt a_memoryArena = 0, ActionControl* a_actionControl = 0, Render::ThreadCommandQueue* a_queue = 0);
			};
			STATIC_ASSERT(sizeof(MovieDef) == 0x20);
		}
	}
}
