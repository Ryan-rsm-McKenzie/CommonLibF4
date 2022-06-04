#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/FormComponents.h"
#include "RE/Bethesda/TESBoundObjects.h"
#include "RE/Bethesda/TESCondition.h"

namespace RE
{
	class QueuedFile;

	struct EffectItemData
	{
	public:
		// members
		float magnitude;        // 0
		std::int32_t area;      // 4
		std::int32_t duration;  // 8
	};
	static_assert(sizeof(EffectItemData) == 0xC);

	class EffectItem
	{
	public:
		// members
		EffectItemData data;           // 00
		EffectSetting* effectSetting;  // 10
		float rawCost;                 // 18
		TESCondition conditions;       // 20
	};
	static_assert(sizeof(EffectItem) == 0x28);

	class __declspec(novtable) MagicItem :
		public TESBoundObject,  // 00
		public TESFullName,     // 68
		public BGSKeywordForm   // 70
	{
	public:
		static constexpr auto RTTI{ RTTI::MagicItem };
		static constexpr auto VTABLE{ VTABLE::MagicItem };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kNONE };

		struct SkillUsageData
		{
		public:
			// members
			EffectItem* effect;     // 00
			ActorValueInfo* skill;  // 08
			float magnitude;        // 10
			bool custom;            // 14
		};
		static_assert(sizeof(SkillUsageData) == 0x18);

		class Data
		{
		public:
			// members
			std::int32_t costOverride;  // 0
			std::uint32_t flags;        // 4
		};
		static_assert(sizeof(Data) == 0x8);

		// add
		virtual MagicSystem::SpellType GetSpellType() const = 0;                                                            // 67
		virtual void SetCastingType([[maybe_unused]] MagicSystem::CastingType a_castingType) { return; }                    // 68
		virtual MagicSystem::CastingType GetCastingType() const = 0;                                                        // 69
		virtual void SetDelivery([[maybe_unused]] MagicSystem::Delivery a_delivery) { return; }                             // 6A
		virtual MagicSystem::Delivery GetDelivery() const = 0;                                                              // 6B
		virtual bool IsValidDelivery(MagicSystem::Delivery) { return true; }                                                // 6C
		virtual float GetFixedCastDuration() const { return 0.0F; }                                                         // 6D
		virtual float GetRange() const { return 0.0F; }                                                                     // 6E
		virtual bool IgnoreResistance() const { return false; }                                                             // 6F
		virtual bool IgnoreLOS() const { return false; }                                                                    // 70
		virtual bool IsFood() const { return false; }                                                                       // 71
		virtual bool GetNoAbsorb() const { return false; }                                                                  // 72
		virtual bool GetNoDualCastModifications() const { return false; }                                                   // 73
		virtual bool GetSkillUsageData([[maybe_unused]] SkillUsageData& a_data) const { return false; }                     // 74
		virtual bool IsPoison() const;                                                                                      // 75
		virtual bool IsMedicine() const { return false; }                                                                   // 76
		virtual void AdjustCost(float&, Actor*) const { return; }                                                           // 77
		virtual float GetChargeTime() const { return 0.0F; }                                                                // 78
		virtual std::uint32_t GetMaxEffectCount() const { return 0; }                                                       // 79
		virtual ActorValueInfo* GetAssociatedSkill() const { return nullptr; }                                              // 7A
		virtual bool IsTwoHanded() const { return false; }                                                                  // 7B
		virtual CHUNK_ID GetChunkID() = 0;                                                                                  // 7C
		virtual void CopyMagicItemData(MagicItem* a_copy) = 0;                                                              // 7D
		virtual void LoadMagicItemChunk([[maybe_unused]] TESFile* a_file, [[maybe_unused]] CHUNK_ID a_chunkID) { return; }  // 7E
		virtual void LoadChunkDataPostProcess([[maybe_unused]] TESFile* a_file) { return; }                                 // 7F
		virtual Data* GetData() = 0;                                                                                        // 81
		virtual const Data* GetData() const = 0;                                                                            // 80
		virtual std::size_t GetDataSize() const = 0;                                                                        // 82
		virtual void InitFromChunk(TESFile* a_file) = 0;                                                                    // 83

