#pragma once

#include "RE/Scaleform/GFx/GFx_Resource.h"
#include "RE/Scaleform/Kernel/SF_RefCount.h"
#include "RE/Scaleform/Kernel/SF_System.h"

namespace RE::Scaleform::GFx
{
	class LoaderImpl;
	class MovieDef;
	class ResourceLib;
	class System;

	class __declspec(novtable) State :
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

	class __declspec(novtable) ActionControl :
		public State  // 00
	{
	public:
		enum class ActionControlFlags : std::uint32_t
		{
			Action_Verbose = 0x01,
			Action_ErrorSuppress = 0x02,
			Action_LogRootFilenames = 0x04,
			Action_LogChildFilenames = 0x08,
			Action_LogAllFilenames = 0x04 | 0x08,
			Action_LongFilenames = 0x10
		};

		// members
		stl::enumeration<ActionControlFlags, std::uint32_t> actionFlags;  // 18
	};
	static_assert(sizeof(ActionControl) == 0x20);

	class __declspec(novtable) StateBag :
		public FileTypeConstants  // 00
	{
	protected:
		// add
		virtual StateBag* GetStateBagImpl() const { return nullptr; }  // 00

	public:
		virtual ~StateBag() = default;  // 01

		// NOLINTNEXTLINE(misc-no-recursion)
		virtual void SetState(State::StateType a_stateType, State* a_state)  // 02
		{
			assert(a_state ? true : a_state->GetStateType() == a_stateType);
			const auto bag = GetStateBagImpl();
			if (bag) {
				bag->SetState(a_stateType, a_state);
			}
		}

		// NOLINTNEXTLINE(misc-no-recursion)
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

	struct ExporterInfo
	{
	public:
		enum class ExportFlagConstants : std::uint32_t
		{
			kGlyphTexturesExported = 1 << 0,
			kGradientTexturesExported = 1 << 1,
			kGlyphsStripped = 1 << 4
		};

		// members
		stl::enumeration<FileTypeConstants::FileFormatType, std::int32_t> format;  // 00
		const char* prefix;                                                        // 08
		const char* swfName;                                                       // 10
		std::uint16_t version;                                                     // 18
		stl::enumeration<ExportFlagConstants, std::uint32_t> exportFlags;          // 1C
	};
	static_assert(sizeof(ExporterInfo) == 0x20);

	class __declspec(novtable) Loader :
		public StateBag  // 00
	{
	public:
		enum class LoadConstants : std::uint32_t
		{
			kAll = 0,
			kWaitCompletion = 1 << 0,
			kWaitFrame1 = 1 << 1,
			kOrdered = 1 << 4,
			kOnThread = 1 << 6,
			kKeepBindData = 1 << 7,
			kImageFiles = 1 << 16,
			kDisableSWF = 1 << 19,
			kDisableImports = 1 << 20,
			kQuietOpen = 1 << 21,

			kDebugHeap = 1 << 28
		};

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~Loader();  // 00

		// add
		virtual bool CheckTagLoader(std::int32_t a_tagType) const;  // 04

		[[nodiscard]] MovieDef* CreateMovie(const char* a_filename, LoadConstants a_loadConstants = LoadConstants::kAll, std::size_t a_memoryArena = 0)
		{
			using func_t = decltype(&Loader::CreateMovie);
			REL::Relocation<func_t> func{ REL::ID(912291) };
			return func(this, a_filename, a_loadConstants, a_memoryArena);
		}

		// members
		LoaderImpl* impl;                                             // 08
		ResourceLib* strongResourceLib;                               // 10
		stl::enumeration<LoadConstants, std::uint32_t> defLoadFlags;  // 18
	};
	static_assert(sizeof(Loader) == 0x20);

	class System :
		public Scaleform::System  // 0
	{
	public:
	};
	static_assert(std::is_empty_v<System>);
}
