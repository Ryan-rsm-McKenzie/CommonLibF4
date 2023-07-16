#pragma once

#include "RE/Bethesda/BSBTreeFile.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSResource.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTSmallIndexScatterTable.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/MemoryManager.h"

namespace RE::BSResource::Archive2
{
	class DataReader
	{
	public:
		class DataLoader
		{
		public:
			// members
			MemoryManager::AutoScrapBuffer buffer;  // 00
			BSTSmartPointer<Stream> stream;         // 08
			std::uint64_t initialPosition;          // 10
			std::uint64_t position;                 // 18
			std::uint64_t ioBufferPos;              // 20
			std::uint64_t ioBufferEnd;              // 28
		};
		static_assert(sizeof(DataLoader) == 0x30);

		class StringLoader :
			public DataLoader  // 000
		{
		public:
			char currentString[260];            // 030
			std::uint32_t totalStrings;         // 134
			std::uint32_t nextStringIndex;      // 138
			std::uint16_t currentStringLength;  // 13C
		};
		static_assert(sizeof(StringLoader) == 0x140);

		// members
		BSTSmartPointer<Stream> stream;  // 00
		DataLoader* dataLoader;          // 08
		StringLoader* stringLoader;      // 10
		std::uint32_t totalFiles;        // 18
	};
	static_assert(sizeof(DataReader) == 0x20);

	class RegisteredEvent
	{
	public:
		// members
		DataReader reader;             // 00
		ID nameID;                     // 20
		const char* nameText;          // 30
		std::uint32_t contentsFormat;  // 38
		std::uint32_t fileCount;       // 3C
	};
	static_assert(sizeof(RegisteredEvent) == 0x40);

	struct ClearRegistryEvent
	{
	public:
	};
	static_assert(std::is_empty_v<ClearRegistryEvent>);

	class __declspec(novtable) Index :
		public BSTEventSink<RegisteredEvent>,    // 0000
		public BSTEventSink<ClearRegistryEvent>  // 0008
	{
	public:
		static constexpr auto RTTI{ RTTI::BSResource__Archive2__Index };
		static constexpr auto VTABLE{ VTABLE::BSResource__Archive2__Index };

		class Pager;
		struct NameIDAccess;

		struct Chunk
		{
		public:
			// members
			std::uint64_t dataFileOffset = 0;    // 00
			std::uint32_t compressedSize = 0;    // 08
			std::uint32_t uncompressedSize = 0;  // 0C
		};
		static_assert(sizeof(Chunk) == 0x10);

		struct Loose
		{
		public:
			// members
			Location* location = nullptr;  // 00
			BSFixedString nameText;        // 08
		};
		static_assert(sizeof(Loose) == 0x10);

		struct EntryHeader
		{
		public:
			[[nodiscard]] bool IsChunk() const noexcept { return this->chunkOffsetOrType != 0; }
			[[nodiscard]] bool IsLoose() const noexcept { return this->chunkOffsetOrType == 0; }

			// members
			ID nameID;                            // 00
			std::uint8_t dataFileIndex = 0;       // 0C
			std::uint8_t chunkCount = 0;          // 0D
			std::uint16_t chunkOffsetOrType = 0;  // 0E
		};
		static_assert(sizeof(EntryHeader) == 0x10);

		class Entry :
			public EntryHeader  // 00
		{
		public:
			~Entry()
			{
				if (this->IsLoose()) {
					this->loose.~Loose();
				} else {
					this->chunk.~Chunk();
				}
			}

			// members
			union
			{
				Chunk chunk;
				Loose loose;
				std::byte buffer[std::max(sizeof(Chunk), sizeof(Loose))] = {};
			};                         // 10
			BSFixedString stringName;  // 20
		};
		static_assert(sizeof(Entry) == 0x28);

		class CursorWithEntry :
			public BSBTreeFile::BPTree<Pager, BSBTreeFile::PGFSEDL<Entry, ID, 4096>, 16>::Cursor  // 000
		{
		public:
			// members
			Entry e;  // 148
		};
		static_assert(sizeof(CursorWithEntry) == 0x170);

		// members
		BSTSmallIndexScatterTable<ID, NameIDAccess> nameTable;                     // 0010
		BSTSmartPointer<Stream> dataFiles[256];                                    // 0030
		BSTSmartPointer<AsyncStream> asyncDataFiles[256];                          // 0830
		ID dataFileNameIDs[256];                                                   // 1030
		std::uint32_t dataFileCount;                                               // 1C30
		BSBTreeFile::BPTree<Pager, BSBTreeFile::PGFSEDL<Entry, ID, 4096>, 16> tr;  // 1C38
		BSReadWriteLock lock;                                                      // 1C58
	};
	static_assert(sizeof(Index) == 0x1C60);

