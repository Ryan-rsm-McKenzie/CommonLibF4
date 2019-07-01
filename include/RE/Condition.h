#pragma once


namespace RE
{
	class Condition
	{
	public:
		explicit operator bool() const;


		// members
		void* root;	// 0
	};
	STATIC_ASSERT(sizeof(Condition) == 0x8);
}
