#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSStringT.h"
#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	namespace Scaleform::GFx
	{
		class Event;
	}

	enum class UI_MESSAGE_RESULTS
	{
		kHandled,
		kIgnore,
		kPassOn
	};

	enum class UI_MESSAGE_TYPE
	{
		kUpdate,
		kShow,
		kReshow,
		kHide,
		kForceHide,
		kScaleformEvent,
		kUserEvent,
		kInventoryUpdate,
		kUserProfileChange,
		kMUStatusChange,
		kResumeCaching,
		kUpdateController,
		kChatterEvent,
		kTotal
	};

	class IUIMessageData;

	class __declspec(novtable) UIMessage
	{
	public:
		static constexpr auto RTTI{ RTTI::UIMessage };
		static constexpr auto VTABLE{ VTABLE::UIMessage };

		virtual ~UIMessage() = default;  // 00

		virtual IUIMessageData* QData() { return nullptr; }              // 02
		virtual const IUIMessageData* QData() const { return nullptr; }  // 01

		F4_HEAP_REDEFINE_NEW(UIMessage);

		// members
		BSFixedString menu;                                                               // 08
		stl::enumeration<UI_MESSAGE_TYPE, std::int32_t> type{ UI_MESSAGE_TYPE::kTotal };  // 10
	};
	static_assert(sizeof(UIMessage) == 0x18);

	class __declspec(novtable) IUIMessageData :
		public UIMessage  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::IUIMessageData };
		static constexpr auto VTABLE{ VTABLE::IUIMessageData };

		// override (UIMessage)
		IUIMessageData* QData() override { return this; }              // 02
		const IUIMessageData* QData() const override { return this; }  // 01
	};
	static_assert(sizeof(IUIMessageData) == 0x18);

	class __declspec(novtable) BSUIMessageData :
		public IUIMessageData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSUIMessageData };
		static constexpr auto VTABLE{ VTABLE::BSUIMessageData };

		static void SendUIStringUIntMessage(const BSFixedString& a_menuName, UI_MESSAGE_TYPE a_type, const BSFixedString& a_fixedString, std::uint32_t a_data)
		{
			using func_t = decltype(&BSUIMessageData::SendUIStringUIntMessage);
			REL::Relocation<func_t> func{ REL::ID(99795) };
			return func(a_menuName, a_type, a_fixedString, a_data);
		}

		// members
		BSStringT<char>* string{ nullptr };  // 18
		BSFixedString fixedString;           // 20
		union
		{
			std::uint32_t u;
			void* p{ nullptr };
			float f;
			bool b;
		} data;  // 28
	};
	static_assert(sizeof(BSUIMessageData) == 0x30);

	class __declspec(novtable) BSUIScaleformData :
		public IUIMessageData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSUIScaleformData };
		static constexpr auto VTABLE{ VTABLE::BSUIScaleformData };

		// members
		Scaleform::GFx::Event* scaleformEvent{ nullptr };  // 18
	};
	static_assert(sizeof(BSUIScaleformData) == 0x20);
}
