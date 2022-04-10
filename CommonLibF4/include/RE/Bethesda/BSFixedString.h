#pragma once

#include "RE/Bethesda/BSStringPool.h"
#include "RE/Bethesda/CRC.h"
#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	namespace detail
	{
		template <class CharT, bool CS>
		class BSFixedString
		{
		public:
			using size_type = std::uint32_t;
			using value_type = CharT;
			using pointer = value_type*;
			using const_pointer = const value_type*;
			using reference = value_type&;
			using const_reference = const value_type&;

			BSFixedString() noexcept = default;
			BSFixedString(const volatile BSFixedString&) = delete;
			BSFixedString& operator=(const volatile BSFixedString&) = delete;

			template <bool B>
			BSFixedString(const BSFixedString<value_type, B>& a_rhs) :
				_data(a_rhs._data)
			{
				try_acquire();
			}

			template <bool B>
			BSFixedString(BSFixedString<value_type, B>&& a_rhs) noexcept :
				_data(std::exchange(a_rhs._data, nullptr))
			{}

			BSFixedString(const_pointer a_string)
			{
				if (a_string) {
					GetEntry<value_type>(_data, a_string, CS);
				}
			}

			template <class T>
			BSFixedString(const T& a_string)  //
				requires(std::convertible_to<const T&, std::basic_string_view<value_type>> &&
						 !std::convertible_to<const T&, const_pointer> &&
						 !std::same_as<T, BSFixedString<value_type, true>> &&
						 !std::same_as<T, BSFixedString<value_type, false>>)
			{
				const auto view = static_cast<std::basic_string_view<value_type>>(a_string);
				if (!view.empty()) {
					assert(view.data()[view.length()] == value_type{});
					GetEntry<value_type>(_data, view.data(), CS);
				}
			}

			~BSFixedString() { try_release(); }

			template <bool B>
			BSFixedString& operator=(const BSFixedString<value_type, B>& a_rhs)
			{
				if (this != std::addressof(a_rhs)) {
					try_release();
					_data = a_rhs._data;
					try_acquire();
				}
				return *this;
			}

			template <bool B>
			BSFixedString& operator=(BSFixedString<value_type, B>&& a_rhs)
			{
				if (this != std::addressof(a_rhs)) {
					std::swap(this->_data, a_rhs._data);
				}
				return *this;
			}

			BSFixedString& operator=(const_pointer a_string)
			{
				try_release();
				if (a_string) {
					GetEntry<value_type>(_data, a_string, CS);
				}
				return *this;
			}

			template <class T>
			BSFixedString& operator=(const T& a_string)  //
				requires(std::convertible_to<const T&, std::basic_string_view<value_type>> &&
						 !std::convertible_to<const T&, const_pointer> &&
						 !std::same_as<T, BSFixedString<value_type, true>> &&
						 !std::same_as<T, BSFixedString<value_type, false>>)
			{
				const auto view = static_cast<std::basic_string_view<value_type>>(a_string);
				try_release();
				if (!view.empty()) {
					assert(view.data()[view.length()] == value_type{});
					GetEntry<value_type>(_data, view.data(), CS);
				}
				return *this;
			}

			[[nodiscard]] const_reference front() const noexcept { return data()[0]; }
			[[nodiscard]] const_reference back() const noexcept { return data()[size() - 1]; }

			[[nodiscard]] const_pointer data() const noexcept
			{
				const auto cstr = _data ? _data->data<value_type>() : nullptr;
				return cstr ? cstr : EMPTY;
			}

			[[nodiscard]] const_pointer c_str() const noexcept { return data(); }

			[[nodiscard]] operator std::basic_string_view<value_type>() const noexcept { return { c_str(), length() }; }

			[[nodiscard]] bool empty() const noexcept { return size() == 0; }

			[[nodiscard]] size_type size() const noexcept { return _data ? _data->size() : 0; }
			[[nodiscard]] size_type length() const noexcept { return _data ? _data->length() : 0; }

			template <class T>
			[[nodiscard]] friend bool operator==(const T& a_lhs, const T& a_rhs) noexcept
				requires(std::same_as<T, BSFixedString>)
			{
				const auto leaf = [](const BSFixedString& a_elem) { return a_elem._data ? a_elem._data->leaf() : nullptr; };
				const auto lLeaf = leaf(a_lhs);
				const auto rLeaf = leaf(a_rhs);
				if (lLeaf == rLeaf) {
					return true;
				} else if (a_lhs.empty() && a_rhs.empty()) {
					return true;
				} else {
					return false;
				}
			}

			[[nodiscard]] friend bool operator==(const BSFixedString& a_lhs, std::basic_string_view<value_type> a_rhs)
			{
				if (a_lhs.empty() && a_rhs.empty()) {
					return true;
				} else if (const auto length = a_lhs.length(); length != a_rhs.length()) {
					return false;
				} else {
					return strncmp(a_lhs.c_str(), a_rhs.data(), length) == 0;
				}
			}

		protected:
			template <class>
			friend struct RE::BSCRC32;

			[[nodiscard]] const void* hash_accessor() const noexcept { return _data; }

		private:
			template <class, bool>
			friend class BSFixedString;

			[[nodiscard]] static int strncmp(const char* a_lhs, const char* a_rhs, std::size_t a_length)
			{
				if constexpr (CS) {
					return std::strncmp(a_lhs, a_rhs, a_length);
				} else {
					return _strnicmp(a_lhs, a_rhs, a_length);
				}
			}

			[[nodiscard]] static int strncmp(const wchar_t* a_lhs, const wchar_t* a_rhs, std::size_t a_length)
			{
				if constexpr (CS) {
					return std::wcsncmp(a_lhs, a_rhs, a_length);
				} else {
					return _wcsnicmp(a_lhs, a_rhs, a_length);
				}
			}

			void try_acquire()
			{
				if (_data) {
					_data->acquire();
				}
			}

			void try_release() { BSStringPool::Entry::release(_data); }

			static constexpr const value_type EMPTY[]{ 0 };

			// members
			BSStringPool::Entry* _data{ nullptr };  // 0
		};

		extern template class BSFixedString<char, false>;
		extern template class BSFixedString<char, true>;
		extern template class BSFixedString<wchar_t, false>;
		extern template class BSFixedString<wchar_t, true>;
	}

	using BSFixedString = detail::BSFixedString<char, false>;
	using BSFixedStringCS = detail::BSFixedString<char, true>;
	using BSFixedStringW = detail::BSFixedString<wchar_t, false>;
	using BSFixedStringWCS = detail::BSFixedString<wchar_t, true>;

	namespace BSScript
	{
		template <class>
		struct script_traits;

		template <>
		struct script_traits<RE::BSFixedString> final
		{
			using is_string = std::true_type;
		};

		template <>
		struct script_traits<RE::BSFixedStringCS> final
		{
			using is_string = std::true_type;
		};
	}

	template <class CharT, bool CS>
	struct BSCRC32<detail::BSFixedString<CharT, CS>>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const detail::BSFixedString<CharT, CS>& a_key) const noexcept
		{
			return BSCRC32<const void*>()(a_key.hash_accessor());
		}
	};

	extern template struct BSCRC32<BSFixedString>;
	extern template struct BSCRC32<BSFixedStringCS>;
	extern template struct BSCRC32<BSFixedStringW>;
	extern template struct BSCRC32<BSFixedStringWCS>;

	class BGSLocalizedString
	{
	public:
		using size_type = typename BSFixedStringCS::size_type;
		using value_type = typename BSFixedStringCS::value_type;
		using pointer = typename BSFixedStringCS::pointer;
		using const_pointer = typename BSFixedStringCS::const_pointer;
		using reference = typename BSFixedStringCS::reference;
		using const_reference = typename BSFixedStringCS::const_reference;

		BGSLocalizedString& operator=(std::basic_string_view<value_type> a_rhs)
		{
			const auto self = static_cast<std::basic_string_view<value_type>>(_data);
			if (self.starts_with("<ID=")) {
				assert(self.length() >= PREFIX_LENGTH);
				std::vector<char> buf(PREFIX_LENGTH + a_rhs.length() + 1, '\0');
				strncpy_s(buf.data(), buf.size(), self.data(), PREFIX_LENGTH);
				strcpy_s(buf.data() + PREFIX_LENGTH, buf.size() - PREFIX_LENGTH, (a_rhs.empty() ? "" : a_rhs.data()));
				_data = std::string_view{ buf.data(), buf.size() };
			} else {
				_data = a_rhs;
			}

			return *this;
		}

		[[nodiscard]] const_pointer data() const noexcept { return _data.data(); }
		[[nodiscard]] const_pointer c_str() const noexcept { return _data.c_str(); }

		[[nodiscard]] operator std::basic_string_view<value_type>() const { return { _data }; }

		[[nodiscard]] bool empty() const noexcept { return _data.empty(); }

		[[nodiscard]] size_type size() const noexcept { return _data.size(); }
		[[nodiscard]] size_type length() const noexcept { return _data.length(); }

	protected:
		template <class>
		friend struct BSCRC32;

		[[nodiscard]] const BSFixedStringCS& hash_accessor() const noexcept { return _data; }

	private:
		static constexpr std::size_t PREFIX_LENGTH = 13;

		// members
		BSFixedStringCS _data;  // 0
	};
	static_assert(sizeof(BGSLocalizedString) == 0x8);

	template <>
	struct BSCRC32<BGSLocalizedString>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const BGSLocalizedString& a_key) const noexcept
		{
			return BSCRC32<BSFixedStringCS>()(a_key.hash_accessor());
		}
	};

	struct BGSLocalizedStrings
	{
		struct ScrapStringBuffer
		{
		public:
			[[nodiscard]] const char* GetString() const noexcept { return static_cast<const char*>(buffer.GetPtr()) + offset; }

			// members
			MemoryManager::AutoScrapBuffer buffer;  // 00
			std::size_t offset;                     // 08
		};
		static_assert(sizeof(ScrapStringBuffer) == 0x10);
	};
	static_assert(std::is_empty_v<BGSLocalizedStrings>);
}
