#pragma once

#include "RE/BSSpinLock.h"  // BSSpinLock


namespace RE
{
	class BSGlobalStringTable
	{
	public:
		enum HashMask
		{
			kEntryIndexMask = 0xFFFF,
			kLockIndexMask = 0x7F
		};


		enum class Flag : UInt8
		{
			kNone = 0,
			kInit = 1 << 0
		};


		struct Entry
		{
			enum : UInt16
			{
				kIsReference = 1 << 14,
				kIsWideChar = 1 << 15,
				kRefCountMask = 0x3FFF
			};


			union LengthAndRef
			{
				UInt32	length;
				Entry*	reference;
			};
			STATIC_ASSERT(sizeof(LengthAndRef) == 0x8);


			union CharT
			{
				char	u8;
				wchar_t	u16;
			};


			bool		IsWideChar() const;
			bool		IsReference() const;
			UInt16		GetRefCount() const;
			UInt32		GetLength() const;
			Entry*		GetProxy() const;
			char*		GetDataU8();
			wchar_t*	GetDataU16();


			Entry*			next;				// 00
			UInt16			flagsAndRefCount;	// 08
			UInt16			hash;				// 0A
			UInt32			unk0C;				// 0C
			LengthAndRef	lengthAndRef;		// 10
			CharT			data[0];			// 18
		};
		STATIC_ASSERT(sizeof(Entry) == 0x18);


		struct Lock
		{
			enum { kLockCountMask = 0x7FFFFFFF };

			BSSpinLock	lock;	// 00
			UInt64		unk08;	// 08
		};
		STATIC_ASSERT(sizeof(Lock) == 0x10);


		Entry*	entries[0x10000];	// 00000 - index with hash & kEntryIndexMask
		Lock	locks[0x80];		// 80000 - index with hash & kLockIndexMask
		Flag	flags;				// 80800
		UInt8	pad80801;			// 80801
		UInt16	pad80802;			// 80802
		UInt32	pad80804;			// 80804
	};
	STATIC_ASSERT(sizeof(BSGlobalStringTable) == 0x80808);


	using GlobalStringHandle = BSGlobalStringTable::Entry*;
}
