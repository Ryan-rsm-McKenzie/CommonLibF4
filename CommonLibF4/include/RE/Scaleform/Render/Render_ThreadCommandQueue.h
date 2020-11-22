#pragma once

#include "RE/Scaleform/Kernel/SF_RefCount.h"
#include "RE/Scaleform/Kernel/SF_Threads.h"

namespace RE::Scaleform::Render
{
	class TextureManager;
	class HAL;
	class Renderer2D;

	class __declspec(novtable) ThreadCommand :
		public RefCountBase<ThreadCommand, 2>  // 00
	{
	public:
		// add
		virtual void Execute() = 0;  // 01
	};
	static_assert(sizeof(ThreadCommand) == 0x10);

	struct Interfaces
	{
	public:
		// members
		TextureManager* textureManager;  // 00
		HAL* hal;                        // 08
		Renderer2D* renderer2D;          // 10
		ThreadId renderThreadID;         // 18
	};
	static_assert(sizeof(Interfaces) == 0x20);

	class __declspec(novtable) ThreadCommandQueue
	{
	public:
		virtual ~ThreadCommandQueue() = default;  // 00

		// add
		virtual void PushThreadCommand(ThreadCommand* a_command) = 0;  // 01
		virtual void GetRenderInterfaces(Interfaces* a_ptr);           // 02
	};
	static_assert(sizeof(ThreadCommandQueue) == 0x8);
}
