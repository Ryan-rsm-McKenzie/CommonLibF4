#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSPointerHandle.h"
#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTSmallIndexScatterTable.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/TESCondition.h"
#include "RE/Bethesda/TESForms.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class BGSBaseAlias;
	class BGSQuestInstanceText;
	class BGSQuestObjective;
	class BGSRegisteredStoryEvent;
	class BGSStoryEvent;
	class BGSStoryManagerTreeForm;
	class PeriodicUpdateTimer;
	class BGSStoryManagerQuestNode;
	class QueuedPromoteQuestTask;
	class TESFile;
	class TESQuestStage;

	class __declspec(novtable) BGSStoryManagerTreeVisitor
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSStoryManagerTreeVisitor };
		static constexpr auto VTABLE{ VTABLE::BGSStoryManagerTreeVisitor };

		enum class VisitControl;

		virtual ~BGSStoryManagerTreeVisitor();  // 00

		virtual VisitControl VisitBranchNode(BGSStoryManagerBranchNode& a_node) = 0;                 // 01
		virtual VisitControl VisitQuestNode(BGSStoryManagerQuestNode& a_node, bool a_canReset) = 0;  // 02
		virtual VisitControl VisitQuest(TESQuest& a_quest) = 0;                                      // 03
		virtual void Revert() = 0;                                                                   // 04

		// members
		PeriodicUpdateTimer* timer;                         // 08
		std::int32_t currentCursorDepth;                    // 10
		BGSStoryManagerQuestNode* lastQuestParent;          // 18
		BSTArray<BGSStoryManagerTreeForm*> cursorAncestry;  // 20
		std::uint32_t queryID;                              // 38
	};
	static_assert(sizeof(BGSStoryManagerTreeVisitor) == 0x40);

	class __declspec(novtable) BGSStoryManagerTreeForm :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSStoryManagerTreeForm };
		static constexpr auto VTABLE{ VTABLE::BGSStoryManagerTreeForm };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNONE };

		// add
		virtual std::uint32_t QChildCount() const { return 0; }                                                      // 4A
		virtual BGSStoryManagerTreeForm* GetChild([[maybe_unused]] std::uint32_t a_index) const { return nullptr; }  // 4B
		virtual TESCondition* QConditions() = 0;                                                                     // 4C
		virtual BGSStoryManagerTreeVisitor::VisitControl AcceptVisitor(BGSStoryManagerTreeVisitor& a_visitor) = 0;   // 4D

		// members
		std::uint32_t lastVisitorID;  // 20
	};
	static_assert(sizeof(BGSStoryManagerTreeForm) == 0x28);

	struct QUEST_DATA
	{
	public:
		// members
		float questDelayTime;   // 0
		std::uint16_t flags;    // 4
		std::int8_t priority;   // 6
		std::int8_t questType;  // 7
	};
	static_assert(sizeof(QUEST_DATA) == 0x8);

	class __declspec(novtable) TESQuest :
		public BGSStoryManagerTreeForm,  // 000
		public TESFullName               // 028
	{
	public:
		static constexpr auto RTTI{ RTTI::TESQuest };
		static constexpr auto VTABLE{ VTABLE::TESQuest };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kQUST };

		struct AliasesAccess;
		struct ListObjectivesAccess;
		struct ListStagesAccess;

		// members
		BSTArray<BGSQuestInstanceText*> instanceData;                                                  // 038
		std::uint32_t currentInstanceID;                                                               // 050
		BSTArray<BSTTuple<TESFile*, std::uint32_t>> fileOffsets;                                       // 058
		BSTArray<BGSBaseAlias*> aliases;                                                               // 070
		BSTHashMap<std::uint32_t, BGSLocation*> aliasedLocMap;                                         // 088
		BSTArray<BSTSmallArray<ObjectRefHandle>> aliasedHandles;                                       // 0B8
		BSReadWriteLock aliasAccessLock;                                                               // 0D0
		BGSLocation* nonDormantLocation;                                                               // 0D8
		TESGlobal* questCompleteXPGlobal;                                                              // 0E0
		BSFixedString swfFile;                                                                         // 0E8
		QUEST_DATA data;                                                                               // 0F0
		std::uint32_t eventID;                                                                         // 0F8
		BSTArray<TESQuestStage*> stages;                                                               // 100
		BSTArray<BGSQuestObjective*> objectives;                                                       // 118
		BSTSmallIndexScatterTable<BSTArray<TESQuestStage*>, ListStagesAccess> stageTable;              // 130
		BSTSmallIndexScatterTable<BSTArray<BGSQuestObjective*>, ListObjectivesAccess> objectiveTable;  // 150
		BSTSmallIndexScatterTable<BSTArray<BGSBaseAlias*>, AliasesAccess> aliasesTable;                // 170
		TESCondition objConditions;                                                                    // 190
		TESCondition storyManagerConditions;                                                           // 198
		BSTHashMap<BGSDialogueBranch*, BSTArray<TESTopic*>*> branchedDialogues[2];                     // 1A0
		BSTArray<TESTopic*> topics[6];                                                                 // 200
		BSTArray<BGSScene*> scenes;                                                                    // 290
		BSTArray<TESGlobal*>* textGlobal;                                                              // 2A8
		std::uint32_t totalRefsAliased;                                                                // 2B0
		std::uint16_t currentStage;                                                                    // 2B4
		bool alreadyRun;                                                                               // 2B6
		BSStringT<char> formEditorID;                                                                  // 2B8
		const BGSStoryEvent* startEventData;                                                           // 2C8
		NiPointer<QueuedPromoteQuestTask> promoteTask;                                                 // 2D0
		BSTArray<ObjectRefHandle> promotedRefsArray;                                                   // 2D8
	};
	static_assert(sizeof(TESQuest) == 0x2F0);

	class __declspec(novtable) BGSStoryManagerNodeBase :
		public BGSStoryManagerTreeForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSStoryManagerNodeBase };
		static constexpr auto VTABLE{ VTABLE::BGSStoryManagerNodeBase };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNONE };

		// add
		virtual std::uint32_t GetQuestsStarted() const = 0;  // 4E

		// members
		BGSStoryManagerBranchNode* parent;     // 28
		BGSStoryManagerNodeBase* prevSibling;  // 30
		std::uint32_t maxQuests;               // 38
		std::uint32_t flags;                   // 3C
		TESCondition conditions;               // 40
	};
	static_assert(sizeof(BGSStoryManagerNodeBase) == 0x48);

	class __declspec(novtable) BGSStoryManagerBranchNode :
		public BGSStoryManagerNodeBase  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSStoryManagerBranchNode };
		static constexpr auto VTABLE{ VTABLE::BGSStoryManagerBranchNode };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSMBN };

		// members
		BSTArray<BGSStoryManagerNodeBase*> children;  // 48
	};
	static_assert(sizeof(BGSStoryManagerBranchNode) == 0x60);

	class __declspec(novtable) BGSStoryManagerQuestNode :
		public BGSStoryManagerNodeBase  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSStoryManagerQuestNode };
		static constexpr auto VTABLE{ VTABLE::BGSStoryManagerQuestNode };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSMQN };

		// members
		BSTArray<TESQuest*> children;                          // 48
		BSTHashMap<TESQuest*, std::uint32_t> perQuestFlags;    // 60
		BSTHashMap<TESQuest*, float> perQuestHoursUntilReset;  // 90
		std::uint32_t numQuestsToStart;                        // C0
		BSTArray<float> childrenLastRun;                       // C8
	};
	static_assert(sizeof(BGSStoryManagerQuestNode) == 0xE0);

	class __declspec(novtable) BGSStoryManagerEventNode :
		public BGSStoryManagerBranchNode  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSStoryManagerEventNode };
		static constexpr auto VTABLE{ VTABLE::BGSStoryManagerEventNode };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSMEN };

		// members
		const BGSRegisteredStoryEvent* event;  // 60
	};
	static_assert(sizeof(BGSStoryManagerEventNode) == 0x68);
}
