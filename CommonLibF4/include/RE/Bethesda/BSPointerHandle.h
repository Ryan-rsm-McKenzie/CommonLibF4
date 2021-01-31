#pragma once

#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class Actor;
	class HandleManager;
	class Projectile;
	class TESObjectREFR;

	template <std::uint32_t = 21, std::uint32_t = 5>
	class BSUntypedPointerHandle;

	template <class, class = BSUntypedPointerHandle<>>
	class BSPointerHandle;

	template <class, class = HandleManager>
	class BSPointerHandleManagerInterface;

	template <std::uint32_t FREE_LIST_BITS, std::uint32_t AGE_SHIFT>
	class BSUntypedPointerHandle
	{
	public:
		using value_type = std::uint32_t;

		enum : std::uint32_t
		{
			kFreeListBits = FREE_LIST_BITS,
			kAgeShift = AGE_SHIFT,
		};

		BSUntypedPointerHandle() noexcept = default;
		BSUntypedPointerHandle(const BSUntypedPointerHandle&) noexcept = default;

		explicit BSUntypedPointerHandle(value_type a_handle) noexcept :
			_handle(a_handle)
		{}

		~BSUntypedPointerHandle() noexcept { reset(); }

		BSUntypedPointerHandle& operator=(const BSUntypedPointerHandle&) noexcept = default;

		BSUntypedPointerHandle& operator=(value_type a_rhs) noexcept
		{
			_handle = a_rhs;
			return *this;
		}

		[[nodiscard]] explicit operator bool() const noexcept { return has_value(); }
		[[nodiscard]] bool has_value() const noexcept { return _handle != 0; }

		[[nodiscard]] value_type value() const noexcept { return _handle; }

		void reset() noexcept { _handle = 0; }

		[[nodiscard]] friend bool operator==(const BSUntypedPointerHandle& a_lhs, const BSUntypedPointerHandle& a_rhs) noexcept
		{
			return a_lhs.value() == a_rhs.value();
		}

	private:
		// members
		value_type _handle{ 0 };  // 0
	};

	extern template class BSUntypedPointerHandle<>;

	template <class T, class Handle>
	class BSPointerHandle
	{
	public:
		using native_handle_type = typename Handle::value_type;

		BSPointerHandle() noexcept = default;

		template <class Y>
		BSPointerHandle(BSPointerHandle<Y, Handle> a_rhs) noexcept  //
			requires(std::convertible_to<Y*, T*>) :
			_handle(a_rhs._handle)
		{}

		template <class Y>
		explicit BSPointerHandle(Y* a_rhs)  //
			requires(std::convertible_to<Y*, T*>)
		{
			get_handle(a_rhs);
		}

		~BSPointerHandle() noexcept = default;

		template <class Y>
		BSPointerHandle& operator=(BSPointerHandle<Y, Handle> a_rhs) noexcept  //
			requires(std::convertible_to<Y*, T*>)
		{
			_handle = a_rhs._handle;
			return *this;
		}

		template <class Y>
		BSPointerHandle& operator=(Y* a_rhs)  //
			requires(std::convertible_to<Y*, T*>)
		{
			get_handle(a_rhs);
			return *this;
		}

		void reset() noexcept { _handle.reset(); }

		[[nodiscard]] NiPointer<T> get() const
		{
			NiPointer<T> ptr;
			get_smartptr(ptr);
			return ptr;
		}

		[[nodiscard]] native_handle_type native_handle() noexcept
		{
			return _handle.value();
		}

		[[nodiscard]] explicit operator bool() const noexcept { return _handle.has_value(); }

		[[nodiscard]] friend bool operator==(const BSPointerHandle& a_lhs, const BSPointerHandle& a_rhs) noexcept
		{
			return a_lhs._handle == a_rhs._handle;
		}

	private:
		template <class, class>
		friend class BSPointerHandle;

		void get_handle(T* a_ptr);
		bool get_smartptr(NiPointer<T>& a_smartPointerOut) const;

		Handle _handle;  // 00
	};

	extern template class BSPointerHandle<Actor>;
	extern template class BSPointerHandle<Projectile>;
	extern template class BSPointerHandle<TESObjectREFR>;

	using ActorHandle = BSPointerHandle<Actor>;
	using ProjectileHandle = BSPointerHandle<Projectile>;
	using ObjectRefHandle = BSPointerHandle<TESObjectREFR>;

	template <class T>
	struct BSCRC32<BSPointerHandle<T>>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const BSPointerHandle<T>& a_handle) const noexcept
		{
			return BSCRC32<typename BSPointerHandle<T>::native_handle_type>()(a_handle.native_handle());
		}
	};

	template <class T, class Manager>
	class BSPointerHandleManagerInterface
	{
	public:
		static BSPointerHandle<T> GetHandle(T* a_ptr)
		{
			using func_t = decltype(&BSPointerHandleManagerInterface<T, Manager>::GetHandle);
			REL::Relocation<func_t> func{ REL::ID(901626) };
			return func(a_ptr);
		}

		static bool GetSmartPointer(const BSPointerHandle<T>& a_handle, NiPointer<T>& a_smartPointerOut)
		{
			using func_t = decltype(&BSPointerHandleManagerInterface<T, Manager>::GetSmartPointer);
			REL::Relocation<func_t> func{ REL::ID(967277) };
			return func(a_handle, a_smartPointerOut);
		}
	};

	extern template class BSPointerHandleManagerInterface<Actor>;
	extern template class BSPointerHandleManagerInterface<Projectile>;
	extern template class BSPointerHandleManagerInterface<TESObjectREFR>;

	template <class T, class Handle>
	void BSPointerHandle<T, Handle>::get_handle(T* a_ptr)
	{
		*this = BSPointerHandleManagerInterface<T>::GetHandle(a_ptr);
	}

	template <class T, class Handle>
	bool BSPointerHandle<T, Handle>::get_smartptr(NiPointer<T>& a_smartPointerOut) const
	{
		return BSPointerHandleManagerInterface<T>::GetSmartPointer(*this, a_smartPointerOut);
	}
}
