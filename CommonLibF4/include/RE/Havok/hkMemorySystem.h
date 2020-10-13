#pragma once

#include "RE/Havok/hkBaseTypes.h"
#include "RE/Havok/hkMemoryRouter.h"

namespace RE
{
	class hkDebugMemorySystem;
	class hkMemoryAllocator;
	class hkMemorySnapshot;
	class hkOstream;

	class __declspec(novtable) hkMemorySystem
	{
	public:
		static constexpr auto RTTI{ RTTI::hkMemorySystem };
		static constexpr auto VTABLE{ VTABLE::hkMemorySystem };

		using MemoryWalkCallback = void(void* a_start, std::size_t a_size, bool a_allocated, std::int32_t a_pool, void* a_param);

		enum class FlagBits
		{
			kPersistent = 1,
			kTemporary,
			kAll,

			kRouter = kPersistent,
			kFrame = kTemporary
		};

		struct MemoryStatistics;
		struct FrameInfo;

		virtual ~hkMemorySystem() = default;  // 00

		// add
		virtual hkMemoryRouter* MainInit(const FrameInfo& a_info, hkFlags<FlagBits, std::int32_t> a_flags) = 0;              // 01
		virtual hkResult MainQuit(hkFlags<FlagBits, std::int32_t> a_flags) = 0;                                              // 02
		virtual void ThreadInit(hkMemoryRouter& a_router, const char* a_name, hkFlags<FlagBits, std::int32_t> a_flags) = 0;  // 03
		virtual void ThreadQuit(hkMemoryRouter& a_router, hkFlags<FlagBits, std::int32_t> a_flags) = 0;                      // 04
		virtual hkResult GetHeapSoftLimit([[maybe_unused]] std::int32_t a_numBytes) { return { hkResultEnum::kFailure }; }   // 05
		virtual std::int32_t GetHeapSoftLimit() const { return -1; }                                                         // 06
		virtual bool SolverCanAllocSingleBlock([[maybe_unused]] std::int32_t a_numBytes) { return true; }                    // 07
		virtual bool HeapCanAllocTotal([[maybe_unused]] std::int32_t a_numBytes) { return true; }                            // 08
		virtual void PrintStatistics(hkOstream& a_ostr) const = 0;                                                           // 09
		virtual void GetMemoryStatistics(MemoryStatistics&) = 0;                                                             // 0A
		virtual hkMemoryAllocator* GetUncachedLockedHeapAllocator() = 0;                                                     // 0B
		virtual void GarbageCollectThread([[maybe_unused]] hkMemoryRouter& a_router) { return; }                             // 0C
		virtual void GarbageCollectShared() { return; }                                                                      // 0D

		virtual void GarbageCollect()  // 0E
		{
			GarbageCollectThread(hkMemoryRouter::GetInstance());
			GarbageCollectShared();
		}

		virtual void AdvanceFrame() { return; }                               // 0F
		virtual hkDebugMemorySystem* GetDebugInterface() { return nullptr; }  // 10
		virtual hkResult GetMemorySnapshot(
			[[maybe_unused]] hkMemorySnapshot& a_snapshot) const { return { hkResultEnum::kFailure }; }  // 11
		virtual hkResult GetAllocationCallStack(
			[[maybe_unused]] const void* a_ptr,
			[[maybe_unused]] std::uint64_t* a_callStack,
			[[maybe_unused]] std::int32_t& a_stackSize,
			[[maybe_unused]] std::size_t& a_allocSize) { return { hkResultEnum::kFailure }; }  // 12
		virtual void SetHeapScrubValues(
			[[maybe_unused]] std::uint32_t a_allocValue,
			[[maybe_unused]] std::uint32_t a_freeValue) { return; }  // 13
		virtual std::uint32_t IsOk() const { return 1; }             // 14
	};
	static_assert(sizeof(hkMemorySystem) == 0x8);
}
