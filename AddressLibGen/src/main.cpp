#pragma warning(push)
#pragma warning(disable: 4702)  // unreachable code
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <robin_hood.h>
#include <srell.hpp>
#pragma warning(pop)

using namespace std::literals;

class Version
{
public:
	using value_type = std::uint16_t;
	using reference = value_type&;
	using const_reference = const value_type&;

	constexpr Version() noexcept = default;

	constexpr Version(std::array<value_type, 4> a_version) noexcept :
		_impl(a_version)
	{}

	[[nodiscard]] constexpr reference operator[](std::size_t a_idx) noexcept { return _impl[a_idx]; }
	[[nodiscard]] constexpr const_reference operator[](std::size_t a_idx) const noexcept { return _impl[a_idx]; }

	[[nodiscard]] int constexpr compare(const Version& a_rhs) const noexcept
	{
		for (std::size_t i = 0; i < _impl.size(); ++i) {
			if ((*this)[i] != a_rhs[i]) {
				return (*this)[i] < a_rhs[i] ? -1 : 1;
			}
		}
		return 0;
	}

	[[nodiscard]] std::string string() const
	{
		std::string result;
		for (std::size_t i = 0; i < _impl.size(); ++i) {
			result += std::to_string(_impl[i]);
			result += '-';
		}
		result.pop_back();
		return result;
	}

	[[nodiscard]] std::wstring wstring() const
	{
		std::wstring result;
		for (std::size_t i = 0; i < _impl.size(); ++i) {
			result += std::to_wstring(_impl[i]);
			result += L'-';
		}
		result.pop_back();
		return result;
	}

private:
	std::array<value_type, 4> _impl{ 0, 0, 0, 0 };
};

[[nodiscard]] constexpr bool operator==(const Version& a_lhs, const Version& a_rhs) noexcept { return a_lhs.compare(a_rhs) == 0; }
[[nodiscard]] constexpr bool operator!=(const Version& a_lhs, const Version& a_rhs) noexcept { return a_lhs.compare(a_rhs) != 0; }
[[nodiscard]] constexpr bool operator<(const Version& a_lhs, const Version& a_rhs) noexcept { return a_lhs.compare(a_rhs) < 0; }
[[nodiscard]] constexpr bool operator<=(const Version& a_lhs, const Version& a_rhs) noexcept { return a_lhs.compare(a_rhs) <= 0; }
[[nodiscard]] constexpr bool operator>(const Version& a_lhs, const Version& a_rhs) noexcept { return a_lhs.compare(a_rhs) > 0; }
[[nodiscard]] constexpr bool operator>=(const Version& a_lhs, const Version& a_rhs) noexcept { return a_lhs.compare(a_rhs) >= 0; }

class Mapping
{
public:
	[[nodiscard]] constexpr bool assigned() const noexcept { return static_cast<bool>(_id); }

	void assign(std::uint64_t a_id) noexcept
	{
		_id = a_id;
		for (auto& link : _links) {
			if (!link->assigned()) {
				link->assign(a_id);
			}
		}
	}

	[[nodiscard]] constexpr std::uint64_t id() const noexcept
	{
		assert(assigned());
		return *_id;
	}

	void link(Mapping* a_mapping) { _links.insert(a_mapping); }

private:
	std::set<Mapping*> _links;
	std::optional<std::uint64_t> _id;
};

using files_t = std::vector<std::tuple<Version, Version, std::filesystem::path>>;

[[nodiscard]] files_t get_files(const std::filesystem::path& a_root)
{
	files_t results;
	srell::wregex regex(L"(\\d+)\\.(\\d+)\\.(\\d+)_(\\d+)\\.(\\d+)\\.(\\d+)\\.txt"s, srell::regex::ECMAScript);
	for (const auto& entry : std::filesystem::directory_iterator(a_root)) {
		if (entry.is_regular_file()) {
			const auto filename = entry.path().filename();
			srell::wsmatch matches;
			if (srell::regex_match(filename.native(), matches, regex) && matches.size() == 7) {
				results.emplace_back();
				auto& [lversion, rversion, path] = results.back();

				const auto extract = [&]<std::size_t I>(std::in_place_index_t<I>) {
					return static_cast<std::uint16_t>(std::stoull(matches[I]));
				};

				lversion[0] = extract(std::in_place_index<1>);
				lversion[1] = extract(std::in_place_index<2>);
				lversion[2] = extract(std::in_place_index<3>);

				rversion[0] = extract(std::in_place_index<4>);
				rversion[1] = extract(std::in_place_index<5>);
				rversion[2] = extract(std::in_place_index<6>);

				path = entry.path();
			}
		}
	}
	return results;
}

