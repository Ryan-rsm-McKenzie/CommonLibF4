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

		// add
		void UpdateControllers(NiUpdateData& a_data);															 // 28
		void PerformOp(PerformOpFunc& a_operation);																 // 29
		void AttachProperty([[maybe_unused]] NiAlphaProperty* a_prop) { return; }								 // 2A
		void SetMaterialNeedsUpdate(bool) { return; }															 // 2B
		void SetDefaultMaterialNeedsUpdateFlag(bool) { return; }												 // 2C
		void SetAppCulled(bool a_appCulled);																	 // 2D
		NiAVObject* GetObjectByName(const BSFixedString& a_name) { return name == a_name ? this : nullptr; }	 // 2E
		void SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid);	 // 2F
		void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags);									 // 30
		void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags);							 // 31
		void UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags);								 // 32
		void UpdateWorldBound() { return; }																		 // 33
		void UpdateWorldData(NiUpdateData* a_data);																 // 34
		void UpdateTransformAndBounds(NiUpdateData& a_data);													 // 35
		void UpdateTransforms(NiUpdateData& a_data) { UpdateWorldData(std::addressof(a_data)); }				 // 36
		void PreAttachUpdate(NiNode* a_eventualParent, NiUpdateData& a_data);									 // 37
		void PostAttachUpdate();																				 // 38
		void OnVisible([[maybe_unused]] NiCullingProcess& a_culler) { return; }									 // 39

		// members
		NiNode* parent;								   // 027
		NiTransform local;							   // 030
		NiTransform world;							   // 070
		NiBound worldBound;							   // 0B0
		NiTransform previousWorld;					   // 0C0
		NiPointer<NiCollisionObject> collisionObject;  // 100
		NiTFlags<std::uint64_t, NiAVObject> flags;	   // 108
		std::uintptr_t userData;					   // 110
		float fadeAmount;							   // 118
		std::int8_t multType;						   // 11C
		std::int8_t meshLODFadingLevel;				   // 11D
		std::int8_t currentMeshLODLevel;			   // 11E
		std::int8_t previousMeshLODLevel;			   // 11F
	};
	static_assert(sizeof(NiAVObject) == 0x120);
}
