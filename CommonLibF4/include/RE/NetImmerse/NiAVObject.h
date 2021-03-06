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

	class __declspec(novtable) NiAVObject :
		public NiObjectNET  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::NiAVObject };
		static constexpr auto VTABLE{ VTABLE::NiAVObject };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiAVObject };

		NiAVObject();
		virtual ~NiAVObject();  // NOLINT(modernize-use-override) 00

		// add
		virtual void UpdateControllers(NiUpdateData& a_data);                                                            // 28
		virtual void PerformOp(PerformOpFunc& a_operation);                                                              // 29
		virtual void AttachProperty([[maybe_unused]] NiAlphaProperty* a_prop) { return; }                                // 2A
		virtual void SetMaterialNeedsUpdate(bool) { return; }                                                            // 2B
		virtual void SetDefaultMaterialNeedsUpdateFlag(bool) { return; }                                                 // 2C
		virtual void SetAppCulled(bool a_appCulled);                                                                     // 2D
		virtual NiAVObject* GetObjectByName(const BSFixedString& a_name) { return name == a_name ? this : nullptr; }     // 2E
		virtual void SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid);  // 2F
		virtual void UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags);                                    // 30
		virtual void UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags);                            // 31
		virtual void UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_flags);                               // 32
		virtual void UpdateWorldBound() { return; }                                                                      // 33
		virtual void UpdateWorldData(NiUpdateData* a_data);                                                              // 34
		virtual void UpdateTransformAndBounds(NiUpdateData& a_data);                                                     // 35
		virtual void UpdateTransforms(NiUpdateData& a_data) { UpdateWorldData(std::addressof(a_data)); }                 // 36
		virtual void PreAttachUpdate(NiNode* a_eventualParent, NiUpdateData& a_data);                                    // 37
		virtual void PostAttachUpdate();                                                                                 // 38
		virtual void OnVisible([[maybe_unused]] NiCullingProcess& a_culler) { return; }                                  // 39

		F4_HEAP_REDEFINE_ALIGNED_NEW(NiAVObject);

		[[nodiscard]] bool GetAppCulled() const noexcept { return flags.flags & 1; }
		[[nodiscard]] std::uint64_t GetFlags() const noexcept { return flags.flags; }
		[[nodiscard]] bool ShadowCaster() const noexcept { return ~(flags.flags >> 40) & 1; }

		// members
		NiNode* parent{ nullptr };                     // 027
		NiTransform local;                             // 030
		NiTransform world;                             // 070
		NiBound worldBound;                            // 0B0
		NiTransform previousWorld;                     // 0C0
		NiPointer<NiCollisionObject> collisionObject;  // 100
		NiTFlags<std::uint64_t, NiAVObject> flags;     // 108
		std::uintptr_t userData{ 0 };                  // 110
		float fadeAmount{ 1.0F };                      // 118
		std::int8_t multType{ 0 };                     // 11C
		std::int8_t meshLODFadingLevel{ 0 };           // 11D
		std::int8_t currentMeshLODLevel{ 0 };          // 11E
		std::int8_t previousMeshLODLevel{ 0 };         // 11F
	};
	static_assert(sizeof(NiAVObject) == 0x120);
}
