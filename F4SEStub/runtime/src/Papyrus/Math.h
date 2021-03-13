#pragma once

#include "Papyrus/Common.h"

namespace Papyrus
{
	namespace Math
	{
		inline float Exp(
			std::monostate,
			float a_value)
		{
			return std::exp(a_value);
		}

		inline std::uint32_t LeftShift(
			std::monostate,
			std::uint32_t a_value,
			std::uint32_t a_shiftBy)
		{
			return a_value << a_shiftBy;
		}

		inline float Log(
			std::monostate,
			float a_value)
		{
			return std::log(a_value);
		}

		inline std::uint32_t LogicalAnd(
			std::monostate,
			std::uint32_t a_lhs,
			std::uint32_t a_rhs)
		{
			return a_lhs & a_rhs;
		}

		inline std::uint32_t LogicalNot(
			std::monostate,
			std::uint32_t a_value)
		{
			return ~a_value;
		}

		inline std::uint32_t LogicalOr(
			std::monostate,
			std::uint32_t a_lhs,
			std::uint32_t a_rhs)
		{
			return a_lhs | a_rhs;
		}

		inline std::uint32_t LogicalXor(
			std::monostate,
			std::uint32_t a_lhs,
			std::uint32_t a_rhs)
		{
			return a_lhs ^ a_rhs;
		}

		inline std::uint32_t RightShift(
			std::monostate,
			std::uint32_t a_value,
			std::uint32_t a_shiftBy)
		{
			return a_value >> a_shiftBy;
		}

		inline void Bind(RE::BSScript::IVirtualMachine& a_vm)
		{
			const auto obj = "Math"sv;

			BIND(Exp, true);
			BIND(LeftShift, true);
			BIND(Log, true);
			BIND(LogicalAnd, true);
			BIND(LogicalNot, true);
			BIND(LogicalOr, true);
			BIND(LogicalXor, true);
			BIND(RightShift, true);

			logger::info("bound {} script"sv, obj);
		}
	}
}
