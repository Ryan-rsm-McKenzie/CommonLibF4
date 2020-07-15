#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

using namespace std::literals;

int main(int a_argc, char* a_argv[])
{
	try {
		std::ifstream input;
		std::ofstream output;
		const auto read_binary = [&input](auto& a_data) {
			input.read(
				reinterpret_cast<char*>(std::addressof(a_data)),
				sizeof(std::remove_reference_t<decltype(a_data)>));
		};

		for (int i = 1; i < a_argc; ++i) {
			std::filesystem::path filename = a_argv[static_cast<std::size_t>(i)];
			input.open(filename, std::ios::in | std::ios::binary);
			if (!input.is_open()) {
				throw std::runtime_error("failed to open: "s + filename.string());
			}

			filename.replace_extension(".txt"sv);
			output.open(filename, std::ios::out | std::ios::trunc);
			if (!output.is_open()) {
				throw std::runtime_error("failed to open: "s + filename.string());
			}

			std::uint64_t size = 0;
			read_binary(size);
			while (size--) {
				std::uint64_t id = 0;
				std::uint64_t offset = 0;
				read_binary(id);
				read_binary(offset);
				output << std::dec << id << '\t' << std::hex << offset << '\n';
			}

			input.close();
			output.close();
		}
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
