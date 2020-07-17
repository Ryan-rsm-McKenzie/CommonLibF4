#pragma once

// clang format chokes hard on classes with attributes
#define F4SE_MAYBE_UNUSED [[maybe_unused]]
#define F4SE_MAKE_SOURCE_LOGGER(a_func, a_type)                           \
                                                                          \
	template <class... Args>                                              \
	struct F4SE_MAYBE_UNUSED a_func                                       \
	{                                                                     \
		a_func(                                                           \
			spdlog::string_view_t a_fmt,                                  \
			const Args&... a_args,                                        \
			stl::source_location a_loc = stl::source_location::current()) \
		{                                                                 \
			spdlog::log(                                                  \
				spdlog::source_loc{                                       \
					a_loc.file_name(),                                    \
					static_cast<int>(a_loc.line()),                       \
					a_loc.function_name() },                              \
				spdlog::level::a_type,                                    \
				a_fmt,                                                    \
				a_args...);                                               \
		}                                                                 \
	};                                                                    \
                                                                          \
	template <>                                                           \
	struct F4SE_MAYBE_UNUSED a_func<>                                     \
	{                                                                     \
		a_func(                                                           \
			spdlog::string_view_t a_fmt,                                  \
			stl::source_location a_loc = stl::source_location::current()) \
		{                                                                 \
			spdlog::log(                                                  \
				spdlog::source_loc{                                       \
					a_loc.file_name(),                                    \
					static_cast<int>(a_loc.line()),                       \
					a_loc.function_name() },                              \
				spdlog::level::a_type,                                    \
				std::string_view(                                         \
					a_fmt.data(),                                         \
					a_fmt.size()));                                       \
		}                                                                 \
	};                                                                    \
                                                                          \
	template <class... Args>                                              \
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

		[[nodiscard]] inline std::filesystem::path log_directory()
		{
			wchar_t* buffer{ nullptr };
			auto result = SHGetKnownFolderPath(FOLDERID_Documents, KNOWN_FOLDER_FLAG::KF_FLAG_DEFAULT, nullptr, std::addressof(buffer));
			std::unique_ptr<wchar_t[], decltype(&CoTaskMemFree)> knownPath(buffer, CoTaskMemFree);
			if (!knownPath || result != S_OK) {
				throw std::runtime_error("failed to get known folder path"s);
			}

			std::filesystem::path path = knownPath.get();
			path /= "My Games/Fallout4/F4SE"sv;
			return path;
		}
	}
}

#undef F4SE_MAKE_SOURCE_LOGGER
#undef F4SE_MAYBE_UNUSED
