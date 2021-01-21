#pragma once

namespace RE
{
	struct BSIntrusiveRefCounted
	{
	public:
		static constexpr auto RTTI{ RTTI::BSIntrusiveRefCounted };

		constexpr BSIntrusiveRefCounted() noexcept {}  // NOLINT(modernize-use-equals-default)

		[[nodiscard]] std::uint32_t DecRef() const
		{
			stl::atomic_ref myRefCount{ refCount };
			return --myRefCount;
		}

		std::uint32_t IncRef() const
		{
			stl::atomic_ref myRefCount{ refCount };
			return ++myRefCount;
		}

		[[nodiscard]] constexpr std::uint32_t QRefCount() const noexcept { return refCount; }

		// members
		mutable std::uint32_t refCount{ 0 };  // 0
	};
	static_assert(sizeof(BSIntrusiveRefCounted) == 0x4);

	template <class T>
	struct BSTSmartPointerIntrusiveRefCount
	{
	public:
		static void Acquire(stl::not_null<T*> a_ptr) { a_ptr->IncRef(); }

		static void Release(stl::not_null<T*> a_ptr)
		{
			if (a_ptr->DecRef() == 0) {
				delete a_ptr;
			}
		}
	};

	template <class T>
	struct BSTSmartPointerAutoPtr
	{
	public:
		constexpr static void Acquire(stl::not_null<T*> a_ptr) { return; }
		static void Release(stl::not_null<T*> a_ptr) { delete a_ptr; }
	};

	template <class T>
	struct BSTSmartPointerGamebryoRefCount
	{
	public:
		constexpr static void Acquire(stl::not_null<T*> a_ptr) { a_ptr->IncRefCount(); }
		static void Release(stl::not_null<T*> a_ptr) { a_ptr->DecRefCount(); }
	};

	template <class T, template <class> class RefManager = BSTSmartPointerIntrusiveRefCount>
	class BSTSmartPointer
	{
	public:
		using element_type = T;
		using reference_manager = RefManager<T>;

		// 1
		constexpr BSTSmartPointer() noexcept = default;

		// 2
		constexpr BSTSmartPointer(std::nullptr_t) noexcept {}

		// 3
		template <
			class Y,
			std::enable_if_t<
				std::is_convertible_v<
					Y*,
					element_type*>,
				int> = 0>
		explicit BSTSmartPointer(Y* a_rhs) :
			_ptr(a_rhs)
		{
			TryAttach();
		}

		// 9a
		BSTSmartPointer(const BSTSmartPointer& a_rhs) :
			_ptr(a_rhs._ptr)
		{
			TryAttach();
		}

		// 9b
		template <
			class Y,
			std::enable_if_t<
				std::is_convertible_v<
					Y*,
					element_type*>,
				int> = 0>
		BSTSmartPointer(const BSTSmartPointer<Y>& a_rhs) :
			_ptr(a_rhs._ptr)
		{
			TryAttach();
		}

		// 10a
		BSTSmartPointer(BSTSmartPointer&& a_rhs) noexcept :
			_ptr(a_rhs._ptr)
		{
			a_rhs._ptr = nullptr;
		}

		// 10b
		template <
			class Y,
			std::enable_if_t<
				std::is_convertible_v<
					Y*,
					element_type*>,
				int> = 0>
		BSTSmartPointer(BSTSmartPointer<Y>&& a_rhs) noexcept :
			_ptr(a_rhs._ptr)
		{
			a_rhs._ptr = nullptr;
		}

		~BSTSmartPointer() { TryDetach(); }

		// 1a
		BSTSmartPointer& operator=(const BSTSmartPointer& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				TryDetach();
				_ptr = a_rhs._ptr;
				TryAttach();
			}
			return *this;
		}

		// 1b
		template <
			class Y,
			std::enable_if_t<
				std::is_convertible_v<
					Y*,
					element_type*>,
				int> = 0>
		BSTSmartPointer& operator=(const BSTSmartPointer<Y>& a_rhs)
		{
			TryDetach();
			_ptr = a_rhs._ptr;
			TryAttach();
			return *this;
		}

		// 2a
		BSTSmartPointer& operator=(BSTSmartPointer&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				TryDetach();
				_ptr = a_rhs._ptr;
				a_rhs._ptr = nullptr;
			}
			return *this;
		}

		// 2b
		template <
			class Y,
			std::enable_if_t<
				std::is_convertible_v<
					Y*,
					element_type*>,
				int> = 0>
		BSTSmartPointer& operator=(BSTSmartPointer<Y>&& a_rhs)
		{
			TryDetach();
			_ptr = a_rhs._ptr;
			a_rhs._ptr = nullptr;
			return *this;
		}

		void reset() { TryDetach(); }

		template <
			class Y,
			std::enable_if_t<
				std::is_convertible_v<
					Y*,
					element_type*>,
				int> = 0>
		void reset(Y* a_ptr)
		{
			if (_ptr != a_ptr) {
				TryDetach();
				_ptr = a_ptr;
				TryAttach();
			}
		}

		[[nodiscard]] constexpr element_type* get() const noexcept { return _ptr; }

		[[nodiscard]] explicit constexpr operator bool() const noexcept { return static_cast<bool>(_ptr); }

		[[nodiscard]] constexpr element_type& operator*() const noexcept
		{
			assert(static_cast<bool>(*this));
			return *_ptr;
		}

		[[nodiscard]] constexpr element_type* operator->() const noexcept
		{
			assert(static_cast<bool>(*this));
			return _ptr;
		}

	protected:
		template <class, template <class> class>
		friend class BSTSmartPointer;

		void TryAttach()
		{
			if (_ptr) {
				reference_manager::Acquire(_ptr);
			}
		}

		void TryDetach()
		{
			if (_ptr) {
				reference_manager::Release(_ptr);
				_ptr = nullptr;
			}
		}

		// members
		element_type* _ptr{ nullptr };  // 0
	};
	static_assert(sizeof(BSTSmartPointer<void*>) == 0x8);

	template <class T, class... Args>
	[[nodiscard]] BSTSmartPointer<T> make_smart(Args&&... a_args)
	{
		return BSTSmartPointer<T>{ new T(std::forward<Args>(a_args)...) };
	}

	template <class T1, class T2, template <class> class R>
	[[nodiscard]] constexpr bool operator==(const BSTSmartPointer<T1, R>& a_lhs, const BSTSmartPointer<T2, R>& a_rhs)
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T, template <class> class R>
	[[nodiscard]] constexpr bool operator==(const BSTSmartPointer<T, R>& a_lhs, std::nullptr_t) noexcept
	{
		return !a_lhs;
	}

	template <class T>
	BSTSmartPointer(T*) -> BSTSmartPointer<T, BSTSmartPointerIntrusiveRefCount>;

	template <class T>
	using BSTAutoPointer = BSTSmartPointer<T, BSTSmartPointerAutoPtr>;
	static_assert(sizeof(BSTAutoPointer<void*>) == 0x8);

	template <class T, template <class> class R>
	struct BSCRC32<BSTSmartPointer<T, R>>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const BSTSmartPointer<T, R>& a_ptr) const noexcept
		{
			return BSCRC32<const void*>()(a_ptr.get());
		}
	};
}
