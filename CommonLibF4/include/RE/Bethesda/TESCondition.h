#pragma once

#include "RE/Bethesda/BSPointerHandle.h"

namespace RE
{
	class TESGlobal;

	struct FUNCTION_DATA
	{
	public:
		// members
		std::uint16_t function;  // 00
		void* param[2];          // 08
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
		};                           // 00
		ObjectRefHandle runOnRef;    // 08
		std::uint32_t dataID;        // 0C
		FUNCTION_DATA FunctionData;  // 10
		std::int8_t flags;           // 28
		std::int8_t object;          // 29
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
		// members
		TESConditionItem* head;  // 0
	};
	static_assert(sizeof(TESCondition) == 0x8);
}
