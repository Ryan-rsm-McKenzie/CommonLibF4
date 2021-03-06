#pragma once

#include "RE/Bethesda/CRC.h"

namespace RE
{
	template <class T>
	class NiPointer
	{
	public:
		using element_type = T;

		// 1)
		NiPointer() noexcept = default;

		// 2)
		NiPointer(std::nullptr_t) noexcept {}

		// 3)
		template <class Y>
		explicit NiPointer(Y* a_rhs)  //
			requires(std::convertible_to<Y*, element_type*>) :
			_ptr(static_cast<element_type*>(a_rhs))
		{
			TryAttach();
		}

		// 9a)
		NiPointer(const NiPointer& a_rhs) :
			_ptr(a_rhs._ptr)
		{
			TryAttach();
		}

		// 9b)
		template <class Y>
		NiPointer(const NiPointer<Y>& a_rhs)  //
			requires(std::convertible_to<Y*, element_type*>) :
			_ptr(static_cast<element_type*>(a_rhs._ptr))
		{
			TryAttach();
		}

		// 10a)
		NiPointer(NiPointer&& a_rhs) noexcept :
			_ptr(std::exchange(a_rhs._ptr, nullptr))
		{}

		// 10b)
		template <class Y>
		NiPointer(NiPointer<Y>&& a_rhs) noexcept  //
			requires(std::convertible_to<Y*, element_type*>) :
			_ptr(static_cast<element_type*>(std::exchange(a_rhs._ptr, nullptr)))
		{}

		~NiPointer() noexcept { reset(); }

		// 1a)
		NiPointer& operator=(const NiPointer& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				TryDetach();
				_ptr = a_rhs._ptr;
				TryAttach();
			}
			return *this;
		}

		// 1b)
		template <class Y>
		NiPointer& operator=(const NiPointer<Y>& a_rhs)  //
			requires(std::convertible_to<Y*, element_type*>)
		{
			TryDetach();
			_ptr = static_cast<element_type*>(a_rhs._ptr);
			TryAttach();
			return *this;
		}

		// 2a)
		NiPointer& operator=(NiPointer&& a_rhs) noexcept
		{
			if (this != std::addressof(a_rhs)) {
				TryDetach();
				_ptr = std::exchange(a_rhs._ptr, nullptr);
			}
			return *this;
		}

		// 2b)
		template <class Y>
		NiPointer& operator=(NiPointer<Y>&& a_rhs) noexcept  //
			requires(std::convertible_to<Y*, element_type*>)
		{
			TryDetach();
			_ptr = std::exchange(a_rhs._ptr, nullptr);
			return *this;
		}

		// 1)
		void reset() { TryDetach(); }

		// 2)
		template <class Y>
		void reset(Y* a_ptr)  //
			requires(std::convertible_to<Y*, element_type*>)
		{
			if (_ptr != a_ptr) {
				TryDetach();
				_ptr = static_cast<element_type*>(a_ptr);
				TryAttach();
			}
		}

		[[nodiscard]] element_type* get() const noexcept { return _ptr; }

		[[nodiscard]] element_type& operator*() const noexcept
		{
			assert(static_cast<bool>(*this));
			return *_ptr;
		}

		[[nodiscard]] element_type* operator->() const noexcept
		{
			assert(static_cast<bool>(*this));
			return _ptr;
		}

		[[nodiscard]] explicit operator bool() const noexcept { return _ptr != nullptr; }

	protected:
		template <class>
		friend class NiPointer;

		void TryAttach()
		{
			if (_ptr) {
				_ptr->IncRefCount();
			}
		}

		void TryDetach()
		{
			if (_ptr) {
				_ptr->DecRefCount();
				_ptr = nullptr;
			}
		}

		// members
		element_type* _ptr{ nullptr };  // 0
	};
	//static_assert(sizeof(NiPointer<void*>) == 0x8);

	template <class T, class... Args>
	[[nodiscard]] NiPointer<T> make_nismart(Args&&... a_args)
	{
		return NiPointer<T>{ new T(std::forward<Args>(a_args)...) };
	}

	// 1)
	template <class T, class U>
	[[nodiscard]] bool operator==(const NiPointer<T>& a_lhs, const NiPointer<U>& a_rhs) noexcept
	{
		return a_lhs.get() == a_rhs.get();
	}

	// 7)
	template <class T, class U>
	[[nodiscard]] std::strong_ordering operator<=>(const NiPointer<T>& a_lhs, const NiPointer<U>& a_rhs) noexcept
	{
		return std::compare_three_way{}(a_lhs.get(), a_rhs.get());
	}

	// 8)
	template <class T>
	[[nodiscard]] bool operator==(const NiPointer<T>& a_lhs, std::nullptr_t) noexcept
	{
		return !a_lhs;
	}

	// 20)
	template <class T>
	[[nodiscard]] std::strong_ordering operator<=>(const NiPointer<T>& a_lhs, std::nullptr_t) noexcept
	{
		return std::compare_three_way{}(a_lhs.get(), static_cast<typename NiPointer<T>::element_type*>(nullptr));
	}

	template <class T>
	struct BSCRC32<NiPointer<T>>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const NiPointer<T>& a_key) const noexcept
		{
			return BSCRC32<T*>()(a_key.get());
		}
	};
}
