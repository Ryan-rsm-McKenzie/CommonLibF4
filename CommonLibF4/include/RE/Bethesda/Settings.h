#pragma once

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
	};

	class Setting
	{
	public:
		static constexpr auto RTTI{ RTTI_Setting };

		enum class SETTING_TYPE
		{
			kBinary,  // b
			kChar,	  // c
			kUChar,	  // h
			kInt,	  // i
			kUInt,	  // u
			kFloat,	  // f
			kString,  // s/S
			kRGB,	  // r
			kRGBA,	  // a
			kNone
		};

		virtual ~Setting()	// 00
		{
			if (GetKey()[0] == 'S') {
				free(const_cast<char*>(_key));
				_key = nullptr;
			}
		}

		// add
		[[nodiscard]] virtual bool IsPrefSetting() { return false; }  // 01

		F4_HEAP_REDEFINE_NEW(Setting);

		[[nodiscard]] constexpr bool GetBinary() const noexcept
		{
			assert(GetType() == SETTING_TYPE::kBinary);
			return _value.b;
		}

		[[nodiscard]] constexpr const char* GetKey() const noexcept { return _key ? _key : ""; }

		[[nodiscard]] constexpr SETTING_TYPE GetType() const noexcept
		{
			switch (GetKey()[0]) {
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
		}

	private:
		// members
		SETTING_VALUE _value;  // 08
		const char* _key;	   // 10
	};
	static_assert(sizeof(Setting) == 0x18);

	template <class T>
	class SettingT :
		public Setting
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
}
