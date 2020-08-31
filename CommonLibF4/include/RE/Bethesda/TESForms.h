#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSResource.h"
#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTextureSet.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/NetImmerse/NiAlphaProperty.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiObject.h"
#include "RE/NetImmerse/NiPoint2.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class TESForm;
	class TESObject;
	class TESBoundObject;
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
		kNONE,	// 00 NONE TESForm / TESObject / TESBoundObject
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

	class BSEffectShaderPropertyColorController;
	class BSEffectShaderPropertyFloatController;
	class BSLightingShaderPropertyColorController;
	class BSLightingShaderPropertyFloatController;
	class BSLightingShaderPropertyUShortController;
	class BSNiAlphaPropertyTestRefController;
	class BSShaderTextureSet;
	class BGSLoadFormBuffer;
	class BGSPreviewTransform;
	class BGSSaveFormBuffer;
	class BGSSoundTagComponent;
	class DecalData;
	class NiAVObject;
	class TBO_InstanceData;
	class TESBoundObject;
	class TESFile;

	struct FORM;
	struct FORM_GROUP;

	namespace BSGraphics
	{
		enum class TextureAddressMode;
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
		stl::enumeration<LightingShaderEnum, std::int32_t> lightingShader;					// 004
		bool specularEnabled;																// 008
		NiColor specularColor;																// 00C
		float specularMult;																	// 018
		NiColor emittanceColor;																// 01C
		float emittanceColorScale;															// 028
		float lightingInfluence;															// 02C
		std::int8_t envmapMinLOD;															// 030
		float smoothness;																	// 034
		float fresnelPower_ShaderDataEntry;													// 038
		float wetnessControl_SpecScale_ShaderDataEntry;										// 03C
		float wetnessControl_SpecPowerScale_ShaderDataEntry;								// 040
		float wetnessControl_SpecMin_ShaderDataEntry;										// 044
		float wetnessControl_EnvMapScale_ShaderDataEntry;									// 048
		float wetnessControl_FresnelPower_ShaderDataEntry;									// 04C
		float wetnessControl_Metalness_ShaderDataEntry;										// 050
		bool betnessControl_ScreenSpaceReflections;											// 054
		BSFixedString rootMaterialPath;														// 058
		float alpha;																		// 060
		float emittanceMult;																// 064
		float lookupScale;																	// 068
		bool emitEnabled;																	// 06C
		BSFixedString materialPath;															// 070
		bool alphaBlend;																	// 078
		stl::enumeration<NiAlphaProperty::AlphaFunction, std::int32_t> alphaSrcBlendMode;	// 07C
		stl::enumeration<NiAlphaProperty::AlphaFunction, std::int32_t> alphaDestBlendMode;	// 080
		bool alphaTest;																		// 084
		stl::enumeration<NiAlphaProperty::TestFunction, std::int32_t> alphaTestFunction;	// 088
		std::int8_t alphaTestRef;															// 08C
		bool enableEditorAlphaRef;															// 08D
		bool vertexColors;																	// 08E
		bool vertexAlpha;																	// 08F
		bool modelSpaceNormals;																// 090
		bool decal;																			// 091
		bool externalEmittance;																// 092
		bool hideSecret;																	// 093
		bool noFade;																		// 094
		bool dismemberment;																	// 095
		bool facegen;																		// 096
		bool skinTint;																		// 097
		bool hair;																			// 098
		bool twoSided;																		// 099
		bool tree;																			// 09A
		bool bloodEnabled;																	// 09B
		bool uniqueAlphaProperty;															// 09C
		bool effectLightingEnabled;															// 09D
		bool castShadows;																	// 09E
		bool receiveShadows;																// 09F
		bool dissolveFade;																	// 0A0
		bool glowmap;																		// 0A1
		bool assumeShadowmask;																// 0A2
		bool screenSpaceReflections;														// 0A3
		bool nonOccluder;																	// 0A4
		bool skewSpecularAlpha;																// 0A5
		bool tessellate;																	// 0A6
		bool backLighting;																	// 0A7
		bool subSurfaceLighting;															// 0A8
		bool rimLighting;																	// 0A9
		float subSurfaceRolloff;															// 0AC
		float rimPower;																		// 0B0
		float backLightPower;																// 0B4
		bool anisoLighting;																	// 0B8
		bool zBufferWrite;																	// 0B8
		bool zBufferTest;																	// 0BA
		bool refraction;																	// 0BB
		float refractionPower;																// 0BC
		bool refractionFalloff;																// 0C0
		BSTArray<BSLightingShaderPropertyFloatController*> lightingFloatControllers;		// 0C8
		BSTArray<BSLightingShaderPropertyUShortController*> lightingUShortControllers;		// 0E0
		BSTArray<BSLightingShaderPropertyColorController*> lightingColorControllers;		// 0F8
		BSTArray<BSEffectShaderPropertyFloatController*> effectFloatControllers;			// 110
		BSTArray<BSEffectShaderPropertyColorController*> effectColorControllers;			// 128
		BSNiAlphaPropertyTestRefController* alphaRefTestController;							// 140
		bool parallax;																		// 148
		bool parallaxOcclusion;																// 149
		bool multiLayerParallax;															// 14A
		float parallaxOcclusionHeightScale;													// 14C
		float parallaxOcclusionMaxPasses;													// 150
		float parallaxLayerThickness;														// 154
		float parallaxRefractionScale;														// 158
		float parallaxInnerLayerUScale;														// 15C
		float parallaxInnerLayerVScale;														// 160
		float displacementTextureBias;														// 164
		float displacementTextureScale;														// 168
		float tessellationPNScale;															// 16C
		float tessellationFadeDistance;														// 170
		float tessellationBaseFactor;														// 174
		bool tessellationNeedsDominantUVs;													// 178
		bool tessellationNeedsCrackFreeNormals;												// 179
		bool environmentMapping;															// 17A
		bool environmentMappingEye;															// 17B
		bool environmentMappingWindow;														// 17C
		float environmentMappingMaskScale;													// 180
		std::int32_t skyTYpe;																// 184
		bool reflectionsEnabled;															// 188
		bool silhouetteReflectionsEnabled;													// 189
		bool refractionsEnabled;															// 18A
		bool depthEnabled;																	// 18B
		bool vertexUVEnabled;																// 18C
		bool vertexAlphaDepthEnabled;														// 18D
		bool foggingEnabled;																// 18E
		bool falloffEnabled;																// 18F
		bool rgbFalloffEnabled;																// 190
		NiColorA falloffData;																// 194
		bool softEnabled;																	// 1A4
		float softDepth;																	// 1A8
		NiPoint2 uvOffset;																	// 1AC
		NiPoint2 uvScale;																	// 1B4
		bool grayscaleToPaletteColor;														// 1BC
		bool grayscaleToPaletteAlpha;														// 1BD
		NiColor hairTintColor;																// 1C0
		NiPointer<BSShaderTextureSet> textureSet;											// 1D0
		stl::enumeration<BSGraphics::TextureAddressMode, std::int32_t> clampMode;			// 1D8
	};
	static_assert(sizeof(BSShaderData) == 0x1E0);

	class BGSTextureSet :
		public TESBoundObject,	// 000
		public BSTextureSet		// 068
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSTextureSet };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kTXST };

		// members
		BSFixedString materialName;		   // 078
		TESTexture textures[8];			   // 080
		DecalData* decalData;			   // 100
		std::uint16_t flags;			   // 108
		BSResource::ID textureFileIDs[8];  // 10C
		BSShaderData materialData;		   // 170
	};
	static_assert(sizeof(BGSTextureSet) == 0x350);
}