		// members
		BSTArray<EffectItem*> listOfEffects;                                         // 98
		std::int32_t hostileCount;                                                   // B0
		EffectSetting* avEffectSetting;                                              // B8
		std::uint32_t preloadCount;                                                  // C0
		BSTSmartPointer<QueuedFile, BSTSmartPointerGamebryoRefCount> preloadedItem;  // C8
	};
	static_assert(sizeof(MagicItem) == 0xD0);

	class __declspec(novtable) EnchantmentItem :
		public MagicItem  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::EnchantmentItem };
		static constexpr auto VTABLE{ VTABLE::EnchantmentItem };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kENCH };

		class Data :
			public MagicItem::Data  // 00
		{
		public:
			// members
			stl::enumeration<MagicSystem::CastingType, std::int32_t> castingType;  // 08
			std::int32_t chargeOverride;                                           // 0C
			stl::enumeration<MagicSystem::Delivery, std::int32_t> delivery;        // 10
			stl::enumeration<MagicSystem::SpellType, std::int32_t> spellType;      // 14
			float chargeTime;                                                      // 18
			EnchantmentItem* baseEnchantment;                                      // 20
			BGSListForm* wornRestrictions;                                         // 28
		};
		static_assert(sizeof(Data) == 0x30);

		// members
		Data data;  // 0D0
	};
	static_assert(sizeof(EnchantmentItem) == 0x100);

	class __declspec(novtable) SpellItem :
		public MagicItem,             // 000
		public BGSEquipType,          // 0D0
		public BGSMenuDisplayObject,  // 0E0
		public TESDescription         // 0F0
	{
	public:
		static constexpr auto RTTI{ RTTI::SpellItem };
		static constexpr auto VTABLE{ VTABLE::SpellItem };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSPEL };

		class Data :
			public MagicItem::Data  // 00
		{
		public:
			// members
			stl::enumeration<MagicSystem::SpellType, std::int32_t> spellType;      // 08
			float chargeTime;                                                      // 0C
			stl::enumeration<MagicSystem::CastingType, std::int32_t> castingType;  // 10
			stl::enumeration<MagicSystem::Delivery, std::int32_t> delivery;        // 14
			float castDuration;                                                    // 18
			float range;                                                           // 1C
			BGSPerk* castingPerk;                                                  // 20
		};
		static_assert(sizeof(Data) == 0x28);

		// members
		Data data;  // 108
	};
	static_assert(sizeof(SpellItem) == 0x130);

	class __declspec(novtable) ScrollItem :
		public SpellItem,                  // 000
		public BGSModelMaterialSwap,       // 130
		public BGSDestructibleObjectForm,  // 170
		public BGSPickupPutdownSounds,     // 180
		public TESWeightForm,              // 198
		public TESValueForm                // 1A8
	{
	public:
		static constexpr auto RTTI{ RTTI::ScrollItem };
		static constexpr auto VTABLE{ VTABLE::ScrollItem };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kSCRL };
	};
	static_assert(sizeof(ScrollItem) == 0x1B8);

	class __declspec(novtable) IngredientItem :
		public MagicItem,                  // 000
		public BGSModelMaterialSwap,       //0D0
		public TESIcon,                    // 110
		public TESWeightForm,              // 120
		public BGSEquipType,               // 130
		public BGSDestructibleObjectForm,  // 140
		public BGSPickupPutdownSounds,     // 150
		public TESValueForm                // 168
	{
	public:
		static constexpr auto RTTI{ RTTI::IngredientItem };
		static constexpr auto VTABLE{ VTABLE::IngredientItem };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kINGR };

		struct GameData
		{
		public:
			// members
			std::uint16_t knownEffectFlags;  // 0
			std::uint16_t playerUses;        // 2
		};
		static_assert(sizeof(GameData) == 0x4);

		// members
		MagicItem::Data data;  // 178
		GameData gamedata;     // 180
	};
	static_assert(sizeof(IngredientItem) == 0x188);

	class __declspec(novtable) AlchemyItem :
		public MagicItem,                  // 000
		public BGSModelMaterialSwap,       // 0D0
		public TESIcon,                    // 110
		public BGSMessageIcon,             // 120
		public TESWeightForm,              // 138
		public BGSEquipType,               // 148
		public BGSDestructibleObjectForm,  // 158
		public BGSPickupPutdownSounds,     // 168
		public BGSCraftingUseSound,        // 180
		public TESDescription              // 190
	{
	public:
		static constexpr auto RTTI{ RTTI::AlchemyItem };
		static constexpr auto VTABLE{ VTABLE::AlchemyItem };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kALCH };

		class Data :
			public MagicItem::Data  // 00
		{
		public:
			// members
			SpellItem* addictionItem;                  // 08
			float addictionChance;                     // 10
			BGSSoundDescriptorForm* consumptionSound;  // 18
			BGSLocalizedString addictionName;          // 20
		};
		static_assert(sizeof(Data) == 0x28);

		// members
		Data data;            // 1A8
		TESIcon messageIcon;  // 1D0
	};
	static_assert(sizeof(AlchemyItem) == 0x1E0);
}
