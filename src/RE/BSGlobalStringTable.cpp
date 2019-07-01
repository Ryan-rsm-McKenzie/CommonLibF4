#include "RE/BSGlobalStringTable.h"

#include <cassert>


namespace RE
{
	bool BSGlobalStringTable::Entry::IsWideChar() const
	{
		return (flagsAndRefCount & kIsWideChar) != 0;
	}


	bool BSGlobalStringTable::Entry::IsReference() const
	{
		return (flagsAndRefCount & kIsReference) != 0;
	}


	auto BSGlobalStringTable::Entry::GetProxy() const
		-> Entry*
	{
		auto proxy = const_cast<Entry*>(this);
		while (proxy->IsReference()) {
			proxy = proxy->lengthAndRef.reference;
		}
		return proxy;
	}


	UInt16 BSGlobalStringTable::Entry::GetRefCount() const
	{
		return flagsAndRefCount & kRefCountMask;
	}


	UInt32 BSGlobalStringTable::Entry::GetLength() const
	{
		return lengthAndRef.length;
	}


	char* BSGlobalStringTable::Entry::GetDataU8()
	{
		assert(!IsWideChar());
		auto addr = std::addressof(GetProxy()->data[0].u8);
		return addr;
	}


	wchar_t* BSGlobalStringTable::Entry::GetDataU16()
	{
		assert(IsWideChar());
		return std::addressof(GetProxy()->data[0].u16);
	}
}