	class __declspec(novtable) ReaderStream :
		public Stream  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSResource__Archive2__ReaderStream };
		static constexpr auto VTABLE{ VTABLE::BSResource__Archive2__ReaderStream };

		struct PlatformContext;
		struct StandardContext;

		ReaderStream() { stl::emplace_vtable<ReaderStream>(this); }

		// override
		ErrorCode DoOpen() override  // 01
		{
			using func_t = decltype(&ReaderStream::DoOpen);
			REL::Relocation<func_t> func{ REL::ID(762048) };
			return func(this);
		}

		void DoClose() override  // 02
		{
			using func_t = decltype(&ReaderStream::DoClose);
			REL::Relocation<func_t> func{ REL::ID(109149) };
			return func(this);
		}

		std::uint64_t DoGetKey() const override  // 03
		{
			using func_t = decltype(&ReaderStream::DoGetKey);
			REL::Relocation<func_t> func{ REL::ID(772817) };
			return func(this);
		}

		void DoClone(BSTSmartPointer<Stream>& a_result) const override  // 05
		{
			using func_t = decltype(&ReaderStream::DoClone);
			REL::Relocation<func_t> func{ REL::ID(855081) };
			return func(this, a_result);
		}

		ErrorCode DoRead(void* a_buffer, std::uint64_t a_bytes, std::uint64_t& a_read) const override  // 06
		{
			using func_t = decltype(&ReaderStream::DoRead);
			REL::Relocation<func_t> func{ REL::ID(1359347) };
			return func(this, a_buffer, a_bytes, a_read);
		}

		ErrorCode DoWrite(const void*, std::uint64_t, std::uint64_t& a_write) const override  // 08
		{
			a_write = 0;
			return ErrorCode::kUnsupported;
		}

		ErrorCode DoSeek(std::int64_t a_offset, SeekMode a_whence, std::uint64_t& a_pos) const override  // 09
		{
			using func_t = decltype(&ReaderStream::DoSeek);
			REL::Relocation<func_t> func{ REL::ID(1000164) };
			return func(this, a_offset, a_whence, a_pos);
		}

		ErrorCode DoPrefetchAll(std::uint32_t a_priority) const override  // 0E
		{
			using func_t = decltype(&ReaderStream::DoPrefetchAll);
			REL::Relocation<func_t> func{ REL::ID(1518821) };
			return func(this, a_priority);
		}

		bool DoGetName(BSFixedString& a_result) const override  // 0F
		{
			a_result = this->name;
			return a_result.size() != 0;
		}

		ErrorCode DoCreateAsync(BSTSmartPointer<AsyncStream>& a_result) const override  // 10
		{
			using func_t = decltype(&ReaderStream::DoCreateAsync);
			REL::Relocation<func_t> func{ REL::ID(893405) };
			return func(this, a_result);
		}

		bool DoGetIsFromArchive() const override { return true; }  // 13

		[[nodiscard]] bool IsCompressedStandard() const noexcept { return (this->flags & 0x100) != 0; }
		[[nodiscard]] bool IsCompressedPlatform() const noexcept { return (this->flags & 0x200) != 0; }
		[[nodiscard]] bool IsCompressed() const noexcept { return (this->flags & 0x300) != 0; }
		[[nodiscard]] bool CtxInFullRead() const noexcept { return (this->flags & 0x400) != 0; }
		[[nodiscard]] bool CtxInScrapHeap() const noexcept { return (this->flags & 0x800) != 0; }
		[[nodiscard]] bool CtxMultiplexed() const noexcept { return (this->flags & 0x1000) != 0; }
		[[nodiscard]] bool HasEmbeddedName() const noexcept { return (this->flags & 0x2000) != 0; }

		// members
		BSTSmartPointer<Stream> source;  // 10
		union
		{
			StandardContext* standardCtx = nullptr;
			PlatformContext* platformCtx;
		};                                        // 18
		const std::uint64_t startOffset = 0;      // 02
		BSFixedString name;                       // 28
		std::uint32_t currentRelativeOffset = 0;  // 30
		std::uint32_t compressedSize = 0;         // 34
		std::uint32_t uncompressedSize = 0;       // 38
		std::uint32_t flags = 0;                  // 3C
	};
	static_assert(sizeof(ReaderStream) == 0x40);

	class __declspec(novtable) AsyncReaderStream :
		public AsyncStream  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSResource__Archive2__AsyncReaderStream };
		static constexpr auto VTABLE{ VTABLE::BSResource__Archive2__AsyncReaderStream };

		AsyncReaderStream() { stl::emplace_vtable<AsyncReaderStream>(this); }

		// override
		ErrorCode DoOpen() override  // 01
		{
			using func_t = decltype(&AsyncReaderStream::DoOpen);
			REL::Relocation<func_t> func{ REL::ID(1401160) };
			return func(this);
		}

		void DoClose() override  // 02
		{
			using func_t = decltype(&AsyncReaderStream::DoClose);
			REL::Relocation<func_t> func{ REL::ID(883012) };
			return func(this);
		}

		void DoClone(
			BSTSmartPointer<AsyncStream>& a_result) const override  // 05
		{
			using func_t = decltype(&AsyncReaderStream::DoClone);
			REL::Relocation<func_t> func{ REL::ID(803750) };
			return func(this, a_result);
		}

		ErrorCode DoStartRead(
			void* a_buffer,
			std::uint64_t a_bytes,
			std::uint64_t a_offset) const override  // 06
		{
			using func_t = decltype(&AsyncReaderStream::DoStartRead);
			REL::Relocation<func_t> func{ REL::ID(1215072) };
			return func(this, a_buffer, a_bytes, a_offset);
		}

		ErrorCode DoStartPacketAlignedBufferedRead(
			PacketAlignedBuffer* a_buffer,
			std::uint64_t a_bytes,
			std::uint64_t a_offset) const override  // 07
		{
			using func_t = decltype(&AsyncReaderStream::DoStartPacketAlignedBufferedRead);
			REL::Relocation<func_t> func{ REL::ID(603387) };
			return func(this, a_buffer, a_bytes, a_offset);
		}

		ErrorCode DoStartWrite(
			const void*,
			std::uint64_t,
			std::uint64_t) const override  // 08
		{
			return ErrorCode::kUnsupported;
		}

		ErrorCode DoTruncate(
			std::uint64_t) const override  // 09
		{
			return ErrorCode::kUnsupported;
		}

		ErrorCode DoWait(
			std::uint64_t& a_transferred,
			bool a_block) override  // 0B
		{
			using func_t = decltype(&AsyncReaderStream::DoWait);
			REL::Relocation<func_t> func{ REL::ID(244066) };
			return func(this, a_transferred, a_block);
		}

		// members
		BSTSmartPointer<AsyncStream> source;           // 18
		std::uint64_t startOffset = 0;                 // 20
		PacketAlignedBuffer* currentBuffer = nullptr;  // 28
		BSFixedString nameText;                        // 30
	};
	static_assert(sizeof(AsyncReaderStream) == 0x38);
}