using offset_map = robin_hood::unordered_node_map<std::uint64_t, Mapping>;
//using offset_map = std::unordered_map<std::uint64_t, Mapping>;
using version_map = std::map<Version, offset_map>;

[[nodiscard]] version_map load_mappings(const files_t& a_files)
{
	version_map map;
	std::ifstream file;
	std::stringstream ss;
	std::string line;
	std::string lbuf;
	std::string rbuf;

	const auto find_or_emplace_version = [&map](const Version& a_version) -> offset_map& {
		auto it = map.find(a_version);
		if (it == map.end()) {
			it = map.emplace(a_version, offset_map()).first;
		}
		return it->second;
	};

	const auto find_or_emplace_address = [](offset_map& a_map, std::string a_address) -> Mapping& {
		auto address = static_cast<std::uint64_t>(std::stoull(a_address, 0, 16));
		address -= 0x140000000;
		auto it = a_map.find(address);
		if (it == a_map.end()) {
			it = a_map.emplace(address, Mapping()).first;
		}
		return it->second;
	};

	for (const auto& [lver, rver, path] : a_files) {
		file.open(path);
		if (!file.is_open()) {
			throw std::runtime_error("failed to open file for read"s);
		}
		for (std::size_t i = 0; i < 18; ++i) {
			std::getline(file, line);  // skip header
		}

		auto& laddr = find_or_emplace_version(lver);
		auto& raddr = find_or_emplace_version(rver);

		while (std::getline(file, line)) {
			ss.str(line);
			ss.clear();
			std::getline(ss, lbuf, '\t');
			std::getline(ss, rbuf, '\t');
			if (ss && !lbuf.empty() && !rbuf.empty()) {
				auto& lmap = find_or_emplace_address(laddr, lbuf);
				auto& rmap = find_or_emplace_address(raddr, rbuf);
				lmap.link(std::addressof(rmap));
				rmap.link(std::addressof(lmap));
			}
		}

		file.close();
	}

	return map;
}

void assign_ids(version_map& a_versionMap)
{
	std::uint64_t id = 0;
	for (auto& [ver, offsetMap] : a_versionMap) {
		for (auto& [offset, mapping] : offsetMap) {
			if (!mapping.assigned()) {
				mapping.assign(id++);
			}
		}
	}
}

void write_binaries(version_map& a_versionMap)
{
	std::ofstream file;
	const auto binary_write = [&file](auto&& a_data) {
		file.write(
			reinterpret_cast<const char*>(std::addressof(a_data)),
			sizeof(std::remove_reference_t<decltype(a_data)>));
	};

	std::string filename;
	std::vector<std::pair<std::uint64_t, Mapping>> mappings;
	for (const auto& [ver, offsetMap] : a_versionMap) {
		filename = "version-"sv;
		filename += ver.string();
		filename += ".bin"sv;
		file.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
		if (!file.is_open()) {
			throw std::runtime_error("failed to open file for write"s);
		}

		mappings.clear();
		mappings.reserve(offsetMap.size());
		for (const auto& [first, second] : offsetMap) {
			mappings.emplace_back(first, second);
		}
		std::sort(
			mappings.begin(),
			mappings.end(),
			[](auto&& a_lhs, auto&& a_rhs) {
				return a_lhs.second.id() < a_rhs.second.id();
			});

		binary_write(static_cast<std::uint64_t>(mappings.size()));
		for (const auto& [offset, mapped] : mappings) {
			binary_write(mapped.id());
			binary_write(offset);
		}

		file.close();
	}
}

int main()
{
	try {
		auto mappings = load_mappings(get_files("mappings"sv));
		assign_ids(mappings);
		write_binaries(mappings);
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
