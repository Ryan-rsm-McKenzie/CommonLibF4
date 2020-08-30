#pragma once

// clang format chokes hard on classes with attributes
#define F4SE_MAYBE_UNUSED [[maybe_unused]]
#define F4SE_MAKE_SOURCE_LOGGER(a_func, a_type)                           \
                                                                          \
	template <class... Args>                                              \
	struct F4SE_MAYBE_UNUSED a_func                                       \
	{                                                                     \
		a_func() = delete;                                                \
                                                                          \
		template <class T>                                                \
		a_func(                                                           \
			T&& a_fmt,                                                    \
			Args&&... a_args,                                             \
			stl::source_location a_loc = stl::source_location::current()) \
		{                                                                 \
			spdlog::log(                                                  \
				spdlog::source_loc{                                       \
					a_loc.file_name(),                                    \
					static_cast<int>(a_loc.line()),                       \
					a_loc.function_name() },                              \
				spdlog::level::a_type,                                    \
				std::forward<T>(a_fmt),                                   \
				std::forward<Args>(a_args)...);                           \
		}                                                                 \
	};                                                                    \
                                                                          \
	template <class T, class... Args>                                     \
	a_func(T&&, Args&&...) -> a_func<Args...>;

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

		[[nodiscard]] std::optional<std::filesystem::path> log_directory();
	}
}

#undef F4SE_MAKE_SOURCE_LOGGER
#undef F4SE_MAYBE_UNUSED
