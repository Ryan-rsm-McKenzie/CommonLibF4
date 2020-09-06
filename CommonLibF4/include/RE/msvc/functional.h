#pragma once

namespace RE
{
	namespace msvc
	{
		template <class>
		class function;

		// class std::_Func_class
		template <class R, class... Args>
		class function<R(Args...)>
		{
		public:
			using result_type = R;

			[[nodiscard]] explicit operator bool() const noexcept { return good(); }

			result_type operator()(Args&&... a_args) const
			{
				assert(good());
				return _fn->do_call(std::forward<Args>(a_args)...);
			}

		private:
			// class std::_Func_base
			class proxy_t
			{
			public:
				// add
				virtual proxy_t* copy(void*) = 0;			  // 00
				virtual proxy_t* move(void*) = 0;			  // 01
				virtual result_type do_call(Args&&...) = 0;	  // 02
				virtual const void* target_type() const = 0;  // 03 - TODO: std::type_info
				virtual void delete_this(bool) = 0;			  // 04
				virtual ~proxy_t() = default;				  // 05
				virtual const void* get() const = 0;		  // 06
			};

			[[nodiscard]] bool good() const noexcept { return _fn != nullptr; }

			std::aligned_storage_t<3 * sizeof(void*), alignof(long double)> _storage;  // 00
			proxy_t* _fn;															   // 18
		};
	}
}
