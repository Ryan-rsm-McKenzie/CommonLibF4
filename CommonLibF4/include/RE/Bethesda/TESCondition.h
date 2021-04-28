#pragma once

#include "RE/Bethesda/BSPointerHandle.h"

namespace RE
{
	class TESGlobal;
	class TESObjectREFR;

	struct ConditionCheckParams;

	enum class SCRIPT_OUTPUT;

	enum class CONDITIONITEMOBJECT : unsigned
	{
		kSelf,
		kTarget,
		kRef,
		kCombatTarget,
		kLinkedRef,
		kQuestAlias,
		kPackData,
		kEventData,
		kCommandTarget,
		kEventCameraRef,
		kMyKiller
	};

	enum class ENUM_COMPARISON_CONDITION : std::uint8_t
	{
		kEqual,
		kNotEqual,
		kGreaterThan,
		kGreaterThanEqual,
		kLessThan,
		kLessThanEqual
	};

	struct FUNCTION_DATA
	{
	public:
		// members
		stl::enumeration<SCRIPT_OUTPUT, std::uint16_t> function;  // 00
		void* param[2];                                           // 08
	};
	static_assert(sizeof(FUNCTION_DATA) == 0x18);

	struct CONDITION_ITEM_DATA
	{
	public:
		// members
		union
		{
			TESGlobal* global;
			float value;
		};                                                           // 00
		ObjectRefHandle runOnRef;                                    // 08
		std::uint32_t dataID;                                        // 0C
		FUNCTION_DATA functionData;                                  // 10
		std::uint8_t compareOr: 1;                                   // 28:0
		std::uint8_t aliasParams: 1;                                 // 28:1
		std::uint8_t valueIsGlobal: 1;                               // 28:2
		std::uint8_t packDataParams: 1;                              // 28:3
		std::uint8_t swapsSubjectAndTarget: 1;                       // 28:4
		ENUM_COMPARISON_CONDITION condition: 3;                      // 28:5
		stl::enumeration<CONDITIONITEMOBJECT, std::uint8_t> object;  // 29
	};
	static_assert(sizeof(CONDITION_ITEM_DATA) == 0x30);

	class TESConditionItem
	{
	public:
		// members
		TESConditionItem* next;    // 00
		CONDITION_ITEM_DATA data;  // 08
	};
	static_assert(sizeof(TESConditionItem) == 0x38);

	class TESCondition
	{
	public:
		[[nodiscard]] explicit operator bool() const noexcept { return head != nullptr; }

		[[nodiscard]] bool operator()(TESObjectREFR* a_actionRef, TESObjectREFR* a_targetRef) const
		{
			return IsTrue(a_actionRef, a_targetRef);
		}

		[[nodiscard]] bool IsTrue(TESObjectREFR* a_actionRef, TESObjectREFR* a_targetRef) const
		{
			using func_t = decltype(&TESCondition::IsTrue);
			REL::Relocation<func_t> func{ REL::ID(1275731) };
			return func(this, a_actionRef, a_targetRef);
		}

		[[nodiscard]] bool IsTrueForAllButFunction(ConditionCheckParams& a_paramData, SCRIPT_OUTPUT a_function) const
		{
			using func_t = decltype(&TESCondition::IsTrueForAllButFunction);
			REL::Relocation<func_t> func{ REL::ID(1182457) };
			return func(this, a_paramData, a_function);
		}

		// members
		TESConditionItem* head;  // 0
	};
	static_assert(sizeof(TESCondition) == 0x8);
}
