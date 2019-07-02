#pragma once


namespace RE
{
	struct FileHash
	{
		FO_HEAP_REDEFINE_NEW();

		// members
		UInt32	directoryHash;	// 0
		char	fileExtension;	// 4
		UInt32	fileHash;		// 8
	};
	STATIC_ASSERT(sizeof(FileHash) == 0xC);
}
