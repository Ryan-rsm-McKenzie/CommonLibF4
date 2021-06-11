#pragma once

namespace RE
{
	class __declspec(novtable) BSAwardsSystemUtility
	{
	public:
		static constexpr auto RTTI{ RTTI::BSAwardsSystemUtility };
		static constexpr auto VTABLE{ VTABLE::BSAwardsSystemUtility };

		virtual ~BSAwardsSystemUtility() {}  // 00

		[[nodiscard]] static BSAwardsSystemUtility& GetSingleton()
		{
			using func_t = decltype(&BSAwardsSystemUtility::GetSingleton);
			REL::Relocation<func_t> func{ REL::ID(1569384) };
			return func();
		}

		// add
		virtual void DoInitialize() { return; }                                     // 01
		virtual void DoClearAward([[maybe_unused]] std::int32_t a_id) { return; }   // 02
		virtual void DoDestroy() { return; }                                        // 03
		virtual void DoRegister() { return; }                                       // 04
		virtual void DoUnlockAward([[maybe_unused]] std::int32_t a_id) { return; }  // 05
		virtual bool DoGetUltimateAwardEarned() const { return false; }             // 06
	};
	static_assert(sizeof(BSAwardsSystemUtility) == 0x8);

	class __declspec(novtable) BSSteamAwardsSystemUtility :
		public BSAwardsSystemUtility  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSSteamAwardsSystemUtility };
		static constexpr auto VTABLE{ VTABLE::BSSteamAwardsSystemUtility };

		virtual ~BSSteamAwardsSystemUtility() {}  // 00
	};
	static_assert(sizeof(BSSteamAwardsSystemUtility) == 0x8);
}
