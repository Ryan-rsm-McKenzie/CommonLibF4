#pragma once

namespace RE
{
	inline void* NiMalloc(std::size_t a_num)
	{
		using func_t = decltype(&NiMalloc);
		REL::Relocation<func_t> func{ REL::ID(974443) };
		return func(a_num);
	}

	inline void NiFree(void* a_ptr)
	{
		using func_t = decltype(&NiFree);
		REL::Relocation<func_t> func{ REL::ID(242362) };
		return func(a_ptr);
	}

	template <class T>
	class NiTMallocInterface
	{
	public:
		[[nodiscard]] static T* allocate(std::size_t a_num) { return NiMalloc(sizeof(T) * a_num); }
		static void deallocate(T* a_ptr) { NiFree(a_ptr); }
	};

	template <class T>
	class NiTNewInterface
	{
	public:
		[[nodiscard]] static T* allocate(std::size_t a_num) { return new T[a_num]; }
		static void deallocate(T* a_ptr) { delete[] a_ptr; }
	};
}
