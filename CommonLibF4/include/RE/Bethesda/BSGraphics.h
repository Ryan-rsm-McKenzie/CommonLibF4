#pragma once

namespace RE
{
	struct BSGraphics
	{
		enum class TextureAddressMode;

		class Texture;
	};
	static_assert(std::is_empty_v<BSGraphics>);
}
