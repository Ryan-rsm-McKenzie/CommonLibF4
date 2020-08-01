extern "C" bool DLLEXPORT F4SEPlugin_Query(const F4SE::QueryInterface* a_f4se, F4SE::PluginInfo* a_info)
{
	// ExampleProject
	try {
#ifndef NDEBUG
		auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
		auto path = logger::log_directory() / "ExampleProject.log";
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path.string(), true);
#endif

		auto log = std::make_shared<spdlog::logger>("global log", std::move(sink));

#ifndef NDEBUG
		log->set_level(spdlog::level::trace);
#else
		log->set_level(spdlog::level::info);
		log->flush_on(spdlog::level::warn);
#endif

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("%g(%#): [%^%l%$] %v");

		a_info->infoVersion = F4SE::PluginInfo::kVersion;
		a_info->name = "ExampleProject";
		a_info->version = 1;

		if (a_f4se->IsEditor()) {
			logger::critical("loaded in editor");
			return false;
		}

		const auto ver = a_f4se->RuntimeVersion();
		if (ver < F4SE::RUNTIME_1_10_162) {
			logger::critical("unsupported runtime v{}", ver.string());
			return false;
		}
	} catch (const std::exception& e) {
		logger::critical(e.what());
		return false;
	} catch (...) {
		logger::critical("caught unknown exception");
		return false;
	}

	return true;
}

extern "C" bool DLLEXPORT F4SEPlugin_Load(const F4SE::LoadInterface* a_f4se)
{
	try {
		if (!F4SE::Init(a_f4se)) {
			return false;
		}

		logger::info("hello world!");
	} catch (const std::exception& e) {
		logger::critical(e.what());
		return false;
	} catch (...) {
		logger::critical("caught unknown exception");
		return false;
	}

	return true;
}
