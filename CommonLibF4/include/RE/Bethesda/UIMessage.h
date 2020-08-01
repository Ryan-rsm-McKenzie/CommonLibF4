#pragma once

#include "RE/Bethesda/BSFixedString.h"

namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class Event;
		}
	}

	enum class UI_MESSAGE_RESULTS : std::int32_t
	{
		kHandled,
		kIgnore,
		kPassOn
	};

	enum class UI_MESSAGE_TYPE : std::int32_t
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

	class UIMessage
	{
	public:
		static constexpr auto RTTI{ RTTI_UIMessage };

		virtual ~UIMessage() = default;	 // 00

		virtual IUIMessageData* QData() { return nullptr; }				 // 02
		virtual const IUIMessageData* QData() const { return nullptr; }	 // 01

		// members
		BSFixedString menu;																  // 08
		stl::enumeration<UI_MESSAGE_TYPE, std::int32_t> type{ UI_MESSAGE_TYPE::kTotal };  // 10
	};
	static_assert(sizeof(UIMessage) == 0x18);

	class IUIMessageData :
		public UIMessage  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_IUIMessageData };

		// override (UIMessage)
		IUIMessageData* QData() override { return this; }			   // 02
		const IUIMessageData* QData() const override { return this; }  // 01
	};
	static_assert(sizeof(IUIMessageData) == 0x18);

	class BSUIScaleformData :
		public IUIMessageData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI_BSUIScaleformData };

		// members
		Scaleform::GFx::Event* scaleformEvent{ nullptr };  // 18
	};
	static_assert(sizeof(BSUIScaleformData) == 0x20);
}
