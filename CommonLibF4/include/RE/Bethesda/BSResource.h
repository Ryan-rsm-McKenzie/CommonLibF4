#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSSystemFile.h"

namespace RE::BSResource
{
	struct FileID
	{
	public:
		// members
		std::uint32_t file;  // 0
		std::uint32_t ext;   // 4
	};
	static_assert(sizeof(FileID) == 0x8);

	struct ID :
		public FileID  // 0
	{
	public:
		// members
		std::uint32_t dir;  // 8
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
}
