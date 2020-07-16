#pragma once

// clang format chokes hard on classes with attributes
#define F4SE_MAYBE_UNUSED [[maybe_unused]]
#define F4SE_MAKE_SOURCE_LOGGER(a_func, a_type)                                                                                                 \
                                                                                                                                                \
	template <class... Args>                                                                                                                    \
	struct F4SE_MAYBE_UNUSED a_func                                                                                                             \
	{                                                                                                                                           \
		a_func(                                                                                                                                 \
			spdlog::string_view_t a_fmt,                                                                                                        \
			const Args&... a_args,                                                                                                              \
			const char* a_file = __builtin_FILE(),                                                                                              \
			int			a_line = __builtin_LINE(),                                                                                              \
			const char* a_function = __builtin_FUNCTION())                                                                                      \
		{                                                                                                                                       \
			spdlog::log(spdlog::source_loc{ a_file, a_line, a_function }, spdlog::level::a_type, a_fmt, a_args...);                             \
		}                                                                                                                                       \
	};                                                                                                                                          \
                                                                                                                                                \
	template <>                                                                                                                                 \
	struct F4SE_MAYBE_UNUSED a_func<>                                                                                                           \
	{                                                                                                                                           \
		a_func(                                                                                                                                 \
			spdlog::string_view_t a_fmt,                                                                                                        \
			const char*			  a_file = __builtin_FILE(),                                                                                    \
			int					  a_line = __builtin_LINE(),                                                                                    \
			const char*			  a_function = __builtin_FUNCTION())                                                                            \
		{                                                                                                                                       \
			spdlog::log(spdlog::source_loc{ a_file, a_line, a_function }, spdlog::level::a_type, std::string_view(a_fmt.data(), a_fmt.size())); \
		}                                                                                                                                       \
	};                                                                                                                                          \
                                                                                                                                                \
	template <class... Args>                                                                                                                    \
	a_func(spdlog::string_view_t, const Args&...) -> a_func<Args...>;

namespace F4SE
{
	namespace log
	{
		F4SE_MAKE_SOURCE_LOGGER(trace, trace);
		F4SE_MAKE_SOURCE_LOGGER(debug, debug);
		F4SE_MAKE_SOURCE_LOGGER(info, info);
		F4SE_MAKE_SOURCE_LOGGER(warn, warn);
		F4SE_MAKE_SOURCE_LOGGER(error, err);
		F4SE_MAKE_SOURCE_LOGGER(critical, critical);
	}
}

#undef F4SE_MAKE_SOURCE_LOGGER
#undef F4SE_MAYBE_UNUSED
