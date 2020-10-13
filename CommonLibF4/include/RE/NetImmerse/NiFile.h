#pragma once

#include "RE/Bethesda/BSSystemFile.h"
#include "RE/NetImmerse/NiBinaryStream.h"

namespace RE
{
	class __declspec(novtable) NiFile :
		public NiBinaryStream  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::NiFile };
		static constexpr auto VTABLE{ VTABLE::NiFile };

		enum class OpenMode;

		// members
		std::size_t bufferAllocSize;                    // 10
		std::size_t bufferReadSize;                     // 18
		std::size_t pos;                                // 20
		std::size_t currentFilePos;                     // 28
		char* buffer;                                   // 30
		BSSystemFile systemFile;                        // 38
		stl::enumeration<OpenMode, std::int32_t> mode;  // 48
		bool good;                                      // 4C
	};
	static_assert(sizeof(NiFile) == 0x50);
}
