#pragma once

namespace RE
{
	struct BSStringPool
	{
	public:
		class Entry
		{
		public:
			enum : std::uint16_t
			{
				kShallow = 1 << 14,
				kWide = 1 << 15,
				kRefCountMask = 0x3FFF
			};

			static void release(Entry*& a_entry)
			{
				using func_t = decltype(&Entry::release);
				REL::Relocation<func_t> func{ REL::ID(1204430) };
				return func(a_entry);
			}

			void acquire()
			{
				stl::atomic_ref flags{ _flags };
				std::uint16_t expected{ 0 };
				do {
					expected = flags;
					if ((expected & kRefCountMask) >= kRefCountMask) {
						break;
					}
				} while (!flags.compare_exchange_weak(expected, static_cast<std::uint16_t>(expected + 1)));
			}

			[[nodiscard]] std::uint16_t crc() const noexcept { return _crc; }

			template <class T>
			[[nodiscard]] const T* data() const noexcept;

			template <>
			[[nodiscard]] const char* data<char>() const noexcept
			{
				return u8();
			}

			template <>
			[[nodiscard]] const wchar_t* data<wchar_t>() const noexcept
			{
				return u16();
			}

			[[nodiscard]] const Entry* leaf() const noexcept
			{
				auto iter = this;
				while (iter && iter->shallow()) {
					iter = iter->_right;
				}
				return iter;
			}

			[[nodiscard]] std::uint32_t length() const noexcept
			{
				const auto entry = leaf();
				return entry ? entry->_length : 0;
			}

			[[nodiscard]] bool shallow() const noexcept { return _flags & kShallow; }
			[[nodiscard]] std::uint32_t size() const noexcept { return length(); }

			[[nodiscard]] const char* u8() const noexcept
			{
				const auto entry = leaf();
				if (entry) {
					assert(!entry->wide());
					return reinterpret_cast<const char*>(entry + 1);
				} else {
					return nullptr;
				}
			}

			[[nodiscard]] const wchar_t* u16() const noexcept
			{
				const auto entry = leaf();
				if (entry) {
					assert(entry->wide());
					return reinterpret_cast<const wchar_t*>(entry + 1);
				} else {
					return nullptr;
				}
			}

			[[nodiscard]] bool wide() const noexcept { return _flags & kWide; }

			// members
			Entry* _left;                 // 00
			std::uint16_t _flags;         // 08
			volatile std::uint16_t _crc;  // 08
			union
			{
				std::uint32_t _length;
				Entry* _right;
			};  // 10
		};
		static_assert(sizeof(Entry) == 0x18);
	};
	static_assert(std::is_empty_v<BSStringPool>);

	struct BucketTable
	{
	public:
		struct alignas(0x10) AlignedLock
		{
		public:
			// members
			volatile std::uint32_t val;  // 00
		};
		static_assert(sizeof(AlignedLock) == 0x10);

		static BucketTable& GetSingleton()
		{
			using func_t = decltype(&BucketTable::GetSingleton);
			REL::Relocation<func_t> func{ REL::ID(1390486) };
			return func();
		}

		// members
		BSStringPool::Entry* buckets[0x10000];  // 00000
		AlignedLock locks[0x10000 / 0x200];     // 80000
		bool initialized;                       // 80800
	};
	static_assert(sizeof(BucketTable) == 0x80810);

	template <class T>
	void GetEntry(BSStringPool::Entry*& a_result, const T* a_string, bool a_caseSensitive);

	template <>
	inline void GetEntry<char>(BSStringPool::Entry*& a_result, const char* a_string, bool a_caseSensitive)
	{
		using func_t = decltype(&GetEntry<char>);
		REL::Relocation<func_t> func{ REL::ID(507142) };
		return func(a_result, a_string, a_caseSensitive);
	}

	template <>
	inline void GetEntry<wchar_t>(BSStringPool::Entry*& a_result, const wchar_t* a_string, bool a_caseSensitive)
	{
		using func_t = decltype(&GetEntry<wchar_t>);
		REL::Relocation<func_t> func{ REL::ID(345043) };
		return func(a_result, a_string, a_caseSensitive);
	}
}
