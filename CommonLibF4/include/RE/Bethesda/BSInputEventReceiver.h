#pragma once

namespace RE
{
	class InputEvent;

	class __declspec(novtable) BSInputEventReceiver
	{
	public:
		static constexpr auto RTTI{ RTTI::BSInputEventReceiver };
		static constexpr auto VTABLE{ VTABLE::BSInputEventReceiver };

		// add
		virtual void PerformInputProcessing(const InputEvent* a_queueHead) = 0;  // 00

		// members
		std::uint32_t currInputTimeCount;  // 08
	};
	static_assert(sizeof(BSInputEventReceiver) == 0x10);
}
