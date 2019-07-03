#pragma once


namespace RE
{
	namespace Scaleform
	{
		template <class T>
		class Ptr
		{
		public:
			using element_type = T;


			constexpr Ptr() noexcept;
			constexpr Ptr(std::nullptr_t) noexcept;
			template<class Y, typename std::enable_if_t<std::is_convertible<Y*, T*>::value, int> = 0> explicit Ptr(Y * a_ptr);
			Ptr(const Ptr& a_r) noexcept;
			template<class Y, typename std::enable_if_t<std::is_convertible<Y*, T*>::value, int> = 0> Ptr(const Ptr<Y> & a_r) noexcept;
			Ptr(Ptr&& a_r) noexcept;
			template<class Y, typename std::enable_if_t<std::is_convertible<Y*, T*>::value, int> = 0> Ptr(Ptr<Y> && a_r) noexcept;

			~Ptr();

			Ptr& operator=(const Ptr& a_r) noexcept;
			template<class Y, typename std::enable_if_t<std::is_convertible<Y*, T*>::value, int> = 0> Ptr & operator=(const Ptr<Y> & a_r) noexcept;
			Ptr& operator=(Ptr&& a_r) noexcept;
			template<class Y, typename std::enable_if_t<std::is_convertible<Y*, T*>::value, int> = 0> Ptr & operator=(Ptr<Y> && a_r) noexcept;

			void reset() noexcept;
			template<class Y, typename std::enable_if_t<std::is_convertible<Y*, T*>::value, int> = 0> void reset(Y * a_ptr);

			[[nodiscard]] constexpr element_type* get() const noexcept;

			[[nodiscard]] constexpr T& operator*() const noexcept;
			[[nodiscard]] constexpr T* operator->() const noexcept;

			[[nodiscard]] explicit constexpr operator bool() const noexcept;

		protected:
			void AddRef();
			void Release();


			// members
			T* _ptr;	// 0
		};
		STATIC_ASSERT(sizeof(Ptr<void*>) == 0x8);


		template <class T>
		constexpr Ptr<T>::Ptr() noexcept :
			_ptr(0)
		{}


		template <class T>
		constexpr Ptr<T>::Ptr(std::nullptr_t) noexcept :
			_ptr(0)
		{}


		template <class T>
		template <class Y, typename std::enable_if_t<std::is_convertible<Y*, T*>::value, int>>
		Ptr<T>::Ptr(Y* a_ptr) :
			_ptr(a_ptr)
		{
			AddRef();
		}


		template <class T>
		Ptr<T>::Ptr(const Ptr& a_r) noexcept :
			_ptr(a_r._ptr)
		{
			AddRef();
		}


		template <class T>
		template <class Y, typename std::enable_if_t<std::is_convertible<Y*, T*>::value, int>>
		Ptr<T>::Ptr(const Ptr<Y>& a_r) noexcept :
			_ptr(a_r._ptr)
		{
			AddRef();
		}


		template <class T>
		Ptr<T>::Ptr(Ptr&& a_r) noexcept :
			_ptr(std::move(a_r._ptr))
		{
			a_r._ptr = 0;
		}


		template <class T>
		template <class Y, typename std::enable_if_t<std::is_convertible<Y*, T*>::value, int>>
		Ptr<T>::Ptr(Ptr<Y>&& a_r) noexcept :
			_ptr(std::move(a_r._ptr))
		{
			a_r._ptr = 0;
		}


		template <class T>
		Ptr<T>::~Ptr()
		{
			Release();
		}


		template <class T>
		auto Ptr<T>::operator=(const Ptr& a_r) noexcept
			-> Ptr &
		{
			if (this == &a_r) {
				return *this;
			}

			reset(a_r._ptr);
			return *this;
		}


		template <class T>
		template <class Y, typename std::enable_if_t<std::is_convertible<Y*, T*>::value, int>>
		auto Ptr<T>::operator=(const Ptr<Y>& a_r) noexcept
			-> Ptr &
		{
			reset(a_r._ptr);
			return *this;
		}


		template <class T>
		auto Ptr<T>::operator=(Ptr&& a_r) noexcept
			-> Ptr &
		{
			if (this == &a_r) {
				return *this;
			}

			Release();
			_ptr = std::move(a_r._ptr);
			a_r._ptr = 0;
			return *this;
		}


		template <class T>
		template <class Y, typename std::enable_if_t<std::is_convertible<Y*, T*>::value, int>>
		auto Ptr<T>::operator=(Ptr<Y>&& a_r) noexcept
			-> Ptr &
		{
			Release();
			_ptr = std::move(a_r._ptr);
			a_r._ptr = 0;
			return *this;
		}


		template <class T>
		void Ptr<T>::reset() noexcept
		{
			if (_ptr) {
				_ptr->Release();
				_ptr = 0;
			}
		}


		template <class T>
		template <class Y, typename std::enable_if_t<std::is_convertible<Y*, T*>::value, int>>
		void Ptr<T>::reset(Y* a_ptr)
		{
			_ptr = a_ptr;
			AddRef();
		}


		template <class T>
		[[nodiscard]] constexpr auto Ptr<T>::get() const noexcept
			-> element_type*
		{
			return _ptr;
		}


		template <class T>
		[[nodiscard]] constexpr T& Ptr<T>::operator*() const noexcept
		{
			assert(_ptr != 0);
			return *get();
		}


		template <class T>
		[[nodiscard]] constexpr T* Ptr<T>::operator->() const noexcept
		{
			return get();
		}


		template <class T>
		[[nodiscard]] constexpr Ptr<T>::operator bool() const noexcept
		{
			return _ptr != 0;
		}


		template <class T>
		void Ptr<T>::AddRef()
		{
			if (_ptr) {
				_ptr->AddRef();
			}
		}


		template <class T>
		void Ptr<T>::Release()
		{
			if (_ptr) {
				_ptr->Release();
			}
		}
	}
}
