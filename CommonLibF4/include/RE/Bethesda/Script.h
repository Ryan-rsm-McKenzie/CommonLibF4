#pragma once

#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/BSTList.h"
#include "RE/Bethesda/MemoryManager.h"
#include "RE/Bethesda/TESForms.h"

namespace RE
{
	enum class COMPILER_NAME
	{
		kDefault,
		kSystemWindow,
		kDialogue
	};

	enum class SCRIPT_PARAM_TYPE
	{
		kChar,
		kInt,
		kFloat,
		kInventoryObject,
		kObjectRef,
		kActorValue,
		kActor,
		kSpellItem,
		kAxis,
		kCell,
		kAnimGroup,
		kMagicItem,
		kSound,
		kTopic,
		kQuest,
		kRace,
		kClass,
		kFaction,
		kSex,
		kGlobal,
		kFurnitureOrFormList,
		kObject,
		kScriptVar,
		kStage,
		kMapMarker,
		kActorBase,
		kContainerRef,
		kWorlOrList,
		kCrimeType,
		kPackage,
		kCombatStyle,
		kMagicEffect,
		kFormType,
		kWeather,
		kNPC,
		kOwner,
		kShaderEffect,
		kFormList,
		kMenuIcon,
		kPerk,
		kNote,
		kMiscStat,
		kImageSpaceMod,
		kImageSpace,
		kVATSValue,
		kVATSValueData,
		kEventFunction,
		kEventFunctionMember,
		kEventFunctionData,
		kVoiceType,
		kEncounterZone,
		kIdleForm,
		kMessage,
		kInvObjectOrFormList,
		kAlignment,
		kEquipType,
		kObjectOrFormList,
		kMusic,
		kCritStage,
		kKeyword,
		kRefType,
		kLocation,
		kForm,
		kAlias,
		kShout,
		kWordOfPower,
		kRelationshipRank,
		kBGSScene,
		kCastingSource,
		kAssociationType,
		kWardState,
		kPackageDataCanBeNull,
		kPackageDataNumeric,
		kPackageDataReference,
		kVMScriptVar,
		kReferenceEffect,
		kPackageDataLocation,
		kSoundCategory,
		kKnowableForm,
		kRegion,
		kAction,
		kMovementIdleFromState,
		kMovementIdleToState,
		kVMRefOrAliasScript,
		kDamageType,
		kSceneAction,
		kKeywordOrFormlist,
		kFurnEntryType
	};

	enum class SCRIPT_ERROR;
	enum class SCRIPT_OUTPUT;

	class BGSPackageDataList;
	class BGSStoryEvent;

	struct SCRIPT_PARAMETER
	{
	public:
		// members
		const char* paramName{ "" };                                  // 00
		stl::enumeration<SCRIPT_PARAM_TYPE, std::int32_t> paramType;  // 08
		bool optional{ false };                                       // 0C
	};
	static_assert(sizeof(SCRIPT_PARAMETER) == 0x10);

	struct ACTION_OBJECT
	{
	public:
		// members
		TESForm* form;        // 00
		std::uint32_t flags;  // 08
	};
	static_assert(sizeof(ACTION_OBJECT) == 0x10);

	struct SCRIPT_LOCAL
	{
	public:
		// members
		std::uint32_t id;  // 0
		float value;       // 4
		bool isInteger;    // 8
	};
	static_assert(sizeof(SCRIPT_LOCAL) == 0xC);

	struct SCRIPT_EFFECT_DATA
	{
	public:
		// members
		bool scriptEffectStart;   // 0
		bool scriptEffectFinish;  // 1
		float secondsElapsed;     // 4
	};
	static_assert(sizeof(SCRIPT_EFFECT_DATA) == 0x8);

	class ScriptLocals
	{
	public:
		// members
		Script* masterScript;                      // 00
		std::int8_t flags;                         // 08
		BSSimpleList<ACTION_OBJECT*>* actionList;  // 10
		BSSimpleList<SCRIPT_LOCAL*>* localList;    // 18
		SCRIPT_EFFECT_DATA* scriptEffectData;      // 20
	};
	static_assert(sizeof(ScriptLocals) == 0x28);

