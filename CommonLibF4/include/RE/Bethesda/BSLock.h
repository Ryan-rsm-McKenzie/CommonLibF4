#pragma once

namespace RE
{
	class BSNonReentrantSpinLock
	{
	public:
		constexpr BSNonReentrantSpinLock() noexcept {}	// intentional

		// members
		std::uint32_t lock{ 0 };  // 0
	};
	static_assert(sizeof(BSNonReentrantSpinLock) == 0x4);

	class BSSpinLock
	{
	public:
		void lock(const char* a_id = nullptr)
		{
			using func_t = decltype(&BSSpinLock::lock);
			REL::Relocation<func_t> func{ REL::ID(1425657) };
			return func(this, a_id);
		}

		void try_lock()
		{
			using func_t = decltype(&BSSpinLock::try_lock);
			REL::Relocation<func_t> func{ REL::ID(267930) };
			return func(this);
		}

		void unlock()
		{
			stl::atomic_ref lockCount{ _lockCount };
			std::uint32_t expected{ 1 };
			if (lockCount == expected) {
				_owningThread = 0;
				lockCount.compare_exchange_strong(expected, 0);
			} else {
				--lockCount;
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
		static void lock(Mutex& a_mutex) { a_mutex.lock(); }
		static void unlock(Mutex& a_mutex) { a_mutex.unlock(); }
	};

	extern template struct BSAutoLockDefaultPolicy<BSSpinLock>;

	template <class Mutex, template <class> class Policy = BSAutoLockDefaultPolicy>
	class BSAutoLock
	{
	public:
		using mutex_type = Mutex;
		using policy_type = Policy<mutex_type>;

		BSAutoLock(Mutex& a_mutex) :
			_lock(std::addressof(a_mutex))
		{
			policy_type::lock(*_lock);
		}

		BSAutoLock(Mutex* a_mutex) :
			_lock(a_mutex)
		{
			if (_lock) {
				policy_type::lock(*_lock);
			}
		}

		~BSAutoLock()
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
