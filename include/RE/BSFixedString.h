#pragma once

#include "RE/BSGlobalStringTable.h"


namespace RE
{
	// u8 defaults to case-insensitive
	class BSFixedString
	{
	public:
		using value_type = char;
		using size_type = UInt32;
		using const_reference = const value_type&;

		// (constructor)
		BSFixedString();
		BSFixedString(const BSFixedString& a_rhs);
		BSFixedString(BSFixedString&& a_rhs) noexcept;
		BSFixedString(const char* a_rhs, bool a_ci = true);	// ci == case-insensitive
		BSFixedString(const std::string_view& a_rhs, bool a_ci = true);	// must be null terminated

		// (destructor)
		~BSFixedString();

		// operator=
		BSFixedString& operator=(const BSFixedString& a_rhs);
		BSFixedString& operator=(BSFixedString&& a_rhs);
		BSFixedString& operator=(const char* a_rhs);
		BSFixedString& operator=(const std::string_view& a_rhs);	// must be null terminated

		// Element access
		const_reference at(size_type a_pos) const;

		const_reference operator[](size_type a_pos) const;

		const char& front() const;

		const char& back() const;

		const char* data() const noexcept;

		const char* c_str() const noexcept;

		operator std::string_view() const noexcept;

		// Capacity
		bool empty() const noexcept;

		size_type size() const noexcept;

		size_type length() const noexcept;

	private:
		void ctor(const char* a_string, bool a_ci);
		void dtor();	// post: _data == 0


		// members
		GlobalStringHandle _data;	// 00
	};
	STATIC_ASSERT(sizeof(BSFixedString) == 0x8);


	// u16 defaults to case-sensitive
	class BSFixedStringW
	{
	public:
		using value_type = wchar_t;
		using size_type = UInt32;
		using const_reference = const value_type&;

		// (constructor)
		BSFixedStringW();
		BSFixedStringW(const BSFixedStringW& a_rhs);
		BSFixedStringW(BSFixedStringW&& a_rhs) noexcept;
		BSFixedStringW(const wchar_t* a_rhs);
		BSFixedStringW(const std::wstring_view& a_rhs);	// must be null terminated

		// (destructor)
		~BSFixedStringW();

		// operator=
		BSFixedStringW& operator=(const BSFixedStringW& a_rhs);
		BSFixedStringW& operator=(BSFixedStringW&& a_rhs);
		BSFixedStringW& operator=(const wchar_t* a_rhs);
		BSFixedStringW& operator=(const std::wstring_view& a_rhs);	// must be null terminated

		// Element access
		const_reference at(size_type a_pos) const;

		const_reference operator[](size_type a_pos) const;

		const wchar_t& front() const;

		const wchar_t& back() const;

		const wchar_t* data() const noexcept;

		const wchar_t* c_str() const noexcept;

		operator std::wstring_view() const noexcept;

		// Capacity
		bool empty() const noexcept;

		size_type size() const noexcept;

		size_type length() const noexcept;

	private:
		void ctor(const wchar_t* a_string);
		void dtor();	// post: _data == 0


		// members
		GlobalStringHandle _data;	// 00
	};
	STATIC_ASSERT(sizeof(BSFixedStringW) == 0x8);
}
