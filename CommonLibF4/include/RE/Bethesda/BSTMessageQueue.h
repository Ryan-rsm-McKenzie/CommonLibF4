#pragma once

#include "RE/Bethesda/BSTFreeList.h"

namespace RE
{
	template <class T>
	class __declspec(novtable) BSTMessageQueue
	{
	public:
		virtual ~BSTMessageQueue() = default;  // 00

		// add
		virtual bool Push(const T& a_message) = 0;     // 01
		virtual bool TryPush(const T& a_message) = 0;  // 02
		virtual bool Pop(T& a_message) = 0;            // 03
		virtual bool TryPop(T& a_message) = 0;         // 04
	};

	template <class T>
	class __declspec(novtable) BSTCommonMessageQueue :
		public BSTMessageQueue<T>  // 00
	{
	public:
		// override (BSTMessageQueue<T>)
		bool Push(const T& a_message) override;     // 01
		bool TryPush(const T& a_message) override;  // 02
		bool Pop(T& a_message) override;            // 03
		bool TryPop(T& a_message) override;         // 04

		// add
		virtual bool DoTryPush([[maybe_unused]] const T& a_message) { return false; }  // 05
		virtual bool DoTryPop([[maybe_unused]] T& a_message) { return false; }         // 06

		// members
		std::uint32_t lock;  // 08
	};

	template <class T>
	class __declspec(novtable) BSTCommonLLMessageQueue :
		public BSTCommonMessageQueue<T>  // 00
	{
	public:
		// members
		BSTFreeList<T>* freeList;   // 10
		BSTFreeListElem<T>* head;   // 18
		BSTFreeListElem<T>** tail;  // 20
	};
}
