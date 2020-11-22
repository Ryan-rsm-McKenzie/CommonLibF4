#pragma once

namespace RE
{
	class BSNonReentrantSpinLock
	{
	public:
		constexpr BSNonReentrantSpinLock() noexcept {}  // NOLINT(modernize-use-equals-default)

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

		[[nodiscard]] bool try_lock()
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
		std::uint32_t _owningThread{ 0 };        // 0
		volatile std::uint32_t _lockCount{ 0 };  // 4
	};
	static_assert(sizeof(BSSpinLock) == 0x8);

	class BSReadWriteLock
	{
	public:
		void lock_read()
		{
			using func_t = decltype(&BSReadWriteLock::lock_read);
			REL::Relocation<func_t> func{ REL::ID(1573164) };
			return func(this);
		}

		void lock_write()
		{
			using func_t = decltype(&BSReadWriteLock::lock_write);
			REL::Relocation<func_t> func{ REL::ID(336186) };
			return func(this);
		}

		[[nodiscard]] bool try_lock_read()
		{
			using func_t = decltype(&BSReadWriteLock::try_lock_read);
			REL::Relocation<func_t> func{ REL::ID(1372435) };
			return func(this);
		}

		[[nodiscard]] bool try_lock_write()
		{
			using func_t = decltype(&BSReadWriteLock::try_lock_write);
			REL::Relocation<func_t> func{ REL::ID(1279453) };
			return func(this);
		}

		void unlock_read()
		{
			stl::atomic_ref lock{ _lock };
			--lock;
		}

		void unlock_write()
		{
			stl::atomic_ref lock{ _lock };
			if (_lock == 0x80000001) {
				_writerThread = 0;
				lock.exchange(0);
			} else {
				--lock;
			}
		}

	private:
		// members
		std::uint32_t _writerThread{ 0 };   // 0
		volatile std::uint32_t _lock{ 0 };  // 4
	};
	static_assert(sizeof(BSReadWriteLock) == 0x8);

	template <class Mutex>
	struct BSAutoLockDefaultPolicy
	{
	public:
		static void lock(Mutex& a_mutex) { a_mutex.lock(); }
		static void unlock(Mutex& a_mutex) { a_mutex.unlock(); }
	};

	extern template struct BSAutoLockDefaultPolicy<BSSpinLock>;

	template <class Mutex>
	struct BSAutoLockReadLockPolicy
	{
	public:
		static void lock(Mutex& a_mutex) { a_mutex.lock_read(); }
		static void unlock(Mutex& a_mutex) { a_mutex.unlock_read(); }
	};

	extern template struct BSAutoLockReadLockPolicy<BSReadWriteLock>;

	template <class Mutex>
	struct BSAutoLockWriteLockPolicy
	{
	public:
		static void lock(Mutex& a_mutex) { a_mutex.lock_write(); }
		static void unlock(Mutex& a_mutex) { a_mutex.unlock_write(); }
	};

	extern template struct BSAutoLockWriteLockPolicy<BSReadWriteLock>;

	template <class Mutex, template <class> class Policy = BSAutoLockDefaultPolicy>
	class BSAutoLock
	{
	public:
		using mutex_type = Mutex;
		using policy_type = Policy<mutex_type>;

		explicit BSAutoLock(mutex_type& a_mutex) :
			_lock(std::addressof(a_mutex))
		{
			policy_type::lock(*_lock);
		}

		explicit BSAutoLock(mutex_type* a_mutex) :
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

	extern template class BSAutoLock<BSSpinLock, BSAutoLockDefaultPolicy>;
	extern template class BSAutoLock<BSReadWriteLock, BSAutoLockReadLockPolicy>;
	extern template class BSAutoLock<BSReadWriteLock, BSAutoLockWriteLockPolicy>;

	using BSAutoReadLock = BSAutoLock<BSReadWriteLock, BSAutoLockReadLockPolicy>;
	using BSAutoWriteLock = BSAutoLock<BSReadWriteLock, BSAutoLockWriteLockPolicy>;
}
