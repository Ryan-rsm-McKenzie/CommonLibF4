#pragma once

#include "RE/Scaleform/Kernel/SF_List.h"
#include "RE/Scaleform/Kernel/SF_Memory.h"
#include "RE/Scaleform/Kernel/SF_RefCount.h"
#include "RE/Scaleform/Kernel/SF_Threads.h"
#include "RE/Scaleform/Render/Render_Containers.h"
#include "RE/Scaleform/Render/Render_ThreadCommandQueue.h"

namespace RE::Scaleform::Render
{
	class TreeCacheNode;

	namespace ContextImpl
	{
		class Context;
		class ContextCaptureNotify;
		class ContextLock;
		class Entry;
		class EntryChange;
		class EntryData;
		class EntryTable;
		class RenderNotify;
		class RTHandle;
		class Snapshot;

		struct EntryListAccessor;
		struct EntryPage;
		struct EntryPageBase;
		struct SnapshotPage;

		class __declspec(novtable) ContextLock :
			public RefCountBase<ContextLock, 69>  // 00
		{
		public:
			// members
			Lock lockObject;   // 10
			Context* context;  // 38
		};
		static_assert(sizeof(ContextLock) == 0x40);

		class RTHandle
		{
		public:
			enum class HandleState : std::int32_t
			{
				kPreCapture,
				kValid,
				kDead
			};

			struct __declspec(novtable) HandleData :
				public RefCountBase<HandleData, 69>,  // 00
				public ListNode<HandleData>           // 10
			{
			public:
				// members
				Ptr<ContextLock> contextLock;                       // 20
				stl::enumeration<HandleState, std::int32_t> state;  // 28
				Entry* entry;                                       // 30
			};
			static_assert(sizeof(HandleData) == 0x38);

			// members
			Ptr<HandleData> data;  // 0
		};
		static_assert(sizeof(RTHandle) == 0x8);

		template <class C>
		class DisplayHandle :
			public RTHandle  // 0
		{
		public:
		};
		//static_assert(sizeof(DisplayHandle<void*>) == 0x8);

		class Entry
		{
		public:
			struct PropagateNode :
				public ListNode<PropagateNode>  // 00
			{
			public:
			};
			static_assert(sizeof(PropagateNode) == 0x10);

			// members
			union
			{
				Entry* prev;
				EntryChange* change;
			};  // 00
			union
			{
				Entry* next;
				std::size_t refCount;
			};                        // 08
			EntryData* native;        // 10
			TreeCacheNode* renderer;  // 18
			Entry* parent;            // 20
			PropagateNode node;       // 28
		};
		static_assert(sizeof(Entry) == 0x38);

		struct EntryListAccessor
		{
		public:
		};
		static_assert(std::is_empty_v<EntryListAccessor>);

		using EntryList = List2<Entry, EntryListAccessor>;
		static_assert(sizeof(EntryList) == 0x38);

		class __declspec(novtable) EntryData
		{
		public:
			enum class EntryType : std::uint16_t
			{
				kBase,
				kRoot,
				kContainer,
				kShape,
				kMesh,
				kText
			};

			virtual ~EntryData();  // 00

			// add
			virtual EntryData* ConstructCopy(LinearHeap& a_heap) const = 0;  // 01
			virtual void CopyTo(void* a_dest) const = 0;                     // 02
			virtual void ReleaseNodes() const {}                             // 03
			virtual void Destroy() = 0;                                      // 04
			virtual bool PropagateUp(Entry* a_entry) const;                  // 05

			// members
			stl::enumeration<EntryType, std::uint16_t> type;  // 08
			std::uint16_t flags;                              // 0A
		};
		static_assert(sizeof(EntryData) == 0x10);

		class EntryChange
		{
		public:
			// members
			Entry* node;  // 00
			union
			{
				std::uint32_t changeBits;
				EntryChange* nextFreeNode;
			};  // 08
		};
		static_assert(sizeof(EntryChange) == 0x10);

		using ChangeBuffer = PagedItemBuffer<EntryChange, (0x400 - 16) / sizeof(EntryChange)>;

		class __declspec(novtable) RenderNotify
		{
		public:
			struct ContextNode :
				public ListNode<ContextNode>  // 00
			{
			public:
				// members
				Context* context;  // 10
			};
			static_assert(sizeof(ContextNode) == 0x18);

