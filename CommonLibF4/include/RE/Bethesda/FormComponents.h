#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	class BaseFormComponent;
	class BGSCraftingUseSound;
	class BGSPreviewTransform;
	class BGSSoundTagComponent;
	class TESFullName;
	class TESValueForm;

	namespace BGSMod
	{
		namespace Template
		{
			class Item;
			class Items;
		}
	}

	class BGSKeyword;
	class BGSSoundDescriptorForm;
	class BGSTransform;
	class TESForm;

	class BaseFormComponent
	{
	public:
		static constexpr auto RTTI{ RTTI_BaseFormComponent };

		virtual ~BaseFormComponent() = default;	 // 00

		F4_HEAP_REDEFINE_NEW(BaseFormComponent);

		// add
		virtual std::uint32_t GetFormComponentType() const { return 0; }													   // 01
		virtual void InitializeDataComponent() = 0;																			   // 02
		virtual void ClearDataComponent() = 0;																				   // 03
		virtual void InitComponent() { return; }																			   // 04
		virtual void CopyComponent([[maybe_unused]] BaseFormComponent* a_copy) { return; }									   // 06
		virtual void CopyComponent([[maybe_unused]] BaseFormComponent* a_copy, [[maybe_unused]] TESForm* a_owner) { return; }  // 05
	};
	static_assert(sizeof(BaseFormComponent) == 0x8);

	class BGSCraftingUseSound :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSCraftingUseSound };

		// members
		BGSSoundDescriptorForm* craftingUseSound;  // 08
	};
	static_assert(sizeof(BGSCraftingUseSound) == 0x10);

	class BGSPreviewTransform :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSPreviewTransform };

		// override (BaseFormComponent)
		virtual std::uint32_t GetFormComponentType() const override { return 'NRTP'; }	   // 01
		virtual void InitializeDataComponent() override { transform = nullptr; }		   // 02
		virtual void ClearDataComponent() override { return; }							   // 03
		virtual void InitComponent() override;											   // 04
		virtual void CopyComponent(BaseFormComponent*) override { return; }				   // 06
		virtual void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override;  // 05

		// members
		BGSTransform* transform;  // 08
	};
	static_assert(sizeof(BGSPreviewTransform) == 0x10);

	class BGSSoundTagComponent :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSSoundTagComponent };

		// override (BaseFormComponent)
		virtual std::uint32_t GetFormComponentType() const override { return 'CTAC'; }	   // 01
		virtual void InitializeDataComponent() override { return; }						   // 02
		virtual void ClearDataComponent() override;										   // 03
		virtual void InitComponent() override;											   // 04
		virtual void CopyComponent(BaseFormComponent*) override { return; }				   // 06
		virtual void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override;  // 05
	};
	static_assert(sizeof(BGSSoundTagComponent) == 0x8);

	class TESFullName :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESFullName };

		// add
		virtual std::uint32_t GetFullNameLength() const { return fullName.length(); }  // 07
		virtual const char* GetFullName() const { return fullName.c_str(); }		   // 08

		[[nodiscard]] static const char* GetFullName(const TESForm* a_obj);

		// members
		BGSLocalizedString fullName;  // 08
	};
	static_assert(sizeof(TESFullName) == 0x10);

	class TESValueForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESValueForm };

		// members
		std::int32_t value;	 // 08
	};
	static_assert(sizeof(TESValueForm) == 0x10);

	namespace BGSMod
	{
		struct Container :
			public BSTDataBuffer<2, BSDataBufferHeapAllocator>	// 00
		{
		public:
			static constexpr auto RTTI{ RTTI_BGSMod__Container };
		};
		static_assert(sizeof(Container) == 0x10);

		namespace Template
		{
			class Item :
				public TESFullName,		  // 00
				public BGSMod::Container  // 10
			{
			public:
				static constexpr auto RTTI{ RTTI_BGSMod__Template__Item };

				// members
				BGSMod::Template::Items* parentTemplate;  // 20
				BGSKeyword** nameKeywordA;				  // 28
				std::uint16_t parent;					  // 30
				std::int8_t levelMin;					  // 32
				std::int8_t levelMax;					  // 33
				std::int8_t keywords;					  // 34
				std::int8_t tierStartLevel;				  // 35
				std::int8_t altLevelsPerTier;			  // 36
				bool isDefault : 1;						  // 37:1
				bool fullNameEditorOnly : 1;			  // 37:2
			};
			static_assert(sizeof(Item) == 0x38);

			class Items :
				public BaseFormComponent  // 00
			{
			public:
				static constexpr auto RTTI{ RTTI_BGSMod__Template__Items };

				// override (BaseFormComponent)
				virtual std::uint32_t GetFormComponentType() const override { return 'TJBO'; }	   // 01
				virtual void InitializeDataComponent() override { return; }						   // 02
				virtual void ClearDataComponent() override;										   // 03
				virtual void InitComponent() override;											   // 04
				virtual void CopyComponent(BaseFormComponent*) override { return; }				   // 06
				virtual void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override;  // 05

				// members
				BSTArray<Item*> items;	// 08
			};
			static_assert(sizeof(Items) == 0x20);
		}
	}
}
