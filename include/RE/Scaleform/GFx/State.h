#pragma once

#include "RE/Scaleform/RefCountBase.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class State : public RefCountBase<State, kStat_Default_Mem>
			{
			public:
				enum class StateType : UInt32
				{
					kNone,

					kTranslator,
					kLog,
					kActionControl,
					kUserEventHandler,
					kFSCommandHandler,
					kExternalInterface,
					kMultitouchInterface,
					kVirtualKeyboardInterface,

					kFileOpener,
					kURLBuilder,
					kImageCreator,
					kImageFileHandlerRegistry,
					kParseControl,
					kProgressHandler,
					kImportVisitor,
					kFontPackParams,
					kFontLib,
					kFontProvider,
					kFontMap,
					kTaskManager,
					kTextClipboard,
					kTextKeyMap,
					kIMEManager,
					kXMLSupport,
					kZlibSupport,
					kFontCompactorParams,
					kImagePackerParams,
					kAudio,
					kVideo,
					kTestStream,
					kSharedObject,
					kLocSupport,

					kAS2Support,
					kAS3Support
				};


				State(StateType a_state = StateType::kNone);
				virtual ~State() = default;	// 00

				StateType GetStateType() const;

			protected:
				StateType	_type;	// 10
				UInt32		_pad14;	// 14
			};
			STATIC_ASSERT(sizeof(State) == 0x18);
		}
	}
}