			class __declspec(novtable) ServiceCommand :
				public ThreadCommand  // 00
			{
			public:
				void Execute() override;  // 01

				// members
				RenderNotify* notify;  // 10
			};
			static_assert(sizeof(ServiceCommand) == 0x18);

			virtual ~RenderNotify();

			virtual void NewCapture(Context* a_context, bool a_hasChanges);
			virtual void ContextReleased(Context* a_context);
			virtual void ServiceQueues();
			virtual void EntryChanges(Context&, ChangeBuffer&, [[maybe_unused]] bool a_forceUpdateImages = false) {}
			virtual void EntryDestroy(Entry*) {}
			virtual void EntryFlush(Entry*) {}

			// members
			List<ContextNode> activeContextSet;     // 08
			ThreadCommandQueue* rtCommandQueue;     // 18
			ServiceCommand serviceCommandInstance;  // 20
		};
		static_assert(sizeof(RenderNotify) == 0x38);

		class __declspec(novtable) ContextCaptureNotify :
			public ListNode<ContextCaptureNotify>  // 00
		{
		public:
			virtual ~ContextCaptureNotify();  // 00

			// add
			virtual void OnCapture() {}                                             // 01
			virtual void OnNextCapture([[maybe_unused]] RenderNotify* a_notify) {}  // 02
			virtual void OnShutdown([[maybe_unused]] bool a_waitFlag) {}            // 03

			// members
			Context* ownedContext{ nullptr };  // 18
		};
		static_assert(sizeof(ContextCaptureNotify) == 0x20);

		struct EntryPageBase :
			public ListNode<EntryPageBase>  // 00
		{
		public:
			// members
			std::uint32_t useCount;             // 10
			Snapshot* snapshot;                 // 18
			SnapshotPage* snapshotPage;         // 20
			SnapshotPage* displaySnapshotPage;  // 28
			SnapshotPage* tempPage;             // 30
		};
		static_assert(sizeof(EntryPageBase) == 0x38);

		struct EntryPage :
			public EntryPageBase  // 000
		{
		public:
			// members
			Entry entries[72];  // 038
		};
		static_assert(sizeof(EntryPage) == 0xFF8);

		class EntryTable
		{
		public:
			// members
			Context* context;                           // 00
			MemoryHeap* heap;                           // 08
			List<EntryPage, EntryPageBase> entryPages;  // 10
			EntryList freeNodes;                        // 20
			Snapshot* activeSnapshot;                   // 58
		};
		static_assert(sizeof(EntryTable) == 0x60);

		struct SnapshotPage :
			public ListNode<SnapshotPage>  // 000
		{
		public:
			// members
			EntryPage* entryPage;             // 010
			SnapshotPage* olderSnapshotPage;  // 018
			SnapshotPage* newerSnapshotPage;  // 020
			EntryData* data[72];              // 028
		};
		static_assert(sizeof(SnapshotPage) == 0x268);

		class Context
		{
		public:
			using Entry = ContextImpl::Entry;

			// members
			MemoryHeap* heap;                              // 000
			ThreadId createThreadID;                       // 008
			EntryTable table;                              // 010
			Ptr<ContextLock> captureLock;                  // 070
			List<ContextCaptureNotify> captureNotifyList;  // 078
			RenderNotify* renderer;                        // 088
			bool multiThreadedUse;                         // 090
			bool nextCaptureCalledInFrame;                 // 091
			volatile bool captureCalled;                   // 092
			volatile bool diChangesRequired;               // 093
			volatile bool shutdownRequested;               // 094
			Event* volatile shutdownEvent;                 // 098
			RenderNotify::ContextNode renderNode;          // 0A0
			List<RTHandle::HandleData> rtHandleList;       // 0B8
			Snapshot* snapshots[4];                        // 0C8
			std::uint64_t snapshotFrameIDs[4];             // 0E8
			std::uint64_t finalizedFrameID;                // 108
		};
		static_assert(sizeof(Context) == 0x110);
	}

	using ContextImpl::Context;
	using ContextImpl::ContextCaptureNotify;
	using ContextImpl::DisplayHandle;
}
