#pragma once

#include "RE/Scaleform/Kernel/SF_Array.h"
#include "RE/Scaleform/Kernel/SF_Atomic.h"
#include "RE/Scaleform/Kernel/SF_RefCount.h"

namespace RE::Scaleform
{
	using ThreadId = void*;

	class AcquireInterface;
	class Event;
	class Mutex;
	class MutexImpl;
	class Waitable;
	class WaitCondition;
	class WaitConditionImpl;

	class __declspec(novtable) AcquireInterface
	{
	public:
		static constexpr auto RTTI{ RTTI::Scaleform__AcquireInterface };
		static constexpr auto VTABLE{ VTABLE::Scaleform__AcquireInterface };

		virtual ~AcquireInterface() = default;  // 00

		// add
		virtual bool CanAcquire();        // 01
		virtual bool TryAcquire();        // 02
		virtual bool TryAcquireCommit();  // 03
		virtual bool TryAcquireCancel();  // 04
	};
	static_assert(sizeof(AcquireInterface) == 0x8);

	class __declspec(novtable) Waitable :
		public RefCountBase<Waitable, 2>  // 00
	{
	public:
		using WaitHandler = void(void*);

		class HandlerStruct
		{
		public:
			// members
			WaitHandler* handler;  // 00
			void* userData;        // 08
		};
		static_assert(sizeof(HandlerStruct) == 0x10);

		struct HandlerArray :
			public NewOverrideBase<2>  // 00
		{
			using SizePolicyType = ArrayConstPolicy<0, 16, true>;
			using HandlerArrayType = Array<HandlerStruct, 2, SizePolicyType>;

			void AddRef()
			{
				stl::atomic_ref myRefCount{ refCount.value };
				++myRefCount;
			}

			// members
			AtomicInt<std::int32_t> refCount;  // 00
			HandlerArrayType handlers;         // 08
			Lock handlersLock;                 // 20
		};
		static_assert(sizeof(HandlerArray) == 0x48);

		// members
		HandlerArray* handlers;  // 10
	};
	static_assert(sizeof(Waitable) == 0x18);

	class __declspec(novtable) Mutex :
		public Waitable,         // 00
		public AcquireInterface  // 18
	{
	public:
		// members
		MutexImpl* impl;  // 20
	};
	static_assert(sizeof(Mutex) == 0x28);

	class WaitCondition
	{
	public:
		~WaitCondition() noexcept {}  // NOLINT(modernize-use-equals-default)

		// members
		WaitConditionImpl* impl;  // 00
	};
	static_assert(sizeof(WaitCondition) == 0x8);

	class __declspec(novtable) Event :
		public Waitable,         // 00
		public AcquireInterface  // 18
	{
	public:
		// members
		volatile bool state;               // 20
		volatile bool temporary;           // 21
		mutable Mutex stateMutex;          // 28
		WaitCondition stateWaitCondition;  // 50
	};
	static_assert(sizeof(Event) == 0x58);

	inline ThreadId GetCurrentThreadId()
	{
		return reinterpret_cast<ThreadId>(
			static_cast<std::uintptr_t>(WinAPI::GetCurrentThreadID()));
	}
}
