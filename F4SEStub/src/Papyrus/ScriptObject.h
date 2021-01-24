#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace ScriptObject
	{
		inline void RegisterForCameraState(
			[[maybe_unused]] const RE::BSScript::Object& a_self)
		{}

		inline void RegisterForControl(
			[[maybe_unused]] const RE::BSScript::Object& a_self,
			[[maybe_unused]] std::string_view a_control)
		{}

		inline void RegisterForExternalEvent(
			[[maybe_unused]] const RE::BSScript::Object& a_self,
			[[maybe_unused]] std::string_view a_eventName,
			[[maybe_unused]] std::string_view a_callback)
		{}

		inline void RegisterForFurnitureEvent(
			[[maybe_unused]] const RE::BSScript::Object& a_self,
			[[maybe_unused]] const RE::BSScript::Variable* a_filter)
		{}

		inline void RegisterForKey(
			[[maybe_unused]] const RE::BSScript::Object& a_self,
			[[maybe_unused]] std::uint32_t a_key)
		{}

		inline void UnregisterForCameraState(
			[[maybe_unused]] const RE::BSScript::Object& a_self)
		{}

		inline void UnregisterForControl(
			[[maybe_unused]] const RE::BSScript::Object& a_self,
			[[maybe_unused]] std::string_view a_control)
		{}

		inline void UnregisterForExternalEvent(
			[[maybe_unused]] const RE::BSScript::Object& a_self,
			[[maybe_unused]] std::string_view a_eventName)
		{}

		inline void UnregisterForFurnitureEvent(
			[[maybe_unused]] const RE::BSScript::Object& a_self,
			[[maybe_unused]] const RE::BSScript::Variable* a_filter)
		{}

		inline void UnregisterForKey(
			[[maybe_unused]] const RE::BSScript::Object& a_self,
			[[maybe_unused]] std::uint32_t a_key)
		{}

		inline void Bind([[maybe_unused]] RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "ScriptObject"sv;

			// TODO
			//BIND(RegisterForCameraState);
			//BIND(RegisterForControl);
			//BIND(RegisterForExternalEvent);
			//BIND(RegisterForFurnitureEvent);
			//BIND(RegisterForKey);
			//BIND(UnregisterForCameraState);
			//BIND(UnregisterForControl);
			//BIND(UnregisterForExternalEvent);
			//BIND(UnregisterForKey);

			logger::info("bound {} script"sv, obj);
		}
	}
}
