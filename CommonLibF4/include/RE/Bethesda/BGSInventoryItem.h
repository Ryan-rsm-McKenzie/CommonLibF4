#pragma once

#include "RE/Bethesda/BSExtraData.h"
#include "RE/Bethesda/BSTSmartPointer.h"

namespace RE
{
	namespace BGSMod
	{
		namespace Attachment
		{
			class Mod;
		}
	}

	class TESBoundObject;

	class BGSInventoryItem
	{
	public:
		class __declspec(novtable) Stack :
			public BSIntrusiveRefCounted  // 08
		{
		public:
			static constexpr auto RTTI{ RTTI::BGSInventoryItem__Stack };
			static constexpr auto VTABLE{ VTABLE::BGSInventoryItem__Stack };

			enum class Flag
			{
				kSlotIndex1 = 1 << 0,
				kSlotIndex2 = 1 << 1,
				kSlotIndex3 = 1 << 2,
				kEquipStateLocked = 1 << 3,
				kInvShouldEquip = 1 << 4,
				kTemporary = 1 << 5,
				kSlotMask = kSlotIndex1 | kSlotIndex2 | kSlotIndex3
			};

			virtual ~Stack();  // 00

			[[nodiscard]] std::uint32_t GetCount() const noexcept { return count; }
			[[nodiscard]] bool IsEquipped() const noexcept { return flags.any(Flag::kSlotMask); }

			// members
			BSTSmartPointer<Stack> nextStack;             // 10
			BSTSmartPointer<ExtraDataList> extra;         // 18
			std::uint32_t count;                          // 20
			stl::enumeration<Flag, std::uint16_t> flags;  // 24
		};
		static_assert(sizeof(Stack) == 0x28);

		class __declspec(novtable) StackDataCompareFunctor
		{
		public:
			static constexpr auto RTTI{ RTTI::BGSInventoryItem__StackDataCompareFunctor };
			static constexpr auto VTABLE{ VTABLE::BGSInventoryItem__StackDataCompareFunctor };

			// add
			virtual bool CompareData(const BGSInventoryItem::Stack& a_stack) = 0;  // 00
			virtual bool UseDefaultStackIfNoMatch() const { return false; }        // 01
		};
		static_assert(sizeof(StackDataCompareFunctor) == 0x8);

		class CheckStackIDFunctor :
			public StackDataCompareFunctor  // 00
		{
		public:
			static constexpr auto RTTI{ RTTI::BGSInventoryItem__CheckStackIDFunctor };
			static constexpr auto VTABLE{ VTABLE::BGSInventoryItem__CheckStackIDFunctor };

			CheckStackIDFunctor(std::uint32_t a_targetIndex) noexcept :
				targetIndex(a_targetIndex)
			{}

			// override (StackDataCompareFunctor)
			bool CompareData(const BGSInventoryItem::Stack&) override { return targetIndex-- == 0; }  // 00

			// members
			std::uint32_t targetIndex;  // 08
		};
		static_assert(sizeof(CheckStackIDFunctor) == 0x10);

		class __declspec(novtable) StackDataWriteFunctor
		{
		public:
			static constexpr auto RTTI{ RTTI::BGSInventoryItem__StackDataWriteFunctor };
			static constexpr auto VTABLE{ VTABLE::BGSInventoryItem__StackDataWriteFunctor };

			// add
			virtual void WriteDataImpl(TESBoundObject& a_baseObj, BGSInventoryItem::Stack& a_stack) = 0;  // 01

			// members
			bool shouldSplitStacks{ true };              // 08
			bool transferEquippedToSplitStack{ false };  // 09
		};
		static_assert(sizeof(StackDataWriteFunctor) == 0x10);

		class __declspec(novtable) ModifyModDataFunctor :
			public StackDataWriteFunctor  // 00
		{
		public:
			static constexpr auto RTTI{ RTTI::BGSInventoryItem__ModifyModDataFunctor };
			static constexpr auto VTABLE{ VTABLE::BGSInventoryItem__ModifyModDataFunctor };

			ModifyModDataFunctor(BGSMod::Attachment::Mod* a_mod, std::int8_t a_slotIndex, bool a_attach, bool* a_success) :
				mod(a_mod),
				success(a_success),
				slotIndex(a_slotIndex),
				attach(a_attach)
			{
				stl::emplace_vtable(this);
				if (success) {
					*success = true;
				}
			}

			// override (StackDataWriteFunctor)
			void WriteDataImpl(TESBoundObject&, BGSInventoryItem::Stack&) override;  // 01

			// members
			BGSMod::Attachment::Mod* mod;         // 10
			TESBoundObject* foundObj{ nullptr };  // 18
			bool* success;                        // 20
			const std::int8_t slotIndex;          // 28
			const bool attach;                    // 29
			bool equipLocked{ false };            // 2A
		};
		static_assert(sizeof(ModifyModDataFunctor) == 0x30);

		[[nodiscard]] std::uint32_t GetCount() const noexcept;
		[[nodiscard]] Stack* GetStackByID(std::uint32_t a_stackID) const
		{
			auto iter = stackData.get();
			while (a_stackID--) {
				iter = iter->nextStack.get();
			}

			return iter;
		}

		// members
		TESBoundObject* object;            // 00
		BSTSmartPointer<Stack> stackData;  // 08
	};
	static_assert(sizeof(BGSInventoryItem) == 0x10);
}
