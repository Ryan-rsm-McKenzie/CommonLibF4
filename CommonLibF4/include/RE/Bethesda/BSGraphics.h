#pragma once

namespace RE
{
	struct BSGraphics
	{
		enum class TextureAddressMode;

		class ComputeShader;
		class DomainShader;
		class HullShader;
		class PixelShader;
		class Texture;
		class VertexShader;
	};
	static_assert(std::is_empty_v<BSGraphics>);
}
