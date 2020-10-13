#pragma once

#include "RE/Bethesda/TESForms.h"

namespace RE
{
	struct CombatStyleGeneralData
	{
	public:
		// members
		float offensiveMult;       // 00
		float defensiveMult;       // 04
		float groupOffensiveMult;  // 08
		float meleeScoreMult;      // 0C
		float magicScoreMult;      // 10
		float rangedScoreMult;     // 14
		float shoutScoreMult;      // 18
		float unarmedScoreMult;    // 1C
		float staffScoreMult;      // 20
		float avoidThreatChance;   // 24
		float dodgeThreatChance;   // 28
		float evadeThreatChance;   // 2C
	};
	static_assert(sizeof(CombatStyleGeneralData) == 0x30);

	struct CombatStyleMeleeData
	{
	public:
		// members
		float attackIncapacitatedMult;       // 00
		float powerAttackIncapacitatedMult;  // 04
		float powerAttackBlockingMult;       // 08
		float bashMult;                      // 0C
		float bashRecoiledMult;              // 10
		float bashAttackMult;                // 14
		float bashPowerAttackMult;           // 18
		float specialAttackMult;             // 1C
		float blockWhenIncapacitatedMult;    // 20
		float attackWhenIncapacitatedMult;   // 24
	};
	static_assert(sizeof(CombatStyleMeleeData) == 0x28);

	struct CombatStyleRangedData
	{
	public:
		// members
		float accuracyMult;  // 0
	};
	static_assert(sizeof(CombatStyleRangedData) == 0x4);

	struct CombatStyleCloseRangeData
	{
	public:
		// members
		float circleMult;               // 00
		float fallbackMult;             // 04
		float flankDistanceMult;        // 08
		float stalkTimeMult;            // 0C
		float chargeDistanceMult;       // 10
		float flipThrowProbability;     // 14
		float sprintChargeProbability;  // 18
		float sideswipeProbability;     // 1C
		float disengageProbability;     // 20
		std::uint32_t throwMaxTargets;  // 24
		float flankVarianceMult;        // 28
	};
	static_assert(sizeof(CombatStyleCloseRangeData) == 0x2C);

	struct CombatStyleLongRangeData
	{
	public:
		// members
		float strafeMult;       // 00
		float adjustRangeMult;  // 04
		float crouchMult;       // 08
		float waitMult;         // 0C
		float rangeMult;        // 10
	};
	static_assert(sizeof(CombatStyleLongRangeData) == 0x14);

	struct CombatStyleCoverData
	{
	public:
		// members
		float coverSearchDistanceMult;  // 0
	};
	static_assert(sizeof(CombatStyleCoverData) == 0x4);

	struct CombatStyleFlightData
	{
	public:
		// members
		float hoverChance;           // 00
		float diveBombChance;        // 04
		float groundAttackChance;    // 08
		float hoverTimeMult;         // 0C
		float groundAttackTimeMult;  // 10
		float perchAttackChance;     // 14
		float perchAttackTimeMult;   // 18
		float flyingAttackChance;    // 1C
	};
	static_assert(sizeof(CombatStyleFlightData) == 0x20);

	class __declspec(novtable) TESCombatStyle :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESCombatStyle };
		static constexpr auto VTABLE{ VTABLE::TESCombatStyle };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCSTY };

		// members
		CombatStyleGeneralData generalData;        // 20
		CombatStyleMeleeData meleeData;            // 50
		CombatStyleRangedData rangedData;          // 78
		CombatStyleCloseRangeData closeRangeData;  // 7C
		CombatStyleLongRangeData longRangeData;    // A8
		CombatStyleCoverData coverData;            // BC
		CombatStyleFlightData flightData;          // C0
		std::uint32_t flags;                       // E0
	};
	static_assert(sizeof(TESCombatStyle) == 0xE8);
}
