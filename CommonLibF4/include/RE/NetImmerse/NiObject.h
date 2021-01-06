#pragma once

#include "RE/NetImmerse/NiRefObject.h"

namespace RE
{
	class bhkBlendCollisionObject;
	class bhkLimitedHingeConstraint;
	class bhkNiCollisionObject;
	class bhkNPCollisionObject;
	class bhkRigidBody;
	class BSDynamicTriShape;
	class BSFadeNode;
	class BSGeometry;
	class BSLines;
	class BSMultiBoundNode;
	class BSSegmentedTriShape;
	class BSSubIndexTriShape;
	class BSTriShape;
	class NiCloningProcess;
	class NiControllerManager;
	class NiGeometry;
	class NiLight;
	class NiNode;
	class NiObjectGroup;
	class NiParticles;
	class NiParticleSystem;
	class NiStream;
	class NiSwitchNode;
	class NiTriBasedGeom;
	class NiTriShape;
	class NiTriStrips;

	struct NiRTTI;

	class __declspec(novtable) NiObject :
		public NiRefObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::NiObject };
		static constexpr auto VTABLE{ VTABLE::NiObject };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiObject };

		NiObject() { stl::emplace_vtable(this); }
		virtual ~NiObject() = default;  // NOLINT(modernize-use-override) 00

		// add
		virtual const NiRTTI* GetRTTI() const;                                                             // 02
		virtual NiNode* IsNode() { return nullptr; }                                                       // 04
		virtual const NiNode* IsNode() const { return nullptr; }                                           // 03
		virtual NiSwitchNode* IsSwitchNode() { return nullptr; }                                           // 05
		virtual BSFadeNode* IsFadeNode() { return nullptr; }                                               // 06
		virtual BSMultiBoundNode* IsMultiBoundNode() { return nullptr; }                                   // 07
		virtual BSGeometry* IsGeometry() { return nullptr; }                                               // 08
		virtual NiTriStrips* IsTriStrips() { return nullptr; }                                             // 09
		virtual BSTriShape* IsTriShape() { return nullptr; }                                               // 0A
		virtual BSDynamicTriShape* IsDynamicTriShape() { return nullptr; }                                 // 0B
		virtual BSSegmentedTriShape* IsSegmentedTriShape() { return nullptr; }                             // 0C
		virtual BSSubIndexTriShape* IsSubIndexTriShape() { return nullptr; }                               // 0D
		virtual NiGeometry* IsNiGeometry() { return nullptr; }                                             // 0E
		virtual NiTriBasedGeom* IsNiTriBasedGeom() { return nullptr; }                                     // 0F
		virtual NiTriShape* IsNiTriShape() { return nullptr; }                                             // 10
		virtual NiParticles* IsParticlesGeom() { return nullptr; }                                         // 11
		virtual NiParticleSystem* IsParticleSystem() { return nullptr; }                                   // 12
		virtual BSLines* IsLinesGeom() { return nullptr; }                                                 // 13
		virtual NiLight* IsLight() { return nullptr; }                                                     // 14
		virtual bhkNiCollisionObject* IsBhkNiCollisionObject() { return nullptr; }                         // 15
		virtual bhkBlendCollisionObject* IsBhkBlendCollisionObject() { return nullptr; }                   // 16
		virtual bhkRigidBody* IsBhkRigidBody() { return nullptr; }                                         // 17
		virtual bhkLimitedHingeConstraint* IsBhkLimitedHingeConstraint() { return nullptr; }               // 18
		virtual bhkNPCollisionObject* IsbhkNPCollisionObject() { return nullptr; }                         // 19
		virtual NiObject* CreateClone([[maybe_unused]] NiCloningProcess& a_cloneData) { return nullptr; }  // 1A
		virtual void LoadBinary([[maybe_unused]] NiStream& a_stream) { return; }                           // 1B
		virtual void LinkObject([[maybe_unused]] NiStream& a_stream) { return; }                           // 1C
		virtual bool RegisterStreamables(NiStream& a_stream);                                              // 1D
		virtual void SaveBinary([[maybe_unused]] NiStream& a_stream) { return; }                           // 1E
		virtual bool IsEqual(NiObject* a_object);                                                          // 1F
		virtual void ProcessClone(NiCloningProcess& a_cloning);                                            // 20
		virtual void PostLinkObject([[maybe_unused]] NiStream& a_stream) { return; }                       // 21
		virtual bool StreamCanSkip() { return false; }                                                     // 22
		virtual const NiRTTI* GetStreamableRTTI() { return GetRTTI(); }                                    // 23
		virtual std::uint32_t GetBlockAllocationSize() const { return 0; }                                 // 24
		virtual NiObjectGroup* GetGroup() const { return nullptr; }                                        // 25
		virtual void SetGroup(NiObjectGroup*) { return; }                                                  // 26
		virtual NiControllerManager* IsNiControllerManager() { return nullptr; }                           // 27

		F4_HEAP_REDEFINE_NEW(NiObject);
	};
	static_assert(sizeof(NiObject) == 0x10);
}
