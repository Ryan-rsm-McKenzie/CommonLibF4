#pragma once

#include "RE/Bethesda/Actor.h"
#include "RE/Bethesda/ActorValueInfo.h"
#include "RE/Bethesda/BGSDefaultObjectManager.h"
#include "RE/Bethesda/BGSHeadPart.h"
#include "RE/Bethesda/BGSMod.h"
#include "RE/Bethesda/BGSStoryManagerTreeForm.h"
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
		case ENUM_FORM_ID::kNONE:
			if constexpr (std::is_convertible_v<const TESForm*, const T*>) {
				return static_cast<const TESForm*>(this);
			}
			break;
		case ENUM_FORM_ID::kKYWD:
			if constexpr (std::is_convertible_v<const BGSKeyword*, const T*>) {
				return static_cast<const BGSKeyword*>(this);
			}
			break;
		case ENUM_FORM_ID::kLCRT:
			if constexpr (std::is_convertible_v<const BGSLocationRefType*, const T*>) {
				return static_cast<const BGSLocationRefType*>(this);
			}
			break;
		case ENUM_FORM_ID::kAACT:
			if constexpr (std::is_convertible_v<const BGSAction*, const T*>) {
				return static_cast<const BGSAction*>(this);
			}
			break;
		case ENUM_FORM_ID::kTRNS:
			if constexpr (std::is_convertible_v<const BGSTransform*, const T*>) {
				return static_cast<const BGSTransform*>(this);
			}
			break;
		case ENUM_FORM_ID::kCMPO:
			if constexpr (std::is_convertible_v<const BGSComponent*, const T*>) {
				return static_cast<const BGSComponent*>(this);
			}
			break;
		case ENUM_FORM_ID::kTXST:
			if constexpr (std::is_convertible_v<const BGSTextureSet*, const T*>) {
				return static_cast<const BGSTextureSet*>(this);
			}
			break;
		case ENUM_FORM_ID::kMICN:
			if constexpr (std::is_convertible_v<const BGSMenuIcon*, const T*>) {
				return static_cast<const BGSMenuIcon*>(this);
			}
			break;
		case ENUM_FORM_ID::kGLOB:
			if constexpr (std::is_convertible_v<const TESGlobal*, const T*>) {
				return static_cast<const TESGlobal*>(this);
			}
			break;
		case ENUM_FORM_ID::kDMGT:
			if constexpr (std::is_convertible_v<const BGSDamageType*, const T*>) {
				return static_cast<const BGSDamageType*>(this);
			}
			break;
		case ENUM_FORM_ID::kCLAS:
			if constexpr (std::is_convertible_v<const TESClass*, const T*>) {
				return static_cast<const TESClass*>(this);
			}
			break;
		case ENUM_FORM_ID::kFACT:
			if constexpr (std::is_convertible_v<const TESFaction*, const T*>) {
				return static_cast<const TESFaction*>(this);
			}
			break;
		case ENUM_FORM_ID::kHDPT:
			if constexpr (std::is_convertible_v<const BGSHeadPart*, const T*>) {
				return static_cast<const BGSHeadPart*>(this);
			}
			break;
		case ENUM_FORM_ID::kEYES:
			if constexpr (std::is_convertible_v<const TESEyes*, const T*>) {
				return static_cast<const TESEyes*>(this);
			}
			break;
		case ENUM_FORM_ID::kRACE:
			if constexpr (std::is_convertible_v<const TESRace*, const T*>) {
				return static_cast<const TESRace*>(this);
			}
			break;
		case ENUM_FORM_ID::kSOUN:
			if constexpr (std::is_convertible_v<const TESSound*, const T*>) {
				return static_cast<const TESSound*>(this);
			}
			break;
		case ENUM_FORM_ID::kASPC:
			if constexpr (std::is_convertible_v<const BGSAcousticSpace*, const T*>) {
				return static_cast<const BGSAcousticSpace*>(this);
			}
			break;
		case ENUM_FORM_ID::kMGEF:
			if constexpr (std::is_convertible_v<const EffectSetting*, const T*>) {
				return static_cast<const EffectSetting*>(this);
			}
			break;
		case ENUM_FORM_ID::kSCPT:
			if constexpr (std::is_convertible_v<const Script*, const T*>) {
				return static_cast<const Script*>(this);
			}
			break;
		case ENUM_FORM_ID::kLTEX:
			if constexpr (std::is_convertible_v<const TESLandTexture*, const T*>) {
				return static_cast<const TESLandTexture*>(this);
			}
			break;
		case ENUM_FORM_ID::kENCH:
			if constexpr (std::is_convertible_v<const EnchantmentItem*, const T*>) {
				return static_cast<const EnchantmentItem*>(this);
			}
			break;
		case ENUM_FORM_ID::kSPEL:
			if constexpr (std::is_convertible_v<const SpellItem*, const T*>) {
				return static_cast<const SpellItem*>(this);
			}
			break;
		case ENUM_FORM_ID::kSCRL:
			if constexpr (std::is_convertible_v<const ScrollItem*, const T*>) {
				return static_cast<const ScrollItem*>(this);
			}
			break;
		case ENUM_FORM_ID::kACTI:
			if constexpr (std::is_convertible_v<const TESObjectACTI*, const T*>) {
				return static_cast<const TESObjectACTI*>(this);
			}
			break;
		case ENUM_FORM_ID::kTACT:
			if constexpr (std::is_convertible_v<const BGSTalkingActivator*, const T*>) {
				return static_cast<const BGSTalkingActivator*>(this);
			}
			break;
		case ENUM_FORM_ID::kARMO:
			if constexpr (std::is_convertible_v<const TESObjectARMO*, const T*>) {
				return static_cast<const TESObjectARMO*>(this);
			}
			break;
		case ENUM_FORM_ID::kBOOK:
			if constexpr (std::is_convertible_v<const TESObjectBOOK*, const T*>) {
				return static_cast<const TESObjectBOOK*>(this);
			}
			break;
		case ENUM_FORM_ID::kCONT:
			if constexpr (std::is_convertible_v<const TESObjectCONT*, const T*>) {
				return static_cast<const TESObjectCONT*>(this);
			}
			break;
		case ENUM_FORM_ID::kDOOR:
			if constexpr (std::is_convertible_v<const TESObjectDOOR*, const T*>) {
				return static_cast<const TESObjectDOOR*>(this);
			}
			break;
		case ENUM_FORM_ID::kINGR:
			if constexpr (std::is_convertible_v<const IngredientItem*, const T*>) {
				return static_cast<const IngredientItem*>(this);
			}
			break;
		case ENUM_FORM_ID::kLIGH:
			if constexpr (std::is_convertible_v<const TESObjectLIGH*, const T*>) {
				return static_cast<const TESObjectLIGH*>(this);
			}
			break;
		case ENUM_FORM_ID::kMISC:
			if constexpr (std::is_convertible_v<const TESObjectMISC*, const T*>) {
				return static_cast<const TESObjectMISC*>(this);
			}
			break;
		case ENUM_FORM_ID::kSTAT:
			if constexpr (std::is_convertible_v<const TESObjectSTAT*, const T*>) {
				return static_cast<const TESObjectSTAT*>(this);
			}
			break;
		case ENUM_FORM_ID::kSCOL:
			if constexpr (std::is_convertible_v<const BGSStaticCollection*, const T*>) {
				return static_cast<const BGSStaticCollection*>(this);
			}
			break;
		case ENUM_FORM_ID::kMSTT:
			if constexpr (std::is_convertible_v<const BGSMovableStatic*, const T*>) {
				return static_cast<const BGSMovableStatic*>(this);
			}
			break;
		case ENUM_FORM_ID::kGRAS:
			if constexpr (std::is_convertible_v<const TESGrass*, const T*>) {
				return static_cast<const TESGrass*>(this);
			}
			break;
		case ENUM_FORM_ID::kTREE:
			if constexpr (std::is_convertible_v<const TESObjectTREE*, const T*>) {
				return static_cast<const TESObjectTREE*>(this);
			}
			break;
		case ENUM_FORM_ID::kFLOR:
			if constexpr (std::is_convertible_v<const TESFlora*, const T*>) {
				return static_cast<const TESFlora*>(this);
			}
			break;
		case ENUM_FORM_ID::kFURN:
			if constexpr (std::is_convertible_v<const TESFurniture*, const T*>) {
				return static_cast<const TESFurniture*>(this);
			}
			break;
		case ENUM_FORM_ID::kWEAP:
			if constexpr (std::is_convertible_v<const TESObjectWEAP*, const T*>) {
				return static_cast<const TESObjectWEAP*>(this);
			}
			break;
		case ENUM_FORM_ID::kAMMO:
			if constexpr (std::is_convertible_v<const TESAmmo*, const T*>) {
				return static_cast<const TESAmmo*>(this);
			}
			break;
		case ENUM_FORM_ID::kNPC_:
			if constexpr (std::is_convertible_v<const TESNPC*, const T*>) {
				return static_cast<const TESNPC*>(this);
			}
			break;
		case ENUM_FORM_ID::kLVLN:
			if constexpr (std::is_convertible_v<const TESLevCharacter*, const T*>) {
				return static_cast<const TESLevCharacter*>(this);
			}
			break;
		case ENUM_FORM_ID::kKEYM:
			if constexpr (std::is_convertible_v<const TESKey*, const T*>) {
				return static_cast<const TESKey*>(this);
			}
			break;
		case ENUM_FORM_ID::kALCH:
			if constexpr (std::is_convertible_v<const AlchemyItem*, const T*>) {
				return static_cast<const AlchemyItem*>(this);
			}
			break;
		case ENUM_FORM_ID::kIDLM:
			if constexpr (std::is_convertible_v<const BGSIdleMarker*, const T*>) {
				return static_cast<const BGSIdleMarker*>(this);
			}
			break;
		case ENUM_FORM_ID::kNOTE:
			if constexpr (std::is_convertible_v<const BGSNote*, const T*>) {
				return static_cast<const BGSNote*>(this);
			}
			break;
		case ENUM_FORM_ID::kPROJ:
			if constexpr (std::is_convertible_v<const BGSProjectile*, const T*>) {
				return static_cast<const BGSProjectile*>(this);
			}
			break;
		case ENUM_FORM_ID::kHAZD:
			if constexpr (std::is_convertible_v<const BGSHazard*, const T*>) {
				return static_cast<const BGSHazard*>(this);
			}
			break;
		case ENUM_FORM_ID::kBNDS:
			if constexpr (std::is_convertible_v<const BGSBendableSpline*, const T*>) {
				return static_cast<const BGSBendableSpline*>(this);
			}
			break;
		case ENUM_FORM_ID::kSLGM:
			if constexpr (std::is_convertible_v<const TESSoulGem*, const T*>) {
				return static_cast<const TESSoulGem*>(this);
			}
			break;
		case ENUM_FORM_ID::kTERM:
			if constexpr (std::is_convertible_v<const BGSTerminal*, const T*>) {
				return static_cast<const BGSTerminal*>(this);
			}
			break;
		case ENUM_FORM_ID::kLVLI:
			if constexpr (std::is_convertible_v<const TESLevItem*, const T*>) {
				return static_cast<const TESLevItem*>(this);
			}
			break;
		case ENUM_FORM_ID::kWTHR:
			if constexpr (std::is_convertible_v<const TESWeather*, const T*>) {
				return static_cast<const TESWeather*>(this);
			}
			break;
		case ENUM_FORM_ID::kCLMT:
			if constexpr (std::is_convertible_v<const TESClimate*, const T*>) {
				return static_cast<const TESClimate*>(this);
			}
			break;
		case ENUM_FORM_ID::kSPGD:
			if constexpr (std::is_convertible_v<const BGSShaderParticleGeometryData*, const T*>) {
				return static_cast<const BGSShaderParticleGeometryData*>(this);
			}
			break;
		case ENUM_FORM_ID::kRFCT:
			if constexpr (std::is_convertible_v<const BGSReferenceEffect*, const T*>) {
				return static_cast<const BGSReferenceEffect*>(this);
			}
			break;
		case ENUM_FORM_ID::kREGN:
			if constexpr (std::is_convertible_v<const TESRegion*, const T*>) {
				return static_cast<const TESRegion*>(this);
			}
			break;
		case ENUM_FORM_ID::kNAVI:
			if constexpr (std::is_convertible_v<const NavMeshInfoMap*, const T*>) {
				return static_cast<const NavMeshInfoMap*>(this);
			}
			break;
		case ENUM_FORM_ID::kCELL:
			if constexpr (std::is_convertible_v<const TESObjectCELL*, const T*>) {
				return static_cast<const TESObjectCELL*>(this);
			}
			break;
		case ENUM_FORM_ID::kREFR:
			if constexpr (std::is_convertible_v<const TESObjectREFR*, const T*>) {
				return static_cast<const TESObjectREFR*>(this);
			}
			break;
		case ENUM_FORM_ID::kACHR:
			if constexpr (std::is_convertible_v<const Actor*, const T*>) {
				return static_cast<const Actor*>(this);
			}
			break;
		case ENUM_FORM_ID::kPMIS:
			if constexpr (std::is_convertible_v<const MissileProjectile*, const T*>) {
				return static_cast<const MissileProjectile*>(this);
			}
			break;
		case ENUM_FORM_ID::kPARW:
			if constexpr (std::is_convertible_v<const ArrowProjectile*, const T*>) {
				return static_cast<const ArrowProjectile*>(this);
			}
			break;
		case ENUM_FORM_ID::kPGRE:
			if constexpr (std::is_convertible_v<const GrenadeProjectile*, const T*>) {
				return static_cast<const GrenadeProjectile*>(this);
			}
			break;
		case ENUM_FORM_ID::kPBEA:
			if constexpr (std::is_convertible_v<const BeamProjectile*, const T*>) {
				return static_cast<const BeamProjectile*>(this);
			}
			break;
		case ENUM_FORM_ID::kPFLA:
			if constexpr (std::is_convertible_v<const FlameProjectile*, const T*>) {
				return static_cast<const FlameProjectile*>(this);
			}
			break;
		case ENUM_FORM_ID::kPCON:
			if constexpr (std::is_convertible_v<const ConeProjectile*, const T*>) {
				return static_cast<const ConeProjectile*>(this);
			}
			break;
		case ENUM_FORM_ID::kPBAR:
			if constexpr (std::is_convertible_v<const BarrierProjectile*, const T*>) {
				return static_cast<const BarrierProjectile*>(this);
			}
			break;
		case ENUM_FORM_ID::kPHZD:
			if constexpr (std::is_convertible_v<const Hazard*, const T*>) {
				return static_cast<const Hazard*>(this);
			}
			break;
		case ENUM_FORM_ID::kWRLD:
			if constexpr (std::is_convertible_v<const TESWorldSpace*, const T*>) {
				return static_cast<const TESWorldSpace*>(this);
			}
			break;
		case ENUM_FORM_ID::kLAND:
			if constexpr (std::is_convertible_v<const TESObjectLAND*, const T*>) {
				return static_cast<const TESObjectLAND*>(this);
			}
			break;
		case ENUM_FORM_ID::kNAVM:
			if constexpr (std::is_convertible_v<const NavMesh*, const T*>) {
				return static_cast<const NavMesh*>(this);
			}
			break;
		case ENUM_FORM_ID::kDIAL:
			if constexpr (std::is_convertible_v<const TESTopic*, const T*>) {
				return static_cast<const TESTopic*>(this);
			}
			break;
		case ENUM_FORM_ID::kINFO:
			if constexpr (std::is_convertible_v<const TESTopicInfo*, const T*>) {
				return static_cast<const TESTopicInfo*>(this);
			}
			break;
		case ENUM_FORM_ID::kQUST:
			if constexpr (std::is_convertible_v<const TESQuest*, const T*>) {
				return static_cast<const TESQuest*>(this);
			}
			break;
		case ENUM_FORM_ID::kIDLE:
			if constexpr (std::is_convertible_v<const TESIdleForm*, const T*>) {
				return static_cast<const TESIdleForm*>(this);
			}
			break;
		case ENUM_FORM_ID::kPACK:
			if constexpr (std::is_convertible_v<const TESPackage*, const T*>) {
				return static_cast<const TESPackage*>(this);
			}
			break;
		case ENUM_FORM_ID::kCSTY:
			if constexpr (std::is_convertible_v<const TESCombatStyle*, const T*>) {
				return static_cast<const TESCombatStyle*>(this);
			}
			break;
		case ENUM_FORM_ID::kLSCR:
			if constexpr (std::is_convertible_v<const TESLoadScreen*, const T*>) {
				return static_cast<const TESLoadScreen*>(this);
			}
			break;
		case ENUM_FORM_ID::kLVSP:
			if constexpr (std::is_convertible_v<const TESLevSpell*, const T*>) {
				return static_cast<const TESLevSpell*>(this);
			}
			break;
		case ENUM_FORM_ID::kANIO:
			if constexpr (std::is_convertible_v<const TESObjectANIO*, const T*>) {
				return static_cast<const TESObjectANIO*>(this);
			}
			break;
		case ENUM_FORM_ID::kWATR:
			if constexpr (std::is_convertible_v<const TESWaterForm*, const T*>) {
				return static_cast<const TESWaterForm*>(this);
			}
			break;
		case ENUM_FORM_ID::kEFSH:
			if constexpr (std::is_convertible_v<const TESEffectShader*, const T*>) {
				return static_cast<const TESEffectShader*>(this);
			}
			break;
		case ENUM_FORM_ID::kEXPL:
			if constexpr (std::is_convertible_v<const BGSExplosion*, const T*>) {
				return static_cast<const BGSExplosion*>(this);
			}
			break;
		case ENUM_FORM_ID::kDEBR:
			if constexpr (std::is_convertible_v<const BGSDebris*, const T*>) {
				return static_cast<const BGSDebris*>(this);
			}
			break;
		case ENUM_FORM_ID::kIMGS:
			if constexpr (std::is_convertible_v<const TESImageSpace*, const T*>) {
				return static_cast<const TESImageSpace*>(this);
			}
			break;
		case ENUM_FORM_ID::kIMAD:
			if constexpr (std::is_convertible_v<const TESImageSpaceModifier*, const T*>) {
				return static_cast<const TESImageSpaceModifier*>(this);
			}
			break;
		case ENUM_FORM_ID::kFLST:
			if constexpr (std::is_convertible_v<const BGSListForm*, const T*>) {
				return static_cast<const BGSListForm*>(this);
			}
			break;
		case ENUM_FORM_ID::kPERK:
			if constexpr (std::is_convertible_v<const BGSPerk*, const T*>) {
				return static_cast<const BGSPerk*>(this);
			}
			break;
		case ENUM_FORM_ID::kBPTD:
			if constexpr (std::is_convertible_v<const BGSBodyPartData*, const T*>) {
				return static_cast<const BGSBodyPartData*>(this);
			}
			break;
		case ENUM_FORM_ID::kADDN:
			if constexpr (std::is_convertible_v<const BGSAddonNode*, const T*>) {
				return static_cast<const BGSAddonNode*>(this);
			}
			break;
		case ENUM_FORM_ID::kAVIF:
			if constexpr (std::is_convertible_v<const ActorValueInfo*, const T*>) {
				return static_cast<const ActorValueInfo*>(this);
			}
			break;
		case ENUM_FORM_ID::kCAMS:
			if constexpr (std::is_convertible_v<const BGSCameraShot*, const T*>) {
				return static_cast<const BGSCameraShot*>(this);
			}
			break;
		case ENUM_FORM_ID::kCPTH:
			if constexpr (std::is_convertible_v<const BGSCameraPath*, const T*>) {
				return static_cast<const BGSCameraPath*>(this);
			}
			break;
		case ENUM_FORM_ID::kVTYP:
			if constexpr (std::is_convertible_v<const BGSVoiceType*, const T*>) {
				return static_cast<const BGSVoiceType*>(this);
			}
			break;
		case ENUM_FORM_ID::kMATT:
			if constexpr (std::is_convertible_v<const BGSMaterialType*, const T*>) {
				return static_cast<const BGSMaterialType*>(this);
			}
			break;
		case ENUM_FORM_ID::kIPCT:
			if constexpr (std::is_convertible_v<const BGSImpactData*, const T*>) {
				return static_cast<const BGSImpactData*>(this);
			}
			break;
		case ENUM_FORM_ID::kIPDS:
			if constexpr (std::is_convertible_v<const BGSImpactDataSet*, const T*>) {
				return static_cast<const BGSImpactDataSet*>(this);
			}
			break;
		case ENUM_FORM_ID::kARMA:
			if constexpr (std::is_convertible_v<const TESObjectARMA*, const T*>) {
				return static_cast<const TESObjectARMA*>(this);
			}
			break;
		case ENUM_FORM_ID::kECZN:
			if constexpr (std::is_convertible_v<const BGSEncounterZone*, const T*>) {
				return static_cast<const BGSEncounterZone*>(this);
			}
			break;
		case ENUM_FORM_ID::kLCTN:
			if constexpr (std::is_convertible_v<const BGSLocation*, const T*>) {
				return static_cast<const BGSLocation*>(this);
			}
			break;
		case ENUM_FORM_ID::kMESG:
			if constexpr (std::is_convertible_v<const BGSMessage*, const T*>) {
				return static_cast<const BGSMessage*>(this);
			}
			break;
		case ENUM_FORM_ID::kDOBJ:
			if constexpr (std::is_convertible_v<const BGSDefaultObjectManager*, const T*>) {
				return static_cast<const BGSDefaultObjectManager*>(this);
			}
			break;
		case ENUM_FORM_ID::kDFOB:
			if constexpr (std::is_convertible_v<const BGSDefaultObject*, const T*>) {
				return static_cast<const BGSDefaultObject*>(this);
			}
			break;
		case ENUM_FORM_ID::kLGTM:
			if constexpr (std::is_convertible_v<const BGSLightingTemplate*, const T*>) {
				return static_cast<const BGSLightingTemplate*>(this);
			}
			break;
		case ENUM_FORM_ID::kMUSC:
			if constexpr (std::is_convertible_v<const BGSMusicType*, const T*>) {
				return static_cast<const BGSMusicType*>(this);
			}
			break;
		case ENUM_FORM_ID::kFSTP:
			if constexpr (std::is_convertible_v<const BGSFootstep*, const T*>) {
				return static_cast<const BGSFootstep*>(this);
			}
			break;
		case ENUM_FORM_ID::kFSTS:
			if constexpr (std::is_convertible_v<const BGSFootstepSet*, const T*>) {
				return static_cast<const BGSFootstepSet*>(this);
			}
			break;
		case ENUM_FORM_ID::kSMBN:
			if constexpr (std::is_convertible_v<const BGSStoryManagerBranchNode*, const T*>) {
				return static_cast<const BGSStoryManagerBranchNode*>(this);
			}
			break;
		case ENUM_FORM_ID::kSMQN:
			if constexpr (std::is_convertible_v<const BGSStoryManagerQuestNode*, const T*>) {
				return static_cast<const BGSStoryManagerQuestNode*>(this);
			}
			break;
		case ENUM_FORM_ID::kSMEN:
			if constexpr (std::is_convertible_v<const BGSStoryManagerEventNode*, const T*>) {
				return static_cast<const BGSStoryManagerEventNode*>(this);
			}
			break;
		case ENUM_FORM_ID::kDLBR:
			if constexpr (std::is_convertible_v<const BGSDialogueBranch*, const T*>) {
				return static_cast<const BGSDialogueBranch*>(this);
			}
			break;
		case ENUM_FORM_ID::kMUST:
			if constexpr (std::is_convertible_v<const BGSMusicTrackFormWrapper*, const T*>) {
				return static_cast<const BGSMusicTrackFormWrapper*>(this);
			}
			break;
		case ENUM_FORM_ID::kWOOP:
			if constexpr (std::is_convertible_v<const TESWordOfPower*, const T*>) {
				return static_cast<const TESWordOfPower*>(this);
			}
			break;
		case ENUM_FORM_ID::kSHOU:
			if constexpr (std::is_convertible_v<const TESShout*, const T*>) {
				return static_cast<const TESShout*>(this);
			}
			break;
		case ENUM_FORM_ID::kEQUP:
			if constexpr (std::is_convertible_v<const BGSEquipSlot*, const T*>) {
				return static_cast<const BGSEquipSlot*>(this);
			}
			break;
		case ENUM_FORM_ID::kRELA:
			if constexpr (std::is_convertible_v<const BGSRelationship*, const T*>) {
				return static_cast<const BGSRelationship*>(this);
			}
			break;
		case ENUM_FORM_ID::kSCEN:
			if constexpr (std::is_convertible_v<const BGSScene*, const T*>) {
				return static_cast<const BGSScene*>(this);
			}
			break;
		case ENUM_FORM_ID::kASTP:
			if constexpr (std::is_convertible_v<const BGSAssociationType*, const T*>) {
				return static_cast<const BGSAssociationType*>(this);
			}
			break;
		case ENUM_FORM_ID::kOTFT:
			if constexpr (std::is_convertible_v<const BGSOutfit*, const T*>) {
				return static_cast<const BGSOutfit*>(this);
			}
			break;
		case ENUM_FORM_ID::kARTO:
			if constexpr (std::is_convertible_v<const BGSArtObject*, const T*>) {
				return static_cast<const BGSArtObject*>(this);
			}
			break;
		case ENUM_FORM_ID::kMATO:
			if constexpr (std::is_convertible_v<const BGSMaterialObject*, const T*>) {
				return static_cast<const BGSMaterialObject*>(this);
			}
			break;
		case ENUM_FORM_ID::kMOVT:
			if constexpr (std::is_convertible_v<const BGSMovementType*, const T*>) {
				return static_cast<const BGSMovementType*>(this);
			}
			break;
		case ENUM_FORM_ID::kSNDR:
			if constexpr (std::is_convertible_v<const BGSSoundDescriptorForm*, const T*>) {
				return static_cast<const BGSSoundDescriptorForm*>(this);
			}
			break;
		case ENUM_FORM_ID::kDUAL:
			if constexpr (std::is_convertible_v<const BGSDualCastData*, const T*>) {
				return static_cast<const BGSDualCastData*>(this);
			}
			break;
		case ENUM_FORM_ID::kSNCT:
			if constexpr (std::is_convertible_v<const BGSSoundCategory*, const T*>) {
				return static_cast<const BGSSoundCategory*>(this);
			}
			break;
		case ENUM_FORM_ID::kSOPM:
			if constexpr (std::is_convertible_v<const BGSSoundOutput*, const T*>) {
				return static_cast<const BGSSoundOutput*>(this);
			}
			break;
		case ENUM_FORM_ID::kCOLL:
			if constexpr (std::is_convertible_v<const BGSCollisionLayer*, const T*>) {
				return static_cast<const BGSCollisionLayer*>(this);
			}
			break;
		case ENUM_FORM_ID::kCLFM:
			if constexpr (std::is_convertible_v<const BGSColorForm*, const T*>) {
				return static_cast<const BGSColorForm*>(this);
			}
			break;
		case ENUM_FORM_ID::kREVB:
			if constexpr (std::is_convertible_v<const BGSReverbParameters*, const T*>) {
				return static_cast<const BGSReverbParameters*>(this);
			}
			break;
		case ENUM_FORM_ID::kPKIN:
			if constexpr (std::is_convertible_v<const BGSPackIn*, const T*>) {
				return static_cast<const BGSPackIn*>(this);
			}
			break;
		case ENUM_FORM_ID::kAMDL:
			if constexpr (std::is_convertible_v<const BGSAimModel*, const T*>) {
				return static_cast<const BGSAimModel*>(this);
			}
			break;
		case ENUM_FORM_ID::kCOBJ:
			if constexpr (std::is_convertible_v<const BGSConstructibleObject*, const T*>) {
				return static_cast<const BGSConstructibleObject*>(this);
			}
			break;
		case ENUM_FORM_ID::kOMOD:
			if constexpr (std::is_convertible_v<const BGSMod::Attachment::Mod*, const T*>) {
				return static_cast<const BGSMod::Attachment::Mod*>(this);
			}
			break;
		case ENUM_FORM_ID::kMSWP:
			if constexpr (std::is_convertible_v<const BGSMaterialSwap*, const T*>) {
				return static_cast<const BGSMaterialSwap*>(this);
			}
			break;
		case ENUM_FORM_ID::kZOOM:
			if constexpr (std::is_convertible_v<const BGSZoomData*, const T*>) {
				return static_cast<const BGSZoomData*>(this);
			}
			break;
		case ENUM_FORM_ID::kINNR:
			if constexpr (std::is_convertible_v<const BGSInstanceNamingRules*, const T*>) {
				return static_cast<const BGSInstanceNamingRules*>(this);
			}
			break;
		case ENUM_FORM_ID::kKSSM:
			if constexpr (std::is_convertible_v<const BGSSoundKeywordMapping*, const T*>) {
				return static_cast<const BGSSoundKeywordMapping*>(this);
			}
			break;
		case ENUM_FORM_ID::kAECH:
			if constexpr (std::is_convertible_v<const BGSAudioEffectChain*, const T*>) {
				return static_cast<const BGSAudioEffectChain*>(this);
			}
			break;
		case ENUM_FORM_ID::kAORU:
			if constexpr (std::is_convertible_v<const BGSAttractionRule*, const T*>) {
				return static_cast<const BGSAttractionRule*>(this);
			}
			break;
		case ENUM_FORM_ID::kSCSN:
			if constexpr (std::is_convertible_v<const BGSSoundCategorySnapshot*, const T*>) {
				return static_cast<const BGSSoundCategorySnapshot*>(this);
			}
			break;
		case ENUM_FORM_ID::kSTAG:
			if constexpr (std::is_convertible_v<const BGSSoundTagSet*, const T*>) {
				return static_cast<const BGSSoundTagSet*>(this);
			}
			break;
		case ENUM_FORM_ID::kLENS:
			if constexpr (std::is_convertible_v<const BGSLensFlare*, const T*>) {
				return static_cast<const BGSLensFlare*>(this);
			}
			break;
		case ENUM_FORM_ID::kGDRY:
			if constexpr (std::is_convertible_v<const BGSGodRays*, const T*>) {
				return static_cast<const BGSGodRays*>(this);
			}
			break;
		default:
			break;
		}

		return nullptr;
	}
}
