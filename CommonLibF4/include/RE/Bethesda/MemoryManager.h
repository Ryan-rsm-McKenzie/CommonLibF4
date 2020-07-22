#pragma once

namespace RE
{
	class MemoryManager
	{
	public:
		[[nodiscard]] inline void* Allocate(std::size_t a_size, std::uint32_t a_alignment, bool a_alignmentRequired)
		{
			using func_t = decltype(&MemoryManager::Allocate);
			const REL::Relocation<func_t> func{ REL::ID(652767) };
			return func(this, a_size, a_alignment, a_alignmentRequired);
		}

		inline void Deallocate(void* a_mem, bool a_alignmentRequired)
		{
			using func_t = decltype(&MemoryManager::Deallocate);
			const REL::Relocation<func_t> func{ REL::ID(1582181) };
			return func(this, a_mem, a_alignmentRequired);
		}

		[[nodiscard]] inline void* Reallocate(void* a_oldMem, std::size_t a_newSize, std::uint32_t a_alignment, bool a_alignmentRequired)
		{
			using func_t = decltype(&MemoryManager::Reallocate);
			const REL::Relocation<func_t> func{ REL::ID(1502917) };
			return func(this, a_oldMem, a_newSize, a_alignment, a_alignmentRequired);
		}

		// members
		std::uint8_t unk[0x480];  // 000
	};
	static_assert(sizeof(MemoryManager) == 0x480);
}
