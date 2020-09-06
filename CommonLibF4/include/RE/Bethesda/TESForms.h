#pragma once

#include "RE/Bethesda/BGSBodyPartDefs.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTList.h"
#include "RE/Bethesda/BSTSingleton.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/Settings.h"
#include "RE/Bethesda/TESCondition.h"
#include "RE/NetImmerse/NiColor.h"
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
	class TESWorldSpace;
	class TESObjectLAND;
	class NavMesh;
	class TESTopic;
	class TESTopicInfo;
	class TESQuest;
	class TESIdleForm;
	class TESPackage;
	class DialoguePackage;
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

	namespace BGSMod
	{
		namespace Attachment
		{
			class Mod;
		}
	}

	enum class ENUM_FORM_ID
	{
		kNONE,	// 00 NONE X TESForm
				//         X TESObject
				//         X TESBoundObject
				//         X MagicItem
				//         X TESBoundAnimObject
				//         X TESActorBase
				//         X BGSStoryManagerTreeForm
		kTES4,	// 01 TES4
		kGRUP,	// 02 GRUP
		kGMST,	// 03 GMST
		kKYWD,	// 04 KYWD X BGSKeyword
		kLCRT,	// 05 LCRT X BGSLocationRefType
		kAACT,	// 06 AACT X BGSAction
		kTRNS,	// 07 TRNS X BGSTransform
		kCMPO,	// 08 CMPO X BGSComponent
		kTXST,	// 09 TXST X BGSTextureSet
		kMICN,	// 0A MICN X BGSMenuIcon
		kGLOB,	// 0B GLOB X TESGlobal
		kDMGT,	// 0C DMGT X BGSDamageType
		kCLAS,	// 0D CLAS X TESClass
		kFACT,	// 0E FACT X TESFaction
		kHDPT,	// 0F HDPT X BGSHeadPart
		kEYES,	// 10 EYES X TESEyes
		kRACE,	// 11 RACE X TESRace
		kSOUN,	// 12 SOUN X TESSound
		kASPC,	// 13 ASPC X BGSAcousticSpace
		kSKIL,	// 14 SKIL
		kMGEF,	// 15 MGEF X EffectSetting
		kSCPT,	// 16 SCPT X Script
		kLTEX,	// 17 LTEX X TESLandTexture
		kENCH,	// 18 ENCH X EnchantmentItem
		kSPEL,	// 19 SPEL X SpellItem
		kSCRL,	// 1A SCRL X ScrollItem
		kACTI,	// 1B ACTI X TESObjectACTI
		kTACT,	// 1C TACT X BGSTalkingActivator
		kARMO,	// 1D ARMO X TESObjectARMO
		kBOOK,	// 1E BOOK X TESObjectBOOK
		kCONT,	// 1F CONT X TESObjectCONT
		kDOOR,	// 20 DOOR X TESObjectDOOR
		kINGR,	// 21 INGR X IngredientItem
		kLIGH,	// 22 LIGH X TESObjectLIGH
		kMISC,	// 23 MISC X TESObjectMISC
		kSTAT,	// 24 STAT X TESObjectSTAT
		kSCOL,	// 25 SCOL X BGSStaticCollection
		kMSTT,	// 26 MSTT X BGSMovableStatic
		kGRAS,	// 27 GRAS X TESGrass
		kTREE,	// 28 TREE X TESObjectTREE
		kFLOR,	// 29 FLOR X TESFlora
		kFURN,	// 2A FURN X TESFurniture
		kWEAP,	// 2B WEAP X TESObjectWEAP
		kAMMO,	// 2C AMMO X TESAmmo
		kNPC_,	// 2D NPC_ X TESNPC
		kLVLN,	// 2E LVLN X TESLevCharacter
		kKEYM,	// 2F KEYM X TESKey
		kALCH,	// 30 ALCH X AlchemyItem
		kIDLM,	// 31 IDLM X BGSIdleMarker
		kNOTE,	// 32 NOTE X BGSNote
		kPROJ,	// 33 PROJ X BGSProjectile
		kHAZD,	// 34 HAZD X BGSHazard
		kBNDS,	// 35 BNDS X BGSBendableSpline
		kSLGM,	// 36 SLGM X TESSoulGem
		kTERM,	// 37 TERM X BGSTerminal
		kLVLI,	// 38 LVLI X TESLevItem
		kWTHR,	// 39 WTHR X TESWeather
		kCLMT,	// 3A CLMT X TESClimate
		kSPGD,	// 3B SPGD X BGSShaderParticleGeometryData
		kRFCT,	// 3C RFCT X BGSReferenceEffect
		kREGN,	// 3D REGN X TESRegion
		kNAVI,	// 3E NAVI X NavMeshInfoMap
		kCELL,	// 3F CELL X TESObjectCELL
		kREFR,	// 40 REFR X TESObjectREFR
				//         X Explosion
				//         X Projectile
		kACHR,	// 41 ACHR X Actor
				//         X PlayerCharacter
		kPMIS,	// 42 PMIS X MissileProjectile
		kPARW,	// 43 PARW X ArrowProjectile
		kPGRE,	// 44 PGRE X GrenadeProjectile
		kPBEA,	// 45 PBEA X BeamProjectile
		kPFLA,	// 46 PFLA X FlameProjectile
		kPCON,	// 47 PCON X ConeProjectile
		kPBAR,	// 48 PBAR X BarrierProjectile
		kPHZD,	// 49 PHZD X Hazard
		kWRLD,	// 4A WRLD X TESWorldSpace
		kLAND,	// 4B LAND X TESObjectLAND
		kNAVM,	// 4C NAVM X NavMesh
		kTLOD,	// 4D TLOD
		kDIAL,	// 4E DIAL X TESTopic
		kINFO,	// 4F INFO X TESTopicInfo
		kQUST,	// 50 QUST X TESQuest
		kIDLE,	// 51 IDLE X TESIdleForm
		kPACK,	// 52 PACK X TESPackage
				//         X AlarmPackage
				//         X DialoguePackage
				//         X FleePackage
				//         X SpectatorPackage
				//         X TrespassPackage
		kCSTY,	// 53 CSTY X TESCombatStyle
		kLSCR,	// 54 LSCR X TESLoadScreen
		kLVSP,	// 55 LVSP X TESLevSpell
		kANIO,	// 56 ANIO X TESObjectANIO
		kWATR,	// 57 WATR X TESWaterForm
		kEFSH,	// 58 EFSH X TESEffectShader
		kTOFT,	// 59 TOFT
		kEXPL,	// 5A EXPL X BGSExplosion
		kDEBR,	// 5B DEBR X BGSDebris
		kIMGS,	// 5C IMGS X TESImageSpace
		kIMAD,	// 5D IMAD X TESImageSpaceModifier
		kFLST,	// 5E FLST X BGSListForm
		kPERK,	// 5F PERK X BGSPerk
		kBPTD,	// 60 BPTD X BGSBodyPartData
		kADDN,	// 61 ADDN X BGSAddonNode
		kAVIF,	// 62 AVIF X ActorValueInfo
		kCAMS,	// 63 CAMS _ BGSCameraShot
		kCPTH,	// 64 CPTH _ BGSCameraPath
		kVTYP,	// 65 VTYP _ BGSVoiceType
		kMATT,	// 66 MATT _ BGSMaterialType
		kIPCT,	// 67 IPCT _ BGSImpactData
		kIPDS,	// 68 IPDS _ BGSImpactDataSet
		kARMA,	// 69 ARMA _ TESObjectARMA
		kECZN,	// 6A ECZN _ BGSEncounterZone
		kLCTN,	// 6B LCTN _ BGSLocation
		kMESG,	// 6C MESG _ BGSMessage
		kRGDL,	// 6D RGDL
		kDOBJ,	// 6E DOBJ _ BGSDefaultObjectManager
		kDFOB,	// 6F DFOB _ BGSDefaultObject
		kLGTM,	// 70 LGTM _ BGSLightingTemplate
		kMUSC,	// 71 MUSC _ BGSMusicType
		kFSTP,	// 72 FSTP _ BGSFootstep
		kFSTS,	// 73 FSTS _ BGSFootstepSet
		kSMBN,	// 74 SMBN _ BGSStoryManagerBranchNode
		kSMQN,	// 75 SMQN _ BGSStoryManagerQuestNode
		kSMEN,	// 76 SMEN _ BGSStoryManagerEventNode
		kDLBR,	// 77 DLBR _ BGSDialogueBranch
		kMUST,	// 78 MUST _ BGSMusicTrackFormWrapper
		kDLVW,	// 79 DLVW
		kWOOP,	// 7A WOOP _ TESWordOfPower
		kSHOU,	// 7B SHOU _ TESShout
		kEQUP,	// 7C EQUP _ BGSEquipSlot
		kRELA,	// 7D RELA _ BGSRelationship
		kSCEN,	// 7E SCEN _ BGSScene
		kASTP,	// 7F ASTP _ BGSAssociationType
		kOTFT,	// 80 OTFT _ BGSOutfit
		kARTO,	// 81 ARTO _ BGSArtObject
		kMATO,	// 82 MATO _ BGSMaterialObject
		kMOVT,	// 83 MOVT _ BGSMovementType
		kSNDR,	// 84 SNDR _ BGSSoundDescriptorForm
		kDUAL,	// 85 DUAL _ BGSDualCastData
		kSNCT,	// 86 SNCT _ BGSSoundCategory
		kSOPM,	// 87 SOPM _ BGSSoundOutput
		kCOLL,	// 88 COLL _ BGSCollisionLayer
		kCLFM,	// 89 CLFM _ BGSColorForm
		kREVB,	// 8A REVB _ BGSReverbParameters
		kPKIN,	// 8B PKIN _ BGSPackIn
		kRFGP,	// 8C RFGP
		kAMDL,	// 8D AMDL _ BGSAimModel
		kLAYR,	// 8E LAYR
		kCOBJ,	// 8F COBJ _ BGSConstructibleObject
		kOMOD,	// 90 OMOD _ BGSMod::Attachment::Mod
		kMSWP,	// 91 MSWP _ BGSMaterialSwap
		kZOOM,	// 92 ZOOM _ BGSZoomData
		kINNR,	// 93 INNR _ BGSInstanceNamingRules
		kKSSM,	// 94 KSSM _ BGSSoundKeywordMapping
		kAECH,	// 95 AECH _ BGSAudioEffectChain
		kSCCO,	// 96 SCCO
		kAORU,	// 97 AORU _ BGSAttractionRule
		kSCSN,	// 98 SCSN _ BGSSoundCategorySnapshot
		kSTAG,	// 99 STAG _ BGSSoundTagSet
		kNOCM,	// 9A NOCM
		kLENS,	// 9B LENS _ BGSLensFlare
		kLSPR,	// 9C LSPR
		kGDRY,	// 9D GDRY _ BGSGodRays
		kOVIS,	// 9E OVIS

		kTotal
	};

	enum class _D3DBLEND;
	enum class _D3DBLENDOP;
	enum class _D3DCMPFUNC;
	enum class CHUNK_ID;
	enum class COMMAND_REFUSAL_TYPE;
	enum class DIALOGUE_SUBTYPE;
	enum class SOUND_LEVEL;
	enum class STAGGER_MAGNITUDE;

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
	class BGSPerkEntry;
	class BGSPreviewTransform;
	class BGSSaveFormBuffer;
	class BSGeometry;
	class ExtraDataList;
	class NavMeshArray;
	class NiColorInterpolator;
	class NiFloatInterpolator;
	class NiFormArray;
	class NiTexture;
	class QueuedFile;
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
	struct INTERIOR_DATA;
	struct LOADED_CELL_DATA;

	namespace BGSWaterCollisionManager
	{
		class AutoWater;
		class BGSWaterUpdateI;
	}

	class TESFileArray :
		BSStaticArray<TESFile*>	 // 00
	{
	public:
	};
	static_assert(sizeof(TESFileArray) == 0x10);

	struct TESFileContainer
	{
	public:
		// members
		const TESFileArray* array;	// 0
	};
	static_assert(sizeof(TESFileContainer) == 0x8);

	class TESForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESForm };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNONE };

		// add
		virtual void InitializeData() { return; }																																													  // 07
		virtual void ClearData() { return; }																																														  // 08
		virtual bool Load([[maybe_unused]] TESFile* a_file) { return true; }																																						  // 09
		virtual bool LoadPartial([[maybe_unused]] TESFile* a_file) { return true; }																																					  // 0A
		virtual bool LoadEdit(TESFile* a_file) { return Load(a_file); }																																								  // 0B
		virtual TESForm* CreateDuplicateForm(bool a_createEditorID, BSTHashMap<TESForm*, TESForm*>* a_copyMap);																														  // 0C
		virtual bool AddChange(std::int32_t a_changeFlags);																																											  // 0D
		virtual void RemoveChange(std::int32_t a_changeFlags);																																										  // 0E
		virtual bool FindInFileFast([[maybe_unused]] TESFile* a_file) { return false; }																																				  // 0F
		virtual bool CheckSaveGame([[maybe_unused]] BGSSaveFormBuffer* a_saveGameBuffer) const { return true; }																														  // 10
		virtual void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer);																																									  // 11
		virtual void LoadGame(BGSLoadFormBuffer* a_loadGameBuffer);																																									  // 12
		virtual void InitLoadGame([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) { return; }																																	  // 13
		virtual void FinishLoadGame([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) { return; }																																  // 14
		virtual void Revert([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) { return; }																																		  // 15
		virtual void InitItemImpl() { return; }																																														  // 16
		virtual TESFile* GetRevertFile() const;																																														  // 17
		virtual TESFile* GetDescriptionOwnerFile() const;																																											  // 18
		virtual ENUM_FORM_ID GetSavedFormType() const { return *formType; }																																							  // 19
		virtual void GetFormDetailedString(char* a_dest, std::uint32_t a_size) const;																																				  // 1A
		virtual bool GetKnown() const { return (formFlags >> 6) & 1; }																																								  // 1B
		virtual bool GetRandomAnim() const { return (formFlags >> 16) & 1; }																																						  // 1C
		virtual bool GetPlayable([[maybe_unused]] const TBO_InstanceData* a_data) const { return (formFlags >> 2) & 1; }																											  // 1D
		virtual bool IsHeadingMarker() const { return false; }																																										  // 1E
		virtual bool IsHeadtrackMarker() const { return false; }																																									  // 1F
		virtual bool GetDangerous() const { return (formFlags >> 17) & 1; }																																							  // 20
		virtual bool QHasCurrents() const { return (formFlags >> 19) & 1; }																																							  // 21
		virtual bool GetObstacle() const { return (formFlags >> 25) & 1; }																																							  // 22
		virtual bool QIsLODLandObject() const { return false; }																																										  // 23
		virtual bool GetOnLocalMap() const { return (formFlags >> 9) & 1; }																																							  // 24
		virtual bool GetMustUpdate() const { return (formFlags >> 8) & 1; }																																							  // 25
		virtual void SetOnLocalMap(bool a_val);																																														  // 26
		virtual bool GetIgnoredBySandbox() const { return false; }																																									  // 27
		virtual void SetDelete(bool a_deleted);																																														  // 28
		virtual void SetAltered(bool a_altered);																																													  // 29
		virtual void SaveObjectBound() { return; }																																													  // 2A
		virtual void LoadObjectBound([[maybe_unused]] TESFile* a_file) { return; }																																					  // 2B
		virtual void SavePreviewTransform(CHUNK_ID) { return; }																																										  // 2C
		virtual void LoadPreviewTransform([[maybe_unused]] TESFile* a_file) { return; }																																				  // 2D
		virtual bool IsBoundObject() const { return false; }																																										  // 2E
		virtual bool IsObject() const { return false; }																																												  // 2F
		virtual bool IsMagicItem() const { return false; }																																											  // 30
		virtual bool IsWater() const { return false; }																																												  // 31
		virtual TESObjectREFR* IsReference() { return nullptr; }																																									  // 33
		virtual const TESObjectREFR* IsReference() const { return nullptr; }																																						  // 32
		virtual std::uint32_t GetRefCount() const { return 0; }																																										  // 34
		virtual const char* GetTextForParsedSubTag(const BSFixedString& a_subTag) const;																																			  // 35
		virtual void Copy([[maybe_unused]] TESForm* a_copy) { return; }																																								  // 36
		virtual bool BelongsInGroup(FORM* a_groupFORM, bool a_allowParentGroups, bool a_currentOnly);																																  // 37
		virtual void CreateGroupData(FORM* a_outGroupFORM, FORM_GROUP* a_parentGroup);																																				  // 38
		virtual std::uint32_t GetFormEditorIDLength() const;																																										  // 39
		virtual const char* GetFormEditorID() const { return ""; }																																									  // 3A
		virtual bool SetFormEditorID([[maybe_unused]] const char* a_editorID) { return true; }																																		  // 3B
		virtual bool IsParentForm() { return false; }																																												  // 3C
		virtual bool IsParentFormTree() { return false; }																																											  // 3D
		virtual bool IsFormTypeChild([[maybe_unused]] std::uint8_t a_type) { return false; }																																		  // 3E
		virtual bool LoopingActivate(TESObjectREFR* a_itemActivated, TESObjectREFR* a_actionRef) { return Activate(a_itemActivated, a_actionRef, nullptr, 1); }																		  // 3F
		virtual bool Activate([[maybe_unused]] TESObjectREFR* a_itemActivated, [[maybe_unused]] TESObjectREFR* a_actionRef, [[maybe_unused]] TESBoundObject* a_objectToGet, [[maybe_unused]] std::int32_t a_count) { return false; }  // 40
		virtual void SetFormID(std::uint32_t a_id, bool a_updateFile);																																								  // 41
		virtual const char* GetObjectTypeName() const { return ""; }																																								  // 42
		virtual bool QAvailableInGame() const { return true; }																																										  // 43
		virtual BGSMod::Template::Items* GetObjectTemplate() { return nullptr; }																																					  // 44
		virtual BGSPreviewTransform* GetPreviewTransform() { return nullptr; }																																						  // 45
		virtual BGSSoundTagComponent* GetSoundTagComponent() { return nullptr; }																																					  // 46
		virtual std::uint32_t GetFilledSlots() const;																																												  // 47
		virtual std::uint32_t GetFilledSlotsImpl() const { return static_cast<std::uint32_t>(-1); }																																	  // 48
		virtual float GetDesirability([[maybe_unused]] TBO_InstanceData* a_instanceData, [[maybe_unused]] const TESForm* a_user) const { return 0.0F; }																				  // 49

		// members
		TESFileContainer sourceFiles;						   // 08
		std::uint32_t formFlags;							   // 10
		std::uint32_t formID;								   // 14
		std::uint16_t inGameFormFlags;						   // 18
		stl::enumeration<ENUM_FORM_ID, std::int8_t> formType;  // 1A
	};
	static_assert(sizeof(TESForm) == 0x20);

	class BGSKeyword :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSKeyword };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kKYWD };

		// members
		BSFixedString formEditorID;	 // 20
	};
	static_assert(sizeof(BGSKeyword) == 0x28);

	class BGSLocationRefType :
		public BGSKeyword  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSLocationRefType };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLCRT };
	};
	static_assert(sizeof(BGSLocationRefType) == 0x28);

	class BGSAction :
		public BGSKeyword  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSAction };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kAACT };

		// members
		std::uint32_t index;  // 28
	};
	static_assert(sizeof(BGSAction) == 0x30);

	class BGSTransform :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSTransform };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kTRNS };

		struct TransformData
		{
		public:
			// members
			NiPoint3 position;	// 00
			NiPoint3 rotation;	// 0C
			float scale;		// 18
			float minZoom;		// 1C
			float maxZoom;		// 20
		};
		static_assert(sizeof(TransformData) == 0x24);

		// members
		TransformData data;	 // 20
	};
	static_assert(sizeof(BGSTransform) == 0x48);

	class BGSMenuIcon :
		public TESForm,	 // 00
		public TESIcon	 // 20
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSMenuIcon };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kMICN };
	};
	static_assert(sizeof(BGSMenuIcon) == 0x30);

	class TESGlobal :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESGlobal };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kGLOB };

		// members
		BSStringT<char> formEditorID;  // 20
		float value;				   // 30
	};
	static_assert(sizeof(TESGlobal) == 0x38);

	class BGSDamageType :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSDamageType };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kDMGT };

		struct Data
		{
		public:
			// members
			ActorValueInfo* resistance;	 // 00
			MagicItem* spell;			 // 08
		};
		static_assert(sizeof(Data) == 0x10);

		// members
		Data data;	// 20
	};
	static_assert(sizeof(BGSDamageType) == 0x30);

	struct CLASS_DATA
	{
	public:
		// members
		std::int32_t serviceFlags;	// 0
		float bleedoutDefault;		// 4
	};
	static_assert(sizeof(CLASS_DATA) == 0x8);

	class TESClass :
		public TESForm,			 // 00
		public TESFullName,		 // 20
		public TESDescription,	 // 30
		public TESTexture,		 // 48
		public BGSPropertySheet	 // 58
	{
	public:
		static constexpr auto RTTI{ RTTI_TESClass };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCLAS };

		// members
		CLASS_DATA data;  // 68
	};
	static_assert(sizeof(TESClass) == 0x70);

	class TESEyes :
		public TESForm,		 // 00
		public TESFullName,	 // 20
		public TESTexture	 // 30
	{
	public:
		static constexpr auto RTTI{ RTTI_TESEyes };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kEYES };

		// members
		std::int8_t flags;	// 40
	};
	static_assert(sizeof(TESEyes) == 0x48);

	class EffectSetting :
		public TESForm,				  // 000
		public TESFullName,			  // 020
		public BGSMenuDisplayObject,  // 030
		public BGSKeywordForm		  // 040
	{
	public:
		static constexpr auto RTTI{ RTTI_EffectSetting };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kMGEF };

		using FilterValidationFunction_t = bool(EffectSetting*, void*);

		struct EffectSettingData
		{
		public:
			// members
			std::uint32_t flags;													  // 000
			float baseCost;															  // 004
			TESForm* associatedForm;												  // 008
			ActorValueInfo* associatedSkill;										  // 010
			ActorValueInfo* resistVariable;											  // 018
			std::int16_t numCounterEffects;											  // 020
			TESObjectLIGH* light;													  // 028
			float taperWeight;														  // 030
			TESEffectShader* effectShader;											  // 038
			TESEffectShader* enchantEffect;											  // 040
			std::int32_t minimumSkill;												  // 048
			std::int32_t spellmakingArea;											  // 04C
			float spellmakingChargeTime;											  // 050
			float taperCurve;														  // 054
			float taperDuration;													  // 058
			float secondaryAVWeight;												  // 05C
			stl::enumeration<EffectArchetypes::ArchetypeID, std::int32_t> archetype;  // 060
			ActorValueInfo* primaryAV;												  // 068
			BGSProjectile* projectileBase;											  // 070
			BGSExplosion* explosion;												  // 078
			stl::enumeration<MagicSystem::CastingType, std::int32_t> castingType;	  // 080
			stl::enumeration<MagicSystem::Delivery, std::int32_t> delivery;			  // 084
			ActorValueInfo* secondaryAV;											  // 088
			BGSArtObject* castingArt;												  // 090
			BGSArtObject* hitEffectArt;												  // 098
			BGSImpactDataSet* impactDataSet;										  // 0A0
			float skillUsageMult;													  // 0A8
			BGSDualCastData* dualCastData;											  // 0B0
			float dualCastScale;													  // 0B8
			BGSArtObject* enchantEffectArt;											  // 0C0
			BGSReferenceEffect* hitVisuals;											  // 0C8
			BGSReferenceEffect* enchantVisuals;										  // 0D0
			SpellItem* equipAbility;												  // 0D8
			TESImageSpaceModifier* imageSpaceMod;									  // 0E0
			BGSPerk* perk;															  // 0E8
			stl::enumeration<SOUND_LEVEL, std::int32_t> castingSoundLevel;			  // 0F0
			float aiScore;															  // 0F4
			float aiDelayTime;														  // 0F8
		};
		static_assert(sizeof(EffectSettingData) == 0x100);

		struct SoundPair
		{
		public:
			// members
			stl::enumeration<MagicSystem::SoundID, std::int32_t> id;  // 00
			BGSSoundDescriptorForm* sound;							  // 08
		};
		static_assert(sizeof(SoundPair) == 0x10);

		// members
		FilterValidationFunction_t* filterValidationFunction;  // 060
		void* filterValidationItem;							   // 068
		EffectSettingData data;								   // 070
		BSSimpleList<EffectSetting*> counterEffects;		   // 170
		BSTArray<EffectSetting::SoundPair> effectSounds;	   // 180
		BGSLocalizedString magicItemDescription;			   // 198
		std::int32_t effectLoadedCount;						   // 1A0
		std::int32_t associatedItemLoadedCount;				   // 1A4
		TESCondition conditions;							   // 1A8
	};
	static_assert(sizeof(EffectSetting) == 0x1B0);

	struct TEXTURE_HAVOK_DATA
	{
	public:
		// members
		std::int8_t friction;	  // 0
		std::int8_t restitution;  // 1
	};
	static_assert(sizeof(TEXTURE_HAVOK_DATA) == 0x2);

	class TESLandTexture :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESLandTexture };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLTEX };

		// members
		BGSTextureSet* textureSet;				   // 20
		TEXTURE_HAVOK_DATA havokData;			   // 28
		BGSMaterialType* materialType;			   // 30
		std::int8_t specularExponent;			   // 38
		std::int32_t shaderTextureIndex;		   // 3C
		BSSimpleList<TESGrass*> textureGrassList;  // 40
	};
	static_assert(sizeof(TESLandTexture) == 0x50);

	class BGSDirectionalAmbientLightingColors
	{
	public:
		// members
		std::uint32_t colorValues[7];  // 00
		float fresnelPower;			   // 1C
	};
	static_assert(sizeof(BGSDirectionalAmbientLightingColors) == 0x20);

	class TESWeather :
		public TESForm	// 000
	{
	public:
		static constexpr auto RTTI{ RTTI_TESWeather };
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
			BGSSoundDescriptorForm* soundForm;				 // 00
			stl::enumeration<SoundType, std::int32_t> type;	 // 08
		};
		static_assert(sizeof(WeatherSound) == 0x10);

		struct WeatherSoundList :
			public BSSimpleList<WeatherSound*>
		{
		public:
		};
		static_assert(sizeof(WeatherSoundList) == 0x10);

		// members
		stl::enumeration<SpellContext, std::int32_t> context;					  // 020
		TESTexture1024 cloudTexture[32];										  // 028
		std::int8_t cloudLayerSpeedY[32];										  // 228
		std::int8_t cloudLayerSpeedX[32];										  // 248
		std::uint32_t cloudColorData[32][8];									  // 268
		float cloudAlpha[32][8];												  // 668
		std::uint32_t cloudLayerDisabledBits;									  // A68
		std::int8_t weatherData[20];											  // A6C
		float fogData[18];														  // A80
		std::uint32_t colorData[19][8];											  // AC8
		float fogColorScales[4][8];												  // D28
		SpellData weatherSpellData[2];											  // DA8
		WeatherSoundList soundList;												  // DC8
		BSTArray<TESObjectSTAT*> skyStatics;									  // DD8
		std::uint32_t numCloudLayers;											  // DF0
		TESImageSpace* imageSpace[8];											  // DF8
		BGSGodRays* godRays[8];													  // E38
		BGSDirectionalAmbientLightingColors directionalAmbientLightingColors[8];  // E78
		TESModel aurora;														  // F78
		BGSLensFlare* sunGlareLensFlare;										  // FA8
		float volatilityMult;													  // FB0
		float isibilityMult;													  // FB4
		BGSShaderParticleGeometryData* precipitationData;						  // FB8
		BGSReferenceEffect* referenceEffect;									  // FC0
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

	class TESClimate :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESClimate };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCLMT };

		// members
		TESModel nightSky;			 // 20
		TESWeatherList weatherList;	 // 50
		TESTexture skyObjects[2];	 // 60
		std::int8_t data[6];		 // 80
	};
	static_assert(sizeof(TESClimate) == 0x88);

	class BGSShaderParticleGeometryData :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSShaderParticleGeometryData };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSPGD };

		// members
		BSTArray<SETTING_VALUE> data;  // 20
		TESTexture particleTexture;	   // 38
		BSFixedString materialName;	   // 48
	};
	static_assert(sizeof(BGSShaderParticleGeometryData) == 0x50);

	class BGSReferenceEffect :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSReferenceEffect };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kRFCT };

		struct Data
		{
		public:
			// members
			BGSArtObject* artObject;		// 00
			TESEffectShader* effectShader;	// 08
			std::uint32_t flags;			// 10
		};
		static_assert(sizeof(Data) == 0x18);

		// members
		Data data;	// 20
	};
	static_assert(sizeof(BGSReferenceEffect) == 0x38);

	class TESRegion :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESRegion };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kREGN };

		// add
		virtual bool Validate();  // 49

		// members
		TESRegionDataList* dataList;					// 20
		BSSimpleList<TESRegionPointList*>* pointLists;	// 28
		TESWorldSpace* worldSpace;						// 30
		TESWeather* currentWeather;						// 38
		NiColor emittanceColor;							// 40
		float lodDistanceModifier;						// 4C
		float occlusionAccuracy;						// 50
	};
	static_assert(sizeof(TESRegion) == 0x58);

	class TESObjectCELL :
		public TESForm,		// 00
		public TESFullName	// 20
	{
	public:
		static constexpr auto RTTI{ RTTI_TESObjectCELL };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCELL };

		// members
		BSSpinLock grassCreateLock;				   // 30
		BSSpinLock grassTaskLock;				   // 38
		std::uint16_t cellFlags;				   // 40
		std::uint16_t cellGameFlags;			   // 42
		std::int8_t cellState;					   // 44
		bool autoWaterLoaded;					   // 45
		bool cellDetached;						   // 46
		BSTSmartPointer<ExtraDataList> extraList;  // 48
		union
		{
			void* cellData;
			EXTERIOR_DATA* cellDataExterior;
			INTERIOR_DATA* cellDataInterior;
		};																			  // 50
		TESObjectLAND* cellLand;													  // 58
		float waterHeight;															  // 60
		NavMeshArray* navMeshes;													  // 68
		BSTArray<NiPointer<TESObjectREFR>, BSTArrayHeapAllocator> references;		  // 70
		BSTSmartPointer<BGSWaterCollisionManager::AutoWater> autoWater;				  // 77
		BSTSet<BSTSmartPointer<BGSWaterCollisionManager::BGSWaterUpdateI>> waterSet;  // 80
		BSSpinLock spinLock;														  // C0
		union
		{
			TESWorldSpace* worldSpace;
			std::uint32_t tempDataOffset;
		};										// C8
		LOADED_CELL_DATA* loadedData;			// D0
		BGSLightingTemplate* lightingTemplate;	// D8
		void* visibilityData;					// E0 - TODO
		std::uint32_t rootVisibilityCellID;		// E8
		std::uint16_t visCalcDate;				// EC
		std::uint16_t preCombineDate;			// F0
	};
	static_assert(sizeof(TESObjectCELL) == 0xF0);

	struct OBJ_LAND
	{
	public:
		// members
		std::uint32_t flags;  // 0
	};
	static_assert(sizeof(OBJ_LAND) == 0x4);

	class TESObjectLAND :
		public TESForm,		 // 00
		public TESChildCell	 // 20
	{
	public:
		static constexpr auto RTTI{ RTTI_TESObjectLAND };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLAND };

		struct LoadedLandData;

		// members
		OBJ_LAND data;						   // 28
		TESObjectCELL* parentCell;			   // 30
		NiPointer<QueuedFile> queuedTextures;  // 38
		LoadedLandData* loadedData;			   // 40
	};
	static_assert(sizeof(TESObjectLAND) == 0x48);

	struct DIALOGUE_DATA
	{
	public:
		// members
		std::int8_t flags;		// 0
		std::int8_t type;		// 1
		std::uint16_t subtype;	// 2
	};
	static_assert(sizeof(DIALOGUE_DATA) == 0x4);

	class TESTopic :
		public TESForm,		// 00
		public TESFullName	// 20
	{
	public:
		static constexpr auto RTTI{ RTTI_TESTopic };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kDIAL };

		struct InfoTree;

		// members
		DIALOGUE_DATA data;						// 30
		std::uint32_t priorityAndJournalIndex;	// 34
		BGSDialogueBranch* ownerBranch;			// 38
		TESQuest* ownerQuest;					// 40
		BGSKeyword* subtypeKeyword;				// 48
		TESTopicInfo** topicInfos;				// 50
		InfoTree* infoTree;						// 58
		std::uint32_t numTopicInfos;			// 60
		std::uint32_t topicInfoAllocSize;		// 64
		std::uint32_t firstFileOffset;			// 68
		BSFixedString formEditorID;				// 70
	};
	static_assert(sizeof(TESTopic) == 0x78);

	struct TOPIC_INFO_DATA
	{
	public:
		// members
		std::uint16_t flags;		   // 0
		std::uint16_t timeUntilReset;  // 2
	};
	static_assert(sizeof(TOPIC_INFO_DATA) == 0x4);

	class ResponseListWrapper
	{
	public:
		// members
		TESResponse* head;	// 0
	};
	static_assert(sizeof(ResponseListWrapper) == 0x8);

	class TESTopicInfo :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESTopicInfo };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kINFO };

		// members
		TESTopic* parentTopic;			// 20
		TESGlobal* resetGlobal;			// 28
		TESTopicInfo* dataInfo;			// 30
		TESCondition objConditions;		// 38
		std::uint16_t infoIndex;		// 40
		std::int8_t subtitlePriority;	// 42
		bool saidOnce;					// 43
		TOPIC_INFO_DATA data;			// 44
		ResponseListWrapper responses;	// 48
	};
	static_assert(sizeof(TESTopicInfo) == 0x50);

	struct IDLE_DATA
	{
	public:
		// members
		std::int8_t loopMin;		// 0
		std::int8_t loopMax;		// 1
		std::int8_t flags;			// 2
		std::uint16_t replayDelay;	// 4
	};
	static_assert(sizeof(IDLE_DATA) == 0x6);

	class TESIdleForm :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESIdleForm };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kIDLE };

		// members
		TESCondition conditions;		  // 20
		IDLE_DATA data;					  // 28
		NiFormArray* childIdles;		  // 30
		TESIdleForm* parentIdle;		  // 38
		TESIdleForm* prevIdle;			  // 40
		BSFixedString behaviorGraphName;  // 48
		BSFixedString animEventName;	  // 50
		BSFixedString animFileName;		  // 58
		BSStringT<char> formEditorID;	  // 60
	};
	static_assert(sizeof(TESIdleForm) == 0x70);

	class TESLoadScreen :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESLoadScreen };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kLSCR };

		struct LoadNIFData;

		// members
		TESCondition conditions;		 // 20
		LoadNIFData* loadNIFData;		 // 28
		BGSLocalizedString loadingText;	 // 30
	};
	static_assert(sizeof(TESLoadScreen) == 0x38);

	class TESObjectANIO :
		public TESForm,				 // 00
		public BGSModelMaterialSwap	 // 20
	{
	public:
		static constexpr auto RTTI{ RTTI_TESObjectANIO };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kANIO };

		// members
		BSFixedString formEditorID;		// 60
		BSFixedString unloadEventName;	// 68
	};
	static_assert(sizeof(TESObjectANIO) == 0x70);

	struct EffectShaderData
	{
	public:
		// members
		stl::enumeration<_D3DBLEND, std::int32_t> textureBlendModeSource;	// 00
		stl::enumeration<_D3DBLENDOP, std::int32_t> textureBlendOperation;	// 04
		stl::enumeration<_D3DCMPFUNC, std::int32_t> textureZTestFunction;	// 08
		std::uint32_t fillColor1;											// 0C
		float fillAlphaFadeInTime;											// 10
		float fillAlphaFullTime;											// 14
		float fillAlphaFadeOutTime;											// 18
		float fillAlphaPersistentPercent;									// 1C
		float fillAlphaPulseAmplitude;										// 20
		float fillAlphaPulseFrequency;										// 24
		float fillTextureUAnimSpeed;										// 28
		float fillTextureVAnimSpeed;										// 2C
		float edgeExponentValue;											// 30
		std::uint32_t edgeColor;											// 34
		float edgeAlphaFadeInTime;											// 38
		float edgeAlphaFullTime;											// 3C
		float edgeAlphaFadeOutTime;											// 40
		float edgeAlphaPersistentPercent;									// 44
		float edgeAlphaPulseAmplitude;										// 48
		float edgeAlphaPulseFrequency;										// 4C
		float fillAlphaFullPercent;											// 50
		float edgeAlphaFullPercent;											// 54
		stl::enumeration<_D3DBLEND, std::int32_t> textureBlendModeDest;		// 58
		float alphaTestStartTime;											// 5C
		float alphaTestEndTime;												// 60
		float alphaTestStartValue;											// 64
		float alphaTestEndValue;											// 68
		BGSSoundDescriptorForm* ambientSound;								// 70
		std::uint32_t fillColor2;											// 78
		std::uint32_t fillColor3;											// 7C
		float fillColorScaleA[3];											// 80
		float fillColorTimeA[3];											// 8C
		std::uint32_t flags;												// 98
		float fillTextureUScale;											// 9C
		float fillTextureVScale;											// A0
		std::int8_t boneDepth;												// A4
	};
	static_assert(sizeof(EffectShaderData) == 0xA8);

	class TESEffectShader :
		public TESForm,	 // 000
		public TESModel	 // 020
	{
	public:
		static constexpr auto RTTI{ RTTI_TESEffectShader };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kEFSH };

		// members
		EffectShaderData data;					  // 050
		TESTexture textureShaderTexture;		  // 0F8
		TESTexture blockOutTexture;				  // 108
		TESTexture paletteTexture;				  // 118
		NiPointer<BSGeometry> shareableGeometry;  // 128
	};
	static_assert(sizeof(TESEffectShader) == 0x130);

	class BGSDebris :
		public TESForm,		   // 00
		public BGSPreloadable  // 20
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSDebris };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kDEBR };

		// members
		BSSimpleList<BGSDebrisData*> dataList;	// 28
	};
	static_assert(sizeof(BGSDebris) == 0x38);

	struct ImageSpaceBaseData
	{
	public:
		// members
		float hdrData[9];		 // 00
		float cinematicData[3];	 // 24
		float tintData[4];		 // 30
		float dofData[6];		 // 40
	};
	static_assert(sizeof(ImageSpaceBaseData) == 0x58);

	class TESImageSpace :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESImageSpace };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kIMGS };

		// members
		ImageSpaceBaseData data;			// 20
		TESTexture lutTexture;				// 78
		NiPointer<NiTexture> niLutTexture;	// 88
	};
	static_assert(sizeof(TESImageSpace) == 0x90);

	class TESImageSpaceModifier :
		public TESForm	// 000
	{
	public:
		static constexpr auto RTTI{ RTTI_TESImageSpaceModifier };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kIMAD };

		struct ImageSpaceModifierData
		{
		public:
			// members
			bool animatable;									// 00
			float fduration;									// 04
			std::uint32_t keySize[21][2];						// 08
			std::uint32_t tintColorKeySize;						// B0
			std::uint32_t blurKeySize;							// B4
			std::uint32_t doubleKeySize;						// B8
			std::uint32_t radialBlurStrengthKeySize;			// BC
			std::uint32_t radialBlurRampupKeySize;				// C0
			std::uint32_t radialBlurStartKeySize;				// C4
			bool useTargetForRadialBlur;						// C8
			NiPoint2 radialBlurCenter;							// CC
			std::uint32_t depthOfFieldStrengthKeySize;			// D4
			std::uint32_t depthOfFieldDistanceKeySize;			// D8
			std::uint32_t depthOfFieldRangeKeySize;				// DC
			bool useTargetForDepthOfField;						// E0
			std::int8_t depthOfFieldMode;						// E1
			std::uint32_t radialBlurRampDownKeySize;			// E4
			std::uint32_t radialBlurDownStartKeySize;			// E8
			std::uint32_t fadeColorKeySize;						// EC
			std::uint32_t motionBlurStrengthKeySize;			// F0
			std::uint32_t depthOfFieldVignetteRadiusKeySize;	// F4
			std::uint32_t depthOfFieldVignetteStrengthKeySize;	// F8
		};
		static_assert(sizeof(ImageSpaceModifierData) == 0xFC);

		// members
		ImageSpaceModifierData data;											  // 020
		NiPointer<NiFloatInterpolator> interpolator[21][2];						  // 120
		NiPointer<NiFloatInterpolator> blurInterpolator;						  // 270
		NiPointer<NiFloatInterpolator> doubleInterpolator;						  // 278
		NiPointer<NiColorInterpolator> tintColorInterpolator;					  // 280
		NiPointer<NiColorInterpolator> fadeColorInterpolator;					  // 288
		NiPointer<NiFloatInterpolator> radialBlurStrengthInterpolator;			  // 290
		NiPointer<NiFloatInterpolator> radialBlurRampupInterpolator;			  // 298
		NiPointer<NiFloatInterpolator> radialBlurStartInterpolator;				  // 2A0
		NiPointer<NiFloatInterpolator> radialBlurRampDownInterpolator;			  // 2A8
		NiPointer<NiFloatInterpolator> radialBlurDownStartInterpolator;			  // 2B0
		NiPointer<NiFloatInterpolator> depthOfFieldStrengthInterpolator;		  // 2B8
		NiPointer<NiFloatInterpolator> depthOfFieldDistanceInterpolator;		  // 2C0
		NiPointer<NiFloatInterpolator> depthOfFieldRangeInterpolator;			  // 2C8
		NiPointer<NiFloatInterpolator> depthOfFieldVignetteRadiusInterpolator;	  // 2D0
		NiPointer<NiFloatInterpolator> depthOfFieldVignetteStrengthInterpolator;  // 2D8
		NiPointer<NiFloatInterpolator> motionBlurStrengthInterpolator;			  // 2E0
		BSStringT<char> formEditorID;											  // 2E8
	};
	static_assert(sizeof(TESImageSpaceModifier) == 0x2F8);

	class BGSListForm :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSListForm };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kFLST };

		// members
		BSTArray<TESForm*> arrayOfForms;				// 20
		BSTArray<std::uint32_t>* scriptAddedTempForms;	// 38
		std::uint32_t scriptAddedFormCount;				// 40
	};
	static_assert(sizeof(BGSListForm) == 0x48);

	struct PerkData
	{
	public:
		// members
		bool trait;			   // 0
		std::int8_t level;	   // 1
		std::int8_t numRanks;  // 2
		bool playable;		   // 3
		bool hidden;		   // 4
	};
	static_assert(sizeof(PerkData) == 0x5);

	class BGSPerk :
		public TESForm,			// 00
		public TESFullName,		// 20
		public TESDescription,	// 30
		public TESIcon			// 48
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSPerk };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kPERK };

		// members
		PerkData data;						  // 58
		TESCondition perkConditions;		  // 60
		BSTArray<BGSPerkEntry*> perkEntries;  // 68
		BGSPerk* nextPerk;					  // 80
		BGSSoundDescriptorForm* sound;		  // 88
		BSFixedStringCS swfFile;			  // 90
	};
	static_assert(sizeof(BGSPerk) == 0x98);

	class BGSBodyPartData :
		public TESForm,		   // 000
		public TESModel,	   // 020
		public BGSPreloadable  // 050
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSBodyPartData };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kBPTD };

		// members
		BGSBodyPart* partArray[26];								  // 058
		BGSBodyPartDefs::HitReactionData defaultHitReactionData;  // 128
	};
	static_assert(sizeof(BGSBodyPartData) == 0x150);
}
