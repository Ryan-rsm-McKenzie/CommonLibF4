#pragma once

#include "RE/Bethesda/BSLock.h"
#include "RE/NetImmerse/NiObject.h"
#include "RE/NetImmerse/NiShadeProperty.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class BSEffectShaderData;
	class BSRenderPass;
	class BSShaderAccumulator;
	class BSShaderMaterial;
	class NiTexture;

	struct __declspec(novtable) BSShaderProperty :
		public NiShadeProperty  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSShaderProperty };
		static constexpr auto VTABLE{ VTABLE::BSShaderProperty };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSShaderProperty };

		enum class TextureTypeEnum;

		class ForEachVisitor;

		class RenderPassArray
		{
		public:
			constexpr RenderPassArray() noexcept {}  // NOLINT(modernize-use-equals-default)

			// members
			BSRenderPass* passList{ nullptr };  // 0
		};
		static_assert(sizeof(RenderPassArray) == 0x8);

		// add
		virtual RenderPassArray* GetRenderPasses(BSGeometry* a_geom, std::uint32_t a_renderMode, BSShaderAccumulator* a_accumulator) = 0;  // 2B
		virtual RenderPassArray* GetRenderPasses_ShadowMapOrMask(BSGeometry*, std::uint32_t, BSShaderAccumulator*) { return nullptr; }     // 2C
		virtual RenderPassArray* GetRenderPasses_LocalMap(BSGeometry*, std::uint32_t, BSShaderAccumulator*) { return nullptr; }            // 2D
		virtual BSRenderPass* CreateVatsMaskRenderPass(BSGeometry*) { return nullptr; }                                                    // 2E
		virtual std::uint16_t GetNumberofPasses([[maybe_unused]] BSGeometry* a_geom) { return 1; }                                         // 2F
		virtual BSRenderPass* GetRenderDepthPass(BSGeometry*) { return nullptr; }                                                          // 30
		virtual bool CanMerge(const BSShaderProperty* a_prop);                                                                             // 31
		virtual void SetMaterialAlpha(float) { return; }                                                                                   // 32
		virtual float QMaterialAlpha() const { return 1.0F; }                                                                              // 33
		virtual const BSFixedString& GetRootName() const;                                                                                  // 34
		virtual std::int32_t ForEachTexture(ForEachVisitor&) { return 1; }                                                                 // 35
		virtual std::int32_t QShader() const { return 0; }                                                                                 // 36
		virtual void ClearUnusedMaterialValues() { return; }                                                                               // 37
		virtual BSShaderProperty* ClarifyShader(BSGeometry*, bool, bool) { return nullptr; }                                               // 38
		virtual NiTexture* GetBaseTexture() const { return nullptr; }                                                                      // 39
		virtual RenderPassArray* GetWaterFogPassList(BSGeometry*) { return nullptr; }                                                      // 3A
		virtual bool AcceptsEffectData() const { return false; }                                                                           // 3B
		virtual void PrecacheTextures() { return; }                                                                                        // 3C
		virtual std::uint32_t DetermineUtilityShaderDecl() const { return 0; }                                                             // 3D
		virtual std::uint32_t GetMaterialType() const { return 0; }                                                                        // 3E
		virtual void DoClearRenderPasses() { return; }                                                                                     // 3F

		// members
		float alpha;                                   // 28
		std::int32_t lastRenderPassState;              // 2C
		std::uint64_t flags;                           // 30
		RenderPassArray renderPassList;                // 38
		RenderPassArray debugRenderPassList;           // 40
		BSFadeNode* fadeNode;                          // 48
		BSEffectShaderData* effectData;                // 50
		BSShaderMaterial* material;                    // 58
		std::uint32_t lastAccumTime;                   // 60
		float lodFade;                                 // 64
		BSNonReentrantSpinLock clearRenderPassesLock;  // 68
	};
	static_assert(sizeof(BSShaderProperty) == 0x70);

	class __declspec(novtable) BSTextureSet :
		public NiObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSTextureSet };
		static constexpr auto VTABLE{ VTABLE::BSTextureSet };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSTextureSet };

		// add
		virtual const BSFixedString* GetTextureFilenameFS(BSShaderProperty::TextureTypeEnum a_type) = 0;                                                  // 28
		virtual const char* GetTextureFilename(BSShaderProperty::TextureTypeEnum a_type) = 0;                                                             // 29
		virtual void GetTexture(const void* a_prefetchedHandle, BSShaderProperty::TextureTypeEnum a_type, NiPointer<NiTexture>* a_texture, bool a_srgb);  // 2A
		virtual void GetTexture(BSShaderProperty::TextureTypeEnum a_type, NiPointer<NiTexture>* a_texture, bool a_srgb) = 0;                              // 2B
		virtual void SetTextureFilename(BSShaderProperty::TextureTypeEnum a_type, const char* a_filename) = 0;                                            // 2C
	};
	static_assert(sizeof(BSTextureSet) == 0x10);
}
