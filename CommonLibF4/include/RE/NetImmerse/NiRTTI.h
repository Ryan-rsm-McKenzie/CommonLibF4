#pragma once

namespace RE
{
	struct NiRTTI
	{
	public:
		[[nodiscard]] constexpr const char* GetName() const noexcept { return name; }

		// members
		const char* name;  // 00
		NiRTTI* baseRTTI;  // 08
	};
	static_assert(sizeof(NiRTTI) == 0x10);
}
