#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTSingleton.h"
#include "RE/Bethesda/UIMessage.h"

namespace RE
{
	class UIMessageQueue :
		public BSTSingletonSDM<UIMessageQueue>  // 000
	{
	public:
		[[nodiscard]] static UIMessageQueue* GetSingleton()
		{
			REL::Relocation<UIMessageQueue**> singleton{ REL::ID(82123) };
			return *singleton;
		}

		void AddMessage(const BSFixedString& a_menu, UI_MESSAGE_TYPE a_type)
		{
			using func_t = decltype(&UIMessageQueue::AddMessage);
			REL::Relocation<func_t> func{ REL::ID(1182019) };
			return func(this, a_menu, a_type);
		}

		// members
		BSTSmallArray<msvc::unique_ptr<UIMessage>, 64> messages;  // 008
		BSSpinLock uiMessagesLock;                                // 218
	};
	static_assert(sizeof(UIMessageQueue) == 0x220);
}
