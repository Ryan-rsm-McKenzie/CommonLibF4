#pragma once

#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/TESForms.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	enum class EDGE_EXTRA_INFO_TYPE;

	class BSNavmeshInfo;
	class BSNavmeshObstacleData;
	class BSNavmeshObstacleUndoData;
	class BSPathingCell;
	class BSPathingDoor;

	struct FORM;

	struct BSNavmeshVertex
	{
	public:
		// members
		NiPoint3 location;  // 0
	};
	static_assert(sizeof(BSNavmeshVertex) == 0xC);

	struct BSNavmeshTriangle
	{
	public:
		// members
		std::uint16_t vertices[3];    // 00
		std::uint16_t triangles[3];   // 06
		float height;                 // 0C
		std::uint32_t triangleFlags;  // 10
		std::int8_t traversalFlags;   // 14
	};
	static_assert(sizeof(BSNavmeshTriangle) == 0x18);

	struct BSNavmeshTriangleEdgePortal
	{
	public:
		// members
		std::uint32_t otherMeshID;  // 0
		std::uint16_t triangle;     // 4
		std::int8_t edgeIndex;      // 6
	};
	static_assert(sizeof(BSNavmeshTriangleEdgePortal) == 0x8);

	struct BSNavmeshEdgeExtraInfo
	{
	public:
		// members
		stl::enumeration<EDGE_EXTRA_INFO_TYPE, std::int32_t> type;  // 0
		BSNavmeshTriangleEdgePortal portal;                         // 4
	};
	static_assert(sizeof(BSNavmeshEdgeExtraInfo) == 0xC);

	struct BSNavmeshTriangleDoorPortal
	{
	public:
		// members
		BSTSmartPointer<BSPathingDoor> door;  // 00
		std::uint16_t owningTriangleIndex;    // 08
	};
	static_assert(sizeof(BSNavmeshTriangleDoorPortal) == 0x10);

	struct BSNavmeshClosedDoorInfo
	{
	public:
		// members
		BSTSmartPointer<BSPathingDoor> door;  // 00
		std::uint16_t iriangleIndex;          // 08
	};
	static_assert(sizeof(BSNavmeshClosedDoorInfo) == 0x10);

	struct BSNavmeshCoverEdgeBase
	{
	public:
	};
	static_assert(std::is_empty_v<BSNavmeshCoverEdgeBase>);

	class BSNavmeshCoverEdge :
		public BSNavmeshCoverEdgeBase  // 0
	{
	public:
		// members
		std::uint16_t vertexArray[2];  // 0
		std::uint32_t data;            // 4
	};
	static_assert(sizeof(BSNavmeshCoverEdge) == 0x8);

	struct BSNavmeshGrid
	{
	public:
		// members
		std::uint32_t gridSize;             // 00
		float columnSectionLen;             // 04
		float rowSectionLen;                // 08
		NiPoint3 gridBoundsMin;             // 0C
		NiPoint3 gridBoundsMax;             // 18
		BSTArray<std::uint16_t>* gridData;  // 28
	};
	static_assert(sizeof(BSNavmeshGrid) == 0x30);

	struct BSNavmeshWaypoint
	{
	public:
		// members
		NiPoint3 position;            // 00
		std::uint16_t triangleIndex;  // 0C
		std::uint32_t flags;          // 10
	};
	static_assert(sizeof(BSNavmeshWaypoint) == 0x14);

	class __declspec(novtable) BSNavmesh :
		public BSIntrusiveRefCounted  // 008
	{
	public:
		static constexpr auto RTTI{ RTTI::BSNavmesh };
		static constexpr auto VTABLE{ VTABLE::BSNavmesh };

		struct DisabledLink
		{
		public:
			// members
			std::uint16_t triIndex;     // 0
			std::uint16_t adjTriIndex;  // 2
			std::int32_t edgeIndex;     // 4
			std::int32_t adjEdgeIndex;  // 8
		};
		static_assert(sizeof(DisabledLink) == 0xC);

		virtual ~BSNavmesh();  // 00

		// add
		virtual std::uint32_t QNavmeshID() const = 0;  // 01

		// members
		BSTArray<BSNavmeshVertex> vertices;                                                  // 010
		BSTArray<BSNavmeshTriangle> triangles;                                               // 028
		BSTArray<BSNavmeshEdgeExtraInfo> extraEdgeInfo;                                      // 040
		BSTArray<BSNavmeshTriangleDoorPortal> doorPortals;                                   // 058
		BSTArray<BSNavmeshClosedDoorInfo> closedDoors;                                       // 070
		BSTArray<BSNavmeshCoverEdge> coverArray;                                             // 088
		BSTHashMap<std::uint16_t, std::uint16_t> coverMap;                                   // 0A0
		BSNavmeshGrid meshGrid;                                                              // 0D0
		BSTArray<NiPointer<BSNavmeshObstacleUndoData>> obstacles;                            // 100
		BSTHashMap<std::uint16_t, NiPointer<BSNavmeshObstacleData>>* triangleToObstacleMap;  // 118
		BSTArray<std::uint16_t> obstaclePOVs;                                                // 120
		BSTHashMap<std::uint32_t, BSTArray<std::uint16_t>*> precuts;                         // 138
		BSTSet<std::uint32_t> activePrecuts;                                                 // 168
		BSTHashMap<std::uint32_t, std::uint32_t> portalSwaps;                                // 198
		BSTArray<BSNavmesh::DisabledLink> disabledLinks;                                     // 1C8
		BSTSmartPointer<BSPathingCell> parentCell;                                           // 1E0
		BSNavmeshInfo* navmeshInfo;                                                          // 1E8
		BSTArray<BSNavmeshWaypoint> waypoints;                                               // 1F0
	};
	static_assert(sizeof(BSNavmesh) == 0x208);

	class __declspec(novtable) NavMesh :
		public TESForm,       // 00
		public TESChildCell,  // 20
		public BSNavmesh      // 28
	{
	public:
		static constexpr auto RTTI{ RTTI::NavMesh };
		static constexpr auto VTABLE{ VTABLE::NavMesh };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNAVM };

		// add
		virtual void Save() { return; }                                                 // 4A
		virtual bool SavesBefore([[maybe_unused]] FORM* a_groupFORM) { return false; }  // 4B
		virtual bool SavesBefore([[maybe_unused]] TESForm* a_form) { return false; }    // 4C
		virtual bool ProcessBeforeSave() { return false; }                              // 4D
	};
	static_assert(sizeof(NavMesh) == 0x230);
}
