#pragma once


namespace RE
{
	class TESForm;
	class BGSTerminal;


	enum class FormType : UInt8
	{
		kNone = 0,		// 00 NONE TESForm
		kTerminal = 55,	// 37 TERM BGSTerminal

		kTotal = 159
	};
}
