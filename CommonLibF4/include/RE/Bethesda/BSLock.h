#pragma once

namespace RE
{
	class BSSpinLock
	{
	public:
		inline void lock(const char* a_id = nullptr)
		{
			using func_t = decltype(&BSSpinLock::lock);
			REL::Relocation<func_t> func{ REL::ID(1425657) };
			return func(this, a_id);
		}

		inline void try_lock()
		{
			using func_t = decltype(&BSSpinLock::try_lock);
			REL::Relocation<func_t> func{ REL::ID(267930) };
			return func(this);
		}

		inline void unlock()
		{
			if (_lockCount == 1) {
				_owningThread = 0;
				_mm_mfence();
				InterlockedCompareExchange(std::addressof(_lockCount), 0, 1);
			} else {
				InterlockedDecrement(std::addressof(_lockCount));
			}
		}

	private:
		// members
		std::uint32_t _owningThread{ 0 };		 // 0
		volatile std::uint32_t _lockCount{ 0 };	 // 4
	};
	static_assert(sizeof(BSSpinLock) == 0x8);

	template <class Mutex>
	struct BSAutoLockDefaultPolicy
	{
	public:
		static inline void lock(Mutex& a_mutex) { a_mutex.lock(); }
		static inline void unlock(Mutex& a_mutex) { a_mutex.unlock(); }
	};

	extern template struct BSAutoLockDefaultPolicy<BSSpinLock>;

	template <class Mutex, template <class> class Policy = BSAutoLockDefaultPolicy>
	class BSAutoLock
	{
	public:
		using mutex_type = Mutex;
		using policy_type = Policy<mutex_type>;

		inline BSAutoLock(Mutex& a_mutex) :
			_lock(std::addressof(a_mutex))
		{
			policy_type::lock(*_lock);
		}

		inline BSAutoLock(Mutex* a_mutex) :
			_lock(a_mutex)
		{
			if (_lock) {
				policy_type::lock(*_lock);
			}
		}

		inline ~BSAutoLock()
		{
			if (_lock) {
				policy_type::unlock(*_lock);
			}
		}

	private:
		// members
		mutex_type* _lock{ nullptr };  // 00
	};

	template <class Mutex>
	BSAutoLock(Mutex&) -> BSAutoLock<Mutex>;

	template <class Mutex>
	BSAutoLock(Mutex*) -> BSAutoLock<Mutex>;

	extern template class BSAutoLock<BSSpinLock>;
}
