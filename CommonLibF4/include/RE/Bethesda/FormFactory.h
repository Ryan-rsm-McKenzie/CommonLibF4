#pragma once

#include "RE/Bethesda/TESForms.h"

namespace RE
{
	namespace BGSMod::Property
	{
		class BridgeI;
	}

	enum class ENUM_FORM_ID;
	enum class OBJECT_CATEGORY_TYPE;
	enum class OBJECT_TYPE;

	class TESForm;

	class __declspec(novtable) IFormFactory
	{
	public:
		static constexpr auto RTTI{ RTTI::IFormFactory };
		static constexpr auto VTABLE{ VTABLE::IFormFactory };

		virtual ~IFormFactory();  // 00

		// add
		[[nodiscard]] virtual TESForm* DoCreate() = 0;                                                  // 01
		[[nodiscard]] virtual const char* GetFormName() const = 0;                                      // 02
		[[nodiscard]] virtual ENUM_FORM_ID GetFormID() const = 0;                                       // 03
		[[nodiscard]] virtual const char* GetObjectName() const { return nullptr; }                     // 04
		[[nodiscard]] virtual OBJECT_TYPE GetObjectType() const;                                        // 05
		[[nodiscard]] virtual OBJECT_CATEGORY_TYPE GetObjectCategory() const;                           // 06
		[[nodiscard]] virtual BGSMod::Property::BridgeI* GetPropertyBridge() const { return nullptr; }  // 07

		[[nodiscard]] static auto GetFormFactories()
			-> std::span<IFormFactory*, stl::to_underlying(ENUM_FORM_ID::kTotal)>
		{
			constexpr auto len = stl::to_underlying(ENUM_FORM_ID::kTotal);
			REL::Relocation<IFormFactory*(*)[len]> factories{ REL::ID(228366) };
			return { *factories };
		}
	};
	static_assert(sizeof(IFormFactory) == 0x8);

	template <class T, ENUM_FORM_ID ID = T::FORM_ID>
	class __declspec(novtable) ConcreteFormFactory :
		public IFormFactory  // 00
	{
	public:
		[[nodiscard]] static ConcreteFormFactory* GetFormFactory()
		{
			const auto factories = GetFormFactories();
			return static_cast<ConcreteFormFactory*>(factories[stl::to_underlying(ID)]);
		}

		[[nodiscard]] T* Create() { return static_cast<T*>(DoCreate()); }

		// members
		const char* name{ nullptr };
	};

	template <class T, ENUM_FORM_ID ID, OBJECT_TYPE TYPE, OBJECT_CATEGORY_TYPE CATEGORY>
	class __declspec(novtable) ConcreteObjectFormFactory :
		public ConcreteFormFactory<T, ID>  // 00
	{
	public:
	};
}
