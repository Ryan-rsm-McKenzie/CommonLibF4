#pragma once


namespace RE
{
	class BSSpinLock
	{
	public:
		BSSpinLock();
		~BSSpinLock() = default;

		FO_HEAP_REDEFINE_NEW();

	private:
		enum
		{
			kFastSpinThreshold = 10000,
			kLockWrite = 0x80000000,
			kLockCountMask = 0xFFFFFFF
		};


		// members
		volatile SInt32	_threadID;	// 00
		volatile SInt32	_lockValue;	// 04
	};
	STATIC_ASSERT(sizeof(BSSpinLock) == 0x8);
}
