#pragma once

struct __type_info_node;  // NOLINT(bugprone-reserved-identifier)

namespace RE::msvc
{
	class __declspec(novtable) type_info
	{
	public:
		virtual ~type_info();  // 00

		[[nodiscard]] const char* name() const noexcept
		{
			using func_t = const char* (*)(const type_info*, __type_info_node*) noexcept;
			REL::Relocation<func_t*> func{ REL::ID(1419793) };
			return (*func)(this, std::addressof(get_root_node()));
		}

		[[nodiscard]] const char* mangled_name() const noexcept { return _name; }

	private:
		[[nodiscard]] static __type_info_node& get_root_node() noexcept
		{
			REL::Relocation<__type_info_node*> root{ REL::ID(161235) };
			return *root;
		}

		// members
		void* _data;    // 08
		char _name[1];  // 10
	};
	static_assert(sizeof(type_info) == 0x18);
}
