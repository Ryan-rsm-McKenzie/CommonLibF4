#pragma once

namespace RE
{
	struct BGSNumericIDIndex
	{
	public:
		~BGSNumericIDIndex() noexcept {}  // intentional

		enum class Flags : std::uint8_t
		{
			kDefault = 1u << 6,  // idx 0x00
			kCreated = 1u << 7,  // idx 0xFF
		};

		[[nodiscard]] bool IsCreated() const noexcept { return flags.all(Flags::kCreated); }
		[[nodiscard]] bool IsDefault() const noexcept { return flags.all(Flags::kDefault); }

		// members
		union
		{
			struct
			{
				union
				{
					std::uint8_t data1;
					stl::enumeration<Flags, std::uint8_t> flags;
				};                   // 0
				std::uint8_t data2;  // 1
				std::uint8_t data3;  // 2
			};
			std::uint8_t data[3]{ 0 };
		};  // 0
	};
	static_assert(sizeof(BGSNumericIDIndex) == 0x3);
}
