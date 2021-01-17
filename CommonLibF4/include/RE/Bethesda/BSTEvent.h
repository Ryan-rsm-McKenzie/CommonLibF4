#pragma once

#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTOptional.h"

namespace RE
{
	enum class BSEventNotifyControl : std::int32_t
	{
		kContinue,
		kStop
	};

	template <class>
	class BSTEventSource;

	template <class Event>
	class __declspec(novtable) BSTEventSink
	{
	public:
		virtual ~BSTEventSink() = default;  // 00

		// add
		virtual BSEventNotifyControl ProcessEvent(const Event& a_event, BSTEventSource<Event>* a_source) = 0;  // 01
	};
	//static_assert(sizeof(BSTEventSink<void*>) == 0x8);

	template <class Event>
	class BSTEventSource
	{
	public:
		using event_type = Event;

		void Notify(const event_type& a_event)
		{
			const BSAutoLock locker(_lock);

			if (!_notifying && !_pendingRegisters.empty()) {
				for (const auto& toAdd : _pendingRegisters) {
					if (std::find(_sinks.begin(), _sinks.end(), toAdd) == _sinks.end()) {
						_sinks.push_back(toAdd);
					}
				}
				_pendingRegisters.clear();
			}

			++_notifying;
			for (const auto& sink : _sinks) {
				if (std::find(_pendingUnregisters.begin(), _pendingUnregisters.end(), sink) == _pendingUnregisters.end()) {
					if (sink->ProcessEvent(a_event, this) == BSEventNotifyControl::kStop) {
						break;
					}
				}
			}

			const auto uncontended = _notifying-- == 1;
			if (uncontended && !_pendingUnregisters.empty()) {
				for (const auto& toRemove : _pendingUnregisters) {
					auto it = std::find(_sinks.begin(), _sinks.end(), toRemove);
					if (it != _sinks.end()) {
						_sinks.erase(it);
					}
				}
				_pendingUnregisters.clear();
			}
		}

		void RegisterSink(BSTEventSink<event_type>* a_sink)
		{
			if (!a_sink) {
				return;
			}

			const BSAutoLock locker(_lock);

			if (_notifying) {
				if (std::find(_pendingRegisters.begin(), _pendingRegisters.end(), a_sink) == _pendingRegisters.end()) {
					_pendingRegisters.push_back(a_sink);
				}
			} else {
				if (std::find(_sinks.begin(), _sinks.end(), a_sink) == _sinks.end()) {
					_sinks.push_back(a_sink);
				}
			}

			const auto it = std::find(_pendingUnregisters.begin(), _pendingUnregisters.end(), a_sink);
			if (it != _pendingUnregisters.end()) {
				_pendingUnregisters.erase(it);
			}
		}

		void UnregisterSink(BSTEventSink<event_type>* a_sink)
		{
			if (!a_sink) {
				return;
			}

			const BSAutoLock locker(_lock);

			if (_notifying) {
				if (std::find(_pendingUnregisters.begin(), _pendingUnregisters.end(), a_sink) == _pendingUnregisters.end()) {
					_pendingUnregisters.push_back(a_sink);
				}
			} else {
				const auto it = std::find(_sinks.begin(), _sinks.end(), a_sink);
				if (it != _sinks.end()) {
					_sinks.erase(it);
				}
			}

			const auto it = std::find(_pendingRegisters.begin(), _pendingRegisters.end(), a_sink);
			if (it != _pendingRegisters.end()) {
				_pendingRegisters.erase(it);
			}
		}

	private:
		// members
		BSSpinLock _lock;                                         // 00
		BSTArray<BSTEventSink<event_type>*> _sinks;               // 08
		BSTArray<BSTEventSink<event_type>*> _pendingRegisters;    // 20
		BSTArray<BSTEventSink<event_type>*> _pendingUnregisters;  // 38
		std::int8_t _notifying{ 0 };                              // 50
	};
	//static_assert(sizeof(BSTEventSource<void*>) == 0x58);

	template <class T>
	class BSTValueEvent
	{
	public:
		using value_type = T;

		// members
		BSTOptional<T> optionalValue;  // 00
	};

	template <class T>
	class BSTValueEventSink :
		public BSTEventSink<T>  // 00
	{
	public:
		struct BSTEventValueData
		{
		public:
			// members
			BSTOptional<typename T::value_type> optionalValue;  // 00
			bool eventReceived;                                 // ??
		};

		// override (BSTEventSink<T>)
		BSEventNotifyControl ProcessEvent(const T& a_event, BSTEventSource<T>*) override;  // 01

		// members
		BSTEventValueData eventDataStruct;  // 08
		BSSpinLock dataLock;                // ??
	};

	template <class T>
	class BSTValueRequestEvent
	{
	public:
		// members
		BSTValueEventSink<T>& valueEventSink;  // 00
	};

	template <class T>
	class BSTValueEventSource :
		public BSTEventSink<BSTValueRequestEvent<T>>  // 00
	{
	public:
		using event_type = BSTValueRequestEvent<T>;

		// override (BSTEventSink<BSTValueRequestEvent<T>>)
		BSEventNotifyControl ProcessEvent(const event_type& a_event, BSTEventSource<event_type>*) override  // 01
		{
			BSAutoLock l{ dataLock };
			T event;
			event.optionalValue = optionalValue;
			a_event.valueEventSink.ProcessEvent(event, nullptr);
		}

		// members
		BSTOptional<typename T::value_type> optionalValue;  // ??
		BSSpinLock dataLock;                                // ??
	};
}
