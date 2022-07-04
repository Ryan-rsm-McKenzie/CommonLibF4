#pragma once

#include "RE/Bethesda/Atomic.h"
#include "RE/Bethesda/BGSBodyPartDefs.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSPointerHandle.h"
#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTList.h"
#include "RE/Bethesda/BSTSingleton.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTTuple.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/Movement.h"
#include "RE/Bethesda/Settings.h"
#include "RE/Bethesda/TESCondition.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiFlags.h"
#include "RE/NetImmerse/NiPoint2.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class TESForm;
	class TESObject;
	class TESBoundObject;
	class MagicItem;
	class TESBoundAnimObject;
	class TESActorBase;
	class BGSStoryManagerTreeForm;
	class BGSStoryManagerNodeBase;
	class BGSKeyword;
	class BGSLocationRefType;
	class BGSAction;
	class BGSTransform;
	class BGSComponent;
	class BGSTextureSet;
	class BGSMenuIcon;
	class TESGlobal;
	class BGSDamageType;
	class TESClass;
	class TESFaction;
	class BGSHeadPart;
	class TESEyes;
	class TESRace;
	class TESSound;
	class BGSAcousticSpace;
	class EffectSetting;
	class Script;
	class TESLandTexture;
	class EnchantmentItem;
	class SpellItem;
	class ScrollItem;
	class TESObjectACTI;
	class BGSTalkingActivator;
	class TESObjectARMO;
	class TESObjectBOOK;
	class TESObjectCONT;
	class TESObjectDOOR;
	class IngredientItem;
	class TESObjectLIGH;
	class TESObjectMISC;
	class TESObjectSTAT;
	class BGSStaticCollection;
	class BGSMovableStatic;
	class TESGrass;
	class TESObjectTREE;
	class TESFlora;
	class TESFurniture;
	class TESObjectWEAP;
	class TESAmmo;
	class TESNPC;
	class TESLevCharacter;
	class TESKey;
	class AlchemyItem;
	class BGSIdleMarker;
	class BGSNote;
	class BGSProjectile;
	class BGSHazard;
	class BGSBendableSpline;
	class TESSoulGem;
	class BGSTerminal;
	class TESLevItem;
	class TESWeather;
	class TESClimate;
	class BGSShaderParticleGeometryData;
	class BGSReferenceEffect;
	class TESRegion;
	class NavMeshInfoMap;
	class TESObjectCELL;
	class Actor;
	class PlayerCharacter;
	class MissileProjectile;
	class ArrowProjectile;
	class GrenadeProjectile;
	class BeamProjectile;
	class FlameProjectile;
	class ConeProjectile;
	class BarrierProjectile;
	class TESObjectREFR;
	class Explosion;
	class Projectile;
	class TESWorldSpace;
	class TESObjectLAND;
	class NavMesh;
	class TESTopic;
	class TESTopicInfo;
	class TESQuest;
	class TESIdleForm;
	class TESPackage;
	class AlarmPackage;
	class DialoguePackage;
	class FleePackage;
	class SpectatorPackage;
	class TrespassPackage;
	class TESCombatStyle;
	class TESLoadScreen;
	class TESLevSpell;
	class TESObjectANIO;
	class TESWaterForm;
	class TESEffectShader;
	class BGSExplosion;
	class BGSDebris;
	class TESImageSpace;
	class TESImageSpaceModifier;
	class BGSListForm;
	class BGSPerk;
	class BGSBodyPartData;
	class BGSAddonNode;
	class ActorValueInfo;
	class BGSCameraShot;
	class BGSCameraPath;
	class BGSVoiceType;
	class BGSMaterialType;
	class BGSImpactData;
	class BGSImpactDataSet;
	class TESObjectARMA;
	class BGSEncounterZone;
	class BGSLocation;
	class BGSMessage;
	class BGSDefaultObjectManager;
	class BGSDefaultObject;
	class BGSLightingTemplate;
	class BGSMusicType;
	class BGSFootstep;
	class BGSFootstepSet;
	class BGSStoryManagerBranchNode;
	class BGSStoryManagerQuestNode;
	class BGSStoryManagerEventNode;
	class BGSDialogueBranch;
	class BGSMusicTrackFormWrapper;
	class TESWordOfPower;
	class TESShout;
	class BGSEquipSlot;
	class BGSRelationship;
	class BGSScene;
	class BGSAssociationType;
	class BGSOutfit;
	class BGSArtObject;
	class BGSMaterialObject;
	class BGSMovementType;
	class BGSSoundDescriptorForm;
	class BGSDualCastData;
	class BGSSoundCategory;
	class BGSSoundOutput;
	class BGSCollisionLayer;
	class BGSColorForm;
	class BGSReverbParameters;
	class BGSPackIn;
	class BGSAimModel;
	class BGSConstructibleObject;
	class BGSMaterialSwap;
	class BGSZoomData;
	class BGSInstanceNamingRules;
	class BGSSoundKeywordMapping;
	class BGSAudioEffectChain;
	class BGSAttractionRule;
	class BGSSoundCategorySnapshot;
	class BGSSoundTagSet;
	class BGSLensFlare;
	class BGSGodRays;

	namespace BGSMod::Attachment
	{
		class Mod;
	}

	enum class ENUM_FORM_ID
	{
		kNONE,  // 00 NONE X TESForm
				//         X TESObject
				//         X TESBoundObject
				//         X MagicItem
				//         X TESBoundAnimObject
				//         X TESActorBase
				//         X BGSStoryManagerTreeForm
				//         X BGSStoryManagerNodeBase
		kTES4,  // 01 TES4
		kGRUP,  // 02 GRUP
		kGMST,  // 03 GMST
		kKYWD,  // 04 KYWD X BGSKeyword
		kLCRT,  // 05 LCRT X BGSLocationRefType
		kAACT,  // 06 AACT X BGSAction
		kTRNS,  // 07 TRNS X BGSTransform
		kCMPO,  // 08 CMPO X BGSComponent
		kTXST,  // 09 TXST X BGSTextureSet
		kMICN,  // 0A MICN X BGSMenuIcon
		kGLOB,  // 0B GLOB X TESGlobal
		kDMGT,  // 0C DMGT X BGSDamageType
		kCLAS,  // 0D CLAS X TESClass
		kFACT,  // 0E FACT X TESFaction
		kHDPT,  // 0F HDPT X BGSHeadPart
		kEYES,  // 10 EYES X TESEyes
		kRACE,  // 11 RACE X TESRace
		kSOUN,  // 12 SOUN X TESSound
		kASPC,  // 13 ASPC X BGSAcousticSpace
		kSKIL,  // 14 SKIL
		kMGEF,  // 15 MGEF X EffectSetting
		kSCPT,  // 16 SCPT X Script
		kLTEX,  // 17 LTEX X TESLandTexture
		kENCH,  // 18 ENCH X EnchantmentItem
		kSPEL,  // 19 SPEL X SpellItem
		kSCRL,  // 1A SCRL X ScrollItem
		kACTI,  // 1B ACTI X TESObjectACTI
		kTACT,  // 1C TACT X BGSTalkingActivator
		kARMO,  // 1D ARMO X TESObjectARMO
		kBOOK,  // 1E BOOK X TESObjectBOOK
		kCONT,  // 1F CONT X TESObjectCONT
		kDOOR,  // 20 DOOR X TESObjectDOOR
		kINGR,  // 21 INGR X IngredientItem
		kLIGH,  // 22 LIGH X TESObjectLIGH
		kMISC,  // 23 MISC X TESObjectMISC
		kSTAT,  // 24 STAT X TESObjectSTAT
		kSCOL,  // 25 SCOL X BGSStaticCollection
		kMSTT,  // 26 MSTT X BGSMovableStatic
		kGRAS,  // 27 GRAS X TESGrass
		kTREE,  // 28 TREE X TESObjectTREE
		kFLOR,  // 29 FLOR X TESFlora
		kFURN,  // 2A FURN X TESFurniture
		kWEAP,  // 2B WEAP X TESObjectWEAP
		kAMMO,  // 2C AMMO X TESAmmo
		kNPC_,  // 2D NPC_ X TESNPC
		kLVLN,  // 2E LVLN X TESLevCharacter
		kKEYM,  // 2F KEYM X TESKey
		kALCH,  // 30 ALCH X AlchemyItem
		kIDLM,  // 31 IDLM X BGSIdleMarker
		kNOTE,  // 32 NOTE X BGSNote
		kPROJ,  // 33 PROJ X BGSProjectile
		kHAZD,  // 34 HAZD X BGSHazard
		kBNDS,  // 35 BNDS X BGSBendableSpline
		kSLGM,  // 36 SLGM X TESSoulGem
		kTERM,  // 37 TERM X BGSTerminal
		kLVLI,  // 38 LVLI X TESLevItem
		kWTHR,  // 39 WTHR X TESWeather
		kCLMT,  // 3A CLMT X TESClimate
		kSPGD,  // 3B SPGD X BGSShaderParticleGeometryData
		kRFCT,  // 3C RFCT X BGSReferenceEffect
		kREGN,  // 3D REGN X TESRegion
		kNAVI,  // 3E NAVI X NavMeshInfoMap
		kCELL,  // 3F CELL X TESObjectCELL
		kREFR,  // 40 REFR X TESObjectREFR
				//         X Explosion
				//         X Projectile
		kACHR,  // 41 ACHR X Actor
				//         X PlayerCharacter
		kPMIS,  // 42 PMIS X MissileProjectile
		kPARW,  // 43 PARW X ArrowProjectile
		kPGRE,  // 44 PGRE X GrenadeProjectile
		kPBEA,  // 45 PBEA X BeamProjectile
		kPFLA,  // 46 PFLA X FlameProjectile
		kPCON,  // 47 PCON X ConeProjectile
		kPBAR,  // 48 PBAR X BarrierProjectile
		kPHZD,  // 49 PHZD X Hazard
		kWRLD,  // 4A WRLD X TESWorldSpace
		kLAND,  // 4B LAND X TESObjectLAND
		kNAVM,  // 4C NAVM X NavMesh
		kTLOD,  // 4D TLOD
		kDIAL,  // 4E DIAL X TESTopic
		kINFO,  // 4F INFO X TESTopicInfo
		kQUST,  // 50 QUST X TESQuest
		kIDLE,  // 51 IDLE X TESIdleForm
		kPACK,  // 52 PACK X TESPackage
				//         X AlarmPackage
				//         X DialoguePackage
				//         X FleePackage
				//         X SpectatorPackage
				//         X TrespassPackage
		kCSTY,  // 53 CSTY X TESCombatStyle
		kLSCR,  // 54 LSCR X TESLoadScreen
		kLVSP,  // 55 LVSP X TESLevSpell
		kANIO,  // 56 ANIO X TESObjectANIO
		kWATR,  // 57 WATR X TESWaterForm
		kEFSH,  // 58 EFSH X TESEffectShader
		kTOFT,  // 59 TOFT
		kEXPL,  // 5A EXPL X BGSExplosion
		kDEBR,  // 5B DEBR X BGSDebris
		kIMGS,  // 5C IMGS X TESImageSpace
		kIMAD,  // 5D IMAD X TESImageSpaceModifier
		kFLST,  // 5E FLST X BGSListForm
		kPERK,  // 5F PERK X BGSPerk
		kBPTD,  // 60 BPTD X BGSBodyPartData
		kADDN,  // 61 ADDN X BGSAddonNode
		kAVIF,  // 62 AVIF X ActorValueInfo
		kCAMS,  // 63 CAMS X BGSCameraShot
		kCPTH,  // 64 CPTH X BGSCameraPath
		kVTYP,  // 65 VTYP X BGSVoiceType
		kMATT,  // 66 MATT X BGSMaterialType
		kIPCT,  // 67 IPCT X BGSImpactData
		kIPDS,  // 68 IPDS X BGSImpactDataSet
		kARMA,  // 69 ARMA X TESObjectARMA
		kECZN,  // 6A ECZN X BGSEncounterZone
		kLCTN,  // 6B LCTN X BGSLocation
		kMESG,  // 6C MESG X BGSMessage
		kRGDL,  // 6D RGDL
		kDOBJ,  // 6E DOBJ X BGSDefaultObjectManager
		kDFOB,  // 6F DFOB X BGSDefaultObject
		kLGTM,  // 70 LGTM X BGSLightingTemplate
		kMUSC,  // 71 MUSC X BGSMusicType
		kFSTP,  // 72 FSTP X BGSFootstep
		kFSTS,  // 73 FSTS X BGSFootstepSet
		kSMBN,  // 74 SMBN X BGSStoryManagerBranchNode
		kSMQN,  // 75 SMQN X BGSStoryManagerQuestNode
		kSMEN,  // 76 SMEN X BGSStoryManagerEventNode
		kDLBR,  // 77 DLBR X BGSDialogueBranch
		kMUST,  // 78 MUST X BGSMusicTrackFormWrapper
		kDLVW,  // 79 DLVW
		kWOOP,  // 7A WOOP X TESWordOfPower
		kSHOU,  // 7B SHOU X TESShout
		kEQUP,  // 7C EQUP X BGSEquipSlot
		kRELA,  // 7D RELA X BGSRelationship
		kSCEN,  // 7E SCEN X BGSScene
		kASTP,  // 7F ASTP X BGSAssociationType
		kOTFT,  // 80 OTFT X BGSOutfit
		kARTO,  // 81 ARTO X BGSArtObject
		kMATO,  // 82 MATO X BGSMaterialObject
		kMOVT,  // 83 MOVT X BGSMovementType
		kSNDR,  // 84 SNDR X BGSSoundDescriptorForm
		kDUAL,  // 85 DUAL X BGSDualCastData
		kSNCT,  // 86 SNCT X BGSSoundCategory
		kSOPM,  // 87 SOPM X BGSSoundOutput
		kCOLL,  // 88 COLL X BGSCollisionLayer
		kCLFM,  // 89 CLFM X BGSColorForm
		kREVB,  // 8A REVB X BGSReverbParameters
		kPKIN,  // 8B PKIN X BGSPackIn
		kRFGP,  // 8C RFGP
		kAMDL,  // 8D AMDL X BGSAimModel
		kLAYR,  // 8E LAYR
		kCOBJ,  // 8F COBJ X BGSConstructibleObject
		kOMOD,  // 90 OMOD X BGSMod::Attachment::Mod
		kMSWP,  // 91 MSWP X BGSMaterialSwap
		kZOOM,  // 92 ZOOM X BGSZoomData
		kINNR,  // 93 INNR X BGSInstanceNamingRules
		kKSSM,  // 94 KSSM X BGSSoundKeywordMapping
		kAECH,  // 95 AECH X BGSAudioEffectChain
		kSCCO,  // 96 SCCO
		kAORU,  // 97 AORU X BGSAttractionRule
		kSCSN,  // 98 SCSN X BGSSoundCategorySnapshot
		kSTAG,  // 99 STAG X BGSSoundTagSet
		kNOCM,  // 9A NOCM
		kLENS,  // 9B LENS X BGSLensFlare
		kLSPR,  // 9C LSPR
		kGDRY,  // 9D GDRY X BGSGodRays
		kOVIS,  // 9E OVIS

		kTotal
	};

	enum class _D3DBLEND;    // NOLINT(bugprone-reserved-identifier)
	enum class _D3DBLENDOP;  // NOLINT(bugprone-reserved-identifier)
	enum class _D3DCMPFUNC;  // NOLINT(bugprone-reserved-identifier)
	enum class CHUNK_ID;
	enum class COMMAND_REFUSAL_TYPE;
	enum class DIALOGUE_SUBTYPE;
	enum class DIALOGUE_TYPE;
	enum class SOUND_LEVEL;
	enum class STAGGER_MAGNITUDE;

	namespace BGSMod::Template
	{
		class Items;
	}

	namespace EffectArchetypes
	{
		enum class ArchetypeID;
	}

	namespace MagicSystem
	{
		enum class CastingType;
		enum class Delivery;
		enum class SoundID;
		enum class SpellType;
	}

	class BGSBodyPart;
	class BGSLoadFormBuffer;
	class BGSLoadGameBuffer;
	class BGSMusicTrack;
	class BGSPerkEntry;
	class BGSPreviewTransform;
	class BGSSaveFormBuffer;
	class BGSSceneAction;
	class BGSSoundDescriptor;
	class BSGeometry;
	class BSMultiBoundNode;
	class BSPortalGraph;
	class BSIAudioEffectParameters;
	class BSLensFlareSpriteRenderData;
	class ExtraDataList;
	class NavMeshArray;
	class NiColorInterpolator;
	class NiFloatInterpolator;
	class NiFormArray;
	class NiNode;
	class NiTexture;
	class QueuedFile;
	class QueuedPromoteLocationReferencesTask;
	class TBO_InstanceData;
	class TESFile;
	class TESPackageData;
	class TESRegionDataList;
	class TESRegionPointList;
	class TESResponse;

	struct BGSDebrisData;
	struct FORM;
	struct FORM_GROUP;
	struct EXTERIOR_DATA;
	struct OverrideData;

	namespace BGSWaterCollisionManager
	{
		class AutoWater;
		class BGSWaterUpdateI;
	}

	struct CHANGE_TYPES
	{
		enum CHANGE_TYPE : std::uint32_t
		{
			kFormCreated = 0,
			kFormFlags = 1u << 0,
			kRefrMove = 1u << 1,
			kRefrHavokMove = 1u << 2,
			kRefrCellChange = 1u << 3,
			kRefrScale = 1u << 4,
			kRefrInventory = 1u << 5,
			kRefrExtraOwnership = 1u << 6,
			kRefrBaseObject = 1u << 7,
			kRefrExtraLinkRef = 1u << 8,
			kRefrExtraWorkshop = 1u << 9,
			kRefrExtraGameOnly = 1u << 31,
			kRefrExtraCreatedOnly = 1u << 30,
			kRefrExtraEncounterZone = 1u << 29,
			kRefrAnimation = 1u << 28,
			kRefrLeveledInventory = 1u << 27,
			kRefrExtraActivatingChildren = 1u << 26,
			kRefrPromoted = 1u << 25,
			kActorLifestate = 1u << 10,
			kActorExtraPackageData = 1u << 11,
			kActorExtraMerchantContainer = 1u << 12,
			kActorPermanentModifiers = 1u << 23,
			kActorOverrideModifiers = 1u << 22,
			kActorDamageModifiers = 1u << 21,
			kActorTempModifiers = 1u << 20,
			kActorDispositionModifiers = 1u << 19,
			kActorExtraLeveledActor = 1u << 18,
			kActorExtraDismemberedLimbs = 1u << 17,
			kObjectExtraItemData = 1u << 10,
			kObjectExtraAmmo = 1u << 11,
			kObjectExtraLock = 1u << 12,
			kObjectForceMove = 1u << 13,
			kObjectOpenState = 1u << 23,
			kObjectOpenDefaultState = 1u << 22,
			kObjectEmpty = 1u << 21,
			kDoorExtraTeleport = 1u << 17,
			kQuestFlags = 1u << 1,
			kQuestScriptDelay = 1u << 2,
			kQuestStages = 1u << 31,
			kQuestScript = 1u << 30,
			kQuestObjectives = 1u << 29,
			kQuestRunData = 1u << 28,
			kQuestInstances = 1u << 27,
			kQuestAlreadyRun = 1u << 26,
			kTopicSaidPlayer = 1u << 30,
			kTopicSaidOnce = 1u << 31,
			kRelationshipData = 1u << 1,
			kLocationSpecRefs = 1u < 28,
			kLocationNewRefs = 1u << 29,
			kLocationKeywordData = 1u << 30,
			kLocationCleared = 1u << 31,
			kNoteRead = 1u << 31,
			kCellSeenData = 1u << 31,
			kCellDetachTime = 1u << 30,
			kCellExteriorChar = 1u << 29,
			kCellExteriorShort = 1u << 28,
			kCellFlags = 1u << 1,
			kCellFullname = 1u << 2,
			kCellOwnership = 1u << 3,
			kFactionFlags = 1u << 1,
			kFactionReactions = 1u << 2,
			kFactionVendorData = 1u << 30,
			kFactionCrimeCounts = 1u << 31,
			kPackageNeverRun = 1u << 31,
			kPackageWaiting = 1u << 30,
			kBaseObjectValue = 1u << 1,
			kBaseObjectFullName = 1u << 2,
			kBookTeaches = 1u << 5,
			kBookRead = 1u << 6,
			kTalkingActivatorSpeaker = 1u << 23,
			kActorBaseData = 1u << 1,
			kActorBaseAttributes = 1u << 2,
			kActorBaseAIData = 1u << 3,
			kActorBaseSpellList = 1u << 4,
			kActorBaseFullName = 1u << 5,
			kActorBaseFactions = 1u << 6,
			kNPCSkills = 1u << 9,
			kNPCClass = 1u << 10,
			kNPCFace = 1u << 11,
			kNPCDefaultOutfit = 1u << 12,
			kNPCSleepOutfit = 1u << 13,
			kNPCBodyScales = 1u << 14,
			kNPCRace = 1u << 25,
			kNPCGender = 1u << 24,
			kCreatureSkills = 1u << 9,
			kClassTagSkills = 1u << 1,
			kEncounterZoneFlags = 1u << 1,
			kEncounterZoneGameData = 1u << 31,
			kQuestNodeRunTime = 1u << 31,
			kSceneActive = 1u << 31,
			kFormListAddedForm = 1u << 31,
			kLeveledListAddedObject = 1u << 31,
			kIngredientUse = 1u << 31,
			kINRMergeTarget = 1u << 31
		};
	};
	using CHANGE_TYPE = CHANGE_TYPES::CHANGE_TYPE;

	class TESFileArray :
		public BSStaticArray<TESFile*>  // 00
	{
	public:
	};
	static_assert(sizeof(TESFileArray) == 0x10);

	struct TESFileContainer
	{
	public:
		// members
		const TESFileArray* array;  // 0
	};
	static_assert(sizeof(TESFileContainer) == 0x8);

	class __declspec(novtable) TESForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESForm };
		static constexpr auto VTABLE{ VTABLE::TESForm };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNONE };

		// override (BaseFormComponent)
		void InitializeDataComponent() override { return; }          // 02
		void ClearDataComponent() override { SetFormEditorID(""); }  // 03
		void CopyComponent(BaseFormComponent*) override { return; }  // 06

		// add
		virtual void InitializeData() { return; }                                                                                                                                                                                     // 07
		virtual void ClearData() { return; }                                                                                                                                                                                          // 08
		virtual bool Load([[maybe_unused]] TESFile* a_file) { return true; }                                                                                                                                                          // 09
		virtual bool LoadPartial([[maybe_unused]] TESFile* a_file) { return true; }                                                                                                                                                   // 0A
		virtual bool LoadEdit(TESFile* a_file) { return Load(a_file); }                                                                                                                                                               // 0B
		virtual TESForm* CreateDuplicateForm(bool a_createEditorID, BSTHashMap<TESForm*, TESForm*>* a_copyMap);                                                                                                                       // 0C
		virtual bool AddChange(std::uint32_t a_changeFlags);                                                                                                                                                                          // 0D
		virtual void RemoveChange(std::uint32_t a_changeFlags);                                                                                                                                                                       // 0E
		virtual bool FindInFileFast([[maybe_unused]] TESFile* a_file) { return false; }                                                                                                                                               // 0F
		virtual bool CheckSaveGame([[maybe_unused]] BGSSaveFormBuffer* a_saveGameBuffer) const { return true; }                                                                                                                       // 10
		virtual void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer);                                                                                                                                                                   // 11
		virtual void LoadGame(BGSLoadFormBuffer* a_loadGameBuffer);                                                                                                                                                                   // 12
		virtual void InitLoadGame([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) { return; }                                                                                                                                   // 13
		virtual void FinishLoadGame([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) { return; }                                                                                                                                 // 14
		virtual void Revert([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) { return; }                                                                                                                                         // 15
		virtual void InitItemImpl() { return; }                                                                                                                                                                                       // 16
		virtual TESFile* GetRevertFile() const;                                                                                                                                                                                       // 17
		virtual TESFile* GetDescriptionOwnerFile() const;                                                                                                                                                                             // 18
		virtual ENUM_FORM_ID GetSavedFormType() const { return *formType; }                                                                                                                                                           // 19
		virtual void GetFormDetailedString(char* a_dest, std::uint32_t a_size) const;                                                                                                                                                 // 1A
		virtual bool GetKnown() const { return (formFlags >> 6) & 1; }                                                                                                                                                                // 1B
		virtual bool GetRandomAnim() const { return (formFlags >> 16) & 1; }                                                                                                                                                          // 1C
		virtual bool GetPlayable([[maybe_unused]] const TBO_InstanceData* a_data) const { return (formFlags >> 2) & 1; }                                                                                                              // 1D
		virtual bool IsHeadingMarker() const { return false; }                                                                                                                                                                        // 1E
		virtual bool IsHeadtrackMarker() const { return false; }                                                                                                                                                                      // 1F
		virtual bool GetDangerous() const { return (formFlags >> 17) & 1; }                                                                                                                                                           // 20
		virtual bool QHasCurrents() const { return (formFlags >> 19) & 1; }                                                                                                                                                           // 21
		virtual bool GetObstacle() const { return (formFlags >> 25) & 1; }                                                                                                                                                            // 22
		virtual bool QIsLODLandObject() const { return false; }                                                                                                                                                                       // 23
		virtual bool GetOnLocalMap() const { return (formFlags >> 9) & 1; }                                                                                                                                                           // 24
		virtual bool GetMustUpdate() const { return (formFlags >> 8) & 1; }                                                                                                                                                           // 25
		virtual void SetOnLocalMap(bool a_val);                                                                                                                                                                                       // 26
		virtual bool GetIgnoredBySandbox() const { return false; }                                                                                                                                                                    // 27
		virtual void SetDelete(bool a_deleted);                                                                                                                                                                                       // 28
		virtual void SetAltered(bool a_altered);                                                                                                                                                                                      // 29
		virtual void SaveObjectBound() { return; }                                                                                                                                                                                    // 2A
		virtual void LoadObjectBound([[maybe_unused]] TESFile* a_file) { return; }                                                                                                                                                    // 2B
		virtual void SavePreviewTransform(CHUNK_ID) { return; }                                                                                                                                                                       // 2C
		virtual void LoadPreviewTransform([[maybe_unused]] TESFile* a_file) { return; }                                                                                                                                               // 2D
		virtual bool IsBoundObject() const { return false; }                                                                                                                                                                          // 2E
		virtual bool IsObject() const { return false; }                                                                                                                                                                               // 2F
		virtual bool IsMagicItem() const { return false; }                                                                                                                                                                            // 30
		virtual bool IsWater() const { return false; }                                                                                                                                                                                // 31
		virtual TESObjectREFR* IsReference() { return nullptr; }                                                                                                                                                                      // 33
		virtual const TESObjectREFR* IsReference() const { return nullptr; }                                                                                                                                                          // 32
		virtual std::uint32_t GetRefCount() const { return 0; }                                                                                                                                                                       // 34
		virtual const char* GetTextForParsedSubTag(const BSFixedString& a_subTag) const;                                                                                                                                              // 35
		virtual void Copy([[maybe_unused]] TESForm* a_copy) { return; }                                                                                                                                                               // 36
		virtual bool BelongsInGroup(FORM* a_groupFORM, bool a_allowParentGroups, bool a_currentOnly);                                                                                                                                 // 37
		virtual void CreateGroupData(FORM* a_outGroupFORM, FORM_GROUP* a_parentGroup);                                                                                                                                                // 38
		virtual std::uint32_t GetFormEditorIDLength() const;                                                                                                                                                                          // 39
		virtual const char* GetFormEditorID() const { return ""; }                                                                                                                                                                    // 3A
		virtual bool SetFormEditorID([[maybe_unused]] const char* a_editorID) { return true; }                                                                                                                                        // 3B
		virtual bool IsParentForm() { return false; }                                                                                                                                                                                 // 3C
		virtual bool IsParentFormTree() { return false; }                                                                                                                                                                             // 3D
		virtual bool IsFormTypeChild([[maybe_unused]] std::uint8_t a_type) { return false; }                                                                                                                                          // 3E
		virtual bool LoopingActivate(TESObjectREFR* a_itemActivated, TESObjectREFR* a_actionRef) { return Activate(a_itemActivated, a_actionRef, nullptr, 1); }                                                                       // 3F
		virtual bool Activate([[maybe_unused]] TESObjectREFR* a_itemActivated, [[maybe_unused]] TESObjectREFR* a_actionRef, [[maybe_unused]] TESBoundObject* a_objectToGet, [[maybe_unused]] std::int32_t a_count) { return false; }  // 40
		virtual void SetFormID(std::uint32_t a_id, bool a_updateFile);                                                                                                                                                                // 41
		virtual const char* GetObjectTypeName() const { return ""; }                                                                                                                                                                  // 42
		virtual bool QAvailableInGame() const { return true; }                                                                                                                                                                        // 43
		virtual BGSMod::Template::Items* GetObjectTemplate() { return nullptr; }                                                                                                                                                      // 44
		virtual BGSPreviewTransform* GetPreviewTransform() { return nullptr; }                                                                                                                                                        // 45
		virtual BGSSoundTagComponent* GetSoundTagComponent() { return nullptr; }                                                                                                                                                      // 46
		virtual std::uint32_t GetFilledSlots() const;                                                                                                                                                                                 // 47
		virtual std::uint32_t GetFilledSlotsImpl() const { return static_cast<std::uint32_t>(-1); }                                                                                                                                   // 48
		virtual float GetDesirability([[maybe_unused]] TBO_InstanceData* a_instanceData, [[maybe_unused]] const TESForm* a_user) const { return 0.0F; }                                                                               // 49

		static void AddCompileIndex(std::uint32_t& a_id, TESFile* a_file)
		{
			using func_t = decltype(&TESForm::AddCompileIndex);
			REL::Relocation<func_t> func{ REL::ID(1315637) };
			return func(a_id, a_file);
		}

		[[nodiscard]] static auto GetAllForms()
			-> std::pair<
				BSTHashMap<std::uint32_t, TESForm*>*,
				std::reference_wrapper<BSReadWriteLock>>
		{
			REL::Relocation<BSTHashMap<std::uint32_t, TESForm*>**> allForms{ REL::ID(422985) };
			REL::Relocation<BSReadWriteLock*> allFormsMapLock{ REL::ID(691815) };
			return { *allForms, *allFormsMapLock };
		}

		[[nodiscard]] static auto GetAllFormsByEditorID()
			-> std::pair<
				BSTHashMap<BSFixedString, TESForm*>*,
				std::reference_wrapper<BSReadWriteLock>>
		{
			REL::Relocation<BSTHashMap<BSFixedString, TESForm*>**> allFormsByEditorID{ REL::ID(642758) };
			REL::Relocation<BSReadWriteLock*> allFormsEditorIDMapLock{ REL::ID(910917) };
			return { *allFormsByEditorID, *allFormsEditorIDMapLock };
		}

		[[nodiscard]] TESFile* GetFile(std::int32_t a_index = -1) const
		{
			using func_t = decltype(&TESForm::GetFile);
			REL::Relocation<func_t> func{ REL::ID(1376557) };
			return func(this, a_index);
		}

		[[nodiscard]] static TESForm* GetFormByID(std::uint32_t a_formID)
		{
			const auto& [map, lock] = GetAllForms();
			BSAutoReadLock l{ lock };
			if (map) {
				const auto it = map->find(a_formID);
				return it != map->end() ? it->second : nullptr;
			} else {
				return nullptr;
			}
		}

		template <class T>
		[[nodiscard]] static T* GetFormByID(std::uint32_t a_formID)
		{
			const auto form = GetFormByID(a_formID);
			return form ? form->As<T>() : nullptr;
		}

		[[nodiscard]] static TESForm* GetFormByEditorID(const BSFixedString& a_editorID)
		{
			const auto& [map, lock] = GetAllFormsByEditorID();
			BSAutoReadLock l{ lock };
			if (map) {
				const auto it = map->find(a_editorID);
				return it != map->end() ? it->second : nullptr;
			} else {
				return nullptr;
			}
		}

		template <class T>
		[[nodiscard]] static T* GetFormByEditorID(const BSFixedString& a_editorID)
		{
			const auto form = GetFormByEditorID(a_editorID);
			return form ? form->As<T>() : nullptr;
		}

		[[nodiscard]] std::uint32_t GetFormFlags() const noexcept { return formFlags; }
		[[nodiscard]] std::uint32_t GetFormID() const noexcept { return formID; }
		[[nodiscard]] ENUM_FORM_ID GetFormType() const noexcept { return *formType; }
		[[nodiscard]] bool Is(ENUM_FORM_ID a_type) const noexcept { return GetFormType() == a_type; }

		template <class T>
		[[nodiscard]] bool Is() const noexcept  //
			requires(std::derived_from<T, TESForm> &&
					 !std::is_pointer_v<T> &&
					 !std::is_reference_v<T>)
		{
			return Is(T::FORM_ID);
		}

		[[nodiscard]] bool IsAlchemyItem() const noexcept { return Is(ENUM_FORM_ID::kALCH); }
		[[nodiscard]] bool IsCreated() const noexcept { return (formID >> (8 * 3)) == 0xFF; }
		[[nodiscard]] bool IsDeleted() noexcept { return (formFlags & (1u << 5)) != 0; }
		[[nodiscard]] bool IsInitialized() const noexcept { return (formFlags & (1u << 3)) != 0; }
		[[nodiscard]] bool IsPlayer() const noexcept { return GetFormID() == 0x00000007; }
		[[nodiscard]] bool IsPlayerRef() const noexcept { return GetFormID() == 0x00000014; }
		[[nodiscard]] bool IsWeapon() const noexcept { return Is(ENUM_FORM_ID::kWEAP); }

		void SetTemporary()
		{
			using func_t = decltype(&TESForm::SetTemporary);
			REL::Relocation<func_t> func{ REL::ID(482454) };
			return func(this);
		}

		template <
			class T,
			class = std::enable_if_t<
				std::negation_v<
					std::disjunction<
						std::is_pointer<T>,
						std::is_reference<T>,
						std::is_const<T>,
						std::is_volatile<T>>>>>
		[[nodiscard]] T* As() noexcept;

		template <
			class T,
			class = std::enable_if_t<
				std::negation_v<
					std::disjunction<
						std::is_pointer<T>,
						std::is_reference<T>,
						std::is_const<T>,
						std::is_volatile<T>>>>>
		[[nodiscard]] const T* As() const noexcept;

		// members
		TESFileContainer sourceFiles;                           // 08
		std::uint32_t formFlags;                                // 10
		std::uint32_t formID;                                   // 14
		std::uint16_t inGameFormFlags;                          // 18
		stl::enumeration<ENUM_FORM_ID, std::uint8_t> formType;  // 1A
	};
	static_assert(sizeof(TESForm) == 0x20);

	class __declspec(novtable) BGSKeyword :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSKeyword };
		static constexpr auto VTABLE{ VTABLE::BGSKeyword };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kKYWD };

		using KeywordType = RE::KeywordType;

		[[nodiscard]] static BGSKeyword* GetTypedKeywordByIndex(KeywordType a_type, std::uint16_t a_index)
		{
			assert(a_type < KeywordType::kTotal);
			const auto keywords = GetTypedKeywords();
			if (keywords) {
				const auto& arr = (*keywords)[stl::to_underlying(a_type)];
				return a_index < arr.size() ? arr[a_index] : nullptr;
			} else {
				return nullptr;
			}
		}

		[[nodiscard]] static auto GetTypedKeywords()
			-> std::optional<std::span<BSTArray<BGSKeyword*>, stl::to_underlying(KeywordType::kTotal)>>
		{
			REL::Relocation<BSTArray<BGSKeyword*>(*)[stl::to_underlying(KeywordType::kTotal)]> keywords{ REL::ID(1095775) };
			if (*keywords) {
				return { *keywords };
			} else {
				return std::nullopt;
			}
		}

		// members
		BSFixedString formEditorID;  // 20
	};
	static_assert(sizeof(BGSKeyword) == 0x28);

	class __declspec(novtable) BGSLocationRefType :
		public BGSKeyword  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSLocationRefType };
		static constexpr auto VTABLE{ VTABLE::BGSLocationRefType };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLCRT };
	};
	static_assert(sizeof(BGSLocationRefType) == 0x28);

	class __declspec(novtable) BGSAction :
		public BGSKeyword  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSAction };
		static constexpr auto VTABLE{ VTABLE::BGSAction };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kAACT };

		// members
		std::uint32_t index;  // 28
	};
	static_assert(sizeof(BGSAction) == 0x30);

	class __declspec(novtable) BGSTransform :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSTransform };
		static constexpr auto VTABLE{ VTABLE::BGSTransform };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kTRNS };

		struct TransformData
		{
		public:
			// members
			NiPoint3 position;  // 00
			NiPoint3 rotation;  // 0C
			float scale;        // 18
			float minZoom;      // 1C
			float maxZoom;      // 20
		};
		static_assert(sizeof(TransformData) == 0x24);

		// members
		TransformData data;  // 20
	};
	static_assert(sizeof(BGSTransform) == 0x48);

	class __declspec(novtable) BGSMenuIcon :
		public TESForm,  // 00
		public TESIcon   // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSMenuIcon };
		static constexpr auto VTABLE{ VTABLE::BGSMenuIcon };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kMICN };
	};
	static_assert(sizeof(BGSMenuIcon) == 0x30);

	class __declspec(novtable) TESGlobal :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESGlobal };
		static constexpr auto VTABLE{ VTABLE::TESGlobal };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kGLOB };

		[[nodiscard]] float GetValue() const noexcept { return value; }

		// members
		BSStringT<char> formEditorID;  // 20
		float value;                   // 30
	};
	static_assert(sizeof(TESGlobal) == 0x38);

	class __declspec(novtable) BGSDamageType :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSDamageType };
		static constexpr auto VTABLE{ VTABLE::BGSDamageType };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kDMGT };

		struct Data
		{
		public:
			// members
			ActorValueInfo* resistance;  // 00
			MagicItem* spell;            // 08
		};
		static_assert(sizeof(Data) == 0x10);

		// members
		Data data;  // 20
	};
	static_assert(sizeof(BGSDamageType) == 0x30);

	struct CLASS_DATA
	{
	public:
		// members
		std::int32_t serviceFlags;  // 0
		float bleedoutDefault;      // 4
	};
	static_assert(sizeof(CLASS_DATA) == 0x8);

	class __declspec(novtable) TESClass :
		public TESForm,          // 00
		public TESFullName,      // 20
		public TESDescription,   // 30
		public TESTexture,       // 48
		public BGSPropertySheet  // 58
	{
	public:
		static constexpr auto RTTI{ RTTI::TESClass };
		static constexpr auto VTABLE{ VTABLE::TESClass };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCLAS };

		// members
		CLASS_DATA data;  // 68
	};
	static_assert(sizeof(TESClass) == 0x70);

	class __declspec(novtable) TESEyes :
		public TESForm,      // 00
		public TESFullName,  // 20
		public TESTexture    // 30
	{
	public:
		static constexpr auto RTTI{ RTTI::TESEyes };
		static constexpr auto VTABLE{ VTABLE::TESEyes };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kEYES };

		// members
		std::int8_t flags;  // 40
	};
	static_assert(sizeof(TESEyes) == 0x48);

	class __declspec(novtable) EffectSetting :
		public TESForm,               // 000
		public TESFullName,           // 020
		public BGSMenuDisplayObject,  // 030
		public BGSKeywordForm         // 040
	{
	public:
		static constexpr auto RTTI{ RTTI::EffectSetting };
		static constexpr auto VTABLE{ VTABLE::EffectSetting };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kMGEF };

		using FilterValidationFunction_t = bool(EffectSetting*, void*);

		struct EffectSettingData
		{
		public:
			// members
			std::uint32_t flags;                                                      // 000
			float baseCost;                                                           // 004
			TESForm* associatedForm;                                                  // 008
			ActorValueInfo* associatedSkill;                                          // 010
			ActorValueInfo* resistVariable;                                           // 018
			std::int16_t numCounterEffects;                                           // 020
			TESObjectLIGH* light;                                                     // 028
			float taperWeight;                                                        // 030
			TESEffectShader* effectShader;                                            // 038
			TESEffectShader* enchantEffect;                                           // 040
			std::int32_t minimumSkill;                                                // 048
			std::int32_t spellmakingArea;                                             // 04C
			float spellmakingChargeTime;                                              // 050
			float taperCurve;                                                         // 054
			float taperDuration;                                                      // 058
			float secondaryAVWeight;                                                  // 05C
			stl::enumeration<EffectArchetypes::ArchetypeID, std::int32_t> archetype;  // 060
			ActorValueInfo* primaryAV;                                                // 068
			BGSProjectile* projectileBase;                                            // 070
			BGSExplosion* explosion;                                                  // 078
			stl::enumeration<MagicSystem::CastingType, std::int32_t> castingType;     // 080
			stl::enumeration<MagicSystem::Delivery, std::int32_t> delivery;           // 084
			ActorValueInfo* secondaryAV;                                              // 088
			BGSArtObject* castingArt;                                                 // 090
			BGSArtObject* hitEffectArt;                                               // 098
			BGSImpactDataSet* impactDataSet;                                          // 0A0
			float skillUsageMult;                                                     // 0A8
			BGSDualCastData* dualCastData;                                            // 0B0
			float dualCastScale;                                                      // 0B8
			BGSArtObject* enchantEffectArt;                                           // 0C0
			BGSReferenceEffect* hitVisuals;                                           // 0C8
			BGSReferenceEffect* enchantVisuals;                                       // 0D0
			SpellItem* equipAbility;                                                  // 0D8
			TESImageSpaceModifier* imageSpaceMod;                                     // 0E0
			BGSPerk* perk;                                                            // 0E8
			stl::enumeration<SOUND_LEVEL, std::int32_t> castingSoundLevel;            // 0F0
			float aiScore;                                                            // 0F4
			float aiDelayTime;                                                        // 0F8
		};
		static_assert(sizeof(EffectSettingData) == 0x100);

		struct SoundPair
		{
		public:
			// members
			stl::enumeration<MagicSystem::SoundID, std::int32_t> id;  // 00
			BGSSoundDescriptorForm* sound;                            // 08
		};
		static_assert(sizeof(SoundPair) == 0x10);

		// members
		FilterValidationFunction_t* filterValidationFunction;  // 060
		void* filterValidationItem;                            // 068
		EffectSettingData data;                                // 070
		BSSimpleList<EffectSetting*> counterEffects;           // 170
		BSTArray<EffectSetting::SoundPair> effectSounds;       // 180
		BGSLocalizedString magicItemDescription;               // 198
		std::int32_t effectLoadedCount;                        // 1A0
		std::int32_t associatedItemLoadedCount;                // 1A4
		TESCondition conditions;                               // 1A8
	};
	static_assert(sizeof(EffectSetting) == 0x1B0);

	struct TEXTURE_HAVOK_DATA
	{
	public:
		// members
		std::int8_t friction;     // 0
		std::int8_t restitution;  // 1
	};
	static_assert(sizeof(TEXTURE_HAVOK_DATA) == 0x2);

	class __declspec(novtable) TESLandTexture :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESLandTexture };
		static constexpr auto VTABLE{ VTABLE::TESLandTexture };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLTEX };

		// members
		BGSTextureSet* textureSet;                 // 20
		TEXTURE_HAVOK_DATA havokData;              // 28
		BGSMaterialType* materialType;             // 30
		std::int8_t specularExponent;              // 38
		std::int32_t shaderTextureIndex;           // 3C
		BSSimpleList<TESGrass*> textureGrassList;  // 40
	};
	static_assert(sizeof(TESLandTexture) == 0x50);

	class __declspec(novtable) TESWeather :
		public TESForm  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::TESWeather };
		static constexpr auto VTABLE{ VTABLE::TESWeather };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kWTHR };

		enum class SpellContext
		{
			kApplyOnLightning,
			kApplyWhenActive
		};

		enum class SoundType
		{
			kDefault,
			kPrecipitation,
			kWind,
			kThunder
		};

		struct SpellData
		{
		public:
			// members
			MagicItem* spell;  // 00
			float threshold;   // 08
		};
		static_assert(sizeof(SpellData) == 0x10);

		struct WeatherSound
		{
		public:
			// members
			BGSSoundDescriptorForm* soundForm;               // 00
			stl::enumeration<SoundType, std::int32_t> type;  // 08
		};
		static_assert(sizeof(WeatherSound) == 0x10);

		struct WeatherSoundList :
			public BSSimpleList<WeatherSound*>
		{
		public:
		};
		static_assert(sizeof(WeatherSoundList) == 0x10);

		// members
		stl::enumeration<SpellContext, std::int32_t> context;                     // 020
		TESTexture1024 cloudTexture[32];                                          // 028
		std::int8_t cloudLayerSpeedY[32];                                         // 228
		std::int8_t cloudLayerSpeedX[32];                                         // 248
		std::uint32_t cloudColorData[32][8];                                      // 268
		float cloudAlpha[32][8];                                                  // 668
		std::uint32_t cloudLayerDisabledBits;                                     // A68
		std::int8_t weatherData[20];                                              // A6C
		float fogData[18];                                                        // A80
		std::uint32_t colorData[19][8];                                           // AC8
		float fogColorScales[4][8];                                               // D28
		SpellData weatherSpellData[2];                                            // DA8
		WeatherSoundList soundList;                                               // DC8
		BSTArray<TESObjectSTAT*> skyStatics;                                      // DD8
		std::uint32_t numCloudLayers;                                             // DF0
		TESImageSpace* imageSpace[8];                                             // DF8
		BGSGodRays* godRays[8];                                                   // E38
		BGSDirectionalAmbientLightingColors directionalAmbientLightingColors[8];  // E78
		TESModel aurora;                                                          // F78
		BGSLensFlare* sunGlareLensFlare;                                          // FA8
		float volatilityMult;                                                     // FB0
		float isibilityMult;                                                      // FB4
		BGSShaderParticleGeometryData* precipitationData;                         // FB8
		BGSReferenceEffect* referenceEffect;                                      // FC0
	};
	static_assert(sizeof(TESWeather) == 0xFC8);

	struct WeatherEntry
	{
	public:
		// members
		TESWeather* weather;   // 00
		std::uint32_t chance;  // 08
		TESGlobal* chanceVar;  // 10
	};
	static_assert(sizeof(WeatherEntry) == 0x18);

	class TESWeatherList :
		BSSimpleList<WeatherEntry*>
	{
	public:
	};
	static_assert(sizeof(TESWeatherList) == 0x10);

	class __declspec(novtable) TESClimate :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESClimate };
		static constexpr auto VTABLE{ VTABLE::TESClimate };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCLMT };

		// members
		TESModel nightSky;           // 20
		TESWeatherList weatherList;  // 50
		TESTexture skyObjects[2];    // 60
		std::int8_t data[6];         // 80
	};
	static_assert(sizeof(TESClimate) == 0x88);

	class __declspec(novtable) BGSShaderParticleGeometryData :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSShaderParticleGeometryData };
		static constexpr auto VTABLE{ VTABLE::BGSShaderParticleGeometryData };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSPGD };

		// members
		BSTArray<SETTING_VALUE> data;  // 20
		TESTexture particleTexture;    // 38
		BSFixedString materialName;    // 48
	};
	static_assert(sizeof(BGSShaderParticleGeometryData) == 0x50);

	class __declspec(novtable) BGSReferenceEffect :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSReferenceEffect };
		static constexpr auto VTABLE{ VTABLE::BGSReferenceEffect };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kRFCT };

		struct Data
		{
		public:
			// members
			BGSArtObject* artObject;        // 00
			TESEffectShader* effectShader;  // 08
			std::uint32_t flags;            // 10
		};
		static_assert(sizeof(Data) == 0x18);

		// members
		Data data;  // 20
	};
	static_assert(sizeof(BGSReferenceEffect) == 0x38);

	class __declspec(novtable) TESRegion :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESRegion };
		static constexpr auto VTABLE{ VTABLE::TESRegion };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kREGN };

		// add
		virtual bool Validate();  // 49

		// members
		TESRegionDataList* dataList;                    // 20
		BSSimpleList<TESRegionPointList*>* pointLists;  // 28
		TESWorldSpace* worldSpace;                      // 30
		TESWeather* currentWeather;                     // 38
		NiColor emittanceColor;                         // 40
		float lodDistanceModifier;                      // 4C
		float occlusionAccuracy;                        // 50
	};
	static_assert(sizeof(TESRegion) == 0x58);

	struct LOADED_CELL_DATA
	{
	public:
		struct AnimatedRefObject
		{
		public:
			// members
			ObjectRefHandle handle;      // 0
			std::int32_t numSkipFrames;  // 4
		};
		static_assert(sizeof(AnimatedRefObject) == 0x8);

		// members
		BSTHashMap<ObjectRefHandle, TESForm*> emittanceSourceRefMap;                // 000
		BSTHashMap<ObjectRefHandle, NiNode*> emittanceLightRefMap;                  // 030
		BSTHashMap<ObjectRefHandle, NiPointer<BSMultiBoundNode>> multiboundRefMap;  // 060
		BSTHashMap<BSMultiBoundNode*, ObjectRefHandle> refMultiboundMap;            // 090
		BSTArray<NiPointer<NiNode>> preCombined;                                    // 0C0
		BSTArray<NiPointer<NiNode>> attachedTransitionCells;                        // 0D8
		BSTArray<AnimatedRefObject> animatedRefs;                                   // 0F0
		BSTArray<ObjectRefHandle> flickeringLights;                                 // 108
		BSTArray<ObjectRefHandle> movingRefs;                                       // 120
		BSTArray<ObjectRefHandle> decalRefs;                                        // 138
		BSTArray<ObjectRefHandle> skyActors;                                        // 150
		BSTArray<ObjectRefHandle> flightAvoidAreas;                                 // 168
		BSReadWriteLock waterLock;                                                  // 180
		void* combinedGeometry;                                                     // 188 - TODO
		NiPointer<QueuedFile> combinedGeometryTask;                                 // 190
		BSSimpleList<ObjectRefHandle> activatingRefs;                               // 198
		BSSimpleList<ObjectRefHandle> waterRefs;                                    // 1A8
		NiPointer<BSPortalGraph> portalGraph;                                       // 1B8
		NiPointer<NiNode> cell3D;                                                   // 1C0
		NiPointer<NiNode> lightMarkerNode;                                          // 1C8
		NiPointer<NiNode> soundMarkerNode;                                          // 1D0
		NiPointer<NiNode> multiBoundNode;                                           // 1D8
		NiPointer<NiNode> combinedObjects;                                          // 1E0
		NiPointer<NiNode> combinedStaticCollision;                                  // 1E8
		BGSEncounterZone* encounterZone;                                            // 1F0
		std::size_t visibleDistantFadeInTime;                                       // 1F8
		std::int32_t criticalQueuedRefCount;                                        // 200
		std::int32_t queuedRefCount;                                                // 204
		std::int32_t queuedDistantRefCount;                                         // 208
		std::uint32_t refsAttachedDelay;                                            // 20C
		BSTAtomicValue<std::uint32_t> combinedObjectsAttached;                      // 210
		bool decalsQueued;                                                          // 214
		bool refsFullyLoaded;                                                       // 215
		bool combinedObjectsRegistered;                                             // 216
		bool grassIsShown;                                                          // 217
	};
	static_assert(sizeof(LOADED_CELL_DATA) == 0x218);

	class __declspec(novtable) TESObjectCELL :
		public TESForm,     // 00
		public TESFullName  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectCELL };
		static constexpr auto VTABLE{ VTABLE::TESObjectCELL };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCELL };

		enum class CELL_STATE
		{
			kNotLoaded,
			kUnloading,
			kLoadingData,
			kLoading,
			kLoaded,
			kDetaching,
			kAttachQueued,
			kAttaching,
			kAttached
		};

		enum class Flag
		{
			kInterior = 1u << 0,
			kHasWater = 1u << 1
		};

		[[nodiscard]] BGSEncounterZone* GetEncounterZone() const
		{
			using func_t = decltype(&TESObjectCELL::GetEncounterZone);
			REL::Relocation<func_t> func{ REL::ID(1414637) };
			return func(this);
		}

		[[nodiscard]] TESWaterForm* GetWaterType() const noexcept;
		[[nodiscard]] bool HasWater() const noexcept { return cellFlags.all(Flag::kHasWater); }
		[[nodiscard]] bool IsExterior() const noexcept { return !IsInterior(); }
		[[nodiscard]] bool IsInterior() const noexcept { return cellFlags.all(Flag::kInterior); }

		// members
		BSSpinLock grassCreateLock;                            // 30
		BSSpinLock grassTaskLock;                              // 38
		stl::enumeration<Flag, std::uint16_t> cellFlags;       // 40
		std::uint16_t cellGameFlags;                           // 42
		stl::enumeration<CELL_STATE, std::uint8_t> cellState;  // 44
		bool autoWaterLoaded;                                  // 45
		bool cellDetached;                                     // 46
		BSTSmartPointer<ExtraDataList> extraList;              // 48
		union
		{
			void* cellData;
			EXTERIOR_DATA* cellDataExterior;
			INTERIOR_DATA* cellDataInterior;
		};                                                                            // 50
		TESObjectLAND* cellLand;                                                      // 58
		float waterHeight;                                                            // 60
		NavMeshArray* navMeshes;                                                      // 68
		BSTArray<NiPointer<TESObjectREFR>> references;                                // 70
		BSTSmartPointer<BGSWaterCollisionManager::AutoWater> autoWater;               // 77
		BSTSet<BSTSmartPointer<BGSWaterCollisionManager::BGSWaterUpdateI>> waterSet;  // 80
		BSSpinLock spinLock;                                                          // C0
		union
		{
			TESWorldSpace* worldSpace;
			std::uint32_t tempDataOffset;
		};                                      // C8
		LOADED_CELL_DATA* loadedData;           // D0
		BGSLightingTemplate* lightingTemplate;  // D8
		void* visibilityData;                   // E0 - TODO
		std::uint32_t rootVisibilityCellID;     // E8
		std::uint16_t visCalcDate;              // EC
		std::uint16_t preCombineDate;           // F0
	};
	static_assert(sizeof(TESObjectCELL) == 0xF0);

	struct OBJ_LAND
	{
	public:
		enum class LAND
		{
			kHeightAltered = 1 << 0,
			kCLRAltered = 1 << 1,
			kTexAltered = 1 << 2,
			kLoaded = 1 << 3,
			kGoodNormals = 1 << 4,
			kHiResHeightfield = 1 << 5,

			kRemapped = 1 << 10,

			kDataAltered = kHeightAltered | kCLRAltered | kTexAltered | kHiResHeightfield,
		};

		// members
		stl::enumeration<LAND, std::uint32_t> flags;  // 0
	};
	static_assert(sizeof(OBJ_LAND) == 0x4);

	class __declspec(novtable) TESObjectLAND :
		public TESForm,      // 00
		public TESChildCell  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectLAND };
		static constexpr auto VTABLE{ VTABLE::TESObjectLAND };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLAND };

		struct LoadedLandData;

		// members
		OBJ_LAND data;                         // 28
		TESObjectCELL* parentCell;             // 30
		NiPointer<QueuedFile> queuedTextures;  // 38
		LoadedLandData* loadedData;            // 40
	};
	static_assert(sizeof(TESObjectLAND) == 0x48);

	struct DIALOGUE_DATA
	{
	public:
		// members
		std::int8_t flags;      // 0
		std::int8_t type;       // 1
		std::uint16_t subtype;  // 2
	};
	static_assert(sizeof(DIALOGUE_DATA) == 0x4);

	class __declspec(novtable) TESTopic :
		public TESForm,     // 00
		public TESFullName  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::TESTopic };
		static constexpr auto VTABLE{ VTABLE::TESTopic };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kDIAL };

		struct InfoTree;

		// members
		DIALOGUE_DATA data;                     // 30
		std::uint32_t priorityAndJournalIndex;  // 34
		BGSDialogueBranch* ownerBranch;         // 38
		TESQuest* ownerQuest;                   // 40
		BGSKeyword* subtypeKeyword;             // 48
		TESTopicInfo** topicInfos;              // 50
		InfoTree* infoTree;                     // 58
		std::uint32_t numTopicInfos;            // 60
		std::uint32_t topicInfoAllocSize;       // 64
		std::uint32_t firstFileOffset;          // 68
		BSFixedString formEditorID;             // 70
	};
	static_assert(sizeof(TESTopic) == 0x78);

	struct TOPIC_INFO_DATA
	{
	public:
		// members
		std::uint16_t flags;           // 0
		std::uint16_t timeUntilReset;  // 2
	};
	static_assert(sizeof(TOPIC_INFO_DATA) == 0x4);

	class ResponseListWrapper
	{
	public:
		// members
		TESResponse* head;  // 0
	};
	static_assert(sizeof(ResponseListWrapper) == 0x8);

	class __declspec(novtable) TESTopicInfo :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESTopicInfo };
		static constexpr auto VTABLE{ VTABLE::TESTopicInfo };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kINFO };

		// members
		TESTopic* parentTopic;          // 20
		TESGlobal* resetGlobal;         // 28
		TESTopicInfo* dataInfo;         // 30
		TESCondition objConditions;     // 38
		std::uint16_t infoIndex;        // 40
		std::int8_t subtitlePriority;   // 42
		bool saidOnce;                  // 43
		TOPIC_INFO_DATA data;           // 44
		ResponseListWrapper responses;  // 48
	};
	static_assert(sizeof(TESTopicInfo) == 0x50);

	struct IDLE_DATA
	{
	public:
		// members
		std::int8_t loopMin;        // 0
		std::int8_t loopMax;        // 1
		std::int8_t flags;          // 2
		std::uint16_t replayDelay;  // 4
	};
	static_assert(sizeof(IDLE_DATA) == 0x6);

	class __declspec(novtable) TESIdleForm :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESIdleForm };
		static constexpr auto VTABLE{ VTABLE::TESIdleForm };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kIDLE };

		// members
		TESCondition conditions;          // 20
		IDLE_DATA data;                   // 28
		NiFormArray* childIdles;          // 30
		TESIdleForm* parentIdle;          // 38
		TESIdleForm* prevIdle;            // 40
		BSFixedString behaviorGraphName;  // 48
		BSFixedString animEventName;      // 50
		BSFixedString animFileName;       // 58
		BSStringT<char> formEditorID;     // 60
	};
	static_assert(sizeof(TESIdleForm) == 0x70);

	class __declspec(novtable) TESLoadScreen :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESLoadScreen };
		static constexpr auto VTABLE{ VTABLE::TESLoadScreen };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLSCR };

		struct LoadNIFData;

		// members
		TESCondition conditions;         // 20
		LoadNIFData* loadNIFData;        // 28
		BGSLocalizedString loadingText;  // 30
	};
	static_assert(sizeof(TESLoadScreen) == 0x38);

	class __declspec(novtable) TESObjectANIO :
		public TESForm,              // 00
		public BGSModelMaterialSwap  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectANIO };
		static constexpr auto VTABLE{ VTABLE::TESObjectANIO };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kANIO };

		// members
		BSFixedString formEditorID;     // 60
		BSFixedString unloadEventName;  // 68
	};
	static_assert(sizeof(TESObjectANIO) == 0x70);

	struct EffectShaderData
	{
	public:
		// members
		stl::enumeration<_D3DBLEND, std::int32_t> textureBlendModeSource;   // 00
		stl::enumeration<_D3DBLENDOP, std::int32_t> textureBlendOperation;  // 04
		stl::enumeration<_D3DCMPFUNC, std::int32_t> textureZTestFunction;   // 08
		std::uint32_t fillColor1;                                           // 0C
		float fillAlphaFadeInTime;                                          // 10
		float fillAlphaFullTime;                                            // 14
		float fillAlphaFadeOutTime;                                         // 18
		float fillAlphaPersistentPercent;                                   // 1C
		float fillAlphaPulseAmplitude;                                      // 20
		float fillAlphaPulseFrequency;                                      // 24
		float fillTextureUAnimSpeed;                                        // 28
		float fillTextureVAnimSpeed;                                        // 2C
		float edgeExponentValue;                                            // 30
		std::uint32_t edgeColor;                                            // 34
		float edgeAlphaFadeInTime;                                          // 38
		float edgeAlphaFullTime;                                            // 3C
		float edgeAlphaFadeOutTime;                                         // 40
		float edgeAlphaPersistentPercent;                                   // 44
		float edgeAlphaPulseAmplitude;                                      // 48
		float edgeAlphaPulseFrequency;                                      // 4C
		float fillAlphaFullPercent;                                         // 50
		float edgeAlphaFullPercent;                                         // 54
		stl::enumeration<_D3DBLEND, std::int32_t> textureBlendModeDest;     // 58
		float alphaTestStartTime;                                           // 5C
		float alphaTestEndTime;                                             // 60
		float alphaTestStartValue;                                          // 64
		float alphaTestEndValue;                                            // 68
		BGSSoundDescriptorForm* ambientSound;                               // 70
		std::uint32_t fillColor2;                                           // 78
		std::uint32_t fillColor3;                                           // 7C
		float fillColorScaleA[3];                                           // 80
		float fillColorTimeA[3];                                            // 8C
		std::uint32_t flags;                                                // 98
		float fillTextureUScale;                                            // 9C
		float fillTextureVScale;                                            // A0
		std::int8_t boneDepth;                                              // A4
	};
	static_assert(sizeof(EffectShaderData) == 0xA8);

	class __declspec(novtable) TESEffectShader :
		public TESForm,  // 000
		public TESModel  // 020
	{
	public:
		static constexpr auto RTTI{ RTTI::TESEffectShader };
		static constexpr auto VTABLE{ VTABLE::TESEffectShader };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kEFSH };

		// members
		EffectShaderData data;                    // 050
		TESTexture textureShaderTexture;          // 0F8
		TESTexture blockOutTexture;               // 108
		TESTexture paletteTexture;                // 118
		NiPointer<BSGeometry> shareableGeometry;  // 128
	};
	static_assert(sizeof(TESEffectShader) == 0x130);

	class __declspec(novtable) BGSDebris :
		public TESForm,        // 00
		public BGSPreloadable  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSDebris };
		static constexpr auto VTABLE{ VTABLE::BGSDebris };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kDEBR };

		// members
		BSSimpleList<BGSDebrisData*> dataList;  // 28
	};
	static_assert(sizeof(BGSDebris) == 0x38);

	struct ImageSpaceBaseData
	{
	public:
		// members
		float hdrData[9];        // 00
		float cinematicData[3];  // 24
		float tintData[4];       // 30
		float dofData[6];        // 40
	};
	static_assert(sizeof(ImageSpaceBaseData) == 0x58);

	class __declspec(novtable) TESImageSpace :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESImageSpace };
		static constexpr auto VTABLE{ VTABLE::TESImageSpace };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kIMGS };

		// members
		ImageSpaceBaseData data;            // 20
		TESTexture lutTexture;              // 78
		NiPointer<NiTexture> niLutTexture;  // 88
	};
	static_assert(sizeof(TESImageSpace) == 0x90);

	class __declspec(novtable) TESImageSpaceModifier :
		public TESForm  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::TESImageSpaceModifier };
		static constexpr auto VTABLE{ VTABLE::TESImageSpaceModifier };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kIMAD };

		struct ImageSpaceModifierData
		{
		public:
			// members
			bool animatable;                                    // 00
			float duration;                                     // 04
			std::uint32_t keySize[21][2];                       // 08
			std::uint32_t tintColorKeySize;                     // B0
			std::uint32_t blurKeySize;                          // B4
			std::uint32_t doubleKeySize;                        // B8
			std::uint32_t radialBlurStrengthKeySize;            // BC
			std::uint32_t radialBlurRampupKeySize;              // C0
			std::uint32_t radialBlurStartKeySize;               // C4
			bool useTargetForRadialBlur;                        // C8
			NiPoint2 radialBlurCenter;                          // CC
			std::uint32_t depthOfFieldStrengthKeySize;          // D4
			std::uint32_t depthOfFieldDistanceKeySize;          // D8
			std::uint32_t depthOfFieldRangeKeySize;             // DC
			bool useTargetForDepthOfField;                      // E0
			std::int8_t depthOfFieldMode;                       // E1
			std::uint32_t radialBlurRampDownKeySize;            // E4
			std::uint32_t radialBlurDownStartKeySize;           // E8
			std::uint32_t fadeColorKeySize;                     // EC
			std::uint32_t motionBlurStrengthKeySize;            // F0
			std::uint32_t depthOfFieldVignetteRadiusKeySize;    // F4
			std::uint32_t depthOfFieldVignetteStrengthKeySize;  // F8
		};
		static_assert(sizeof(ImageSpaceModifierData) == 0xFC);

		// members
		ImageSpaceModifierData data;                                              // 020
		NiPointer<NiFloatInterpolator> interpolator[21][2];                       // 120
		NiPointer<NiFloatInterpolator> blurInterpolator;                          // 270
		NiPointer<NiFloatInterpolator> doubleInterpolator;                        // 278
		NiPointer<NiColorInterpolator> tintColorInterpolator;                     // 280
		NiPointer<NiColorInterpolator> fadeColorInterpolator;                     // 288
		NiPointer<NiFloatInterpolator> radialBlurStrengthInterpolator;            // 290
		NiPointer<NiFloatInterpolator> radialBlurRampupInterpolator;              // 298
		NiPointer<NiFloatInterpolator> radialBlurStartInterpolator;               // 2A0
		NiPointer<NiFloatInterpolator> radialBlurRampDownInterpolator;            // 2A8
		NiPointer<NiFloatInterpolator> radialBlurDownStartInterpolator;           // 2B0
		NiPointer<NiFloatInterpolator> depthOfFieldStrengthInterpolator;          // 2B8
		NiPointer<NiFloatInterpolator> depthOfFieldDistanceInterpolator;          // 2C0
		NiPointer<NiFloatInterpolator> depthOfFieldRangeInterpolator;             // 2C8
		NiPointer<NiFloatInterpolator> depthOfFieldVignetteRadiusInterpolator;    // 2D0
		NiPointer<NiFloatInterpolator> depthOfFieldVignetteStrengthInterpolator;  // 2D8
		NiPointer<NiFloatInterpolator> motionBlurStrengthInterpolator;            // 2E0
		BSStringT<char> formEditorID;                                             // 2E8
	};
	static_assert(sizeof(TESImageSpaceModifier) == 0x2F8);

	class __declspec(novtable) BGSListForm :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSListForm };
		static constexpr auto VTABLE{ VTABLE::BGSListForm };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kFLST };

		[[nodiscard]] std::optional<std::uint32_t> GetItemIndex(const TESForm& a_item) const noexcept
		{
			if (scriptAddedTempForms) {
				const auto it = std::find(
					scriptAddedTempForms->begin(),
					scriptAddedTempForms->end(),
					a_item.formID);
				if (it != scriptAddedTempForms->end()) {
					return static_cast<std::uint32_t>(it - scriptAddedTempForms->begin());
				}
			}

			const auto it = std::find(
				arrayOfForms.begin(),
				arrayOfForms.end(),
				&a_item);
			if (it != arrayOfForms.end()) {
				const auto base = scriptAddedTempForms ? scriptAddedTempForms->size() : 0;
				return base + static_cast<std::uint32_t>(it - arrayOfForms.begin());
			}

			return std::nullopt;
		}

		// members
		BSTArray<TESForm*> arrayOfForms;                // 20
		BSTArray<std::uint32_t>* scriptAddedTempForms;  // 38
		std::uint32_t scriptAddedFormCount;             // 40
	};
	static_assert(sizeof(BGSListForm) == 0x48);

	struct PerkData
	{
	public:
		// members
		bool trait;            // 0
		std::int8_t level;     // 1
		std::int8_t numRanks;  // 2
		bool playable;         // 3
		bool hidden;           // 4
	};
	static_assert(sizeof(PerkData) == 0x5);

	class __declspec(novtable) BGSPerk :
		public TESForm,         // 00
		public TESFullName,     // 20
		public TESDescription,  // 30
		public TESIcon          // 48
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSPerk };
		static constexpr auto VTABLE{ VTABLE::BGSPerk };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kPERK };

		// members
		PerkData data;                        // 58
		TESCondition perkConditions;          // 60
		BSTArray<BGSPerkEntry*> perkEntries;  // 68
		BGSPerk* nextPerk;                    // 80
		BGSSoundDescriptorForm* sound;        // 88
		BSFixedStringCS swfFile;              // 90
	};
	static_assert(sizeof(BGSPerk) == 0x98);

	class __declspec(novtable) BGSBodyPartData :
		public TESForm,        // 000
		public TESModel,       // 020
		public BGSPreloadable  // 050
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSBodyPartData };
		static constexpr auto VTABLE{ VTABLE::BGSBodyPartData };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kBPTD };

		// members
		BGSBodyPart* partArray[26];                               // 058
		BGSBodyPartDefs::HitReactionData defaultHitReactionData;  // 128
	};
	static_assert(sizeof(BGSBodyPartData) == 0x150);

	class __declspec(novtable) BGSCameraShot :
		public TESForm,                     // 00
		public TESModel,                    // 20
		public TESImageSpaceModifiableForm  // 50
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSCameraShot };
		static constexpr auto VTABLE{ VTABLE::BGSCameraShot };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCAMS };

		enum class CAM_ACTION;
		enum class CAM_OBJECT;

		struct CAMERA_SHOT_DATA
		{
		public:
			// members
			stl::enumeration<CAM_ACTION, std::int32_t> cameraAction;  // 00
			stl::enumeration<CAM_OBJECT, std::int32_t> location;      // 04
			stl::enumeration<CAM_OBJECT, std::int32_t> target;        // 08
			std::uint32_t flags;                                      // 0C
			float playerTimeMult;                                     // 10
			float targetTimeMult;                                     // 14
			float globalTimeMult;                                     // 18
			float maxTime;                                            // 1C
			float minTime;                                            // 20
			float targetPercentBetweenActors;                         // 24
			float nearTargetDistance;                                 // 28
			float locationSpring;                                     // 2C
			float targetSpring;                                       // 30
			float rotationOffsetX;                                    // 34
			float rotationOffsetY;                                    // 38
			float rotationOffsetZ;                                    // 3C
		};
		static_assert(sizeof(CAMERA_SHOT_DATA) == 0x40);

		// members
		CAMERA_SHOT_DATA data;    // 60
		TESCondition conditions;  // A0
	};
	static_assert(sizeof(BGSCameraShot) == 0xA8);

	struct PATH_DATA
	{
	public:
		// members
		std::int8_t flags;  // 0
	};
	static_assert(sizeof(PATH_DATA) == 0x1);

	class __declspec(novtable) BGSCameraPath :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSCameraPath };
		static constexpr auto VTABLE{ VTABLE::BGSCameraPath };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCPTH };

		// members
		TESCondition conditions;             // 20
		BSSimpleList<BGSCameraShot*> shots;  // 28
		PATH_DATA data;                      // 38
		NiFormArray* childPaths;             // 40
		BGSCameraPath* parentPath;           // 48
		BGSCameraPath* prevPath;             // 50
	};
	static_assert(sizeof(BGSCameraPath) == 0x58);

	struct VOICE_TYPE_DATA
	{
	public:
		// members
		std::int8_t flags;
	};
	static_assert(sizeof(VOICE_TYPE_DATA) == 0x1);

	class __declspec(novtable) BGSVoiceType :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSVoiceType };
		static constexpr auto VTABLE{ VTABLE::BGSVoiceType };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kVTYP };

		// members
		VOICE_TYPE_DATA data;          // 20
		BSStringT<char> formEditorID;  // 28
	};
	static_assert(sizeof(BGSVoiceType) == 0x38);

	class __declspec(novtable) BGSMaterialType :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSMaterialType };
		static constexpr auto VTABLE{ VTABLE::BGSMaterialType };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kMATT };

		// members
		TESModel breakableFXModel;             // 20
		BGSMaterialType* parentType;           // 50
		BGSImpactDataSet* havokImpactDataSet;  // 58
		BSFixedString materialName;            // 60
		std::uint32_t materialID;              // 68
		NiColor materialColor;                 // 6C
		float buoyancy;                        // 78
		std::uint32_t flags;                   // 7C
	};
	static_assert(sizeof(BGSMaterialType) == 0x80);

	struct DECAL_DATA_DATA
	{
	public:
		// members
		float decalMinWidth;         // 00
		float decalMaxWidth;         // 04
		float decalMinHeight;        // 08
		float decalMaxHeight;        // 0C
		float depth;                 // 10
		float shininess;             // 14
		float parallaxScale;         // 18
		std::int8_t parallaxPasses;  // 1C
		std::int8_t flags;           // 1D
		std::uint32_t color;         // 20
	};
	static_assert(sizeof(DECAL_DATA_DATA) == 0x24);

	class DecalData
	{
	public:
		// members
		DECAL_DATA_DATA data;  // 00
	};
	static_assert(sizeof(DecalData) == 0x24);

	class __declspec(novtable) BGSImpactData :
		public TESForm,  // 00
		public TESModel  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSImpactData };
		static constexpr auto VTABLE{ VTABLE::BGSImpactData };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kIPCT };

		enum class ORIENTATION;

		struct IMPACT_DATA_DATA
		{
		public:
			// members
			float effectDuration;                                    // 00
			stl::enumeration<ORIENTATION, std::int32_t> orient;      // 04
			float angleThreshold;                                    // 08
			float placementRadius;                                   // 0C
			stl::enumeration<SOUND_LEVEL, std::int32_t> soundLevel;  // 10
			std::int8_t flags;                                       // 14
			std::int8_t resultOverride;                              // 15
		};
		static_assert(sizeof(IMPACT_DATA_DATA) == 0x18);

		// members
		IMPACT_DATA_DATA data;            // 50
		BGSTextureSet* decalTextureSet;   // 68
		BGSTextureSet* decalTextureSet2;  // 70
		BGSSoundDescriptorForm* sound1;   // 78
		BGSSoundDescriptorForm* sound2;   // 80
		BGSExplosion* explosion;          // 88
		BGSHazard* hazard;                // 90
		DecalData decalData;              // 98
		float maxFootstepParticleDist;    // BC
	};
	static_assert(sizeof(BGSImpactData) == 0xC0);

	class __declspec(novtable) BGSImpactDataSet :
		public TESForm,        // 00
		public BGSPreloadable  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSImpactDataSet };
		static constexpr auto VTABLE{ VTABLE::BGSImpactDataSet };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kIPDS };

		// members
		BSTHashMap<const BGSMaterialType*, BGSImpactData*> impactMap;  // 28
	};
	static_assert(sizeof(BGSImpactDataSet) == 0x58);

	struct ENCOUNTER_ZONE_GAME_DATA
	{
	public:
		// members
		std::uint32_t detachTime;  // 00
		std::uint32_t attachTime;  // 04
		std::uint32_t resetTime;   // 08
		std::uint16_t zoneLevel;   // 0C
	};
	static_assert(sizeof(ENCOUNTER_ZONE_GAME_DATA) == 0x10);

	struct ENCOUNTER_ZONE_DATA
	{
	public:
		enum class FLAG
		{
			kNeverReset = 1u << 0,
			kMatchPCBelowMin = 1u << 1,
			kDisableCombatBoundary = 1u << 2,
			kWorkshopZone = 1u << 3
		};

		// members
		TESForm* zoneOwner;                          // 00
		BGSLocation* location;                       // 08
		std::int8_t ownerRank;                       // 10
		std::int8_t minLevel;                        // 11
		stl::enumeration<FLAG, std::uint8_t> flags;  // 12
		std::int8_t maxLevel;                        // 13
	};
	static_assert(sizeof(ENCOUNTER_ZONE_DATA) == 0x18);

	class __declspec(novtable) BGSEncounterZone :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSEncounterZone };
		static constexpr auto VTABLE{ VTABLE::BGSEncounterZone };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kECZN };

		[[nodiscard]] bool NeverResets() const noexcept { return data.flags.all(ENCOUNTER_ZONE_DATA::FLAG::kNeverReset); }
		[[nodiscard]] bool IsWorkshop() const noexcept { return data.flags.all(ENCOUNTER_ZONE_DATA::FLAG::kWorkshopZone); }

		void SetDetachTime(std::uint32_t a_time)
		{
			gameData.detachTime = a_time;
			AddChange(CHANGE_TYPE::kEncounterZoneGameData);
		}

		// members
		ENCOUNTER_ZONE_DATA data;           // 20
		ENCOUNTER_ZONE_GAME_DATA gameData;  // 38
	};
	static_assert(sizeof(BGSEncounterZone) == 0x48);

	struct UnloadedRefData
	{
	public:
		// members
		std::uint32_t refID;          // 0
		std::uint32_t parentSpaceID;  // 4
		std::uint32_t cellKey;        // 8
	};
	static_assert(sizeof(UnloadedRefData) == 0xC);

	struct SpecialRefData
	{
	public:
		// members
		BGSLocationRefType* type;  // 00
		UnloadedRefData refData;   // 08
	};
	static_assert(sizeof(SpecialRefData) == 0x18);

	struct UniqueNPCData
	{
	public:
		// members
		TESNPC* npc;             // 00
		std::uint32_t refID;     // 08
		BGSLocation* editorLoc;  // 10
	};
	static_assert(sizeof(UniqueNPCData) == 0x18);

	class __declspec(novtable) BGSLocation :
		public TESForm,        // 000
		public TESFullName,    // 020
		public BGSKeywordForm  // 030
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSLocation };
		static constexpr auto VTABLE{ VTABLE::BGSLocation };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLCTN };

		struct KEYWORD_DATA
		{
		public:
			// members
			BGSKeyword* keyword;  // 00
			float data;           // 08
		};
		static_assert(sizeof(KEYWORD_DATA) == 0x10);

		// members
		BGSLocation* parentLoc;                                                 // 050
		TESFaction* unreportedCrimeFaction;                                     // 058
		BGSMusicType* musicType;                                                // 060
		BGSEncounterZone* zone;                                                 // 068
		ObjectRefHandle worldLocMarker;                                         // 070
		float worldLocRadius;                                                   // 074
		float actorFadeMult;                                                    // 078
		ObjectRefHandle horseLocMarker;                                         // 07C
		BSTArray<SpecialRefData> specialRefs;                                   // 080
		BSTArray<UniqueNPCData> uniqueNPCs;                                     // 098
		OverrideData* overrideData;                                             // 0B0
		BSTArray<std::uint32_t> newUnloadedRefs;                                // 0B8
		BSTArray<BSTTuple<BGSLocationRefType*, std::uint32_t>> newSpecialRefs;  // 0D0
		NiPointer<QueuedPromoteLocationReferencesTask> promoteRefsTask;         // 0E8
		BSTArray<ObjectRefHandle> promotedRefsArray;                            // 0F0
		volatile std::int32_t loadedCount;                                      // 108
		std::uint32_t fileOffset;                                               // 10C
		BSTArray<KEYWORD_DATA> keywordData;                                     // 110
		BSSpinLock locLoadedLock;                                               // 128
		std::uint32_t lastChecked;                                              // 130
		bool cleared;                                                           // 134
		bool everCleared;                                                       // 135
		BSReadWriteLock locker;                                                 // 138
	};
	static_assert(sizeof(BGSLocation) == 0x140);

	struct MESSAGEBOX_BUTTON
	{
	public:
		// members
		BGSLocalizedString text;  // 00
		TESCondition conditions;  // 08
	};
	static_assert(sizeof(MESSAGEBOX_BUTTON) == 0x10);

	class __declspec(novtable) BGSMessage :
		public TESForm,        // 00
		public TESFullName,    // 20
		public TESDescription  // 30
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSMessage };
		static constexpr auto VTABLE{ VTABLE::BGSMessage };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kMESG };

		// members
		BGSMenuIcon* icon;                            // 48
		TESQuest* ownerQuest;                         // 50
		BSSimpleList<MESSAGEBOX_BUTTON*> buttonList;  // 58
		BSFixedStringCS swfFile;                      // 68
		BGSLocalizedString shortName;                 // 70
		std::uint32_t flags;                          // 78
		std::uint32_t displayTime;                    // 7C
	};
	static_assert(sizeof(BGSMessage) == 0x80);

	class __declspec(novtable) BGSLightingTemplate :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSLightingTemplate };
		static constexpr auto VTABLE{ VTABLE::BGSLightingTemplate };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLGTM };

		// members
		INTERIOR_DATA data;                                                    // 20
		BGSGodRays* godRays;                                                   // B0
		BGSDirectionalAmbientLightingColors directionalAmbientLightingColors;  // B8
	};
	static_assert(sizeof(BGSLightingTemplate) == 0xD8);

	class __declspec(novtable) BGSMusicType :
		public TESForm,      // 00
		public BSIMusicType  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSMusicType };
		static constexpr auto VTABLE{ VTABLE::BGSMusicType };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kMUSC };

		// members
		BSFixedString formEditorID;  // 70
	};
	static_assert(sizeof(BGSMusicType) == 0x78);

	class __declspec(novtable) BGSFootstep :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSFootstep };
		static constexpr auto VTABLE{ VTABLE::BGSFootstep };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kFSTP };

		// members
		BSFixedString tagString;      // 20
		BGSImpactDataSet* impactSet;  // 28
	};
	static_assert(sizeof(BGSFootstep) == 0x30);

	class __declspec(novtable) BGSFootstepSet :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSFootstepSet };
		static constexpr auto VTABLE{ VTABLE::BGSFootstepSet };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kFSTS };

		// members
		BSTArray<BGSFootstep*> entries[5];  // 20
	};
	static_assert(sizeof(BGSFootstepSet) == 0x98);

	class __declspec(novtable) BGSDialogueBranch :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSDialogueBranch };
		static constexpr auto VTABLE{ VTABLE::BGSDialogueBranch };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kDLBR };

		// members
		std::uint32_t flags;                                 // 20
		TESQuest* quest;                                     // 28
		TESTopic* startingTopic;                             // 30
		stl::enumeration<DIALOGUE_TYPE, std::int32_t> type;  // 38
	};
	static_assert(sizeof(BGSDialogueBranch) == 0x40);

	class __declspec(novtable) BGSMusicTrackFormWrapper :
		public TESForm,       // 00
		public BSIMusicTrack  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSMusicTrackFormWrapper };
		static constexpr auto VTABLE{ VTABLE::BGSMusicTrackFormWrapper };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kMUST };

		// members
		BGSMusicTrack* trackImpl;  // 30
	};
	static_assert(sizeof(BGSMusicTrackFormWrapper) == 0x38);

	class __declspec(novtable) TESWordOfPower :
		public TESForm,     // 00
		public TESFullName  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::TESWordOfPower };
		static constexpr auto VTABLE{ VTABLE::TESWordOfPower };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kWOOP };

		// members
		BGSLocalizedString translation;  // 30
	};
	static_assert(sizeof(TESWordOfPower) == 0x38);

	class __declspec(novtable) TESShout :
		public TESForm,               // 00
		public TESFullName,           // 20
		public BGSMenuDisplayObject,  // 30
		public BGSEquipType,          // 40
		public TESDescription         // 50
	{
	public:
		static constexpr auto RTTI{ RTTI::TESShout };
		static constexpr auto VTABLE{ VTABLE::TESShout };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSHOU };

		struct Variation
		{
		public:
			// members
			TESWordOfPower* word;  // 00
			SpellItem* spell;      // 08
			float recoveryTime;    // 10
		};
		static_assert(sizeof(Variation) == 0x18);

		// members
		Variation variations[3];  // 68
	};
	static_assert(sizeof(TESShout) == 0xB0);

	class __declspec(novtable) BGSEquipSlot :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSEquipSlot };
		static constexpr auto VTABLE{ VTABLE::BGSEquipSlot };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kEQUP };

		// members
		BSTArray<BGSEquipSlot*> parentSlots;  // 20
		std::uint32_t flags;                  // 38
		ActorValueInfo* conditionActorValue;  // 40
	};
	static_assert(sizeof(BGSEquipSlot) == 0x48);

	class __declspec(novtable) BGSRelationship :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSRelationship };
		static constexpr auto VTABLE{ VTABLE::BGSRelationship };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kRELA };

		// members
		TESNPC* npc1;                   // 20
		TESNPC* npc2;                   // 28
		BGSAssociationType* assocType;  // 30
		std::uint32_t packedData;       // 38
	};
	static_assert(sizeof(BGSRelationship) == 0x40);

	struct BGSScenePhase
	{
	public:
		// members
		TESCondition startConditions;       // 00
		TESCondition completionConditions;  // 08
		std::uint16_t phaseFlags;           // 10
		bool active;                        // 12
		bool scriptEndRun;                  // 13
		bool runEnd;                        // 14
	};
	static_assert(sizeof(BGSScenePhase) == 0x18);

	class __declspec(novtable) BGSScene :
		public TESForm,          // 00
		public IKeywordFormBase  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSScene };
		static constexpr auto VTABLE{ VTABLE::BGSScene };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSCEN };

		// members
		NiTFlags<std::uint32_t, BGSScene> niFlags;      // 28
		BSTArray<BGSScenePhase*> phases;                // 30
		BSTArray<std::uint32_t> actors;                 // 48
		BSTArray<std::uint32_t> actorFlags;             // 60
		BSTArray<std::uint32_t> actorProgressionFlags;  // 78
		BSTArray<BGSSceneAction*> actions;              // 90
		TESQuest* parentQuest;                          // A8
		BGSScene* templateScene;                        // B0
		std::uint32_t flags;                            // B8
		TESCondition repeatConditions;                  // C0
		std::uint32_t speakerID;                        // C8
		std::uint32_t currentActivePhase;               // CC
		std::uint32_t startPhase;                       // D0
		float randomSceneTimer;                         // D4
		float maxREFDistanceCenter;                     // D8
		ObjectRefHandle targetRef;                      // DC
		bool shouldNotRotateToTrack;                    // E0
	};
	static_assert(sizeof(BGSScene) == 0xE8);

	class __declspec(novtable) BGSAssociationType :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSAssociationType };
		static constexpr auto VTABLE{ VTABLE::BGSAssociationType };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kASTP };

		// members
		BSFixedStringCS associationLabel[2][2];  // 20
		std::uint32_t flags;                     // 40
	};
	static_assert(sizeof(BGSAssociationType) == 0x48);

	class __declspec(novtable) BGSOutfit :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSOutfit };
		static constexpr auto VTABLE{ VTABLE::BGSOutfit };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kOTFT };

		// members
		BSTArray<TESForm*> outfitItems;  // 20
	};
	static_assert(sizeof(BGSOutfit) == 0x38);

	class __declspec(novtable) BGSMaterialObject :
		public TESForm,          // 00
		public TESModel,         // 20
		public BSMaterialObject  // 50
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSMaterialObject };
		static constexpr auto VTABLE{ VTABLE::BGSMaterialObject };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kMATO };

		struct FILE_DATA
		{
		public:
			// members
			std::int8_t* nuffer;       // 00
			std::uint32_t bufferSize;  // 08
		};
		static_assert(sizeof(FILE_DATA) == 0x10);

		// members
		BSTArray<FILE_DATA> fileData;  // A0
	};
	static_assert(sizeof(BGSMaterialObject) == 0xB8);

	class __declspec(novtable) BGSMovementType :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSMovementType };
		static constexpr auto VTABLE{ VTABLE::BGSMovementType };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kMOVT };

		// members
		Movement::TypeData movementTypeData;  // 20
	};
	static_assert(sizeof(BGSMovementType) == 0xA0);

	class __declspec(novtable) BGSSoundDescriptorForm :
		public TESForm,            // 00
		public BSISoundDescriptor  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSSoundDescriptorForm };
		static constexpr auto VTABLE{ VTABLE::BGSSoundDescriptorForm };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSNDR };

		// members
		BGSSoundDescriptor* impl;  // 28
	};
	static_assert(sizeof(BGSSoundDescriptorForm) == 0x30);

	class __declspec(novtable) BGSSoundCategory :
		public TESForm,          // 00
		public TESFullName,      // 20
		public BSISoundCategory  // 30
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSSoundCategory };
		static constexpr auto VTABLE{ VTABLE::BGSSoundCategory };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSNCT };

		// members
		BGSSoundCategory* parentCategory;  // 38
		BGSSoundCategory* sliderCategory;  // 40
		float volumeMult;                  // 48
		float snapshotMult;                // 4C
		float currCompressionMult;         // 50
		float fullyCompressedMult;         // 54
		float frequencyMult;               // 58
		float minFrequencyMult;            // 5C
		std::uint32_t appFlags;            // 60
		std::uint16_t attenuation[6];      // 64
		std::uint16_t stateFlags;          // 70
		std::uint16_t staticMult;          // 72
		std::uint16_t defaultMenuValue;    // 74
	};
	static_assert(sizeof(BGSSoundCategory) == 0x78);

	class __declspec(novtable) BGSSoundOutput :
		public TESForm,             // 00
		public BSISoundOutputModel  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSSoundOutput };
		static constexpr auto VTABLE{ VTABLE::BGSSoundOutput };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSOPM };

		enum class SPEAKER_OUTPUT_MODE;

		struct DynamicAttenuationCharacteristics;
		struct SpeakerArrays;

		// members
		DynamicAttenuationCharacteristics* attenuation;            // 28
		SpeakerArrays* speakerOutputArrays;                        // 30
		BGSAudioEffectChain* effectChain;                          // 38
		std::uint32_t flags;                                       // 40
		stl::enumeration<SPEAKER_OUTPUT_MODE, std::int32_t> mode;  // 44
		std::uint16_t staticAttenuation;                           // 48
	};
	static_assert(sizeof(BGSSoundOutput) == 0x50);

	class __declspec(novtable) BGSCollisionLayer :
		public TESForm,        // 00
		public TESDescription  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSCollisionLayer };
		static constexpr auto VTABLE{ VTABLE::BGSCollisionLayer };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCOLL };

		// members
		std::uint32_t collisionIdx;                 // 38
		std::uint32_t debugColor;                   // 3C
		std::uint32_t flags;                        // 40
		BSFixedString name;                         // 48
		BSTArray<BGSCollisionLayer*> collidesWith;  // 50
	};
	static_assert(sizeof(BGSCollisionLayer) == 0x68);

	class __declspec(novtable) BGSColorForm :
		public TESForm,     // 00
		public TESFullName  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSColorForm };
		static constexpr auto VTABLE{ VTABLE::BGSColorForm };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCLFM };

		// members
		union
		{
			std::uint32_t color;
			float remappingIndex;
		};                        // 30
		TESCondition conditions;  // 38
		std::uint32_t flags;      // 40
	};
	static_assert(sizeof(BGSColorForm) == 0x48);

	class __declspec(novtable) BGSReverbParameters :
		public TESForm,       // 00
		public BSIReverbType  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSReverbParameters };
		static constexpr auto VTABLE{ VTABLE::BGSReverbParameters };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kREVB };

		struct ReverbParams
		{
		public:
			// members
			std::uint16_t decayTime;      // 0
			std::uint16_t hfReference;    // 2
			std::int8_t roomFilter;       // 4
			std::int8_t roomHFFilter;     // 5
			std::int8_t reflections;      // 6
			std::int8_t reverb;           // 7
			std::int8_t decayHFRatio;     // 8
			std::int8_t reflectionDelay;  // 9
			std::int8_t reverbDelay;      // A
			std::int8_t diffusionPct;     // B
			std::int8_t densityPct;       // C
		};
		static_assert(sizeof(ReverbParams) == 0xE);

		// members
		ReverbParams data;          // 28
		std::uint32_t reverbClass;  // 38
	};
	static_assert(sizeof(BGSReverbParameters) == 0x40);

	class __declspec(novtable) BGSPackIn :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSPackIn };
		static constexpr auto VTABLE{ VTABLE::BGSPackIn };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kPKIN };
	};
	static_assert(sizeof(BGSPackIn) == 0x20);

	class __declspec(novtable) BGSAimModel :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSAimModel };
		static constexpr auto VTABLE{ VTABLE::BGSAimModel };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kAMDL };

		struct Data
		{
		public:
			// members
			float aimModelMinConeDegrees;                 // 00
			float aimModelMaxConeDegrees;                 // 04
			float aimModelConeIncreasePerShot;            // 08
			float aimModelConeDecreasePerSec;             // 0C
			std::uint32_t aimModelConeDecreaseDelayMs;    // 10
			float aimModelConeSneakMultiplier;            // 14
			float aimModelRecoilDiminishSpringForce;      // 18
			float aimModelRecoilDiminishSightsMult;       // 1C
			float aimModelRecoilMaxDegPerShot;            // 20
			float aimModelRecoilMinDegPerShot;            // 24
			float aimModelRecoilHipMult;                  // 28
			std::uint32_t aimModelRecoilShotsForRunaway;  // 2C
			float aimModelRecoilArcDeg;                   // 30
			float aimModelRecoilArcRotateDeg;             // 34
			float aimModelConeIronSightsMultiplier;       // 38
			float aimModelBaseStability;                  // 3C
		};
		static_assert(sizeof(Data) == 0x40);

		// members
		Data aimModelData;  // 20
	};
	static_assert(sizeof(BGSAimModel) == 0x60);

	class __declspec(novtable) BGSConstructibleObject :
		public TESForm,                 // 00
		public BGSPickupPutdownSounds,  // 20
		public TESDescription           // 38
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSConstructibleObject };
		static constexpr auto VTABLE{ VTABLE::BGSConstructibleObject };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCOBJ };

		struct ConstructibleObjectData
		{
		public:
			// members
			std::uint16_t numConstructed;    // 0
			std::uint16_t workshopPriority;  // 2
		};
		static_assert(sizeof(ConstructibleObjectData) == 0x4);

		[[nodiscard]] RE::TESForm* GetCreatedItem() const noexcept { return createdItem; }
		[[nodiscard]] std::uint16_t GetWorkshopPriority() const noexcept { return data.workshopPriority; }

		// members
		BSTArray<BSTTuple<TESForm*, BGSTypedFormValuePair::SharedVal>>* requiredItems;  // 50
		TESCondition conditions;                                                        // 58
		TESForm* createdItem;                                                           // 60
		BGSKeyword* benchKeyword;                                                       // 68
		BGSConstructibleObject::ConstructibleObjectData data;                           // 70
		BGSTypedKeywordValueArray<KeywordType::kRecipeFilter> filterKeywords;           // 78
	};
	static_assert(sizeof(BGSConstructibleObject) == 0x88);

	class __declspec(novtable) BGSMaterialSwap :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSMaterialSwap };
		static constexpr auto VTABLE{ VTABLE::BGSMaterialSwap };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kMSWP };

		struct Entry
		{
		public:
			// members
			BSFixedString swapMaterial;  // 00
			float colorRemappingIndex;   // 08
		};
		static_assert(sizeof(Entry) == 0x10);

		// members
		BSTHashMap<BSFixedString, Entry> swapMap;  // 20
	};
	static_assert(sizeof(BGSMaterialSwap) == 0x50);

	class __declspec(novtable) BGSZoomData :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSZoomData };
		static constexpr auto VTABLE{ VTABLE::BGSZoomData };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kZOOM };

		struct Data
		{
		public:
			// members
			float fovMult;              // 00
			std::uint32_t overlay;      // 04
			std::uint32_t isModFormID;  // 08
			NiPoint3 cameraOffset;      // 0C
		};
		static_assert(sizeof(Data) == 0x18);

		// members
		Data zoomData;                 // 20
		TESImageSpaceModifier* isMod;  // 38
	};
	static_assert(sizeof(BGSZoomData) == 0x40);

	class __declspec(novtable) BGSInstanceNamingRules :
		public TESForm  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSInstanceNamingRules };
		static constexpr auto VTABLE{ VTABLE::BGSInstanceNamingRules };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kINNR };

		class RuleData
		{
		public:
			// members
			BGSLocalizedString text;               // 00
			BGSKeywordForm keywords;               // 08
			float compareVal;                      // 28
			std::int8_t propertyBridgeArrayIndex;  // 2C
			std::int8_t operatorType;              // 2D
			std::uint16_t index;                   // 2E
			bool revert;                           // 30
		};
		static_assert(sizeof(RuleData) == 0x38);

		struct RuleSet :
			public BSTArray<RuleData>  // 00
		{
		public:
		};
		static_assert(sizeof(RuleSet) == 0x18);

		// members
		stl::enumeration<ENUM_FORM_ID, std::int32_t> type;     // 020
		RuleSet ruleSets[10];                                  // 028
		BSTArray<const BGSInstanceNamingRules*> mergeSources;  // 118
	};
	static_assert(sizeof(BGSInstanceNamingRules) == 0x130);

	class __declspec(novtable) BGSSoundKeywordMapping :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSSoundKeywordMapping };
		static constexpr auto VTABLE{ VTABLE::BGSSoundKeywordMapping };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kKSSM };

		// members
		BSTSet<BGSKeyword*> keywordSet;                                    // 20
		BSTHashMap<std::uint32_t, BGSSoundDescriptorForm*> reverbDescMap;  // 50
		BGSSoundDescriptorForm* descriptor;                                // 80
		BGSSoundDescriptorForm* exteriorTail;                              // 88
		BGSSoundDescriptorForm* vatsDescriptor;                            // 90
		float vatsDescThreshold;                                           // 98
	};
	static_assert(sizeof(BGSSoundKeywordMapping) == 0xA0);

	class __declspec(novtable) BGSAudioEffectChain :
		public TESForm,             // 00
		public BSIAudioEffectChain  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSAudioEffectChain };
		static constexpr auto VTABLE{ VTABLE::BGSAudioEffectChain };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kAECH };

		// members
		BSTArray<BSIAudioEffectParameters*> effects;  // 28
	};
	static_assert(sizeof(BGSAudioEffectChain) == 0x40);

	class __declspec(novtable) BGSAttractionRule :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSAttractionRule };
		static constexpr auto VTABLE{ VTABLE::BGSAttractionRule };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kAORU };

		struct ATTRACTION_RULE_DATA
		{
		public:
			// members
			float radius;       // 00
			float minDelay;     // 04
			float maxDelay;     // 08
			bool requiresLOS;   // 0C
			bool combatTarget;  // 0D
		};
		static_assert(sizeof(ATTRACTION_RULE_DATA) == 0x10);

		// members
		ATTRACTION_RULE_DATA data;   // 20
		BSFixedString formEditorID;  // 30
	};
	static_assert(sizeof(BGSAttractionRule) == 0x38);

	class __declspec(novtable) BGSSoundCategorySnapshot :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSSoundCategorySnapshot };
		static constexpr auto VTABLE{ VTABLE::BGSSoundCategorySnapshot };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSCSN };

		// members
		BSTHashMap<BGSSoundCategory*, float> categoryMult;  // 20
		std::int8_t priority;                               // 50
	};
	static_assert(sizeof(BGSSoundCategorySnapshot) == 0x58);

	class __declspec(novtable) BGSSoundTagSet :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSSoundTagSet };
		static constexpr auto VTABLE{ VTABLE::BGSSoundTagSet };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSTAG };

		// members
		BSTHashMap<BSFixedString, BGSSoundDescriptorForm*> soundTags;  // 20
	};
	static_assert(sizeof(BGSSoundTagSet) == 0x50);

	class BSLensFlareRenderData
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLensFlareRenderData };

		// members
		float fadeDistRadiusScale;                                 // 00
		float colorInfluence;                                      // 04
		BSTArray<NiPointer<BSLensFlareSpriteRenderData>> sprites;  // 08
		BSSpinLock lock;                                           // 20
		std::uint32_t refCount;                                    // 28
	};
	static_assert(sizeof(BSLensFlareRenderData) == 0x30);

	class __declspec(novtable) BGSLensFlare :
		public TESForm,               // 00
		public BSLensFlareRenderData  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSLensFlare };
		static constexpr auto VTABLE{ VTABLE::BGSLensFlare };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLENS };
	};
	static_assert(sizeof(BGSLensFlare) == 0x50);

	class __declspec(novtable) BGSGodRays :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSGodRays };
		static constexpr auto VTABLE{ VTABLE::BGSGodRays };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kGDRY };

		struct GodRaysData
		{
		public:
			// members
			NiColor colorAir;   // 00
			NiColor colorBack;  // 0C
			NiColor colorFwd;   // 18
			float intensity;    // 24
			float scatterAir;   // 28
			float scatterBack;  // 2C
			float scatterFwd;   // 30
			float phaseBack;    // 34
			float phaseFwd;     // 38
		};
		static_assert(sizeof(GodRaysData) == 0x3C);

		// members
		GodRaysData data;  // 20
	};
	static_assert(sizeof(BGSGodRays) == 0x60);
}
