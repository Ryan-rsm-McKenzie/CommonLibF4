#pragma once

#include "RE/Bethesda/Actor.h"
#include "RE/Bethesda/ActorValueInfo.h"
#include "RE/Bethesda/BGSDefaultObjectManager.h"
#include "RE/Bethesda/BGSHeadPart.h"
#include "RE/Bethesda/BGSMod.h"
#include "RE/Bethesda/BGSStoryManagerTreeForm.h"
#include "RE/Bethesda/BGSTextureSet.h"
#include "RE/Bethesda/MagicItems.h"
#include "RE/Bethesda/NavMesh.h"
#include "RE/Bethesda/NavMeshInfoMap.h"
#include "RE/Bethesda/PlayerCharacter.h"
#include "RE/Bethesda/Projectiles.h"
#include "RE/Bethesda/Script.h"
#include "RE/Bethesda/TESBoundAnimObjects.h"
#include "RE/Bethesda/TESBoundObjects.h"
#include "RE/Bethesda/TESCombatStyle.h"
#include "RE/Bethesda/TESFaction.h"
#include "RE/Bethesda/TESForms.h"
#include "RE/Bethesda/TESObjectREFRs.h"
#include "RE/Bethesda/TESPackages.h"
#include "RE/Bethesda/TESRace.h"
#include "RE/Bethesda/TESWaterForm.h"
#include "RE/Bethesda/TESWorldSpace.h"

#define F4SE_FORMUTIL(a_elem)                                           \
	case a_elem::FORM_ID:                                               \
		if constexpr (std::is_convertible_v<const a_elem*, const T*>) { \
			return static_cast<const a_elem*>(this);                    \
		}                                                               \
		break

namespace RE
{
	template <class T, class>
	[[nodiscard]] T* TESForm::As() noexcept
	{
		return const_cast<T*>(static_cast<const TESForm*>(this)->As<T>());
	}

