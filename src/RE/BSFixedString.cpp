#include "RE/BSFixedString.h"

#include "f4se/GameTypes.h"

#include <stdexcept>
#include <string>

#include "RE/Offset.h"
#include "REL/Relocation.h"


namespace RE
{
	BSFixedString::BSFixedString() :
		_data(0)
	{
		ctor("", false);
	}


	BSFixedString::BSFixedString(const BSFixedString& a_rhs) :
		_data(0)
	{
		ctor(a_rhs.c_str(), false);
	}


	BSFixedString::BSFixedString(BSFixedString&& a_rhs) noexcept :
		_data(std::move(a_rhs._data))
	{

		a_rhs._data = 0;
	}


	BSFixedString::BSFixedString(const char* a_rhs, bool a_ci) :
		_data(0)
	{
		ctor(a_rhs, a_ci);
	}


	BSFixedString::BSFixedString(const std::string_view& a_rhs, bool a_ci) :
		_data(0)
	{
		ctor(a_rhs.data(), a_ci);
	}


	BSFixedString::~BSFixedString()
	{
		dtor();
	}


	BSFixedString& BSFixedString::operator=(const BSFixedString& a_rhs)
	{
		if (this == &a_rhs) {
			return *this;
		}

		dtor();
		ctor(a_rhs.c_str(), true);
		return *this;
	}


	BSFixedString& BSFixedString::operator=(BSFixedString&& a_rhs)
	{
		if (this == &a_rhs) {
			return *this;
		}

		dtor();
		_data = std::move(a_rhs._data);
		a_rhs._data = 0;
		return *this;
	}


	BSFixedString& BSFixedString::operator=(const char* a_rhs)
	{
		dtor();
		ctor(a_rhs, true);
		return *this;
	}


	BSFixedString& BSFixedString::operator=(const std::string_view& a_rhs)
	{
		dtor();
		ctor(a_rhs.data(), true);
		return *this;
	}


	auto BSFixedString::at(size_type a_pos) const
		-> const_reference
	{
		if (a_pos >= size()) {
			std::string err = __FUNCTION__;
			err += ": ";
			err += MAKE_STR(a_pos);
			err += " (which is" + std::to_string(a_pos) + ") >= this->size() (which is" + std::to_string(this->size()) + ")";
			throw std::out_of_range(err);
		} else {
			return operator[](a_pos);
		}
	}


	auto BSFixedString::operator[](size_type a_pos) const
		-> const_reference
	{
		return data()[a_pos];
	}


	const char& BSFixedString::front() const
	{
		return operator[](0);
	}


	const char& BSFixedString::back() const
	{
		return operator[](size() - 1);
	}


	const char* BSFixedString::data() const
	{
		return _data ? _data->GetDataU8() : "";
	}


	const char* BSFixedString::c_str() const
	{
		return data();
	}


	BSFixedString::operator std::string_view() const
	{
		return { data(), size() };
	}


	bool BSFixedString::empty() const
	{
		return _data ? size() == 0 : true;
	}


	auto BSFixedString::size() const
		-> size_type
	{
		return _data ? _data->GetLength() : 0;
	}


	auto BSFixedString::length() const
		-> size_type
	{
		return size();
	}


	void BSFixedString::clear()
	{
		dtor();
		ctor("", true);
	}


	void BSFixedString::ctor(const char* a_string, bool a_ci)
	{
		using func_t = function_type_t<decltype(&BSFixedString::ctor)>;
		REL::Offset<func_t*> func(Offset::BSFixedString::CtorU8);
		return func(this, a_string, a_ci);
	}


	void BSFixedString::dtor()
	{
		using func_t = function_type_t<decltype(&BSFixedString::dtor)>;
		func_t* func = EXTRACT_F4SE_MEMBER_FN_ADDR(::BSFixedString, Release, func_t*);
		return func(this);
	}


	BSFixedStringW::BSFixedStringW() :
		_data(0)
	{
		ctor(L"");
	}


	BSFixedStringW::BSFixedStringW(const BSFixedStringW& a_rhs) :
		_data(0)
	{
		ctor(a_rhs.c_str());
	}


	BSFixedStringW::BSFixedStringW(BSFixedStringW&& a_rhs) noexcept :
		_data(std::move(a_rhs._data))
	{
		a_rhs._data = 0;
	}


	BSFixedStringW::BSFixedStringW(const wchar_t* a_rhs) :
		_data(0)
	{
		ctor(a_rhs);
	}


	BSFixedStringW::BSFixedStringW(const std::wstring_view& a_rhs)
	{
		ctor(a_rhs.data());
	}


	BSFixedStringW::~BSFixedStringW()
	{
		dtor();
	}


	BSFixedStringW& BSFixedStringW::operator=(const BSFixedStringW& a_rhs)
	{
		if (this == &a_rhs) {
			return *this;
		}

		dtor();
		ctor(a_rhs.c_str());
		return *this;
	}


	BSFixedStringW& BSFixedStringW::operator=(BSFixedStringW&& a_rhs)
	{
		if (this == &a_rhs) {
			return *this;
		}

		dtor();
		_data = std::move(a_rhs._data);
		a_rhs._data = 0;
		return *this;
	}


	BSFixedStringW& BSFixedStringW::operator=(const wchar_t* a_rhs)
	{
		dtor();
		ctor(a_rhs);
		return *this;
	}


	BSFixedStringW& BSFixedStringW::operator=(const std::wstring_view& a_rhs)
	{
		dtor();
		ctor(a_rhs.data());
		return *this;
	}


	auto BSFixedStringW::at(size_type a_pos) const
		-> const_reference
	{
		if (a_pos >= size()) {
			std::string err = __FUNCTION__;
			err += ": ";
			err += MAKE_STR(a_pos);
			err += " (which is" + std::to_string(a_pos) + ") >= this->size() (which is" + std::to_string(this->size()) + ")";
			throw std::out_of_range(err);
		} else {
			return operator[](a_pos);
		}
	}


	auto BSFixedStringW::operator[](size_type a_pos) const
		-> const_reference
	{
		return data()[a_pos];
	}


	const wchar_t& BSFixedStringW::front() const
	{
		return operator[](0);
	}


	const wchar_t& BSFixedStringW::back() const
	{
		return operator[](size() - 1);
	}


	const wchar_t* BSFixedStringW::data() const
	{
		return _data ? _data->GetDataU16() : L"";
	}


	const wchar_t* BSFixedStringW::c_str() const
	{
		return data();
	}


	BSFixedStringW::operator std::wstring_view() const
	{
		return { data(), size() };
	}


	bool BSFixedStringW::empty() const
	{
		return size() == 0;
	}


	auto BSFixedStringW::size() const
		-> size_type
	{
		return _data ? _data->GetLength() : 0;
	}


	auto BSFixedStringW::length() const
		-> size_type
	{
		return size();
	}


	void BSFixedStringW::clear()
	{
		dtor();
		ctor(L"");
	}


	void BSFixedStringW::ctor(const wchar_t* a_string)
	{
		using func_t = function_type_t<decltype(&BSFixedStringW::ctor)>;
		func_t* func = EXTRACT_F4SE_MEMBER_FN_ADDR(::BSFixedStringW, ctor_w, func_t*);
		return func(this, a_string);
	}


	void BSFixedStringW::dtor()
	{
		using func_t = function_type_t<decltype(&BSFixedStringW::dtor)>;
		func_t* func = EXTRACT_F4SE_MEMBER_FN_ADDR(::BSFixedStringW, Release, func_t*);
		return func(this);
	}
}
