#pragma once

#include "RE/Scaleform/GFx/GFx_Resource.h"
#include "RE/Scaleform/Kernel/SF_RefCount.h"

namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class State :
				public RefCountBase<State, 2>  // 00
			{
			public:
				enum class StateType : std::int32_t
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

				[[nodiscard]] constexpr StateType GetStateType() const noexcept { return *sType; }

			protected:
				// members
				stl::enumeration<StateType, std::int32_t> sType;  // 10
			};
			static_assert(sizeof(State) == 0x18);

			class StateBag :
				public FileTypeConstants  // 00
			{
			protected:
				// add
				virtual StateBag* GetStateBagImpl() const { return nullptr; }  // 00

			public:
				virtual ~StateBag() = default;	// 01

				virtual void SetState(State::StateType a_stateType, State* a_state)	 // 02
				{
					assert(a_state ? true : a_state->GetStateType() == a_stateType);
					const auto bag = GetStateBagImpl();
					if (bag) {
						bag->SetState(a_stateType, a_state);
					}
				}

				virtual State* GetStateAddRef(State::StateType a_stateType) const  // 03
				{
					const auto bag = GetStateBagImpl();
					return bag ? bag->GetStateAddRef(a_stateType) : nullptr;
				}

				virtual void GetStatesAddRef(State** a_states, const State::StateType* a_stateTypes, std::uint32_t a_count) const  // 04
				{
					const auto bag = GetStateBagImpl();
					if (bag) {
						bag->GetStatesAddRef(a_states, a_stateTypes, a_count);
					}
				}
			};
			static_assert(sizeof(StateBag) == 0x8);
		}
	}
}
