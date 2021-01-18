#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSTBTree.h"
#include "RE/Bethesda/BSTList.h"
#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	union SETTING_VALUE
	{
		std::int8_t c;
		bool b;
		float f;
		std::uint8_t h;
		std::int32_t i;
		char* s;
		std::uint32_t u;
		std::uint32_t r;
		std::uint32_t a;
	};

	class __declspec(novtable) Setting
	{
	public:
		static constexpr auto RTTI{ RTTI::Setting };
		static constexpr auto VTABLE{ VTABLE::Setting };

		enum class SETTING_TYPE
		{
			kBinary,  // b
			kChar,    // c
			kUChar,   // h
			kInt,     // i
			kUInt,    // u
			kFloat,   // f
			kString,  // s/S
			kRGB,     // r
			kRGBA,    // a
			kNone
		};

		virtual ~Setting()  // 00
		{
			if (_key && _key[0] == 'S') {
				free(const_cast<char*>(_key));
				_key = nullptr;
			}
		}

		// add
		[[nodiscard]] virtual bool IsPrefSetting() { return false; }  // 01

		F4_HEAP_REDEFINE_NEW(Setting);

		[[nodiscard]] bool GetBinary() const noexcept
		{
			assert(GetType() == SETTING_TYPE::kBinary);
			return _value.b;
		}

		[[nodiscard]] char GetChar() const noexcept
		{
			assert(GetType() == SETTING_TYPE::kChar);
			return _value.c;
		}

		[[nodiscard]] float GetFloat() const noexcept
		{
			assert(GetType() == SETTING_TYPE::kFloat);
			return _value.f;
		}

		[[nodiscard]] std::int32_t GetInt() const noexcept
		{
			assert(GetType() == SETTING_TYPE::kInt);
			return _value.i;
		}

		[[nodiscard]] std::string_view GetKey() const noexcept { return _key ? _key : ""sv; }

		[[nodiscard]] std::span<const std::uint8_t, 3> GetRGB() const noexcept
		{
			assert(GetType() == SETTING_TYPE::kRGB);
			return std::span<const std::uint8_t, 3>{
				reinterpret_cast<const std::uint8_t(&)[3]>(*std::addressof(_value.r))
			};
		}

		[[nodiscard]] std::span<const std::uint8_t, 4> GetRGBA() const noexcept
		{
			assert(GetType() == SETTING_TYPE::kRGBA);
			return std::span<const std::uint8_t, 4>{
				reinterpret_cast<const std::uint8_t(&)[4]>(*std::addressof(_value.a))
			};
		}

		[[nodiscard]] std::string_view GetString() const noexcept
		{
			assert(GetType() == SETTING_TYPE::kString);
			return _value.s ? _value.s : ""sv;
		}

		[[nodiscard]] SETTING_TYPE GetType() const noexcept
		{
			if (_key) {
				switch (_key[0]) {
				case 'b':
					return SETTING_TYPE::kBinary;
				case 'c':
					return SETTING_TYPE::kChar;
				case 'h':
					return SETTING_TYPE::kUChar;
				case 'i':
					return SETTING_TYPE::kInt;
				case 'u':
					return SETTING_TYPE::kUInt;
				case 'f':
					return SETTING_TYPE::kFloat;
				case 's':
				case 'S':
					return SETTING_TYPE::kString;
				case 'r':
					return SETTING_TYPE::kRGB;
				case 'a':
					return SETTING_TYPE::kRGBA;
				default:
					return SETTING_TYPE::kNone;
				}
			} else {
				return SETTING_TYPE::kNone;
			}
		}

		[[nodiscard]] std::uint8_t GetUChar() const noexcept
		{
			assert(GetType() == SETTING_TYPE::kUChar);
			return _value.h;
		}

		[[nodiscard]] std::uint32_t GetUInt() const noexcept
		{
			assert(GetType() == SETTING_TYPE::kUInt);
			return _value.u;
		}

		void SetBinary(bool a_value) noexcept
		{
			assert(GetType() == SETTING_TYPE::kBinary);
			_value.b = a_value;
		}

		void SetChar(char a_value) noexcept
		{
			assert(GetType() == SETTING_TYPE::kChar);
			_value.c = a_value;
		}

		void SetFloat(float a_value) noexcept
		{
			assert(GetType() == SETTING_TYPE::kFloat);
			_value.f = a_value;
		}

		void SetInt(std::int32_t a_value) noexcept
		{
			assert(GetType() == SETTING_TYPE::kInt);
			_value.i = a_value;
		}

		void SetRGB(std::span<const std::uint8_t, 3> a_value) noexcept
		{
			assert(GetType() == SETTING_TYPE::kRGB);
			std::copy(
				a_value.begin(),
				a_value.end(),
				std::addressof(_value.r));
		}

		void SetRGBA(std::span<const std::uint8_t, 4> a_value) noexcept
		{
			assert(GetType() == SETTING_TYPE::kRGBA);
			std::copy(
				a_value.begin(),
				a_value.end(),
				std::addressof(_value.r));
		}

		void SetString(char* a_value) noexcept
		{
			assert(GetType() == SETTING_TYPE::kString);
			_value.s = a_value;
		}

		void SetUChar(std::uint8_t a_value) noexcept
		{
			assert(GetType() == SETTING_TYPE::kUChar);
			_value.h = a_value;
		}

		void SetUInt(std::uint32_t a_value) noexcept
		{
			assert(GetType() == SETTING_TYPE::kUInt);
			_value.u = a_value;
		}

	private:
		// members
		SETTING_VALUE _value;  // 08
		const char* _key;      // 10
	};
	static_assert(sizeof(Setting) == 0x18);

	template <class T>
	class __declspec(novtable) SettingT :
		public Setting  // 00
	{
	public:
	};

	class GameSettingCollection;
	class INIPrefSettingCollection;
	class INISettingCollection;
	class LipSynchroSettingCollection;
	class RegSettingCollection;

	extern template class SettingT<GameSettingCollection>;
	extern template class SettingT<INIPrefSettingCollection>;
	extern template class SettingT<INISettingCollection>;
	extern template class SettingT<LipSynchroSettingCollection>;
	extern template class SettingT<RegSettingCollection>;

	template <class T>
	class __declspec(novtable) SettingCollection
	{
	public:
		virtual ~SettingCollection() = default;  // 00

		// add
		virtual void Add(T* a_setting) = 0;                                 // 01
		virtual void Remove(T* a_setting) = 0;                              // 02
		virtual bool WriteSetting(T& a_setting) = 0;                        // 03
		virtual bool ReadSetting(T& a_setting) = 0;                         // 04
		virtual bool Open([[maybe_unused]] bool a_write) { return false; }  // 05
		virtual bool Close() { return true; }                               // 06
		virtual bool ReadSettingsFromProfile() { return false; }            // 07
		virtual bool WriteSettings() { return handle != nullptr; }          // 08
		virtual bool ReadSettings() { return handle != nullptr; }           // 09

		// members
		char settingFile[260];  // 008
		void* handle;           // 110
	};

	extern template class SettingCollection<Setting>;

	namespace detail
	{
		struct SettingCollectionMapCompare
		{
			[[nodiscard]] bool operator()(const RE::BSFixedString& a_lhs, const RE::BSFixedString& a_rhs) const noexcept
			{
				return a_lhs.c_str() < a_rhs.c_str();
			}
		};
	}

	template <class T>
	class __declspec(novtable) SettingCollectionMap :
		public SettingCollection<T>  // 000
	{
	public:
		// members
		BSTBTree<BSFixedString, T*, detail::SettingCollectionMapCompare> settings;  // 118
	};

	extern template class SettingCollectionMap<Setting>;

	template <class T>
	class __declspec(novtable) SettingCollectionList :
		public SettingCollection<T>
	{
	public:
		// members
		BSSimpleList<T*> settings;  // 118
	};

	extern template class SettingCollectionList<Setting>;

	class __declspec(novtable) GameSettingCollection :
		public SettingCollectionMap<Setting>  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::GameSettingCollection };
		static constexpr auto VTABLE{ VTABLE::GameSettingCollection };

		[[nodiscard]] static GameSettingCollection* GetSingleton()
		{
			REL::Relocation<GameSettingCollection**> singleton{ REL::ID(8308) };
			return *singleton;
		}
	};
	static_assert(sizeof(GameSettingCollection) == 0x138);

	class __declspec(novtable) INISettingCollection :
		public SettingCollectionList<Setting>  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::INISettingCollection };
		static constexpr auto VTABLE{ VTABLE::INISettingCollection };

		[[nodiscard]] static INISettingCollection* GetSingleton()
		{
			REL::Relocation<INISettingCollection**> singleton{ REL::ID(791183) };
			return *singleton;
		}
	};
	static_assert(sizeof(INISettingCollection) == 0x128);

	class __declspec(novtable) INIPrefSettingCollection :
		public INISettingCollection  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::INIPrefSettingCollection };
		static constexpr auto VTABLE{ VTABLE::INIPrefSettingCollection };

		[[nodiscard]] static INIPrefSettingCollection* GetSingleton()
		{
			REL::Relocation<INIPrefSettingCollection**> singleton{ REL::ID(767844) };
			return *singleton;
		}
	};
	static_assert(sizeof(INIPrefSettingCollection) == 0x128);
}
