#pragma once

#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	class __declspec(novtable) NiRefObject
	{
	public:
		static constexpr auto RTTI{ RTTI::NiRefObject };
		static constexpr auto VTABLE{ VTABLE::NiRefObject };

		NiRefObject()
		{
			stl::emplace_vtable(this);
			REL::Relocation<std::uint32_t*> objects{ REL::ID(1161724) };
			stl::atomic_ref myObjects{ *objects };
			++myObjects;
		}

		virtual ~NiRefObject()  // 00
		{
			REL::Relocation<std::uint32_t*> objects{ REL::ID(1161724) };
			stl::atomic_ref myObjects{ *objects };
			--myObjects;
		}

		// add
		virtual void DeleteThis() { delete this; }  // 01

		F4_HEAP_REDEFINE_NEW(NiRefObject);

		std::uint32_t DecRefCount()
		{
			stl::atomic_ref myRefCount{ refCount };
			const auto newRefCount = --myRefCount;
			if (newRefCount == 0) {
				DeleteThis();
			}
			return newRefCount;
		}

		std::uint32_t IncRefCount()
		{
			stl::atomic_ref myRefCount{ refCount };
			return ++myRefCount;
		}

		// members
		std::uint32_t refCount;  // 08
	};
	static_assert(sizeof(NiRefObject) == 0x10);
}
