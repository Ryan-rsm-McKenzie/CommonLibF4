#pragma once

#include "RE/Bethesda/AITimeStamp.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/TESForms.h"

namespace RE
{
	class PackageLocation;
	class TESCondition;

	struct FACTION_DATA
	{
	public:
		// members
		std::uint32_t flags;  // 0
	};
	static_assert(sizeof(FACTION_DATA) == 0x4);

	struct FACTION_CRIME_DATA_VALUES
	{
	public:
		// members
		bool arrest;                        // 00
		bool attackOnSight;                 // 01
		std::uint16_t murderCrimeGold;      // 02
		std::uint16_t assaultCrimeGold;     // 04
		std::uint16_t trespassCrimeGold;    // 06
		std::uint16_t pickpocketCrimeGold;  // 08
		float stealCrimeGoldMult;           // 0C
		std::uint16_t escapeCrimeGold;      // 10
		std::uint16_t unused;               // 12
	};
	static_assert(sizeof(FACTION_CRIME_DATA_VALUES) == 0x14);

	struct FACTION_CRIME_DATA
	{
	public:
		// members
		TESObjectREFR* factionJailMarker;                // 00
		TESObjectREFR* factionWaitMarker;                // 08
		TESObjectREFR* factionStolenContainer;           // 10
		TESObjectREFR* factionPlayerInventoryContainer;  // 18
		BGSListForm* crimeGroup;                         // 20
		BGSOutfit* jailOutfit;                           // 28
		FACTION_CRIME_DATA_VALUES crimevalues;           // 30
	};
	static_assert(sizeof(FACTION_CRIME_DATA) == 0x48);

	struct FACTION_VENDOR_DATA_VALUES
	{
	public:
		// members
		std::uint16_t startHour;       // 0
		std::uint16_t endHour;         // 2
		std::uint32_t locationRadius;  // 4
		bool buysStolen;               // 8
		bool notBuySell;               // 9
		bool buysNonStolen;            // A
	};
	static_assert(sizeof(FACTION_VENDOR_DATA_VALUES) == 0xC);

	struct FACTION_VENDOR_DATA
	{
	public:
		// members
		FACTION_VENDOR_DATA_VALUES vendorValues;  // 00
		PackageLocation* vendorLocation;          // 10
		TESCondition* vendorConditions;           // 18
		BGSListForm* vendorSellBuyList;           // 20
		TESObjectREFR* merchantContainer;         // 28
		std::uint32_t lastDayReset;               // 30
	};
	static_assert(sizeof(FACTION_VENDOR_DATA) == 0x38);

	struct RANK_DATA
	{
	public:
		// members
		BGSLocalizedString maleRankTitle;    // 00
		BGSLocalizedString femaleRankTitle;  // 08
		TESTexture textureInsignia;          // 10
	};
	static_assert(sizeof(RANK_DATA) == 0x20);

	class __declspec(novtable) TESFaction :
		public TESForm,         // 000
		public TESFullName,     // 020
		public TESReactionForm  // 030
	{
	public:
		static constexpr auto RTTI{ RTTI::TESFaction };
		static constexpr auto VTABLE{ VTABLE::TESFaction };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kFACT };

		// members
		BSTHashMap<const TESNPC*, std::uint32_t>* crimeGoldMap;  // 50
		FACTION_DATA data;                                       // 58
		FACTION_CRIME_DATA crimeData;                            // 60
		FACTION_VENDOR_DATA vendorData;                          // A8
		BSSimpleList<RANK_DATA*> rankDataList;                   // E0
		std::int32_t majorCrime;                                 // F0
		std::int32_t minorCrime;                                 // F4
		AITimeStamp resistArrestTimeStamp;                       // F8
		float enemyFlagTimeStamp;                                // FC
	};
	static_assert(sizeof(TESFaction) == 0x100);
}