	struct SCRIPT_LINE
	{
	public:
		// members
		std::uint32_t lineNumber;                                  // 000
		char line[512];                                            // 004
		std::uint32_t size;                                        // 204
		std::uint32_t offset;                                      // 208
		char output[512];                                          // 20C
		std::uint32_t outputSize;                                  // 40C
		SCRIPT_OUTPUT expression;                                  // 410
		std::uint32_t refObjectIndex;                              // 414
		stl::enumeration<SCRIPT_ERROR, std::int32_t> scriptError;  // 418
	};
	static_assert(sizeof(SCRIPT_LINE) == 0x41C);

	struct SCRIPT_HEADER
	{
	public:
		// members
		std::uint32_t variableCount;   // 00
		std::uint32_t refObjectCount;  // 04
		std::uint32_t dataSize;        // 08
		std::uint32_t lastID;          // 0C
		bool isQuestScript;            // 10
		bool isMagicEffectScript;      // 11
		bool isCompiled;               // 12
	};
	static_assert(sizeof(SCRIPT_HEADER) == 0x14);

	struct ScriptVariable
	{
	public:
		// members
		SCRIPT_LOCAL data;     // 00
		BSStringT<char> name;  // 10
	};
	static_assert(sizeof(ScriptVariable) == 0x20);

	struct SCRIPT_REFERENCED_OBJECT
	{
	public:
		// members
		BSStringT<char> editorID;  // 00
		TESForm* form;             // 10
		std::uint32_t variableID;  // 18
	};
	static_assert(sizeof(SCRIPT_REFERENCED_OBJECT) == 0x20);

	class ScriptCompileData
	{
	public:
		// members
		const char* input;                                            // 00
		std::uint32_t inputOffset;                                    // 08
		stl::enumeration<COMPILER_NAME, std::int32_t> compilerIndex;  // 0C
		BSStringT<char> scriptName;                                   // 10
		SCRIPT_ERROR lastError;                                       // 20
		bool isPartialScript;                                         // 24
		std::uint32_t uiLastLineNumber;                               // 28
		char* output;                                                 // 30
		std::uint32_t outputOffset;                                   // 38
		SCRIPT_HEADER header;                                         // 3C
		BSSimpleList<ScriptVariable*> listVariables;                  // 50
		BSSimpleList<SCRIPT_REFERENCED_OBJECT*> listRefObjects;       // 60
		Script* currentScript;                                        // 70
		BSSimpleList<SCRIPT_LINE*> listLines;                         // 78
	};
	static_assert(sizeof(ScriptCompileData) == 0x88);

	struct ConditionCheckParams
	{
	public:
		// members
		TESObjectREFR* actionRef{ nullptr };                      // 00
		TESObjectREFR* targetRef{ nullptr };                      // 08
		const TESQuest* scopeQuest{ nullptr };                    // 10
		const BGSStoryEvent* scopeEvent{ nullptr };               // 18
		Actor* scopeActor{ nullptr };                             // 20
		const BGSPackageDataList* runningPackageData{ nullptr };  // 28
		BGSMod::Template::Item* objectTemplateItem{ nullptr };    // 30
		const TESForm* extraForms[5]{ nullptr };                  // 38
		std::uint32_t extraFormCount{ 0 };                        // 60
		bool outDispFailure{ false };                             // 64
	};
	static_assert(sizeof(ConditionCheckParams) == 0x68);

	struct SCRIPT_FUNCTION
	{
	public:
		using ConditionFunction_t = bool(ConditionCheckParams& a_data, void* a_param2, void* a_param1, float& a_returnValue);
		using CompileFunction_t = bool(const std::uint16_t a_paramCount, const SCRIPT_PARAMETER* a_parameters, SCRIPT_LINE* a_scriptLine, ScriptCompileData* a_compileData);
		using ExecuteFunction_t = bool(const SCRIPT_PARAMETER* a_parameters, const char* a_compiledParams, TESObjectREFR* a_refObject, TESObjectREFR* a_container, Script* a_script, ScriptLocals* a_scriptLocals, float& a_returnValue, std::uint32_t& a_offset);

