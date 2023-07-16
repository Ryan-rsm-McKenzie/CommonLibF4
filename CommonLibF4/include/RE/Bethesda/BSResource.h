#pragma once

#include "RE/Bethesda/Atomic.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSSystemFile.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTSingleton.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/NetImmerse/NiBinaryStream.h"

namespace RE
{
	class BSEventFlag;
}

namespace RE::BSResource
{
	class ICacheDriveOp;
	class LocationTraverser;

	enum class ErrorCode
	{
		kNone = 0,
		kNotExist = 1,
		kInvalidPath = 2,
		kFileError = 3,
		kInvalidType = 4,
		kMemoryError = 5,
		kBusy = 6,
		kInvalidParam = 7,
		kUnsupported = 8
	};

	enum class SeekMode
	{
		kSet = 0,
		kCur = 1,
		kEnd = 2
	};

	struct FileID
	{
	public:
		[[nodiscard]] bool operator==(const FileID&) const noexcept = default;

		// members
		std::uint32_t file = 0;  // 0
		std::uint32_t ext = 0;   // 4
	};
	static_assert(sizeof(FileID) == 0x8);

	struct ID :
		public FileID  // 0
	{
	public:
		[[nodiscard]] bool operator==(const ID&) const noexcept = default;

		// members
		std::uint32_t dir = 0;  // 8
	};
	static_assert(sizeof(ID) == 0xC);

	struct LooseFileStreamBase
	{
	public:
		static constexpr auto RTTI{ RTTI::BSResource____LooseFileStreamBase };

		[[nodiscard]] std::string_view GetDirName() const { return dirName; }
		[[nodiscard]] std::string_view GetFileName() const { return fileName; }
		[[nodiscard]] std::string_view GetPrefix() const { return prefix; }

		// members
		BSFixedString prefix;             // 00
		BSFixedString dirName;            // 08
		BSFixedString fileName;           // 10
		BSSystemFile file;                // 18
		BSSystemFileStreamer::ID pathID;  // 28
	};
	static_assert(sizeof(LooseFileStreamBase) == 0x30);

	struct Info
	{
	public:
		// members
		_FILETIME modifyTime;    // 00
		_FILETIME createTime;    // 08
		std::uint64_t fileSize;  // 10
	};
	static_assert(sizeof(Info) == 0x18);

	class __declspec(novtable) StreamBase
	{
	public:
		static constexpr auto RTTI{ RTTI::BSResource__StreamBase };
		static constexpr auto VTABLE{ VTABLE::BSResource__StreamBase };

		StreamBase() noexcept = default;
		StreamBase(const StreamBase& a_other) noexcept :
			totalSize(a_other.totalSize),
			flags(a_other.flags & 0x1)
		{}

		StreamBase& operator=(const StreamBase& a_other) noexcept
		{
			if (this != &a_other) {
				this->totalSize = a_other.totalSize;
				this->flags = a_other.flags & 0x1;
			}
			return *this;
		}

		virtual ~StreamBase() {}  // 00

		// add
		virtual ErrorCode DoOpen() = 0;                                                      // 01
		virtual void DoClose() = 0;                                                          // 02
		[[nodiscard]] virtual std::uint64_t DoGetKey() const { return 0xFFFFFFFF00000000; }  // 03
		virtual ErrorCode DoGetInfo(
			[[maybe_unused]] Info& a_result) { return ErrorCode::kUnsupported; }  // 04

		[[nodiscard]] bool IsWritable() const noexcept { return (this->flags & 0x1) != 0; }

		F4_HEAP_REDEFINE_NEW(StreamBase);

		std::uint32_t IncRef()
		{
			auto atomic = stl::atomic_ref(this->flags);
			std::uint32_t expected = 0;
			std::uint32_t desired = 0;
			do {
				expected = flags;
				desired = expected + 0x1000;
			} while (!atomic.compare_exchange_weak(expected, desired));
			return desired & 0xFFFFF000;
		}

		std::uint32_t DecRef()
		{
			auto atomic = stl::atomic_ref(this->flags);
			std::uint32_t expected = 0;
			std::uint32_t desired = 0;
			do {
				expected = flags;
				desired = expected - 0x1000;
			} while (!atomic.compare_exchange_weak(expected, desired));
			return desired & 0xFFFFF000;
		}

		// members
		std::uint32_t totalSize = 0;  // 08
		std::uint32_t flags = 0;      // 0C
	};
	static_assert(sizeof(StreamBase) == 0x10);

