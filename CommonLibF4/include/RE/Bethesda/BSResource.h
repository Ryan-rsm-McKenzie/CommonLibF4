#pragma once

namespace RE
{
	namespace BSResource
	{
		struct FileID
		{
		public:
			// members
			std::uint32_t file;	 // 0
			std::uint32_t ext;	 // 4
		};
		static_assert(sizeof(FileID) == 0x8);

		struct ID :
			public FileID  // 0
		{
		public:
			// members
			std::uint32_t dir;	// 8
		};
		static_assert(sizeof(ID) == 0xC);
	}
}
