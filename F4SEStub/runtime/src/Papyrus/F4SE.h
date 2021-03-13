#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace F4SE
	{
		inline std::int32_t GetPluginVersion(
			std::monostate,
			std::string_view a_name)
		{
			const auto plugin = ::F4SE::GetPluginInfo(a_name);
			return plugin ? static_cast<std::int32_t>(plugin->version) : -1;
		}

		inline std::uint32_t GetVersion(std::monostate)
		{
			const auto ver = ::F4SE::GetF4SEVersion();
			return ver[0];
		}

		inline std::uint32_t GetVersionBeta(std::monostate)
		{
			const auto ver = ::F4SE::GetF4SEVersion();
			return ver[2];
		}

		inline std::uint32_t GetVersionMinor(std::monostate)
		{
			const auto ver = ::F4SE::GetF4SEVersion();
			return ver[1];
		}

		inline std::uint32_t GetVersionRelease(std::monostate)
		{
			return ::F4SE::GetReleaseIndex();
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "F4SE"sv;

			if (::F4SE::GetF4SEVersion() >= REL::Version{ 0, 6, 22 }) {
				BIND(GetPluginVersion, true);
			}

			BIND(GetVersion, true);
			BIND(GetVersionBeta, true);
			BIND(GetVersionMinor, true);
			BIND(GetVersionRelease, true);

			logger::info("bound {} script"sv, obj);
		}
	}
}