	class __declspec(novtable) AsyncStream :
		public StreamBase  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSResource__AsyncStream };
		static constexpr auto VTABLE{ VTABLE::BSResource__AsyncStream };

		struct PacketAlignedBuffer
		{
		public:
			std::uint64_t resultOffset = 0;     // 00
			std::uint32_t bufferSize = 0;       // 08
			void* packetBuffer = nullptr;       // 10
			std::uint32_t dataRequestSize = 0;  // 18
			std::uint32_t dataSize = 0;         // 1C
			void* dataStart = nullptr;          // 20
		};
		static_assert(sizeof(PacketAlignedBuffer) == 0x28);

		// add
		virtual void DoClone(BSTSmartPointer<AsyncStream>& a_result) const = 0;                                                                      // 05
		virtual ErrorCode DoStartRead(void* a_buffer, std::uint64_t a_bytes, std::uint64_t a_offset) const = 0;                                      // 06
		virtual ErrorCode DoStartPacketAlignedBufferedRead(PacketAlignedBuffer* a_buffer, std::uint64_t a_bytes, std::uint64_t a_offset) const = 0;  // 07
		virtual ErrorCode DoStartWrite(const void* a_buffer, std::uint64_t a_bytes, std::uint64_t a_offset) const = 0;                               // 08
		virtual ErrorCode DoTruncate(std::uint64_t a_bytes) const = 0;                                                                               // 09
		virtual ErrorCode DoPrefetchAt(
			[[maybe_unused]] std::uint64_t a_bytes,
			[[maybe_unused]] std::uint64_t a_pos,
			[[maybe_unused]] std::uint32_t a_priority) const { return ErrorCode::kUnsupported; }  // 0A
		virtual ErrorCode DoWait(std::uint64_t& a_transferred, bool a_block) = 0;                 // 0B

		// members
		std::uint32_t minPacketSize = 0;  // 10
	};
	static_assert(sizeof(AsyncStream) == 0x18);

	class __declspec(novtable) Stream :
		public StreamBase  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSResource__Stream };
		static constexpr auto VTABLE{ VTABLE::BSResource__Stream };

		// add
		virtual void DoClone(BSTSmartPointer<Stream>& a_result) const = 0;                                 // 05
		virtual ErrorCode DoRead(void* a_buffer, std::uint64_t a_bytes, std::uint64_t& a_read) const = 0;  // 06
		virtual ErrorCode DoReadAt(
			[[maybe_unused]] void* a_buffer,
			[[maybe_unused]] std::uint64_t a_bytes,
			[[maybe_unused]] std::uint64_t a_pos,
			[[maybe_unused]] std::uint64_t& a_read) const { return ErrorCode::kUnsupported; }                      // 07
		virtual ErrorCode DoWrite(const void* a_buffer, std::uint64_t a_bytes, std::uint64_t& a_write) const = 0;  // 08
		virtual ErrorCode DoSeek(std::int64_t a_offset, SeekMode a_whence, std::uint64_t& a_pos) const = 0;        // 09
		virtual ErrorCode DoSetEndOfStream() { return ErrorCode::kUnsupported; }                                   // 0A
		virtual ErrorCode DoPrefetchAt(
			[[maybe_unused]] std::uint64_t a_bytes,
			[[maybe_unused]] std::uint64_t a_offset,
			[[maybe_unused]] std::uint32_t a_priority) const { return ErrorCode::kUnsupported; }  // 0B
		virtual ErrorCode DoStartTaggedPrioritizedRead(
			[[maybe_unused]] void* a_buffer,
			[[maybe_unused]] std::uint64_t a_bytes,
			[[maybe_unused]] std::uint64_t a_offset,
			[[maybe_unused]] std::uint32_t a_priority,
			[[maybe_unused]] volatile std::uint32_t* a_completionTagOut,
			[[maybe_unused]] std::uint32_t& a_completionTagWaitValue,
			[[maybe_unused]] BSEventFlag* a_eventFlag) const { return ErrorCode::kUnsupported; }  // 0C
		virtual ErrorCode DoWaitTags(
			[[maybe_unused]] volatile std::uint32_t* a_completionTag,
			[[maybe_unused]] std::uint32_t a_completionTagWaitValue,
			[[maybe_unused]] BSEventFlag* a_eventFlag) const { return ErrorCode::kUnsupported; }  // 0D
		virtual ErrorCode DoPrefetchAll(
			[[maybe_unused]] std::uint32_t a_priority) const { return ErrorCode::kUnsupported; }  // 0E
		virtual bool DoGetName(BSFixedString& a_result) const                                     // 0F
		{
			a_result = {};
			return false;
		}
		virtual ErrorCode DoCreateAsync(
			[[maybe_unused]] BSTSmartPointer<AsyncStream>& a_result) const { return ErrorCode::kUnsupported; }                            // 10
		[[nodiscard]] virtual bool DoQTaggedPrioritizedReadSupported() const { return false; }                                            // 11
		virtual ErrorCode DoCreateOp(BSTSmartPointer<BSResource::ICacheDriveOp>&, const char*) const { return ErrorCode::kUnsupported; }  // 12
		[[nodiscard]] virtual bool DoGetIsFromArchive() const { return false; }                                                           // 13
	};
	static_assert(sizeof(Stream) == 0x10);

	class __declspec(novtable) Location
	{
	public:
		static constexpr auto RTTI{ RTTI::BSResource__Location };
		static constexpr auto VTABLE{ VTABLE::BSResource__Location };

		virtual ~Location() {}  // 00

		// add
		virtual ErrorCode DoMount() { return ErrorCode::kNone; }                                                                                                              // 01
		virtual void DoUnmount() { return; }                                                                                                                                  // 02
		virtual ErrorCode DoCreateStream(const char* a_path, BSTSmartPointer<Stream>& a_result, Location*& a_location, bool a_writable, LocationTraverser* a_traverser) = 0;  // 03
		virtual ErrorCode DoCreateAsyncStream(
			[[maybe_unused]] const char* a_path,
			[[maybe_unused]] BSTSmartPointer<AsyncStream>& a_result,
			[[maybe_unused]] Location*& a_location,
			[[maybe_unused]] bool a_writable,
			[[maybe_unused]] LocationTraverser* a_traverser) { return ErrorCode::kUnsupported; }       // 04
		virtual ErrorCode DoTraversePrefix(char const* a_prefix, LocationTraverser& a_traverser) = 0;  // 05
		virtual ErrorCode DoGetInfo(
			[[maybe_unused]] char const* a_path,
			[[maybe_unused]] Info& a_result,
			[[maybe_unused]] LocationTraverser* a_traverser) { return ErrorCode::kUnsupported; }  // 07
		virtual ErrorCode DoGetInfo(
			[[maybe_unused]] char const* a_path,
			[[maybe_unused]] Info& a_result,
			[[maybe_unused]] Location*& a_location) { return ErrorCode::kUnsupported; }  // 06
		virtual ErrorCode DoDelete(
			[[maybe_unused]] char const* a_path) { return ErrorCode::kUnsupported; }                 // 08
		[[nodiscard]] virtual char const* DoGetName() const { return nullptr; }                      // 09
		[[nodiscard]] virtual std::uint32_t DoQBufferHint() const { return 0x10000; }                // 0A
		[[nodiscard]] virtual std::uint32_t DoGetMinimumAsyncPacketSize() const { return 0x10000; }  // 0B

		F4_HEAP_REDEFINE_NEW(Location);

		// members
		bool mounted;  // 08
	};
	static_assert(sizeof(Location) == 0x10);

	class __declspec(novtable) GlobalPaths :
		public Location,                     // 00
		public BSTSingletonSDM<GlobalPaths>  // 10
	{
	public:
		static constexpr auto RTTI{ RTTI::BSResource____GlobalPaths };
		static constexpr auto VTABLE{ VTABLE::BSResource____GlobalPaths };

		[[nodiscard]] static GlobalPaths* GetSingleton()
		{
			REL::Relocation<GlobalPaths**> singleton{ REL::ID(210868) };
			return *singleton;
		}

		// members
		BSTArray<BSFixedString> names;  // 18
		Location* rootLocation;         // 30
	};
	static_assert(sizeof(GlobalPaths) == 0x38);

	class __declspec(novtable) GlobalLocations :
		public Location,                         // 00
		public BSTSingletonSDM<GlobalLocations>  // 10
	{
	public:
		static constexpr auto RTTI{ RTTI::BSResource____GlobalLocations };
		static constexpr auto VTABLE{ VTABLE::BSResource____GlobalLocations };

		struct Entry
		{
		public:
			// members
			Entry* next;             // 00
			Location* location;      // 08
			std::uint32_t priority;  // 10
		};
		static_assert(sizeof(Entry) == 0x18);

		[[nodiscard]] static GlobalLocations* GetSingleton()
		{
			REL::Relocation<GlobalLocations**> singleton{ REL::ID(1573818) };
			return *singleton;
		}

		// members
		BSSpinLock lock;      // 14
		Entry* head;          // 20
		Entry* pendingMount;  // 28
		Entry* free;          // 30
	};
	static_assert(sizeof(GlobalLocations) == 0x38);

	inline void RegisterLocation(Location* a_location, std::uint32_t a_priority)
	{
		using func_t = decltype(&RegisterLocation);
		REL::Relocation<func_t> func{ REL::ID(918408) };
		return func(a_location, a_priority);
	}
}

namespace RE
{
	class __declspec(novtable) BSResourceNiBinaryStream :
		public NiBinaryStream  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSResourceNiBinaryStream };
		static constexpr auto VTABLE{ VTABLE::BSResourceNiBinaryStream };

		struct BufferType;

		// members
		BSTSmartPointer<BSResource::Stream> stream;    // 10
		BSResourceNiBinaryStream::BufferType* buffer;  // 18
		std::uint64_t streamPos;                       // 20
		BSResource::ErrorCode lastError;               // 28
	};
	static_assert(sizeof(BSResourceNiBinaryStream) == 0x30);
}
