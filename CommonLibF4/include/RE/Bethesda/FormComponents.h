#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTList.h"
#include "RE/Bethesda/BSTTuple.h"
#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	class BaseFormComponent;
	class BGSCraftingUseSound;
	class BGSPreviewTransform;
	class BGSPropertySheet;
	class BGSSoundTagComponent;
	class TESDescription;
	class TESFullName;
	class TESTexture;
	class TESIcon;
	class TESReactionForm;
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
		virtual std::uint32_t GetFormComponentType() const override { return 'NRTP'; }	// 01
		virtual void InitializeDataComponent() override { transform = nullptr; }		// 02
		virtual void ClearDataComponent() override { return; }							// 03
		virtual void InitComponent() override;											// 04
		virtual void CopyComponent(BaseFormComponent*) override { return; }				// 06
		virtual void CopyComponent(BaseFormComponent*, TESForm*) override;				// 05

		// members
		BGSTransform* transform;  // 08
	};
	static_assert(sizeof(BGSPreviewTransform) == 0x10);

	namespace BGSTypedFormValuePair
	{
		union SharedVal
		{
			std::uint32_t i;
			float f;
		};
		static_assert(sizeof(SharedVal) == 0x4);
	}

	class BGSPropertySheet :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSPropertySheet };

		// members
		BSTArray<BSTTuple<TESForm*, BGSTypedFormValuePair::SharedVal>>* properties;	 // 08
	};
	static_assert(sizeof(BGSPropertySheet) == 0x10);

	class BGSSoundTagComponent :
		public BaseFormComponent  // 0
	{
	public:
		static constexpr auto RTTI{ RTTI_BGSSoundTagComponent };

		// override (BaseFormComponent)
		virtual std::uint32_t GetFormComponentType() const override { return 'CTAC'; }	// 01
		virtual void InitializeDataComponent() override { return; }						// 02
		virtual void ClearDataComponent() override;										// 03
		virtual void InitComponent() override;											// 04
		virtual void CopyComponent(BaseFormComponent*) override { return; }				// 06
		virtual void CopyComponent(BaseFormComponent*, TESForm*) override;				// 05
	};
	static_assert(sizeof(BGSSoundTagComponent) == 0x8);

	struct BGSLocalizedStringDL
	{
	public:
		// members
		std::uint32_t id;  // 0
	};
	static_assert(sizeof(BGSLocalizedStringDL) == 0x4);

	class TESDescription :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESDescription };

		// members
		std::uint32_t fileOffset;			   // 08
		std::uint32_t chunkOffset;			   // 0C
		BGSLocalizedStringDL descriptionText;  // 10
	};
	static_assert(sizeof(TESDescription) == 0x18);

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

	class TESTexture :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESTexture };

		// override (BaseFormComponent)
		virtual void InitializeDataComponent() override;		  // 02
		virtual void ClearDataComponent() override { return; }	  // 03
		virtual void CopyComponent(BaseFormComponent*) override;  // 06

		// add
		virtual std::uint32_t GetMaxAllowedSize() { return 0; }						// 07
		virtual const char* GetAsNormalFile(BSStringT<char>& a_outFilename) const;	// 08
		virtual const char* GetDefaultPath() const { return "Textures\\"; }			// 09

		// members
		BSFixedString textureName;	// 08
	};
	static_assert(sizeof(TESTexture) == 0x10);

	class TESIcon :
		public TESTexture  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESIcon };
	};
	static_assert(sizeof(TESIcon) == 0x10);

	struct GROUP_REACTION
	{
	public:
		// members
		TESForm* form;				 // 00
		std::int32_t reaction;		 // 08
		std::int32_t fightReaction;	 // 0C
	};
	static_assert(sizeof(GROUP_REACTION) == 0x10);

	class TESReactionForm :
		public BaseFormComponent  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_TESReactionForm };

		// members
		BSSimpleList<GROUP_REACTION*> reactionList;	 // 08
		std::int8_t groupFormType;					 // 18
	};
	static_assert(sizeof(TESReactionForm) == 0x20);

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
				virtual std::uint32_t GetFormComponentType() const override { return 'TJBO'; }	// 01
				virtual void InitializeDataComponent() override { return; }						// 02
				virtual void ClearDataComponent() override;										// 03
				virtual void InitComponent() override;											// 04
				virtual void CopyComponent(BaseFormComponent*) override { return; }				// 06
				virtual void CopyComponent(BaseFormComponent*, TESForm*) override;				// 05

				// members
				BSTArray<Item*> items;	// 08
			};
			static_assert(sizeof(Items) == 0x20);
		}
	}
}
