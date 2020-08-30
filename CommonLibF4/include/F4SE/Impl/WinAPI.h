#pragma once

namespace F4SE
{
	namespace WinAPI
	{
		inline constexpr auto(MEM_RELEASE){ static_cast<std::uint32_t>(0x00008000) };
		inline constexpr auto(PAGE_EXECUTE_READWRITE){ static_cast<std::uint32_t>(0x40) };

		struct CRITICAL_SECTION
		{
		public:
			// members
			void* DebugInfo;			  // 00
			std::int32_t LockCount;		  // 08
			std::int32_t RecursionCount;  // 0C
			void* OwningThread;			  // 10
			void* LockSemaphore;		  // 18
			std::uint64_t* SpinCount;	  // 20
		};
		static_assert(sizeof(CRITICAL_SECTION) == 0x28);

		[[nodiscard]] void*(GetCurrentModule)() noexcept;

		[[nodiscard]] std::uint32_t(GetCurrentThreadID)() noexcept;

		[[nodiscard]] bool(GetFileVersionInfo)(
			const char* a_filename,
			std::uint32_t a_handle,
			std::uint32_t a_len,
			void* a_data) noexcept;

		[[nodiscard]] bool(GetFileVersionInfo)(
			const wchar_t* a_filename,
			std::uint32_t a_handle,
			std::uint32_t a_len,
			void* a_data) noexcept;

		[[nodiscard]] std::uint32_t(GetFileVersionInfoSize)(
			const char* a_filename,
			std::uint32_t* a_handle) noexcept;

		[[nodiscard]] std::uint32_t(GetFileVersionInfoSize)(
			const wchar_t* a_filename,
			std::uint32_t* a_handle) noexcept;

		[[nodiscard]] std::size_t(GetMaxPath)() noexcept;

		[[nodiscard]] std::uint32_t(GetModuleFileName)(
			void* a_module,
			char* a_filename,
			std::uint32_t a_size) noexcept;

		[[nodiscard]] std::uint32_t(GetModuleFileName)(
			void* a_module,
			wchar_t* a_filename,
			std::uint32_t a_size) noexcept;

		[[nodiscard]] void*(GetModuleHandle)(
			const char* a_moduleName) noexcept;

		[[nodiscard]] void*(GetModuleHandle)(
			const wchar_t* a_moduleName) noexcept;

		std::int32_t(MessageBox)(
			void* a_wnd,
			const char* a_text,
			const char* a_caption,
			unsigned int a_type) noexcept;

		std::int32_t(MessageBox)(
			void* a_wnd,
			const wchar_t* a_text,
			const wchar_t* a_caption,
			unsigned int a_type) noexcept;

		bool(VirtualFree)(
			void* a_address,
			std::size_t a_size,
			std::uint32_t a_freeType) noexcept;

		[[nodiscard]] bool(VerQueryValue)(
			const void* a_block,
			const char* a_subBlock,
			void** a_buffer,
			unsigned int* a_len) noexcept;

		[[nodiscard]] bool(VerQueryValue)(
			const void* a_block,
			const wchar_t* a_subBlock,
			void** a_buffer,
			unsigned int* a_len) noexcept;

		[[nodiscard]] bool(VirtualProtect)(
			void* a_address,
			std::size_t a_size,
			std::uint32_t a_newProtect,
			std::uint32_t* a_oldProtect) noexcept;
	}
}
