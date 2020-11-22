#pragma once

namespace RE
{
	class __declspec(novtable) NiBinaryStream
	{
	public:
		static constexpr auto RTTI{ RTTI::NiBinaryStream };
		static constexpr auto VTABLE{ VTABLE::NiBinaryStream };

		struct BufferInfo;

		virtual ~NiBinaryStream();  // 00

		// add
		virtual explicit operator bool() const = 0;                                  // 01
		virtual void Seek(std::ptrdiff_t a_numBytes) = 0;                            // 02
		virtual std::size_t GetPosition() const { return absoluteCurrentPos; }       // 03
		virtual void GetBufferInfo(BufferInfo& a_info);                              // 04
		virtual std::size_t DoRead(void* a_buffer, std::size_t a_bytes) = 0;         // 05
		virtual std::size_t DoWrite(const void* a_buffer, std::size_t a_bytes) = 0;  // 06

		// members
		std::size_t absoluteCurrentPos;  // 08
	};
	static_assert(sizeof(NiBinaryStream) == 0x10);
}
