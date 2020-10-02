#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/NetImmerse/NiObject.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class NiExtraDataContainer;
	class NiTimeController;

	class __declspec(novtable) NiObjectNET :
		public NiObject	 // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::NiObjectNET };
		static constexpr auto VTABLE{ VTABLE::NiObjectNET };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiObjectNET };

		NiObjectNET();
		virtual ~NiObjectNET();	 // 00

		// override (NiObject)
		const NiRTTI* GetRTTI() const override	// 02
		{
			REL::Relocation<const NiRTTI*> rtti{ Ni_RTTI };
			return rtti.get();
		}

		void LoadBinary(NiStream& a_stream) override  // 1B
		{
			using func_t = decltype(&NiObjectNET::LoadBinary);
			REL::Relocation<func_t> func{ REL::ID(534848) };
			return func(this, a_stream);
		}

		void LinkObject(NiStream& a_stream) override  // 1C
		{
			using func_t = decltype(&NiObjectNET::LinkObject);
			REL::Relocation<func_t> func{ REL::ID(1146106) };
			return func(this, a_stream);
		}

		bool RegisterStreamables(NiStream& a_stream) override  // 1D
		{
			using func_t = decltype(&NiObjectNET::RegisterStreamables);
			REL::Relocation<func_t> func{ REL::ID(520983) };
			return func(this, a_stream);
		}

		void SaveBinary(NiStream& a_stream) override  // 1E
		{
			using func_t = decltype(&NiObjectNET::SaveBinary);
			REL::Relocation<func_t> func{ REL::ID(427507) };
			return func(this, a_stream);
		}

		bool IsEqual(NiObject* a_object) override  // 1F
		{
			using func_t = decltype(&NiObjectNET::IsEqual);
			REL::Relocation<func_t> func{ REL::ID(507157) };
			return func(this, a_object);
		}

		void ProcessClone(NiCloningProcess& a_cloning) override	 // 20
		{
			using func_t = decltype(&NiObjectNET::ProcessClone);
			REL::Relocation<func_t> func{ REL::ID(942826) };
			return func(this, a_cloning);
		}

		void PostLinkObject(NiStream& a_stream) override { NiObject::PostLinkObject(a_stream); }  // 21

		F4_HEAP_REDEFINE_NEW(NiObjectNET);

		// members
		BSFixedString name{ "" };				  // 10
		NiPointer<NiTimeController> controllers;  // 18
		NiExtraDataContainer* extra{ nullptr };	  // 20
	};
	static_assert(sizeof(NiObjectNET) == 0x28);
}
