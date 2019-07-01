#pragma once


namespace RE
{
	class BGSKeyword;


	// needs double checking
	template <std::size_t SIZE>
	class BGSTypedKeywordValueArray
	{
	public:
		void* unk[SIZE];
	};
}