	template <class T, class>
	[[nodiscard]] const T* TESForm::As() const noexcept
	{
		switch (GetFormType()) {
			F4SE_FORMUTIL(TESForm);
			F4SE_FORMUTIL(BGSKeyword);
			F4SE_FORMUTIL(BGSLocationRefType);
			F4SE_FORMUTIL(BGSAction);
			F4SE_FORMUTIL(BGSTransform);
			F4SE_FORMUTIL(BGSComponent);
			F4SE_FORMUTIL(BGSTextureSet);
			F4SE_FORMUTIL(BGSMenuIcon);
			F4SE_FORMUTIL(TESGlobal);
			F4SE_FORMUTIL(BGSDamageType);
			F4SE_FORMUTIL(TESClass);
			F4SE_FORMUTIL(TESFaction);
			F4SE_FORMUTIL(BGSHeadPart);
			F4SE_FORMUTIL(TESEyes);
			F4SE_FORMUTIL(TESRace);
			F4SE_FORMUTIL(TESSound);
			F4SE_FORMUTIL(BGSAcousticSpace);
			F4SE_FORMUTIL(EffectSetting);
			F4SE_FORMUTIL(Script);
			F4SE_FORMUTIL(TESLandTexture);
			F4SE_FORMUTIL(EnchantmentItem);
			F4SE_FORMUTIL(SpellItem);
			F4SE_FORMUTIL(ScrollItem);
			F4SE_FORMUTIL(TESObjectACTI);
			F4SE_FORMUTIL(BGSTalkingActivator);
			F4SE_FORMUTIL(TESObjectARMO);
			F4SE_FORMUTIL(TESObjectBOOK);
			F4SE_FORMUTIL(TESObjectCONT);
			F4SE_FORMUTIL(TESObjectDOOR);
			F4SE_FORMUTIL(IngredientItem);
			F4SE_FORMUTIL(TESObjectLIGH);
			F4SE_FORMUTIL(TESObjectMISC);
			F4SE_FORMUTIL(TESObjectSTAT);
			F4SE_FORMUTIL(BGSStaticCollection);
			F4SE_FORMUTIL(BGSMovableStatic);
			F4SE_FORMUTIL(TESGrass);
			F4SE_FORMUTIL(TESObjectTREE);
			F4SE_FORMUTIL(TESFlora);
			F4SE_FORMUTIL(TESFurniture);
			F4SE_FORMUTIL(TESObjectWEAP);
			F4SE_FORMUTIL(TESAmmo);
			F4SE_FORMUTIL(TESNPC);
			F4SE_FORMUTIL(TESLevCharacter);
			F4SE_FORMUTIL(TESKey);
			F4SE_FORMUTIL(AlchemyItem);
			F4SE_FORMUTIL(BGSIdleMarker);
			F4SE_FORMUTIL(BGSNote);
			F4SE_FORMUTIL(BGSProjectile);
			F4SE_FORMUTIL(BGSHazard);
			F4SE_FORMUTIL(BGSBendableSpline);
			F4SE_FORMUTIL(TESSoulGem);
			F4SE_FORMUTIL(BGSTerminal);
			F4SE_FORMUTIL(TESLevItem);
			F4SE_FORMUTIL(TESWeather);
			F4SE_FORMUTIL(TESClimate);
			F4SE_FORMUTIL(BGSShaderParticleGeometryData);
			F4SE_FORMUTIL(BGSReferenceEffect);
			F4SE_FORMUTIL(TESRegion);
			F4SE_FORMUTIL(NavMeshInfoMap);
			F4SE_FORMUTIL(TESObjectCELL);
			F4SE_FORMUTIL(TESObjectREFR);
			F4SE_FORMUTIL(Actor);
			F4SE_FORMUTIL(MissileProjectile);
			F4SE_FORMUTIL(ArrowProjectile);
			F4SE_FORMUTIL(GrenadeProjectile);
			F4SE_FORMUTIL(BeamProjectile);
			F4SE_FORMUTIL(FlameProjectile);
			F4SE_FORMUTIL(ConeProjectile);
			F4SE_FORMUTIL(BarrierProjectile);
			F4SE_FORMUTIL(Hazard);
			F4SE_FORMUTIL(TESWorldSpace);
			F4SE_FORMUTIL(TESObjectLAND);
			F4SE_FORMUTIL(NavMesh);
			F4SE_FORMUTIL(TESTopic);
			F4SE_FORMUTIL(TESTopicInfo);
			F4SE_FORMUTIL(TESQuest);
			F4SE_FORMUTIL(TESIdleForm);
			F4SE_FORMUTIL(TESPackage);
			F4SE_FORMUTIL(TESCombatStyle);
			F4SE_FORMUTIL(TESLoadScreen);
			F4SE_FORMUTIL(TESLevSpell);
			F4SE_FORMUTIL(TESObjectANIO);
			F4SE_FORMUTIL(TESWaterForm);
			F4SE_FORMUTIL(TESEffectShader);
			F4SE_FORMUTIL(BGSExplosion);
			F4SE_FORMUTIL(BGSDebris);
			F4SE_FORMUTIL(TESImageSpace);
			F4SE_FORMUTIL(TESImageSpaceModifier);
			F4SE_FORMUTIL(BGSListForm);
			F4SE_FORMUTIL(BGSPerk);
			F4SE_FORMUTIL(BGSBodyPartData);
			F4SE_FORMUTIL(BGSAddonNode);
			F4SE_FORMUTIL(ActorValueInfo);
			F4SE_FORMUTIL(BGSCameraShot);
			F4SE_FORMUTIL(BGSCameraPath);
			F4SE_FORMUTIL(BGSVoiceType);
			F4SE_FORMUTIL(BGSMaterialType);
			F4SE_FORMUTIL(BGSImpactData);
			F4SE_FORMUTIL(BGSImpactDataSet);
			F4SE_FORMUTIL(TESObjectARMA);
			F4SE_FORMUTIL(BGSEncounterZone);
			F4SE_FORMUTIL(BGSLocation);
			F4SE_FORMUTIL(BGSMessage);
			F4SE_FORMUTIL(BGSDefaultObjectManager);
			F4SE_FORMUTIL(BGSDefaultObject);
			F4SE_FORMUTIL(BGSLightingTemplate);
			F4SE_FORMUTIL(BGSMusicType);
			F4SE_FORMUTIL(BGSFootstep);
			F4SE_FORMUTIL(BGSFootstepSet);
			F4SE_FORMUTIL(BGSStoryManagerBranchNode);
			F4SE_FORMUTIL(BGSStoryManagerQuestNode);
			F4SE_FORMUTIL(BGSStoryManagerEventNode);
			F4SE_FORMUTIL(BGSDialogueBranch);
			F4SE_FORMUTIL(BGSMusicTrackFormWrapper);
			F4SE_FORMUTIL(TESWordOfPower);
			F4SE_FORMUTIL(TESShout);
			F4SE_FORMUTIL(BGSEquipSlot);
			F4SE_FORMUTIL(BGSRelationship);
			F4SE_FORMUTIL(BGSScene);
			F4SE_FORMUTIL(BGSAssociationType);
			F4SE_FORMUTIL(BGSOutfit);
			F4SE_FORMUTIL(BGSArtObject);
			F4SE_FORMUTIL(BGSMaterialObject);
			F4SE_FORMUTIL(BGSMovementType);
			F4SE_FORMUTIL(BGSSoundDescriptorForm);
			F4SE_FORMUTIL(BGSDualCastData);
			F4SE_FORMUTIL(BGSSoundCategory);
			F4SE_FORMUTIL(BGSSoundOutput);
			F4SE_FORMUTIL(BGSCollisionLayer);
			F4SE_FORMUTIL(BGSColorForm);
			F4SE_FORMUTIL(BGSReverbParameters);
			F4SE_FORMUTIL(BGSPackIn);
			F4SE_FORMUTIL(BGSAimModel);
			F4SE_FORMUTIL(BGSConstructibleObject);
			F4SE_FORMUTIL(BGSMod::Attachment::Mod);
			F4SE_FORMUTIL(BGSMaterialSwap);
			F4SE_FORMUTIL(BGSZoomData);
			F4SE_FORMUTIL(BGSInstanceNamingRules);
			F4SE_FORMUTIL(BGSSoundKeywordMapping);
			F4SE_FORMUTIL(BGSAudioEffectChain);
			F4SE_FORMUTIL(BGSAttractionRule);
			F4SE_FORMUTIL(BGSSoundCategorySnapshot);
			F4SE_FORMUTIL(BGSSoundTagSet);
			F4SE_FORMUTIL(BGSLensFlare);
			F4SE_FORMUTIL(BGSGodRays);
		default:
			break;
		}

		return nullptr;
	}
}

#undef F4SE_FORMUTIL
