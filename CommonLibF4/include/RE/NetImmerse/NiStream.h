#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/NetImmerse/NiTArray.h"
#include "RE/NetImmerse/NiTLargeArray.h"
#include "RE/NetImmerse/NiTPointerMap.h"

namespace RE
{
	class NiBinaryStream;
	class NiObject;
	class NiObjectGroup;
	class NiSearchPath;

	struct BSStreamHeader
	{
	public:
		// members
		std::uint32_t version;   // 000
		char author[64];         // 004
		char processScript[64];  // 044
		char exportScript[64];   // 084
		char maxFilePath[260];   // 0C4
	};
	static_assert(sizeof(BSStreamHeader) == 0x1C8);

	class __declspec(novtable) NiStream
	{
	public:
		static constexpr auto RTTI{ RTTI::NiStream };
		static constexpr auto VTABLE{ VTABLE::NiStream };

		virtual ~NiStream();  // 00

		// add
		bool Load(NiBinaryStream* a_istr);                                  // 01
		bool Load(char* a_buffer, std::uint64_t a_bufferSize);              // 02
		bool Load(const char* a_fileName);                                  // 03
		bool Save(NiBinaryStream* a_ostr);                                  // 04
		bool Save(char*& a_buffer, std::uint64_t& a_bufferSize);            // 05
		bool Save(const char* a_fileName);                                  // 06
		bool RegisterFixedString(const BSFixedString& a_string);            // 07
		bool RegisterSaveObject(NiObject* a_object);                        // 08
		void ChangeObject(NiObject* a_newObject);                           // 09
		std::uint32_t GetLinkIDFromObject(const NiObject* a_object) const;  // 0A
		void SaveLinkID(const NiObject* a_object);                          // 0B
		bool LoadHeader();                                                  // 0C
		void SaveHeader();                                                  // 0D
		bool LoadStream();                                                  // 0E
		bool SaveStream();                                                  // 0F
		void RegisterObjects();                                             // 10
		void LoadTopLevelObjects();                                         // 11
		void SaveTopLevelObjects();                                         // 12
		bool LoadObject();                                                  // 13
		std::uint64_t PreSaveObjectSizeTable();                             // 14
		bool SaveObjectSizeTable(std::uint64_t a_startOffset);              // 15
		bool LoadObjectSizeTable();                                         // 16

		[[nodiscard]] std::string_view GetFileName() const { return fileName; }

		// members
		BSStreamHeader bsStreamHeader;                              // 008
		BSTSmallArray<NiObjectGroup*, 4> groups;                    // 1D0
		std::uint32_t nifFileVersion;                               // 200
		std::uint32_t nifFileUserDefinedVersion;                    // 204
		char fileName[260];                                         // 208
		bool saveLittleEndian;                                      // 30C
		bool sourceIsLittleEndian;                                  // 30D
		NiSearchPath* searchPath;                                   // 310
		NiTLargeObjectArray<NiPointer<NiObject>> objects;           // 318
		NiTLargePrimitiveArray<std::uint32_t> objectSizes;          // 338
		NiTLargeObjectArray<NiPointer<NiObject>> topObjects;        // 358
		NiTLargeObjectArray<BSFixedString> fixedStrings;            // 378
		NiBinaryStream* istr;                                       // 398
		NiBinaryStream* ostr;                                       // 3A0
		std::uint32_t linkIndex;                                    // 3A8
		std::uint32_t linkBlockIndex;                               // 3AC
		NiTPointerMap<const NiObject*, std::uint32_t> registerMap;  // 3B0
		std::uint16_t niAVObjectFlags;                              // 3D0
		std::uint16_t niTimeControllerFlags;                        // 3D2
		std::uint16_t niPropertyFlags;                              // 3D4
		std::uint16_t streamFlags;                                  // 3D6
		std::uint32_t load;                                         // 3D8
		std::uint32_t link;                                         // 3DC
		std::uint32_t postLink;                                     // 3E0
		char lastLoadedRTTI[260];                                   // 3E4
		std::uint32_t lastError;                                    // 4E8
		char lastErrorMessage[260];                                 // 4EC
		char filePath[260];                                         // 5F0
	};
	static_assert(sizeof(NiStream) == 0x6F8);
}
