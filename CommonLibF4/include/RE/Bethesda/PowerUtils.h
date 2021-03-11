#pragma once

#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/CRC.h"
#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	namespace PowerUtils
	{
		struct GridConnection
		{
		public:
			~GridConnection() noexcept {}  // NOLINT(modernize-use-equals-default)

			// members
			std::uint32_t connection{ 0 };  // 0 - the powered object
			std::uint32_t connector{ 0 };   // 4 - how the object is connected
		};
		static_assert(sizeof(GridConnection) == 0x8);
	}

	template <>
	struct BSCRC32<PowerUtils::GridConnection>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const PowerUtils::GridConnection& a_connection) const noexcept
		{
			return detail::GenerateCRC32(
				std::span(
					reinterpret_cast<const std::uint8_t*>(std::addressof(a_connection)),
					sizeof(PowerUtils::GridConnection)));
		}
	};

	namespace PowerUtils
	{
		struct GridSaveLoadData
		{
		public:
			// members
			std::uint32_t node{ 0 };    // 0
			GridConnection connection;  // 4
		};
		static_assert(sizeof(GridSaveLoadData) == 0xC);

		class PowerGrid
		{
		public:
			// members
			BSTHashMap<std::uint32_t, BSTSet<GridConnection>*> adjacencyMap;  // 00 - maps powered objects to the objects they connect to
			BSTArray<GridSaveLoadData> loadGameData;                          // 30
			std::uint32_t loadElement{ 0 };                                   // 48
			BSTArray<std::uint32_t> currentlyPowered;                         // 50
			float capacity{ 0.0 };                                            // 68
			float load{ 0.0 };                                                // 6C
		};
		static_assert(sizeof(PowerGrid) == 0x70);
	}
}
