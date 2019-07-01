#pragma once


namespace RE
{
	struct FileHash
	{
		UInt32	directoryHash;	// 0
		char	fileExtension;	// 4
		UInt32	fileHash;		// 8
	};
	STATIC_ASSERT(sizeof(FileHash) == 0xC);
}
