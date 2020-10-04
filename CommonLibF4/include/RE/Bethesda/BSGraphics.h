#pragma once

namespace RE
{
	struct ID3D11Buffer;
	struct ID3D11PixelShader;
	struct ID3D11VertexShader;

	struct BSGraphics
	{
		enum class TextureAddressMode;

		class ComputeShader;
		class DomainShader;
		class HullShader;
		class Texture;

		class ConstantGroup
		{
		public:
			// members
			ID3D11Buffer* buffer{ nullptr };	// 00
			float* data{ nullptr };				// 08
			bool dataIsCPUWorkBuffer{ false };	// 10
		};
		static_assert(sizeof(ConstantGroup) == 0x18);

		class PixelShader
		{
		public:
			// members
			std::uint32_t id{ 0 };						   // 00
			ID3D11PixelShader* shader{ nullptr };		   // 08
			BSGraphics::ConstantGroup constantBuffers[3];  // 10
			std::int8_t constantTable[32]{ 0 };			   // 58
		};
		static_assert(sizeof(PixelShader) == 0x78);

		class VertexShader
		{
		public:
			// members
			std::uint32_t id{ 0 };						   // 00
			ID3D11VertexShader* shader{ nullptr };		   // 08
			std::uint32_t byteCodeSize{ 0 };			   // 10
			BSGraphics::ConstantGroup constantBuffers[3];  // 18
			std::uint64_t shaderDesc{ 0 };				   // 60
			std::int8_t constantTable[32]{ 0 };			   // 68
		};
		static_assert(sizeof(VertexShader) == 0x88);
	};
	static_assert(std::is_empty_v<BSGraphics>);
}
