#pragma once

#include "RE/Havok/hkBaseObject.h"

namespace RE
{
	class hkClass;

	class __declspec(novtable) hkReferencedObject :
		public hkBaseObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::hkReferencedObject };
		static constexpr auto VTABLE{ VTABLE::hkReferencedObject };

		// add
		virtual const hkClass* GetClassType() const { return nullptr; }   // 02
		virtual void DeleteThisReferencedObject() const { delete this; }  // 03

		// members
		std::uint32_t memSizeAndRefCount;  // 08
	};
	static_assert(sizeof(hkReferencedObject) == 0x10);
}
