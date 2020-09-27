#pragma once

#include "RE/NetImmerse/NiBound.h"
#include "RE/NetImmerse/NiFlags.h"
#include "RE/NetImmerse/NiObjectNET.h"
#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/NetImmerse/NiTransform.h"

namespace RE
{
	class NiAlphaProperty;
	class NiCollisionObject;
	class NiCullingProcess;
	class NiNode;
	class NiUpdateData;
	class PerformOpFunc;

	class NiAVObject :
		public NiObjectNET	// 000
	{
	public:
		static constexpr auto RTTI{ RTTI::NiAVObject };
		static constexpr auto VTABLE{ VTABLE::NiAVObject };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiAVObject };

		NiAVObject();
		virtual ~NiAVObject();

		// override (NiObjectNET)
		const NiRTTI* GetRTTI() const override	// 02
		{
			REL::Relocation<const NiRTTI*> rtti{ Ni_RTTI };
			return rtti.get();
		}

		void LoadBinary(NiStream& a_stream) override  // 1B
		{
			using func_t = decltype(&NiAVObject::LoadBinary);
			REL::Relocation<func_t> func{ REL::ID(866892) };
			return func(this, a_stream);
		}

		void LinkObject(NiStream& a_stream) override  // 1C
		{
			using func_t = decltype(&NiAVObject::LinkObject);
			REL::Relocation<func_t> func{ REL::ID(1119260) };
			return func(this, a_stream);
		}

		bool RegisterStreamables(NiStream& a_stream) override  // 1D
		{
			using func_t = decltype(&NiAVObject::RegisterStreamables);
			REL::Relocation<func_t> func{ REL::ID(1464982) };
			return func(this, a_stream);
		}

		void SaveBinary(NiStream& a_stream) override  // 1E
		{
			using func_t = decltype(&NiAVObject::SaveBinary);
			REL::Relocation<func_t> func{ REL::ID(493929) };
			return func(this, a_stream);
		}

		bool IsEqual(NiObject* a_object) override  // 1F
		{
			using func_t = decltype(&NiAVObject::IsEqual);
			REL::Relocation<func_t> func{ REL::ID(134822) };
			return func(this, a_object);
		}

		void ProcessClone(NiCloningProcess& a_cloning) override	 // 20
		{
			using func_t = decltype(&NiAVObject::ProcessClone);
			REL::Relocation<func_t> func{ REL::ID(1033683) };
			return func(this, a_cloning);
		}

		void PostLinkObject(NiStream& a_stream) override { NiObject::PostLinkObject(a_stream); }  // 21

		// add
		virtual void UpdateControllers(NiUpdateData& a_data)  // 28
		{
			using func_t = decltype(&NiAVObject::UpdateControllers);
			REL::Relocation<func_t> func{ REL::ID(639515) };
			return func(this, a_data);
		}

		virtual void PerformOp(PerformOpFunc& a_operation)	// 29
		{
			using func_t = decltype(&NiAVObject::PerformOp);
			REL::Relocation<func_t> func{ REL::ID(1251001) };
			return func(this, a_operation);
		}

		virtual void AttachProperty([[maybe_unused]] NiAlphaProperty* a_prop) { return; }  // 2A
		virtual void SetMaterialNeedsUpdate(bool) { return; }							   // 2B
		virtual void SetDefaultMaterialNeedsUpdateFlag(bool) { return; }				   // 2C

		virtual void SetAppCulled(bool a_appCulled)	 // 2D
		{
			using func_t = decltype(&NiAVObject::SetAppCulled);
			REL::Relocation<func_t> func{ REL::ID(1423392) };
			return func(this, a_appCulled);
		}

		virtual NiAVObject* GetObjectByName(const BSFixedString& a_name) { return name == a_name ? this : nullptr; }  // 2E

		virtual void SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid)	// 2F
		{
			using func_t = decltype(&NiAVObject::SetSelectiveUpdateFlags);
			REL::Relocation<func_t> func{ REL::ID(625770) };
			return func(this, a_selectiveUpdate, a_selectiveUpdateTransforms, a_rigid);
		}

		virtual void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags)  // 30
		{
			using func_t = decltype(&NiAVObject::UpdateDownwardPass);
			REL::Relocation<func_t> func{ REL::ID(438836) };
			return func(this, a_data, a_flags);
		}

		virtual void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags)  // 31
		{
			using func_t = decltype(&NiAVObject::UpdateSelectedDownwardPass);
			REL::Relocation<func_t> func{ REL::ID(1223553) };
			return func(this, a_data, a_flags);
		}

		virtual void UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags)  // 32
		{
			using func_t = decltype(&NiAVObject::UpdateRigidDownwardPass);
			REL::Relocation<func_t> func{ REL::ID(1036685) };
			return func(this, a_data, a_flags);
		}

		virtual void UpdateWorldBound() { return; }	 // 33

		virtual void UpdateWorldData(NiUpdateData* a_data)	// 34
		{
			using func_t = decltype(&NiAVObject::UpdateWorldData);
			REL::Relocation<func_t> func{ REL::ID(850280) };
			return func(this, a_data);
		}

		virtual void UpdateTransformAndBounds(NiUpdateData& a_data)	 // 35
		{
			using func_t = decltype(&NiAVObject::UpdateTransformAndBounds);
			REL::Relocation<func_t> func{ REL::ID(263314) };
			return func(this, a_data);
		}

		virtual void UpdateTransforms(NiUpdateData& a_data) { UpdateWorldData(std::addressof(a_data)); }  // 36

		virtual void PreAttachUpdate(NiNode* a_eventualParent, NiUpdateData& a_data)  // 37
		{
			using func_t = decltype(&NiAVObject::PreAttachUpdate);
			REL::Relocation<func_t> func{ REL::ID(170292) };
			return func(this, a_eventualParent, a_data);
		}

		virtual void PostAttachUpdate()	 // 38
		{
			using func_t = decltype(&NiAVObject::PostAttachUpdate);
			REL::Relocation<func_t> func{ REL::ID(342683) };
			return func(this);
		}

		virtual void OnVisible([[maybe_unused]] NiCullingProcess& a_culler) { return; }	 // 39

		F4_HEAP_REDEFINE_ALIGNED_NEW(NiAVObject);

		// members
		NiNode* parent{ nullptr };					   // 027
		NiTransform local;							   // 030
		NiTransform world;							   // 070
		NiBound worldBound;							   // 0B0
		NiTransform previousWorld;					   // 0C0
		NiPointer<NiCollisionObject> collisionObject;  // 100
		NiTFlags<std::uint64_t, NiAVObject> flags;	   // 108
		std::uintptr_t userData{ 0 };				   // 110
		float fadeAmount{ 1.0F };					   // 118
		std::int8_t multType{ 0 };					   // 11C
		std::int8_t meshLODFadingLevel{ 0 };		   // 11D
		std::int8_t currentMeshLODLevel{ 0 };		   // 11E
		std::int8_t previousMeshLODLevel{ 0 };		   // 11F
	};
	static_assert(sizeof(NiAVObject) == 0x120);
}
