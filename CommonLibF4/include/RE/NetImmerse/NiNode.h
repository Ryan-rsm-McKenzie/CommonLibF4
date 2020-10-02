#pragma once

#include "RE/Bethesda/Atomic.h"
#include "RE/NetImmerse/NiAVObject.h"
#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/NetImmerse/NiTArray.h"

namespace RE
{
	class __declspec(novtable) NiNode :
		public NiAVObject  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::NiNode };
		static constexpr auto VTABLE{ VTABLE::NiNode };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiNode };

		NiNode() :
			NiNode(0)
		{}

		NiNode(std::uint32_t a_numChildren) :
			children(a_numChildren)
		{
			emplace_vtable(this);
			REL::Relocation<std::uintptr_t> childrenVTable{ REL::ID(390064) };
			reinterpret_cast<std::uintptr_t&>(children) = childrenVTable.address();
		}

		// override (NiAVObject)
		const NiRTTI* GetRTTI() const override	// 02
		{
			REL::Relocation<const NiRTTI*> rtti{ Ni_RTTI };
			return rtti.get();
		}

		NiNode* IsNode() override { return this; }				// 04
		const NiNode* IsNode() const override { return this; }	// 03

		NiObject* CreateClone(NiCloningProcess& a_cloneData) override  // 1A
		{
			using func_t = decltype(&NiNode::CreateClone);
			REL::Relocation<func_t> func{ REL::ID(262609) };
			return func(this, a_cloneData);
		}

		void LoadBinary(NiStream& a_stream) override  // 1B
		{
			using func_t = decltype(&NiNode::LoadBinary);
			REL::Relocation<func_t> func{ REL::ID(594600) };
			return func(this, a_stream);
		}

		void LinkObject(NiStream& a_stream) override  // 1C
		{
			using func_t = decltype(&NiNode::LinkObject);
			REL::Relocation<func_t> func{ REL::ID(1206045) };
			return func(this, a_stream);
		}

		bool RegisterStreamables(NiStream& a_stream) override  // 1D
		{
			using func_t = decltype(&NiNode::RegisterStreamables);
			REL::Relocation<func_t> func{ REL::ID(846539) };
			return func(this, a_stream);
		}

		void SaveBinary(NiStream& a_stream) override  // 1E
		{
			using func_t = decltype(&NiNode::SaveBinary);
			REL::Relocation<func_t> func{ REL::ID(48456) };
			return func(this, a_stream);
		}

		bool IsEqual(NiObject* a_object) override  // 1F
		{
			using func_t = decltype(&NiNode::IsEqual);
			REL::Relocation<func_t> func{ REL::ID(832847) };
			return func(this, a_object);
		}

		void ProcessClone(NiCloningProcess& a_cloning) override	 // 20
		{
			using func_t = decltype(&NiNode::ProcessClone);
			REL::Relocation<func_t> func{ REL::ID(39314) };
			return func(this, a_cloning);
		}

		NiAVObject* GetObjectByName(const BSFixedString& a_name) override  // 2E
		{
			using func_t = decltype(&NiNode::GetObjectByName);
			REL::Relocation<func_t> func{ REL::ID(1068190) };
			return func(this, a_name);
		}

		void SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid) override	 // 2F
		{
			using func_t = decltype(&NiNode::SetSelectiveUpdateFlags);
			REL::Relocation<func_t> func{ REL::ID(1196889) };
			return func(this, a_selectiveUpdate, a_selectiveUpdateTransforms, a_rigid);
		}

		void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags) override  // 30
		{
			using func_t = decltype(&NiNode::UpdateDownwardPass);
			REL::Relocation<func_t> func{ REL::ID(1054506) };
			return func(this, a_data, a_flags);
		}

		void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags) override  // 31
		{
			using func_t = decltype(&NiNode::UpdateSelectedDownwardPass);
			REL::Relocation<func_t> func{ REL::ID(415327) };
			return func(this, a_data, a_flags);
		}

		void UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags) override	// 32
		{
			using func_t = decltype(&NiNode::UpdateRigidDownwardPass);
			REL::Relocation<func_t> func{ REL::ID(547310) };
			return func(this, a_data, a_flags);
		}

		void UpdateWorldBound() override  // 33
		{
			using func_t = decltype(&NiNode::UpdateWorldBound);
			REL::Relocation<func_t> func{ REL::ID(1438211) };
			return func(this);
		}

		void UpdateTransformAndBounds(NiUpdateData& a_data) override  // 35
		{
			using func_t = decltype(&NiNode::UpdateTransformAndBounds);
			REL::Relocation<func_t> func{ REL::ID(971882) };
			return func(this, a_data);
		}

		void UpdateTransforms(NiUpdateData& a_data) override  // 36
		{
			using func_t = decltype(&NiNode::UpdateTransforms);
			REL::Relocation<func_t> func{ REL::ID(692605) };
			return func(this, a_data);
		}

		void OnVisible(NiCullingProcess& a_culler) override	 // 39
		{
			using func_t = decltype(&NiNode::OnVisible);
			REL::Relocation<func_t> func{ REL::ID(599197) };
			return func(this, a_culler);
		}

		// add
		virtual void AttachChild(NiAVObject* a_child, bool a_firstAvail)  // 3A
		{
			using func_t = decltype(&NiNode::AttachChild);
			REL::Relocation<func_t> func{ REL::ID(273401) };
			return func(this, a_child, a_firstAvail);
		}

		virtual void InsertChildAt(std::uint32_t a_idx, NiAVObject* a_child)  // 3B
		{
			using func_t = decltype(&NiNode::InsertChildAt);
			REL::Relocation<func_t> func{ REL::ID(1230429) };
			return func(this, a_idx, a_child);
		}

		virtual void DetachChild(NiAVObject* a_child)  // 3D
		{
			using func_t = void (NiNode::*)(NiAVObject*);
			REL::Relocation<func_t> func{ REL::ID(1576045) };
			return func(this, a_child);
		}

		virtual void DetachChild(NiAVObject* a_child, NiPointer<NiAVObject>& a_avObject)  // 3C
		{
			using func_t = void (NiNode::*)(NiAVObject*, NiPointer<NiAVObject>&);
			REL::Relocation<func_t> func{ REL::ID(166504) };
			return func(this, a_child, a_avObject);
		}

		virtual void DetachChildAt(std::uint32_t a_idx)	 // 3F
		{
			using func_t = void (NiNode::*)(std::uint32_t);
			REL::Relocation<func_t> func{ REL::ID(1295946) };
			return func(this, a_idx);
		}

		virtual void DetachChildAt(std::uint32_t a_idx, NiPointer<NiAVObject>& a_avObject)	// 3E
		{
			using func_t = void (NiNode::*)(std::uint32_t, NiPointer<NiAVObject>&);
			REL::Relocation<func_t> func{ REL::ID(1468998) };
			return func(this, a_idx, a_avObject);
		}

		virtual void SetAt(std::uint32_t a_idx, NiAVObject* a_child)  // 41
		{
			using func_t = void (NiNode::*)(std::uint32_t, NiAVObject*);
			REL::Relocation<func_t> func{ REL::ID(657350) };
			return func(this, a_idx, a_child);
		}

		virtual void SetAt(std::uint32_t a_idx, NiAVObject* a_child, NiPointer<NiAVObject>& a_avObject)	 // 40
		{
			using func_t = void (NiNode::*)(std::uint32_t, NiAVObject*, NiPointer<NiAVObject>&);
			REL::Relocation<func_t> func{ REL::ID(829835) };
			return func(this, a_idx, a_child, a_avObject);
		}

		virtual void UpdateUpwardPass(NiUpdateData& a_data)	 // 42
		{
			using func_t = decltype(&NiNode::UpdateUpwardPass);
			REL::Relocation<func_t> func{ REL::ID(1265615) };
			return func(this, a_data);
		}

		F4_HEAP_REDEFINE_ALIGNED_NEW(NiNode);

		// members
		NiTObjectArray<NiPointer<NiAVObject>> children;	 // 120
		BSTAtomicValue<std::uint32_t> dirtyState;		 // 138
		float meshLODFadeAmount{ 0.0F };				 // 13C
	};
	static_assert(sizeof(NiNode) == 0x140);
}
