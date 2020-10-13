#pragma once

#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/TESForms.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class BSWaterShaderMaterial;
	class NiTexture;

	struct WaterShaderData
	{
	public:
		// members
		float maxDepth;                      // 00
		std::uint32_t shallowWaterColor;     // 04
		std::uint32_t deepWaterColor;        // 08
		float shallowFogColorRange;          // 0C
		float deepFogColorRange;             // 10
		float shallowAlpha;                  // 14
		float deepAlpha;                     // 18
		float shallowFogAlphaRange;          // 1C
		float deepFogAlphaRange;             // 20
		std::uint32_t underwaterFogColor;    // 24
		float underwaterFogAmount;           // 28
		float underwaterFogDistNear;         // 2C
		float underwaterFogDistFar;          // 30
		float normalMagnitude;               // 34
		float normalFalloffShallow;          // 38
		float normalFalloffDeep;             // 3C
		float reflectionAmount;              // 40
		float fresnelAmount;                 // 44
		float surfaceEffectFalloff;          // 48
		float displacementForce;             // 4C
		float displacementVelocity;          // 50
		float displacementFalloff;           // 54
		float displacementDampener;          // 58
		float displacementSize;              // 5C
		std::uint32_t reflectionWaterColor;  // 60
		float sunSpecularPower;              // 64
		float sunSpecularMagnitude;          // 68
		float sunSparklePower;               // 6C
		float sunSparkleMagnitude;           // 70
		float lightRadius;                   // 74
		float lightBrightness;               // 78
		float shininess;                     // 7C
		float noiseWindDirections[3];        // 80
		float noiseWindSpeeds[3];            // 8C
		float amplitude[3];                  // 98
		float uvScales[3];                   // A4
		float noiseFalloff[3];               // B0
		float siltAmount;                    // BC
		std::uint32_t lightSiltColor;        // C0
		std::uint32_t darkSiltColor;         // C4
		bool ssrEnabled;                     // C8
	};
	static_assert(sizeof(WaterShaderData) == 0xCC);

	class __declspec(novtable) TESWaterForm :
		public TESForm,     // 000
		public TESFullName  // 020
	{
	public:
		static constexpr auto RTTI{ RTTI::TESWaterForm };
		static constexpr auto VTABLE{ VTABLE::TESWaterForm };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kWATR };

		// members
		bool needUpdate;                             // 030
		NiColorA texScroll0;                         // 034
		NiColorA texScroll1;                         // 044
		NiColorA texScroll2;                         // 054
		TESTexture noiseTexture0;                    // 068
		TESTexture noiseTexture1;                    // 078
		TESTexture noiseTexture2;                    // 088
		std::int8_t alpha;                           // 098
		std::int8_t flags;                           // 099
		BGSMaterialType* materialType;               // 0A0
		BGSSoundDescriptorForm* waterSound;          // 0A8
		WaterShaderData data;                        // 0B0
		TESWaterForm* waterWeatherControl[3];        // 180
		std::int32_t currentTextureSelect01;         // 198
		std::int32_t currentTextureSelect02;         // 19C
		std::uint32_t frequencyX;                    // 1A0
		std::uint32_t frequencyY;                    // 1A4
		std::int32_t octaves;                        // 1A8
		float amplitude;                             // 1AC
		float lacunarity;                            // 1B0
		float bias;                                  // 1B4
		float gain;                                  // 1B8
		SpellItem* consumeSpell;                     // 1C0
		SpellItem* contactSpell;                     // 1C8
		NiPointer<NiTexture> niNoiseTexture0;        // 1D0
		NiPointer<NiTexture> niNoiseTexture1;        // 1D8
		NiPointer<NiTexture> niNoiseTexture2;        // 1E0
		TESObjectACTI* placeableAutoWater;           // 1E8
		TESObjectACTI* placeableLODWater;            // 1F0
		BSWaterShaderMaterial* waterShaderMaterial;  // 1F8
		bool resetNoiseTextures;                     // 200
		TESImageSpace* imageSpace;                   // 208
		NiPoint3 linearVelocity;                     // 210
		NiPoint3 angularVelocity;                    // 21C
	};
	static_assert(sizeof(TESWaterForm) == 0x228);
}
