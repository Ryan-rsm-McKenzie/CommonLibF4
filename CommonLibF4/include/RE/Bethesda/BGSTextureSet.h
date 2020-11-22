#pragma once

#include "RE/Bethesda/BSGraphics.h"
#include "RE/Bethesda/BSResource.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTextureSet.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/MemoryManager.h"
#include "RE/Bethesda/TESBoundObjects.h"
#include "RE/Bethesda/TESForms.h"
#include "RE/NetImmerse/NiAlphaProperty.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiPoint2.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class BSEffectShaderPropertyColorController;
	class BSEffectShaderPropertyFloatController;
	class BSLightingShaderPropertyColorController;
	class BSLightingShaderPropertyFloatController;
	class BSLightingShaderPropertyUShortController;
	class BSNiAlphaPropertyTestRefController;
	class BSShaderTextureSet;
	class DecalData;

	struct BSShaderData :
		public BSIntrusiveRefCounted  // 000
	{
	public:
		enum class LightingShaderEnum
		{
			kStandard,
			kWater,
			kEffect,
			kSky,
			kTallGrass
		};

		// members
		stl::enumeration<LightingShaderEnum, std::int32_t> lightingShader;                  // 004
		bool specularEnabled;                                                               // 008
		NiColor specularColor;                                                              // 00C
		float specularMult;                                                                 // 018
		NiColor emittanceColor;                                                             // 01C
		float emittanceColorScale;                                                          // 028
		float lightingInfluence;                                                            // 02C
		std::int8_t envmapMinLOD;                                                           // 030
		float smoothness;                                                                   // 034
		float fresnelPower_ShaderDataEntry;                                                 // 038
		float wetnessControl_SpecScale_ShaderDataEntry;                                     // 03C
		float wetnessControl_SpecPowerScale_ShaderDataEntry;                                // 040
		float wetnessControl_SpecMin_ShaderDataEntry;                                       // 044
		float wetnessControl_EnvMapScale_ShaderDataEntry;                                   // 048
		float wetnessControl_FresnelPower_ShaderDataEntry;                                  // 04C
		float wetnessControl_Metalness_ShaderDataEntry;                                     // 050
		bool betnessControl_ScreenSpaceReflections;                                         // 054
		BSFixedString rootMaterialPath;                                                     // 058
		float alpha;                                                                        // 060
		float emittanceMult;                                                                // 064
		float lookupScale;                                                                  // 068
		bool emitEnabled;                                                                   // 06C
		BSFixedString materialPath;                                                         // 070
		bool alphaBlend;                                                                    // 078
		stl::enumeration<NiAlphaProperty::AlphaFunction, std::int32_t> alphaSrcBlendMode;   // 07C
		stl::enumeration<NiAlphaProperty::AlphaFunction, std::int32_t> alphaDestBlendMode;  // 080
		bool alphaTest;                                                                     // 084
		stl::enumeration<NiAlphaProperty::TestFunction, std::int32_t> alphaTestFunction;    // 088
		std::int8_t alphaTestRef;                                                           // 08C
		bool enableEditorAlphaRef;                                                          // 08D
		bool vertexColors;                                                                  // 08E
		bool vertexAlpha;                                                                   // 08F
		bool modelSpaceNormals;                                                             // 090
		bool decal;                                                                         // 091
		bool externalEmittance;                                                             // 092
		bool hideSecret;                                                                    // 093
		bool noFade;                                                                        // 094
		bool dismemberment;                                                                 // 095
		bool facegen;                                                                       // 096
		bool skinTint;                                                                      // 097
		bool hair;                                                                          // 098
		bool twoSided;                                                                      // 099
		bool tree;                                                                          // 09A
		bool bloodEnabled;                                                                  // 09B
		bool uniqueAlphaProperty;                                                           // 09C
		bool effectLightingEnabled;                                                         // 09D
		bool castShadows;                                                                   // 09E
		bool receiveShadows;                                                                // 09F
		bool dissolveFade;                                                                  // 0A0
		bool glowmap;                                                                       // 0A1
		bool assumeShadowmask;                                                              // 0A2
		bool screenSpaceReflections;                                                        // 0A3
		bool nonOccluder;                                                                   // 0A4
		bool skewSpecularAlpha;                                                             // 0A5
		bool tessellate;                                                                    // 0A6
		bool backLighting;                                                                  // 0A7
		bool subSurfaceLighting;                                                            // 0A8
		bool rimLighting;                                                                   // 0A9
		float subSurfaceRolloff;                                                            // 0AC
		float rimPower;                                                                     // 0B0
		float backLightPower;                                                               // 0B4
		bool anisoLighting;                                                                 // 0B8
		bool zBufferWrite;                                                                  // 0B8
		bool zBufferTest;                                                                   // 0BA
		bool refraction;                                                                    // 0BB
		float refractionPower;                                                              // 0BC
		bool refractionFalloff;                                                             // 0C0
		BSTArray<BSLightingShaderPropertyFloatController*> lightingFloatControllers;        // 0C8
		BSTArray<BSLightingShaderPropertyUShortController*> lightingUShortControllers;      // 0E0
		BSTArray<BSLightingShaderPropertyColorController*> lightingColorControllers;        // 0F8
		BSTArray<BSEffectShaderPropertyFloatController*> effectFloatControllers;            // 110
		BSTArray<BSEffectShaderPropertyColorController*> effectColorControllers;            // 128
		BSNiAlphaPropertyTestRefController* alphaRefTestController;                         // 140
		bool parallax;                                                                      // 148
		bool parallaxOcclusion;                                                             // 149
		bool multiLayerParallax;                                                            // 14A
		float parallaxOcclusionHeightScale;                                                 // 14C
		float parallaxOcclusionMaxPasses;                                                   // 150
		float parallaxLayerThickness;                                                       // 154
		float parallaxRefractionScale;                                                      // 158
		float parallaxInnerLayerUScale;                                                     // 15C
		float parallaxInnerLayerVScale;                                                     // 160
		float displacementTextureBias;                                                      // 164
		float displacementTextureScale;                                                     // 168
		float tessellationPNScale;                                                          // 16C
		float tessellationFadeDistance;                                                     // 170
		float tessellationBaseFactor;                                                       // 174
		bool tessellationNeedsDominantUVs;                                                  // 178
		bool tessellationNeedsCrackFreeNormals;                                             // 179
		bool environmentMapping;                                                            // 17A
		bool environmentMappingEye;                                                         // 17B
		bool environmentMappingWindow;                                                      // 17C
		float environmentMappingMaskScale;                                                  // 180
		std::int32_t skyTYpe;                                                               // 184
		bool reflectionsEnabled;                                                            // 188
		bool silhouetteReflectionsEnabled;                                                  // 189
		bool refractionsEnabled;                                                            // 18A
		bool depthEnabled;                                                                  // 18B
		bool vertexUVEnabled;                                                               // 18C
		bool vertexAlphaDepthEnabled;                                                       // 18D
		bool foggingEnabled;                                                                // 18E
		bool falloffEnabled;                                                                // 18F
		bool rgbFalloffEnabled;                                                             // 190
		NiColorA falloffData;                                                               // 194
		bool softEnabled;                                                                   // 1A4
		float softDepth;                                                                    // 1A8
		NiPoint2 uvOffset;                                                                  // 1AC
		NiPoint2 uvScale;                                                                   // 1B4
		bool grayscaleToPaletteColor;                                                       // 1BC
		bool grayscaleToPaletteAlpha;                                                       // 1BD
		NiColor hairTintColor;                                                              // 1C0
		NiPointer<BSShaderTextureSet> textureSet;                                           // 1D0
		stl::enumeration<BSGraphics::TextureAddressMode, std::int32_t> clampMode;           // 1D8
	};
	static_assert(sizeof(BSShaderData) == 0x1E0);

	class __declspec(novtable) BGSTextureSet :
		public TESBoundObject,  // 000
		public BSTextureSet     // 068
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSTextureSet };
		static constexpr auto VTABLE{ VTABLE::BGSTextureSet };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kTXST };

		F4_HEAP_REDEFINE_NEW(BGSTextureSet);

		// members
		BSFixedString materialName;        // 078
		TESTexture textures[8];            // 080
		DecalData* decalData;              // 100
		std::uint16_t flags;               // 108
		BSResource::ID textureFileIDs[8];  // 10C
		BSShaderData materialData;         // 170
	};
	static_assert(sizeof(BGSTextureSet) == 0x350);
}