		[[nodiscard]] static std::span<SCRIPT_FUNCTION, 522> GetConsoleFunctions()
		{
			REL::Relocation<SCRIPT_FUNCTION(*)[522]> functions{ REL::ID(901511) };
			return { *functions };
		}

		[[nodiscard]] static std::span<SCRIPT_FUNCTION, 819> GetScriptFunctions()
		{
			REL::Relocation<SCRIPT_FUNCTION(*)[819]> functions{ REL::ID(75173) };
			return { *functions };
		}

		// members
		const char* functionName{ "" };                                                                      // 00
		const char* shortName{ "" };                                                                         // 08
		stl::enumeration<SCRIPT_OUTPUT, std::int32_t> output;                                                // 10
		const char* helpString{ "" };                                                                        // 18
		bool referenceFunction{ false };                                                                     // 20
		std::uint16_t paramCount{ 0 };                                                                       // 22
		SCRIPT_PARAMETER* parameters{ nullptr };                                                             // 28
		ExecuteFunction_t* executeFunction{ nullptr };                                                       // 30
		CompileFunction_t* compileFunction{ REL::Relocation<CompileFunction_t*>{ REL::ID(638606) }.get() };  // 38
		ConditionFunction_t* conditionFunction{ nullptr };                                                   // 40
		bool editorFilter{ false };                                                                          // 48
		bool invalidatesCellList{ false };                                                                   // 49
	};
	static_assert(sizeof(SCRIPT_FUNCTION) == 0x50);

	class ScriptCompiler
	{
	public:
	};
	static_assert(std::is_empty_v<ScriptCompiler>);

	class __declspec(novtable) Script :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::Script };
		static constexpr auto VTABLE{ VTABLE::TESForm };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSCPT };

		template <class... Args>
		static bool ParseParameters(const SCRIPT_PARAMETER* a_parameters, const char* a_compiledParams, std::uint32_t& a_offset, TESObjectREFR* a_refObject, TESObjectREFR* a_container, Script* a_script, ScriptLocals* a_scriptLocals, Args... a_args)
		{
			static_assert((std::is_pointer_v<Args> && ...), "arguments must all be pointers");
			using func_t = bool(const SCRIPT_PARAMETER*, const char*, std::uint32_t&, TESObjectREFR*, TESObjectREFR*, Script*, ScriptLocals*, ...);
			REL::Relocation<func_t> func{ REL::ID(1607) };
			return func(a_parameters, a_compiledParams, a_offset, a_refObject, a_container, a_script, a_scriptLocals, a_args...);
		}

		void CompileAndRun(ScriptCompiler* a_compiler, COMPILER_NAME a_compilerIndex, TESObjectREFR* a_ownerObject)
		{
			using func_t = decltype(&Script::CompileAndRun);
			REL::Relocation<func_t> func{ REL::ID(526625) };
			return func(this, a_compiler, a_compilerIndex, a_ownerObject);
		}

		void SetText(std::string_view a_text)
		{
			if (text) {
				free(text);
				text = nullptr;
			}

			text = calloc<char>(a_text.length() + 1);
			std::memset(text, '\0', a_text.length() + 1);
			std::memcpy(text, a_text.data(), a_text.length());
		}

		// members
		SCRIPT_HEADER header;                                // 20
		char* text;                                          // 38
		std::byte* data;                                     // 40
		float profilerTimer;                                 // 48
		float questScriptDelay;                              // 4C
		float questScriptGetSecondsBuffer;                   // 50
		TESQuest* parentQuest;                               // 58
		BSSimpleList<SCRIPT_REFERENCED_OBJECT*> refObjects;  // 60
		BSSimpleList<ScriptVariable*> variables;             // 70
	};
	static_assert(sizeof(Script) == 0x80);
}
