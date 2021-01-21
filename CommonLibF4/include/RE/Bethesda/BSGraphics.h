#pragma once

#include "RE/Bethesda/BSTHashMap.h"

namespace RE
{
	struct ID3D11Buffer;
	struct ID3D11ComputeShader;
	struct ID3D11DomainShader;
	struct ID3D11HullShader;
	struct ID3D11PixelShader;
	struct ID3D11VertexShader;

	struct BSGraphics
	{
		enum class TextureAddressMode;

		class Texture;

		class ConstantGroup
		{
		public:
			// members
			ID3D11Buffer* buffer{ nullptr };    // 00
			float* data{ nullptr };             // 08
			bool dataIsCPUWorkBuffer{ false };  // 10
		};
		static_assert(sizeof(ConstantGroup) == 0x18);

		class ComputeShader
		{
		public:
			// members
			std::uint32_t id{ 0 };                         // 00
			ID3D11ComputeShader* shader{ nullptr };        // 08
			std::uint32_t byteCodeSize{ 0 };               // 10
			BSGraphics::ConstantGroup constantBuffers[3];  // 18
			std::uint64_t shaderDesc{ 0 };                 // 60
			std::int8_t constantTable[32]{ 0 };            // 68
		};
		static_assert(sizeof(ComputeShader) == 0x88);

		class DomainShader
		{
		public:
			// members
			std::uint32_t id{ 0 };                              // 00
			ID3D11DomainShader* shader{ nullptr };              // 08
			std::uint32_t byteCodeSize{ 0 };                    // 10
			BSGraphics::ConstantGroup constantBuffers[3]{ 0 };  // 18
			std::uint64_t shaderDesc{ 0 };                      // 60
			std::int8_t constantTable[32]{ 0 };                 // 68
		};
		static_assert(sizeof(DomainShader) == 0x88);

		class HullShader
		{
		public:
			// members
			std::uint32_t id{ 0 };                         // 00
			ID3D11HullShader* shader{ nullptr };           // 08
			std::uint32_t byteCodeSize{ 0 };               // 10
			BSGraphics::ConstantGroup constantBuffers[3];  // 18
			std::uint64_t shaderDesc{ 0 };                 // 60
			std::int8_t constantTable[32]{ 0 };            // 68
		};
		static_assert(sizeof(HullShader) == 0x88);

		class PixelShader
		{
		public:
			// members
			std::uint32_t id{ 0 };                         // 00
			ID3D11PixelShader* shader{ nullptr };          // 08
			BSGraphics::ConstantGroup constantBuffers[3];  // 10
			std::int8_t constantTable[32]{ 0 };            // 58
		};
		static_assert(sizeof(PixelShader) == 0x78);

		class VertexShader
		{
		public:
			// members
			std::uint32_t id{ 0 };                         // 00
			ID3D11VertexShader* shader{ nullptr };         // 08
			std::uint32_t byteCodeSize{ 0 };               // 10
			BSGraphics::ConstantGroup constantBuffers[3];  // 18
			std::uint64_t shaderDesc{ 0 };                 // 60
			std::int8_t constantTable[32]{ 0 };            // 68
		};
		static_assert(sizeof(VertexShader) == 0x88);
	};
	static_assert(std::is_empty_v<BSGraphics>);

	namespace BSShaderTechniqueIDMap
	{
		template <class T>
		struct HashPolicy
		{
			[[nodiscard]] std::uint32_t operator()(const T a_shader) const noexcept
			{
				assert(a_shader != nullptr);
				return a_shader->id;
			}
		};

		template <class T>
		struct ComparePolicy
		{
			[[nodiscard]] bool operator()(const T a_lhs, const T a_rhs) const noexcept
			{
				assert(a_lhs != nullptr);
				assert(a_rhs != nullptr);
				return a_lhs->id == a_rhs->id;
			}
		};

		template <class T>
		using MapType = BSTSet<T, HashPolicy<T>, ComparePolicy<T>>;
	}
}
