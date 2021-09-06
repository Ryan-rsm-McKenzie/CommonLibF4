#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/UIShaderFXInfo.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiPoint2.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	enum class UI_DEPTH_PRIORITY;

	class BSGeometry;
	class BSShaderAccumulator;
	class NiAVObject;
	class NiCamera;
	class NiDirectionalLight;
	class ShadowSceneNode;

	namespace Interface3D
	{
		enum class BackgroundMode
		{
			kLive,
			kStatic,
			kSolidColor
		};

		enum class PostEffect
		{
			kNone,
			kPipboy,
			kHUDGlass,
			kHUDGlassWithMod,
			kModMenu,
			kModMenuHighlightAll,
			kModMenuHighlightAllNoPulseOrScanLines
		};

		enum class HighlightEffect
		{
			kNone,
			kVATS
		};

		enum class OffscreenMenuSize
		{
			kPipboy,
			kFullFrame,
			kFullFrameText
		};

		enum class ScreenMode
		{
			kNone,
			kWorldAttached,
			kScreenAttached
		};

		enum class OffscreenMenuBlendMode
		{
			kAdditive,
			kAlpha
		};

		enum class LightType
		{
			kSpot,
			kShadowSpot,
			kPoint
		};

		class OldScreenEffectControl
		{
		public:
			// members
			NiPoint2 uvOffset;         // 00
			float burstAmount;         // 08
			float brightness;          // 0C
			float vScanState;          // 10
			float vScanRate;           // 14
			float pulseIntensity;      // 18
			float pulseRate;           // 1C
			float flickerMinDelay;     // 20
			float flickerMaxDelay;     // 24
			float flickerMinDuration;  // 28
			float flickerMaxDuration;  // 2C
			float flickerFrequency;    // 30
			float flickerBrightness;   // 34
			float vScanDelayMin;       // 38
			float vScanDelayMax;       // 3C
			bool doScanlines;          // 40
			float burstState;          // 44
			float burstFadeRate;       // 48
			float shudderState;        // 4C
			float vScanDelay;          // 50
			float flickerDelay;        // 54
			float vHoldState;          // 58
			float shudderScale;        // 5C
			float shudderLength;       // 60
			float vHoldRate;           // 64
			float time;                // 68
			bool flickering;           // 6C
		};
		static_assert(sizeof(OldScreenEffectControl) == 0x70);

		class Renderer
		{
		public:
			struct LightParams
			{
			public:
				// members
				stl::enumeration<LightType, std::int32_t> type;  // 00
				float spotFOV;                                   // 04
				NiPoint3 lookAtPos;                              // 08
				NiPointer<NiAVObject> lookAtObject;              // 18
				NiPointer<NiLight> light;                        // 20
			};
			static_assert(sizeof(LightParams) == 0x28);

			[[nodiscard]] static Renderer* GetByName(const BSFixedString& a_name)
			{
				using func_t = decltype(&Renderer::GetByName);
				REL::Relocation<func_t> func{ REL::ID(140387) };
				return func(a_name);
			}

			void Enable(bool a_unhideGeometries = false)
			{
				using func_t = decltype(&Renderer::Enable);
				REL::Relocation<func_t> func{ REL::ID(326895) };
				return func(this, a_unhideGeometries);
			}

			// members
			BSTAlignedArray<UIShaderFXInfo> colorFXInfos;                      // 000
			BSTAlignedArray<UIShaderFXInfo> backgroundFXInfos;                 // 018
			BSReadWriteLock cachedQuadsLock;                                   // 030
			NiColorA clearColor;                                               // 038
			float opacityAlpha;                                                // 048
			bool enabled;                                                      // 04C
			bool offscreen3DEnabled;                                           // 04D
			bool hideScreenWhenDisabled;                                       // 04E
			bool usePremultAlpha;                                              // 04F
			bool clearRenderTarget;                                            // 050
			bool clearDepthStencilMainScreen;                                  // 051
			bool clearDepthStencilOffscreen;                                   // 052
			bool postAA;                                                       // 053
			bool useFullPremultAlpha;                                          // 054
			bool alwaysRenderWhenEnabled;                                      // 055
			bool defRenderMainScreen;                                          // 056
			bool enableAO;                                                     // 057
			bool useLongRangeCamera;                                           // 058
			bool needsLightSetup;                                              // 059
			bool needsLightSetupOffscreen;                                     // 05A
			stl::enumeration<BackgroundMode, std::int32_t> bgmode;             // 05C
			stl::enumeration<PostEffect, std::int32_t> postfx;                 // 060
			stl::enumeration<HighlightEffect, std::int32_t> highlightfx;       // 064
			stl::enumeration<OffscreenMenuSize, std::int32_t> omsize;          // 068
			stl::enumeration<ScreenMode, std::int32_t> screenmode;             // 06C
			stl::enumeration<OffscreenMenuBlendMode, std::int32_t> menuBlend;  // 070
			stl::enumeration<UI_DEPTH_PRIORITY, std::int32_t> depth;           // 074
			NiPointer<NiAVObject> worldAttachedElementRoot;                    // 078
			NiPointer<NiAVObject> screenAttachedElementRoot;                   // 080
			NiPointer<NiAVObject> offscreenElement;                            // 088
			BSTArray<NiPointer<BSGeometry>> displayGeometry;                   // 090
			NiAVObject* elementRequiringFullVieport;                           // 0A8
			NiAVObject* highlightedElement;                                    // 0B0
			bool highlightOffscreen;                                           // 0B8
			OldScreenEffectControl pipfx;                                      // 0BC
			OldScreenEffectControl vatsfx;                                     // 12C
			NiPointer<BSShaderAccumulator> accum;                              // 1A0
			NiPointer<NiCamera> pipboyAspect;                                  // 1A8
			NiPointer<NiCamera> nativeAspect;                                  // 1B0
			NiPointer<NiCamera> nativeAspectLongRange;                         // 1B8
			std::int32_t customRenderTarget;                                   // 1C0
			std::int32_t customSwapTarget;                                     // 1C4
			BSTArray<LightParams> mainLights;                                  // 1C8
			BSTArray<LightParams> offscreenLights;                             // 1E0
			float menuDiffuseIntensity;                                        // 1F8
			float menuEmitIntensity;                                           // 1FC
			float menuDiffuseIntensityWA;                                      // 200
			float menuEmitIntensityWA;                                         // 204
			BSFixedString name;                                                // 208
			BSFixedString screenGeomName;                                      // 210
			BSFixedString screenMaterialName;                                  // 218
			BSFixedString maskedGeomName;                                      // 220
			BSFixedString maskedMaterialName;                                  // 228
			NiDirectionalLight* directionalLight;                              // 230
			NiPointer<ShadowSceneNode> screenSSN;                              // 238
			NiPointer<ShadowSceneNode> offscreenSSN;                           // 240
		};
		static_assert(sizeof(Renderer) == 0x248);
	}
}
