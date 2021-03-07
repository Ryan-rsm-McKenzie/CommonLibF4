#pragma once

#include "RE/Bethesda/Atomic.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTSmallIndexScatterTable.h"

namespace RE
{
	class BSRenderPass;

	struct PersistentPassList
	{
	public:
		// members
		BSRenderPass* head;  // 00
		BSRenderPass* tail;  // 08
	};
	static_assert(sizeof(PersistentPassList) == 0x10);

	class BSBatchRenderer
	{
	public:
		static constexpr auto RTTI{ RTTI::BSBatchRenderer };
		static constexpr auto VTABLE{ VTABLE::BSBatchRenderer };

		enum class GEOMETRY_GROUP_ENUM : std::uint32_t
		{
			kNone = static_cast<std::underlying_type_t<GEOMETRY_GROUP_ENUM>>(-1),

			kLODLand = 0x0,
			kLODObjects = 0x1,
			kMultiIndexDecal = 0x2,
			kOpaqueDecal = 0x3,
			kBlendedDecal = 0x4,
			kRefrActive = 0x5,
			k1stPersonNonRefractive = 0x6,
			kFading = 0x7,
			kNoShadow = 0x8,
			kLowAniso = 0x9,
			kUnderwaterFog = 0xA,
			kSSLR = 0xB,
			kZOnly = 0xC,
			kPostZOnly = 0xD,
			kSkyClouds = 0xE,
			kSmoothAlphaTest = 0xF,
			kVATSMaskDepthOnly = 0x10,
			kVATSMask = 0x11,
			kSunGlare = 0x12,
			kBloodSpatter = 0x13,
			kZPrepass = 0x14,
			kWaterStencil = 0x15,
			kWaterDepth = 0x16,

			kTotal
		};

		struct CommandBufferPassesMapAccess;
		struct RenderPassMapAccess;

		struct CommandBufferPassesData
		{
		public:
			// members
			std::byte* buffer[1u << 13];    // 00000
			std::byte** currentBuffer;      // 10000
			CommandBufferPassesData* next;  // 10008
			std::uint32_t frame;            // 10010
			std::uint32_t ownerIndex;       // 10014
		};
		static_assert(sizeof(CommandBufferPassesData) == 0x10018);

		struct CommandBufferPassesDataEntry
		{
		public:
			// members
			CommandBufferPassesData* data;  // 00
			std::uint64_t groupAndPass;     // 08
		};
		static_assert(sizeof(CommandBufferPassesDataEntry) == 0x10);

		class GeometryGroup
		{
		public:
			// members
			BSBatchRenderer* batchRenderer;  // 00
			PersistentPassList passList;     // 08
			float depth;                     // 18
			std::uint32_t count;             // 1C
			std::uint8_t flags;              // 20
			std::int8_t group;               // 21
		};
		static_assert(sizeof(GeometryGroup) == 0x28);

		class PassGroup
		{
		public:
			// members
			BSRenderPass* passHead;             // 00
			std::uint32_t passEnum;             // 08
			std::uint16_t nextPassGroup;        // 0C
			std::uint16_t commandBufferPasses;  // 0E
		};
		static_assert(sizeof(PassGroup) == 0x10);

		virtual ~BSBatchRenderer();  // 00

		BSTArray<PassGroup> renderPasses[13];                                                                                  // 008
		BSTSmallIndexScatterTable<BSTArray<PassGroup>, RenderPassMapAccess> renderPassMap[13];                                 // 140
		std::uint32_t activePassIndexLists[13][2];                                                                             // 2E0
		std::uint32_t currentFirstPass;                                                                                        // 348
		std::uint32_t currentLastPass;                                                                                         // 34C
		bool autoClearPasses;                                                                                                  // 350
		GeometryGroup* geometryGroups[stl::to_underlying(GEOMETRY_GROUP_ENUM::kTotal)];                                        // 358
		GeometryGroup* alphaGroup;                                                                                             // 410
		std::uint32_t groupingAlphasGroupCount;                                                                                // 418
		GeometryGroup* groupingAlphasGroup;                                                                                    // 420
		BSTArray<CommandBufferPassesDataEntry> commandBufferPasses;                                                            // 428
		BSTSmallIndexScatterTable<BSTArray<CommandBufferPassesDataEntry>, CommandBufferPassesMapAccess> commandBufferPassMap;  // 440
		CommandBufferPassesData* bufferPassesCurr;                                                                             // 460
		CommandBufferPassesData* bufferPassesHead;                                                                             // 468
		CommandBufferPassesData** bufferPassesTail;                                                                            // 470
		std::uint32_t bufferPassesCurrAllocFrame;                                                                              // 478
	};
	static_assert(sizeof(BSBatchRenderer) == 0x480);

	namespace BSMTAManager
	{
		enum class MODE
		{
			kIdle,
			kCollecting,
			kExecuting,
		};

		class CalculateBoneMatricesTask
		{
		public:
			// members
			BSGeometry* geometry;  // 0
		};
		static_assert(sizeof(CalculateBoneMatricesTask) == 0x8);

		class RegisterBatchRendererPassTask
		{
		public:
			// members
			BSBatchRenderer* batchRenderer;  // 00
			BSRenderPass* renderPass;        // 08
		};
		static_assert(sizeof(RegisterBatchRendererPassTask) == 0x10);

		struct RegisterGeometryGroupPassTask
		{
		public:
			// members
			BSBatchRenderer* batchRenderer;                                               // 00
			BSRenderPass* renderPass;                                                     // 08
			BSBatchRenderer::GeometryGroup* geometryGroup;                                // 10
			stl::enumeration<BSBatchRenderer::GEOMETRY_GROUP_ENUM, std::uint32_t> group;  // 18
			bool addToFront;                                                              // 1C
		};
		static_assert(sizeof(RegisterGeometryGroupPassTask) == 0x20);

		class JobData
		{
		public:
			// members
			BSTArray<RegisterBatchRendererPassTask> registerBatchRendererPasses;  // 00
			BSTArray<RegisterGeometryGroupPassTask> registerGeometryGroupPasses;  // 18
			BSEventFlag finishedEvent;                                            // 30
		};
		static_assert(sizeof(JobData) == 0x38);

		class RegisterObjectTask
		{
		public:
			// members
			BSGeometry* geometry;                               // 00
			std::int32_t groupingAlphas;                        // 08
			BSBatchRenderer::GeometryGroup* currentAlphaGroup;  // 10
			bool alphaGroupZPrePass;                            // 18
			JobData* owner;                                     // 20
			std::uint32_t registerBatchRendererPassIndex;       // 28
			std::uint32_t registerBatchRendererPassCount;       // 2C
			std::uint32_t registerGeometryGroupPassIndex;       // 30
			std::uint32_t registerGeometryGroupPassCount;       // 34
		};
		static_assert(sizeof(RegisterObjectTask) == 0x38);
	}
}
