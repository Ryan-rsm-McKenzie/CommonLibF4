#pragma once

#include "RE/Scaleform/GFx/CharacterDef.h"
#include "RE/Scaleform/GFx/State.h"
#include "RE/Scaleform/GFx/TagType.h"
#include "RE/Scaleform/Ptr.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class ASIMEManager;
			class ButtonDef;
			class DisplayObjectBase;
			class InteractiveObject;
			class LoadProcess;
			class MemoryContext;
			class MovieImpl;
			class PlaceObject2Tag;
			class PlaceObject3Tag;
			class RemoveObjectTag;
			class RemoveObject2Tag;
			class ResourceID;
			struct CharacterCreateInfo;
			struct MemoryParams;
			struct TagInfo;


			class ASSupport : public State
			{
			public:
				ASSupport(StateType a_stateType);

				// add
				virtual MovieImpl*				CreateMovie(MemoryContext* a_ctx) = 0;																																																	// 01
				virtual Ptr<GFx::ASIMEManager>	CreateASIMEManager() = 0;																																																				// 02
				virtual MemoryContext*			CreateMemoryContext(const char* a_heapName, const MemoryParams& a_memParams, bool a_debugHeap) = 0;																																		// 03
				virtual DisplayObjectBase*		CreateCharacterInstance(MovieImpl* a_root, const CharacterCreateInfo& a_charCreateInfo, InteractiveObject* a_parent, ResourceID a_resourceID, CharacterDef::CharacterDefType a_type = CharacterDef::CharacterDefType::kUnknown) = 0;	// 04
				virtual void					DoActions() = 0;																																																						// 05
				virtual UInt8					GetAVMVersion() const = 0;																																																				// 06
				virtual PlaceObject2Tag*		AllocPlaceObject2Tag(LoadProcess* a_proc, UPInt a_dataSize, UInt8 a_swfVer) = 0;																																						// 07
				virtual PlaceObject3Tag*		AllocPlaceObject3Tag(LoadProcess* a_proc, UPInt a_dataSize) = 0;																																										// 08
				virtual RemoveObjectTag*		AllocRemoveObjectTag(LoadProcess* a_proc) = 0;																																															// 09
				virtual RemoveObject2Tag*		AllocRemoveObject2Tag(LoadProcess* a_proc) = 0;																																															// 0A
				virtual void					DoActionLoader(LoadProcess* a_proc, const TagInfo& a_tagInfo) = 0;																																										// 0B
				virtual void					DoInitActionLoader(LoadProcess* a_proc, const TagInfo& a_tagInfo) = 0;																																									// 0C
				virtual void					ReadButtonActions(LoadProcess* a_proc, ButtonDef* a_buttonDef, TagType a_tagType) = 0;																																					// 0D
				virtual void					ReadButton2ActionConditions(LoadProcess* a_proc, ButtonDef* a_buttonDef, TagType a_tagType) = 0;																																		// 0E
			};
			STATIC_ASSERT(sizeof(ASSupport) == 0x18);
		}
	}
}
