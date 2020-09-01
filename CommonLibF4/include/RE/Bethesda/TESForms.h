#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTList.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTextureSet.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/TESCondition.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class TESForm;
	class TESObject;
	class TESBoundObject;
	class TESBoundAnimObject;
	class MagicItem;
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
		kNONE,	// 00 NONE TESForm / TESObject / TESBoundObject / TESBoundAnimObject / MagicItem
		kTES4,	// 01 TES4
		kGRUP,	// 02 GRUP
		kGMST,	// 03 GMST
		kKYWD,	// 04 KYWD BGSKeyword
		kLCRT,	// 05 LCRT BGSLocationRefType
		kAACT,	// 06 AACT BGSAction
		kTRNS,	// 07 TRNS BGSTransform
		kCMPO,	// 08 CMPO BGSComponent
		kTXST,	// 09 TXST BGSTextureSet
		kMICN,	// 0A MICN BGSMenuIcon
		kGLOB,	// 0B GLOB TESGlobal
		kDMGT,	// 0C DMGT BGSDamageType
		kCLAS,	// 0D CLAS TESClass
		kFACT,	// 0E FACT TESFaction
		kHDPT,	// 0F HDPT BGSHeadPart
		kEYES,	// 10 EYES TESEyes
		kRACE,	// 11 RACE TESRace
		kSOUN,	// 12 SOUN TESSound
		kASPC,	// 13 ASPC BGSAcousticSpace
		kSKIL,	// 14 SKIL
		kMGEF,	// 15 MGEF EffectSetting
		kSCPT,	// 16 SCPT Script
		kLTEX,	// 17 LTEX TESLandTexture
		kENCH,	// 18 ENCH EnchantmentItem
		kSPEL,	// 19 SPEL SpellItem
		kSCRL,	// 1A SCRL ScrollItem
		kACTI,	// 1B ACTI TESObjectACTI
		kTACT,	// 1C TACT BGSTalkingActivator
		kARMO,	// 1D ARMO TESObjectARMO
		kBOOK,	// 1E BOOK TESObjectBOOK
		kCONT,	// 1F CONT TESObjectCONT
		kDOOR,	// 20 DOOR TESObjectDOOR
		kINGR,	// 21 INGR IngredientItem
		kLIGH,	// 22 LIGH TESObjectLIGH
		kMISC,	// 23 MISC TESObjectMISC
		kSTAT,	// 24 STAT TESObjectSTAT
		kSCOL,	// 25 SCOL BGSStaticCollection
		kMSTT,	// 26 MSTT BGSMovableStatic
		kGRAS,	// 27 GRAS TESGrass
		kTREE,	// 28 TREE TESObjectTREE
		kFLOR,	// 29 FLOR TESFlora
		kFURN,	// 2A FURN TESFurniture
		kWEAP,	// 2B WEAP TESObjectWEAP
		kAMMO,	// 2C AMMO TESAmmo
		kNPC_,	// 2D NPC_ TESNPC
		kLVLN,	// 2E LVLN TESLevCharacter
		kKEYM,	// 2F KEYM TESKey
		kALCH,	// 30 ALCH AlchemyItem
		kIDLM,	// 31 IDLM BGSIdleMarker
		kNOTE,	// 32 NOTE BGSNote
		kPROJ,	// 33 PROJ BGSProjectile
		kHAZD,	// 34 HAZD BGSHazard
		kBNDS,	// 35 BNDS BGSBendableSpline
		kSLGM,	// 36 SLGM TESSoulGem
		kTERM,	// 37 TERM BGSTerminal
		kLVLI,	// 38 LVLI TESLevItem
		kWTHR,	// 39 WTHR TESWeather
		kCLMT,	// 3A CLMT TESClimate
		kSPGD,	// 3B SPGD BGSShaderParticleGeometryData
		kRFCT,	// 3C RFCT BGSReferenceEffect
		kREGN,	// 3D REGN TESRegion
		kNAVI,	// 3E NAVI NavMeshInfoMap
		kCELL,	// 3F CELL TESObjectCELL
		kREFR,	// 40 REFR TESObjectREFR
		kACHR,	// 41 ACHR Actor / PlayerCharacter
		kPMIS,	// 42 PMIS MissileProjectile
		kPARW,	// 43 PARW ArrowProjectile
		kPGRE,	// 44 PGRE GrenadeProjectile
		kPBEA,	// 45 PBEA BeamProjectile
		kPFLA,	// 46 PFLA FlameProjectile
		kPCON,	// 47 PCON ConeProjectile
		kPBAR,	// 48 PBAR BarrierProjectile
		kPHZD,	// 49 PHZD Hazard
		kWRLD,	// 4A WRLD TESWorldSpace
		kLAND,	// 4B LAND TESObjectLAND
		kNAVM,	// 4C NAVM NavMesh
		kTLOD,	// 4D TLOD
		kDIAL,	// 4E DIAL TESTopic
		kINFO,	// 4F INFO TESTopicInfo
		kQUST,	// 50 QUST TESQuest
		kIDLE,	// 51 IDLE TESIdleForm
		kPACK,	// 52 PACK TESPackage / DialoguePackage
		kCSTY,	// 53 CSTY TESCombatStyle
		kLSCR,	// 54 LSCR TESLoadScreen
		kLVSP,	// 55 LVSP TESLevSpell
		kANIO,	// 56 ANIO TESObjectANIO
		kWATR,	// 57 WATR TESWaterForm
		kEFSH,	// 58 EFSH TESEffectShader
		kTOFT,	// 59 TOFT
		kEXPL,	// 5A EXPL BGSExplosion
		kDEBR,	// 5B DEBR BGSDebris
		kIMGS,	// 5C IMGS TESImageSpace
		kIMAD,	// 5D IMAD TESImageSpaceModifier
		kFLST,	// 5E FLST BGSListForm
		kPERK,	// 5F PERK BGSPerk
		kBPTD,	// 60 BPTD BGSBodyPartData
		kADDN,	// 61 ADDN BGSAddonNode
		kAVIF,	// 62 AVIF ActorValueInfo
		kCAMS,	// 63 CAMS BGSCameraShot
		kCPTH,	// 64 CPTH BGSCameraPath
		kVTYP,	// 65 VTYP BGSVoiceType
		kMATT,	// 66 MATT BGSMaterialType
		kIPCT,	// 67 IPCT BGSImpactData
		kIPDS,	// 68 IPDS BGSImpactDataSet
		kARMA,	// 69 ARMA TESObjectARMA
		kECZN,	// 6A ECZN BGSEncounterZone
		kLCTN,	// 6B LCTN BGSLocation
		kMESG,	// 6C MESG BGSMessage
		kRGDL,	// 6D RGDL
		kDOBJ,	// 6E DOBJ BGSDefaultObjectManager
		kDFOB,	// 6F DFOB BGSDefaultObject
		kLGTM,	// 70 LGTM BGSLightingTemplate
		kMUSC,	// 71 MUSC BGSMusicType
		kFSTP,	// 72 FSTP BGSFootstep
		kFSTS,	// 73 FSTS BGSFootstepSet
		kSMBN,	// 74 SMBN BGSStoryManagerBranchNode
		kSMQN,	// 75 SMQN BGSStoryManagerQuestNode
		kSMEN,	// 76 SMEN BGSStoryManagerEventNode
		kDLBR,	// 77 DLBR BGSDialogueBranch
		kMUST,	// 78 MUST BGSMusicTrackFormWrapper
		kDLVW,	// 79 DLVW
		kWOOP,	// 7A WOOP TESWordOfPower
		kSHOU,	// 7B SHOU TESShout
		kEQUP,	// 7C EQUP BGSEquipSlot
		kRELA,	// 7D RELA BGSRelationship
		kSCEN,	// 7E SCEN BGSScene
		kASTP,	// 7F ASTP BGSAssociationType
		kOTFT,	// 80 OTFT BGSOutfit
		kARTO,	// 81 ARTO BGSArtObject
		kMATO,	// 82 MATO BGSMaterialObject
		kMOVT,	// 83 MOVT BGSMovementType
		kSNDR,	// 84 SNDR BGSSoundDescriptorForm
		kDUAL,	// 85 DUAL BGSDualCastData
		kSNCT,	// 86 SNCT BGSSoundCategory
		kSOPM,	// 87 SOPM BGSSoundOutput
		kCOLL,	// 88 COLL BGSCollisionLayer
		kCLFM,	// 89 CLFM BGSColorForm
		kREVB,	// 8A REVB BGSReverbParameters
		kPKIN,	// 8B PKIN BGSPackIn
		kRFGP,	// 8C RFGP
		kAMDL,	// 8D AMDL BGSAimModel
		kLAYR,	// 8E LAYR
		kCOBJ,	// 8F COBJ BGSConstructibleObject
		kOMOD,	// 90 OMOD BGSMod::Attachment::Mod
		kMSWP,	// 91 MSWP BGSMaterialSwap
		kZOOM,	// 92 ZOOM BGSZoomData
		kINNR,	// 93 INNR BGSInstanceNamingRules
		kKSSM,	// 94 KSSM BGSSoundKeywordMapping
		kAECH,	// 95 AECH BGSAudioEffectChain
		kSCCO,	// 96 SCCO
		kAORU,	// 97 AORU BGSAttractionRule
		kSCSN,	// 98 SCSN BGSSoundCategorySnapshot
		kSTAG,	// 99 STAG BGSSoundTagSet
		kNOCM,	// 9A NOCM
		kLENS,	// 9B LENS BGSLensFlare
		kLSPR,	// 9C LSPR
		kGDRY,	// 9D GDRY BGSGodRays
		kOVIS,	// 9E OVIS

		kTotal
	};

	enum class CHUNK_ID;
	enum class COMMAND_REFUSAL_TYPE;
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

	class BGSLoadFormBuffer;
	class BGSPreviewTransform;
	class BGSSaveFormBuffer;
	class NiAVObject;
	class QueuedFile;
	class TBO_InstanceData;
	class TESFile;

	struct FORM;
	struct FORM_GROUP;

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
		virtual void InitializeData() { return; }																														// 07
		virtual void ClearData() { return; }																															// 08
		virtual bool Load(TESFile*) { return true; }																													// 09
		virtual bool LoadPartial(TESFile*) { return true; }																												// 0A
		virtual bool LoadEdit(TESFile* a_file) { return Load(a_file); }																									// 0B
		virtual TESForm* CreateDuplicateForm(bool a_createEditorID, BSTHashMap<TESForm*, TESForm*>* a_copyMap);															// 0C
		virtual bool AddChange(std::int32_t a_changeFlags);																												// 0D
		virtual void RemoveChange(std::int32_t a_changeFlags);																											// 0E
		virtual bool FindInFileFast(TESFile*) { return false; }																											// 0F
		virtual bool CheckSaveGame(BGSSaveFormBuffer*) const { return true; }																							// 10
		virtual void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer);																										// 11
		virtual void LoadGame(BGSLoadFormBuffer* a_loadGameBuffer);																										// 12
		virtual void InitLoadGame(BGSLoadFormBuffer*) { return; }																										// 13
		virtual void FinishLoadGame(BGSLoadFormBuffer*) { return; }																										// 14
		virtual void Revert(BGSLoadFormBuffer*) { return; }																												// 15
		virtual void InitItemImpl() { return; }																															// 16
		virtual TESFile* GetRevertFile() const;																															// 17
		virtual TESFile* GetDescriptionOwnerFile() const;																												// 18
		virtual ENUM_FORM_ID GetSavedFormType() const { return *formType; }																								// 19
		virtual void GetFormDetailedString(char* a_dest, std::uint32_t a_size) const;																					// 1A
		virtual bool GetKnown() const { return (formFlags >> 6) & 1; }																									// 1B
		virtual bool GetRandomAnim() const { return (formFlags >> 16) & 1; }																							// 1C
		virtual bool GetPlayable(const TBO_InstanceData*) const { return (formFlags >> 2) & 1; }																		// 1D
		virtual bool IsHeadingMarker() const { return false; }																											// 1E
		virtual bool IsHeadtrackMarker() const { return false; }																										// 1F
		virtual bool GetDangerous() const { return (formFlags >> 17) & 1; }																								// 20
		virtual bool QHasCurrents() const { return (formFlags >> 19) & 1; }																								// 21
		virtual bool GetObstacle() const { return (formFlags >> 25) & 1; }																								// 22
		virtual bool QIsLODLandObject() const { return false; }																											// 23
		virtual bool GetOnLocalMap() const { return (formFlags >> 9) & 1; }																								// 24
		virtual bool GetMustUpdate() const { return (formFlags >> 8) & 1; }																								// 25
		virtual void SetOnLocalMap(bool a_val);																															// 26
		virtual bool GetIgnoredBySandbox() const { return false; }																										// 27
		virtual void SetDelete(bool a_deleted);																															// 28
		virtual void SetAltered(bool a_altered);																														// 29
		virtual void SaveObjectBound() { return; }																														// 2A
		virtual void LoadObjectBound(TESFile*) { return; }																												// 2B
		virtual void SavePreviewTransform(CHUNK_ID) { return; }																											// 2C
		virtual void LoadPreviewTransform(TESFile*) { return; }																											// 2D
		virtual bool IsBoundObject() const { return false; }																											// 2E
		virtual bool IsObject() const { return false; }																													// 2F
		virtual bool IsMagicItem() const { return false; }																												// 30
		virtual bool IsWater() const { return false; }																													// 31
		virtual TESObjectREFR* IsReference() { return nullptr; }																										// 33
		virtual const TESObjectREFR* IsReference() const { return nullptr; }																							// 32
		virtual std::uint32_t GetRefCount() const { return 0; }																											// 34
		virtual const char* GetTextForParsedSubTag(const BSFixedString& a_subTag) const;																				// 35
		virtual void Copy([[maybe_unused]] TESForm* a_copy) { return; }																									// 36
		virtual bool BelongsInGroup(FORM* a_groupFORM, bool, bool);																										// 37
		virtual void CreateGroupData(FORM* a_outGroupFORM, FORM_GROUP* a_parentGroup);																					// 38
		virtual std::uint32_t GetFormEditorIDLength() const;																											// 39
		virtual const char* GetFormEditorID() const { return ""; }																										// 3A
		virtual bool SetFormEditorID(const char*) { return true; }																										// 3B
		virtual bool IsParentForm() { return false; }																													// 3C
		virtual bool IsParentFormTree() { return false; }																												// 3D
		virtual bool IsFormTypeChild(std::uint8_t) { return false; }																									// 3E
		virtual bool LoopingActivate(TESObjectREFR* a_itemActivated, TESObjectREFR* a_actionRef) { return Activate(a_itemActivated, a_actionRef, nullptr, 1); }			// 3F
		virtual bool Activate(TESObjectREFR*, TESObjectREFR*, [[maybe_unused]] TESBoundObject* a_objectToGet, [[maybe_unused]] std::int32_t a_count) { return false; }	// 40
		virtual void SetFormID(std::uint32_t a_id, bool a_updateFile);																									// 41
		virtual const char* GetObjectTypeName() const { return ""; }																									// 42
		virtual bool QAvailableInGame() const { return true; }																											// 43
		virtual BGSMod::Template::Items* GetObjectTemplate() { return nullptr; }																						// 44
		virtual BGSPreviewTransform* GetPreviewTransform() { return nullptr; }																							// 45
		virtual BGSSoundTagComponent* GetSoundTagComponent() { return nullptr; }																						// 46
		virtual std::uint32_t GetFilledSlots() const;																													// 47
		virtual std::uint32_t GetFilledSlotsImpl() const { return static_cast<std::uint32_t>(-1); }																		// 48
		virtual float GetDesirability(TBO_InstanceData*, const TESForm*) const { return 0.0F; }																			// 49

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

	struct NiNPShortPoint3
	{
	public:
		// members
		std::int16_t x;	 // 0
		std::int16_t y;	 // 2
		std::int16_t z;	 // 4
	};
	static_assert(sizeof(NiNPShortPoint3) == 0x6);

	class TESObject :
		public TESForm	// 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESObject };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNONE };

		// add
		virtual bool IsBoundAnimObject() { return false; }								// 4A
		virtual TESWaterForm* GetWaterType() const { return nullptr; }					// 4B
		virtual bool IsAutoCalc() const { return false; }								// 4C
		virtual void SetAutoCalc(bool) { return; }										// 4D
		virtual void Clone3D(TESObjectREFR*, NiPointer<NiAVObject>&, bool) { return; }	// 4E
		virtual void UnClone3D(TESObjectREFR* a_requester);								// 4F
		virtual bool IsMarker();														// 50
		virtual bool IsOcclusionMarker();												// 51
		virtual bool ReplaceModel();													// 52
		virtual std::uint32_t IncRef() { return 0; }									// 53
		virtual std::uint32_t DecRef() { return 0; }									// 54
		virtual NiAVObject* LoadGraphics(TESObjectREFR* a_ref);							// 55
	};
	static_assert(sizeof(TESObject) == 0x20);

	class TESBoundObject :
		public TESObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESBoundObject };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNONE };

		struct BOUND_DATA
		{
		public:
			// members
			NiNPShortPoint3 boundMin;  // 00
			NiNPShortPoint3 boundMax;  // 06
		};
		static_assert(sizeof(BOUND_DATA) == 0xC);

		// add
		virtual TBO_InstanceData* CreateInstanceData(const TBO_InstanceData*) const { return nullptr; }										   // 56
		virtual const TBO_InstanceData* GetBaseInstanceData() const { return nullptr; }														   // 57
		virtual bool GetAttachedMarkersVisible(NiAVObject*) const { return false; }															   // 58
		virtual void SetAttachedMarkersVisible(NiAVObject*, bool) const { return; }															   // 59
		virtual bool QSupportsCountPerInstance() const { return false; }																	   // 5A
		virtual void SetObjectVoiceType(BGSVoiceType*) { return; }																			   // 5B
		virtual BGSVoiceType* GetObjectVoiceType() const { return nullptr; }																   // 5C
		virtual BGSSoundDescriptorForm* GetSoundForTag(const BSFixedString& a_tag) const;													   // 5D
		virtual void Clone3D(TESObjectREFR* a_requester, NiPointer<NiAVObject>& a_obj3D) { TESObject::Clone3D(a_requester, a_obj3D, false); }  // 5E
		virtual bool ReplaceModel(const char* a_filename);																					   // 5F
		virtual bool GetActivateText(TESObjectREFR* a_itemActivated, BSStringT<char>& a_resultString);										   // 60
		virtual COMMAND_REFUSAL_TYPE CalculateDoFavor(Actor* a_actor, bool a_owned, TESObjectREFR*, float a_moralityMult) const;			   // 61
		virtual void HandleRemoveItemFromContainer(TESObjectREFR*) { return; }																   // 62
		virtual void OnRemove3D(NiAVObject*) { return; }																					   // 63
		virtual void OnCheckModels() { return; }																							   // 64
		virtual void OnCopyReference() { return; }																							   // 65
		virtual void OnFinishScale() { return; }																							   // 66

		// members
		BOUND_DATA boundData;					 // 20
		BGSMod::Template::Items objectTemplate;	 // 30
		BGSPreviewTransform previewTransform;	 // 50
		BGSSoundTagComponent soundTagComponent;	 // 60
	};
	static_assert(sizeof(TESBoundObject) == 0x68);

	class TESBoundAnimObject :
		public TESBoundObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESBoundAnimObject };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNONE };
	};
	static_assert(sizeof(TESBoundAnimObject) == 0x68);

	struct EffectItemData
	{
	public:
		// members
		float magnitude;		// 0
		std::int32_t area;		// 4
		std::int32_t duration;	// 8
	};
	static_assert(sizeof(EffectItemData) == 0xC);

	class EffectItem
	{
	public:
		// members
		EffectItemData data;		   // 00
		EffectSetting* effectSetting;  // 10
		float rawCost;				   // 18
		TESCondition conditions;	   // 20
	};
	static_assert(sizeof(EffectItem) == 0x28);

	class MagicItem :
		public TESBoundObject,	// 00
		public TESFullName,		// 68
		public BGSKeywordForm	// 70
	{
	public:
		static constexpr auto RTTI{ RTTI_MagicItem };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNONE };

		struct SkillUsageData
		{
		public:
			// members
			EffectItem* effect;		// 00
			ActorValueInfo* skill;	// 08
			float magnitude;		// 10
			bool custom;			// 14
		};
		static_assert(sizeof(SkillUsageData) == 0x18);

		class Data
		{
		public:
			// members
			std::int32_t costOverride;	// 0
			std::uint32_t flags;		// 4
		};
		static_assert(sizeof(Data) == 0x8);

		// add
		virtual MagicSystem::SpellType GetSpellType() const = 0;															// 67
		virtual void SetCastingType([[maybe_unused]] MagicSystem::CastingType a_castingType) { return; }					// 68
		virtual MagicSystem::CastingType GetCastingType() const = 0;														// 69
		virtual void SetDelivery([[maybe_unused]] MagicSystem::Delivery a_delivery) { return; }								// 6A
		virtual MagicSystem::Delivery GetDelivery() const = 0;																// 6B
		virtual bool IsValidDelivery(MagicSystem::Delivery) { return true; }												// 6C
		virtual float GetFixedCastDuration() const { return 0.0F; }															// 6D
		virtual float GetRange() const { return 0.0F; }																		// 6E
		virtual bool IgnoreResistance() const { return false; }																// 6F
		virtual bool IgnoreLOS() const { return false; }																	// 70
		virtual bool IsFood() const { return false; }																		// 71
		virtual bool GetNoAbsorb() const { return false; }																	// 72
		virtual bool GetNoDualCastModifications() const { return false; }													// 73
		virtual bool GetSkillUsageData([[maybe_unused]] SkillUsageData& a_data) const { return false; }						// 74
		virtual bool IsPoison() const;																						// 75
		virtual bool IsMedicine() const { return false; }																	// 76
		virtual void AdjustCost(float&, Actor*) const { return; }															// 77
		virtual float GetChargeTime() const { return 0.0F; }																// 78
		virtual std::uint32_t GetMaxEffectCount() const { return 0; }														// 79
		virtual ActorValueInfo* GetAssociatedSkill() const { return nullptr; }												// 7A
		virtual bool IsTwoHanded() const { return false; }																	// 7B
		virtual CHUNK_ID GetChunkID() = 0;																					// 7C
		virtual void CopyMagicItemData(MagicItem* a_copy) = 0;																// 7D
		virtual void LoadMagicItemChunk([[maybe_unused]] TESFile* a_file, [[maybe_unused]] CHUNK_ID a_chunkID) { return; }	// 7E
		virtual void LoadChunkDataPostProcess([[maybe_unused]] TESFile* a_file) { return; }									// 7F
		virtual Data* GetData() = 0;																						// 81
		virtual const Data* GetData() const = 0;																			// 80
		virtual std::size_t GetDataSize() const = 0;																		// 82
		virtual void InitFromChunk(TESFile* a_file) = 0;																	// 83

		// members
		BSTArray<EffectItem*> listOfEffects;										 // 98
		std::int32_t hostileCount;													 // B0
		EffectSetting* avEffectSetting;												 // B8
		std::uint32_t preloadCount;													 // C0
		BSTSmartPointer<QueuedFile, BSTSmartPointerGamebryoRefCount> preloadedItem;	 // C8
	};
	static_assert(sizeof(MagicItem) == 0xD0);

	class BGSComponent :
		public TESBoundObject,		// 00
		public TESFullName,			// 68
		public TESValueForm,		// 78
		public BGSCraftingUseSound	// 88
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSComponent };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCMPO };

		// members
		TESObjectMISC* scrapItem;	// 98
		TESGlobal* modScrapScalar;	// 90
	};
	static_assert(sizeof(BGSComponent) == 0xA8);

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

	class BGSHeadPart :
		public TESForm,				 // 000
		public TESFullName,			 // 020
		public BGSModelMaterialSwap	 // 030
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSHeadPart };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kHDPT };

		enum class HeadPartType
		{
			kMisc,
			kFace,
			kEyes,
			kHair,
			kFacialHair,
			kScar,
			kEyebrows,
			kMeatcaps,
			kTeeth,
			kHeadRear
		};

		// members
		std::int8_t flags;									// 070
		stl::enumeration<HeadPartType, std::int32_t> type;	// 074
		BSTArray<BGSHeadPart*> extraParts;					// 078
		BGSTextureSet* textureSet;							// 090
		TESModel ChargenModel;								// 098
		TESModelTri morphs[3];								// 0C8
		BGSColorForm* colorForm;							// 158
		BGSListForm* validRaces;							// 160
		TESCondition chargenConditions;						// 168
		BSFixedString formEditorID;							// 170
	};
	static_assert(sizeof(BGSHeadPart) == 0x178);

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

	namespace TESSoundDefs
	{
		struct RepeaterData
		{
		public:
			// members
			float minDelay;	 // 0
			float maxDelay;	 // 4
			bool stackable;	 // 8
		};
		static_assert(sizeof(RepeaterData) == 0xC);
	}

	class TESSound :
		public TESBoundAnimObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESSound };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSOUN };

		// members
		BGSSoundDescriptorForm* descriptor;		// 68
		TESSoundDefs::RepeaterData repeatData;	// 70
	};
	static_assert(sizeof(TESEyes) == 0x48);

	class BGSAcousticSpace :
		public TESBoundObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSAcousticSpace };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kASPC };

		// members
		BGSSoundDescriptorForm* loopingSound;  // 68
		TESRegion* soundRegion;				   // 70
		BGSReverbParameters* reverbType;	   // 78
		std::uint16_t weatherAttenMillibels;   // 80
		bool isInterior;					   // 82
	};
	static_assert(sizeof(BGSAcousticSpace) == 0x88);

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

	class EnchantmentItem :
		public MagicItem  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_EnchantmentItem };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kENCH };

		class Data :
			public MagicItem::Data	// 00
		{
		public:
			// members
			stl::enumeration<MagicSystem::CastingType, std::int32_t> castingType;  // 08
			std::int32_t chargeOverride;										   // 0C
			stl::enumeration<MagicSystem::Delivery, std::int32_t> delivery;		   // 10
			stl::enumeration<MagicSystem::SpellType, std::int32_t> spellType;	   // 14
			float chargeTime;													   // 18
			EnchantmentItem* baseEnchantment;									   // 20
			BGSListForm* wornRestrictions;										   // 28
		};
		static_assert(sizeof(Data) == 0x30);

		// members
		Data data;	// 0D0
	};
	static_assert(sizeof(EnchantmentItem) == 0x100);

	class SpellItem :
		public MagicItem,			  // 000
		public BGSEquipType,		  // 0D0
		public BGSMenuDisplayObject,  // 0E0
		public TESDescription		  // 0F0
	{
	public:
		static constexpr auto RTTI{ RTTI_EnchantmentItem };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSPEL };

		class Data :
			public MagicItem::Data	// 00
		{
		public:
			// members
			stl::enumeration<MagicSystem::SpellType, std::int32_t> spellType;	   // 08
			float chargeTime;													   // 0C
			stl::enumeration<MagicSystem::CastingType, std::int32_t> castingType;  // 10
			stl::enumeration<MagicSystem::Delivery, std::int32_t> delivery;		   // 14
			float castDuration;													   // 18
			float range;														   // 1C
			BGSPerk* castingPerk;												   // 20
		};
		static_assert(sizeof(Data) == 0x28);

		// members
		Data data;	// 108
	};
	static_assert(sizeof(SpellItem) == 0x130);

	class ScrollItem :
		public SpellItem,				   // 000
		public BGSModelMaterialSwap,	   // 130
		public BGSDestructibleObjectForm,  // 170
		public BGSPickupPutdownSounds,	   // 180
		public TESWeightForm,			   // 198
		public TESValueForm				   // 1A8
	{
	public:
		static constexpr auto RTTI{ RTTI_ScrollItem };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSCRL };
	};
	static_assert(sizeof(ScrollItem) == 0x1B8);

	class TESObjectACTI :
		public TESBoundAnimObject,		   // 000
		public TESFullName,				   // 068
		public BGSModelMaterialSwap,	   // 078
		public TESMagicTargetForm,		   // 120
		public BGSDestructibleObjectForm,  // 0B8
		public BGSOpenCloseForm,		   // 0C8
		public BGSKeywordForm,			   // 0D0
		public BGSPropertySheet,		   // 0F0
		public BGSForcedLocRefType,		   // 100
		public BGSNativeTerminalForm,	   // 110
		public BGSNavmeshableObject		   // 120
	{
	public:
		static constexpr auto RTTI{ RTTI_TESObjectACTI };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kACTI };

		// members
		BGSSoundDescriptorForm* soundLoop;		// 128
		BGSSoundDescriptorForm* soundActivate;	// 130
		TESWaterForm* waterForm;				// 138
		std::uint16_t flags;					// 140
	};
	static_assert(sizeof(TESObjectACTI) == 0x148);

	class BGSTalkingActivator :
		public TESObjectACTI  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSTalkingActivator };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kTACT };

		// add
		virtual bool GetReflectedByAutoWater() { return false; }  // 67

		// members
		TESObjectREFR* tempRef;	  // 148
		BGSVoiceType* voiceType;  // 150
	};
	static_assert(sizeof(BGSTalkingActivator) == 0x158);

	class TESObjectARMO :
		public TESBoundObject,			   // 000
		public TESFullName,				   // 068
		public TESRaceForm,				   // 078
		public TESEnchantableForm,		   // 088
		public BGSDestructibleObjectForm,  // 0A0
		public BGSPickupPutdownSounds,	   // 0B0
		public TESBipedModelForm,		   // 0C8
		public BGSEquipType,			   // 1D0
		public BGSBipedObjectForm,		   // 1E0
		public BGSBlockBashData,		   // 1F0
		public BGSKeywordForm,			   // 208
		public TESDescription,			   // 228
		public BGSInstanceNamingRulesForm  // 240
	{
	public:
		static constexpr auto RTTI{ RTTI_TESObjectARMO };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kARMO };

		struct InstanceData :
			public TBO_InstanceData	 // 00
		{
		public:
			static constexpr auto RTTI{ RTTI_TESObjectARMO__InstanceData };

			// members
			BSTArray<EnchantmentItem*>* enchantments;									  // 10
			BSTArray<BGSMaterialSwap*>* materialSwaps;									  // 18
			BGSBlockBashData* blockBashData;											  // 20
			BGSKeywordForm* keywords;													  // 28
			BSTArray<BSTTuple<TESForm*, BGSTypedFormValuePair::SharedVal>>* damageTypes;  // 30
			BSTArray<BSTTuple<TESForm*, BGSTypedFormValuePair::SharedVal>>* actorValues;  // 38
			float weight;																  // 40
			float colorRemappingIndex;													  // 44
			std::uint32_t value;														  // 48
			std::uint32_t health;														  // 4C
			stl::enumeration<STAGGER_MAGNITUDE, std::int32_t> staggerRating;			  // 50
			std::uint16_t rating;														  // 54
			std::uint16_t index;														  // 56
		};
		static_assert(sizeof(InstanceData) == 0x58);

		class ArmorAddon
		{
		public:
			// members
			std::uint16_t index;		// 00
			TESObjectARMA* armorAddon;	// 08
		};
		static_assert(sizeof(ArmorAddon) == 0x10);

		// members
		InstanceData data;					 // 250
		BSTArray<ArmorAddon> modelArray;	 // 2A8
		TESObjectARMO* armorTemplate;		 // 2C0
		BGSAttachParentArray attachParents;	 // 2C8
	};
	static_assert(sizeof(TESObjectARMO) == 0x2E0);
}
