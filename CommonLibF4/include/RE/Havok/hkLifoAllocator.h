#pragma once

#include "RE/Havok/hkMemoryAllocator.h"

namespace RE
{
	class __declspec(novtable) hkLifoAllocator :
		public hkMemoryAllocator  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::hkLifoAllocator };
		static constexpr auto VTABLE{ VTABLE::hkLifoAllocator };

		class Implementation;

		hkLifoAllocator() { stl::emplace_vtable(this); }

		// override (hkMemoryAllocator)
		void* BlockAlloc(std::int32_t a_numBytesIn) override  // 01
		{
			using func_t = decltype(&hkLifoAllocator::BlockAlloc);
			REL::Relocation<func_t> func{ REL::ID(605837) };
			return func(this, a_numBytesIn);
		}

		void BlockFree(void* a_ptr, std::int32_t a_numBytesIn) override  // 02
		{
			using func_t = decltype(&hkLifoAllocator::BlockFree);
			REL::Relocation<func_t> func{ REL::ID(778687) };
			return func(this, a_ptr, a_numBytesIn);
		}

		void* BufAlloc(std::int32_t& a_reqNumBytesInOut) override  // 03
		{
			using func_t = decltype(&hkLifoAllocator::BufAlloc);
			REL::Relocation<func_t> func{ REL::ID(951267) };
			return func(this, a_reqNumBytesInOut);
		}

		void BufFree(void* a_ptr, std::int32_t a_numBytes) override  // 04
		{
			using func_t = decltype(&hkLifoAllocator::BufFree);
			REL::Relocation<func_t> func{ REL::ID(1123850) };
			return func(this, a_ptr, a_numBytes);
		}

		void* BufRealloc(void* a_old, std::int32_t a_oldNumBytes, std::int32_t& a_reqNumBytesInOut) override  // 05
		{
			using func_t = decltype(&hkLifoAllocator::BufRealloc);
			REL::Relocation<func_t> func{ REL::ID(1296646) };
			return func(this, a_old, a_oldNumBytes, a_reqNumBytesInOut);
		}

		void GetMemoryStatistics(
			[[maybe_unused]] MemoryStatistics& a_stats) const override { return; }  // 08
		std::int32_t GetAllocatedSize(
			[[maybe_unused]] const void* a_obj,
			std::int32_t a_numBytes) const override { return a_numBytes; }  // 09

		void Init(
			hkMemoryAllocator* a_slabAllocator,
			hkMemoryAllocator* a_largeAllocator,
			hkMemoryAllocator* a_internalAllocator)
		{
			using func_t = decltype(&hkLifoAllocator::Init);
			REL::Relocation<func_t> func{ REL::ID(1417289) };
			return func(this, a_slabAllocator, a_largeAllocator, a_internalAllocator);
		}

		void Quit(hkMemoryAllocator** a_allocators)
		{
			using func_t = decltype(&hkLifoAllocator::Quit);
			REL::Relocation<func_t> func{ REL::ID(1058127) };
			return func(this, a_allocators);
		}

		// members
		Implementation* impl{ nullptr };                  // 08
		const std::int32_t slabSize{ 0x8000 };            // 10
		void* cur{ nullptr };                             // 18
		void* end{ nullptr };                             // 20
		void* firstNonLifoEnd{ nullptr };                 // 28
		void* cachedEmptySlab{ nullptr };                 // 30
		hkMemoryAllocator* slabAllocator{ nullptr };      // 38
		hkMemoryAllocator* largeAllocator{ nullptr };     // 40
		hkMemoryAllocator* internalAllocator{ nullptr };  // 48
	};
	static_assert(sizeof(hkLifoAllocator) == 0x50);
}
