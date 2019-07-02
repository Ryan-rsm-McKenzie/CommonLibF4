#pragma once


namespace RE
{
	// needs double checking
	template <std::size_t SIZE>
	class BGSTypedKeywordValueArray
	{
	public:
		FO_HEAP_REDEFINE_NEW();

		// members
		void* unk[SIZE];
	};
}
