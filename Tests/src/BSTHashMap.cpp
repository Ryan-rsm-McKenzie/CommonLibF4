namespace stl
{
	[[noreturn]] void report_and_fail(std::string_view a_msg)
	{
		throw std::runtime_error(std::string(a_msg));
	}

	template <class EF>                                    //
	requires(std::invocable<std::remove_reference_t<EF>>)  //
		class scope_exit
	{
	public:
		// 1)
		template <class Fn>
		explicit scope_exit(Fn&& a_fn)  //
			noexcept(std::is_nothrow_constructible_v<EF, Fn> ||
					 std::is_nothrow_constructible_v<EF, Fn&>)  //
			requires(!std::is_same_v<std::remove_cvref_t<Fn>, scope_exit> &&
					 std::is_constructible_v<EF, Fn>)
		{
			static_assert(std::invocable<Fn>);

			if constexpr (!std::is_lvalue_reference_v<Fn> &&
						  std::is_nothrow_constructible_v<EF, Fn>) {
				_fn.emplace(std::forward<Fn>(a_fn));
			} else {
				_fn.emplace(a_fn);
			}
		}

		// 2)
		scope_exit(scope_exit&& a_rhs)  //
			noexcept(std::is_nothrow_move_constructible_v<EF> ||
					 std::is_nothrow_copy_constructible_v<EF>)  //
			requires(std::is_nothrow_move_constructible_v<EF> ||
					 std::is_copy_constructible_v<EF>)
		{
			static_assert(!(std::is_nothrow_move_constructible_v<EF> && !std::is_move_constructible_v<EF>));
			static_assert(!(!std::is_nothrow_move_constructible_v<EF> && !std::is_copy_constructible_v<EF>));

			if (a_rhs.active()) {
				if constexpr (std::is_nothrow_move_constructible_v<EF>) {
					_fn.emplace(std::forward<EF>(*a_rhs._fn));
				} else {
					_fn.emplace(a_rhs._fn);
				}
				a_rhs.release();
			}
		}

		// 3)
		scope_exit(const scope_exit&) = delete;

		~scope_exit() noexcept
		{
			if (_fn.has_value()) {
				(*_fn)();
			}
		}

		void release() noexcept { _fn.reset(); }

	private:
		[[nodiscard]] bool active() const noexcept { return _fn.has_value(); }

		std::optional<std::remove_reference_t<EF>> _fn;
	};

	template <class EF>
	scope_exit(EF) -> scope_exit<EF>;
}

namespace RE
{
	void* malloc(std::size_t a_bytes) { return new std::byte[a_bytes]; }
	void free(void* a_ptr) { delete[] static_cast<std::byte*>(a_ptr); }

	class ScrapHeap
	{
	public:
		void* Allocate(std::size_t a_bytes, [[maybe_unused]] std::size_t a_alignment)
		{
			return malloc(a_bytes);
		}

		void Deallocate(void* a_ptr) { free(a_ptr); }
	};

	class MemoryManager
	{
	public:
		[[nodiscard]] static MemoryManager& GetSingleton()
		{
			static MemoryManager singleton;
			return singleton;
		}

		[[nodiscard]] ScrapHeap* GetThreadScrapHeap() { return &_scrap; }

	private:
		ScrapHeap _scrap;
	};

	template <class T>
	using BSCRC32 = std::hash<T>;

	template <class T1, class T2>
	using BSTTuple = std::pair<T1, T2>;
}

#include "RE/Bethesda/BSTHashMap.h"

#define BOOST_TEST_MODULE CommonLibF4
#include <boost/test/unit_test.hpp>

struct bad_hasher
{
	template <class T>
	[[nodiscard]] std::size_t operator()(const T&) const noexcept
	{
		return 0;
	}
};

using key_type = std::string;
using mapped_type = int;

template <class T>
void evaluate(
	std::function<const key_type&(const typename T::value_type&)> a_getKey,
	std::function<typename T::value_type(key_type, mapped_type)> a_makeValue,
	bool a_movable)
{
	T t1;
	const auto& ct1 = t1;

	// assert initial state
	BOOST_TEST((t1.empty()));
	BOOST_TEST((t1.size() == 0));
	BOOST_TEST((t1.begin() == t1.end()));
	BOOST_TEST((std::distance(t1.begin(), t1.end()) == 0));

	// initial insert, check invariants hold/code compiles
	for (char c = 'a'; c <= 'z'; ++c) {
		key_type key(1, c);
		const auto idx = static_cast<mapped_type>(c - 'a');
		auto elem = a_makeValue(key, idx);

		const auto ins = t1.insert(elem);
		const auto it = t1.find(key);
		BOOST_TEST((ins.second == true));
		BOOST_TEST((ins.first != t1.end()));
		BOOST_TEST((ins.first == it));

		BOOST_TEST((it != t1.end()));
		BOOST_TEST((t1.contains(key)));
		BOOST_TEST((*it == elem));

		const auto size = idx + 1;
		BOOST_TEST((!t1.empty()));
		BOOST_TEST((std::ssize(t1) == size));
		BOOST_TEST((std::distance(t1.begin(), t1.end()) == size));

		BOOST_TEST((t1.begin() == ct1.begin()));
		BOOST_TEST((t1.begin() == t1.cbegin()));
		BOOST_TEST((ct1.begin() == ct1.cbegin()));

		BOOST_TEST((t1.end() == ct1.end()));
		BOOST_TEST((t1.end() == t1.cend()));
		BOOST_TEST((ct1.end() == ct1.cend()));

		BOOST_TEST((t1.begin() != t1.end()));
		BOOST_TEST((t1.begin() != ct1.end()));
		BOOST_TEST((t1.begin() != t1.cend()));

		BOOST_TEST((ct1.begin() != t1.end()));
		BOOST_TEST((ct1.begin() != ct1.end()));
		BOOST_TEST((ct1.begin() != t1.cend()));

		BOOST_TEST((t1.cbegin() != t1.end()));
		BOOST_TEST((t1.cbegin() != ct1.end()));
		BOOST_TEST((t1.cbegin() != t1.cend()));

		for (char d = 'a'; d < c; ++d) {  // assert previous elements weren't lost
			BOOST_TEST((t1.contains(key_type(1, d))));
		}
	}

	// assert all elements actually inserted, and the container holds only those elements
	{
		std::vector<int> found('z' - 'a' + 1, 0);
		for (auto& entry : t1) {
			found[a_getKey(entry)[0] - 'a'] += 1;
		}
		BOOST_TEST((std::ranges::find_if_not(found, [](auto&& a_val) { return a_val == 1; }) == found.end()));
	}

	// test ctor/assignment
	{
		T u1;
		for (char c = 'A'; c <= 'Z'; ++c) {
			u1.insert(a_makeValue(key_type(1, c), static_cast<mapped_type>(c - 'A')));
		}

		const auto eq = [](const T& a_lhs, const T& a_rhs) {
			BOOST_TEST((a_lhs.size() == a_rhs.size()));
			const auto get = [](const T& a_cont) {
				std::multiset<typename T::value_type> m;
				for (auto& elem : a_cont) {
					m.insert(elem);
				}
				return m;
			};
			const auto l = get(a_lhs);
			const auto r = get(a_rhs);
			return l == r;
		};

		// copy ctor/assignment
		{
			auto t2 = t1;
			BOOST_TEST((eq(t2, t1)));
			t2 = u1;
			BOOST_TEST((eq(t2, u1)));
		}

		// move ctor/assignment
		if (a_movable) {  // skip for non-copyable types, but assert the code still compiles
			auto t2 = t1;
			auto t3 = std::move(t2);
			BOOST_TEST((t2.empty()));
			BOOST_TEST((eq(t3, t1)));

			auto u2 = u1;
			t2 = std::move(u2);
			BOOST_TEST((u2.empty()));
			BOOST_TEST((eq(t2, u1)));
		}

		// check swapping works
		{
			auto l = t1;
			auto r = u1;
			std::swap(l, r);
			BOOST_TEST((eq(l, u1)));
			BOOST_TEST((eq(r, t1)));
		}
	}

	// test erase
	for (char c = 'a'; c <= 'z'; ++c) {
		key_type key(1, c);
		BOOST_TEST((t1.contains(key)));
		t1.erase(key);
		BOOST_TEST((!t1.contains(key)));
		for (char d = c + 1; d <= 'z'; ++d) {
			BOOST_TEST((t1.contains(key_type(1, d))));
		}
	}

	// test emplace
	for (char c = 'a'; c <= 'z'; ++c) {
		if constexpr (std::same_as<typename T::mapped_type, void>) {
			t1.emplace(key_type(1, c));
		} else {
			t1.emplace(key_type(1, c), static_cast<mapped_type>(c - 'a'));
		}
	}

	// test clear
	BOOST_TEST((!t1.empty()));
	BOOST_TEST((std::ssize(t1) == 'z' - 'a' + 1));
	t1.clear();
	BOOST_TEST((t1.size() == 0));
	BOOST_TEST((t1.empty()));
}

struct LogCfg
{
	LogCfg() { boost::unit_test::unit_test_log.set_stream(std::cout); }
};

BOOST_TEST_GLOBAL_CONFIGURATION(LogCfg);

BOOST_AUTO_TEST_SUITE(test_scatter_table)

[[nodiscard]] const key_type& get1(const key_type& a_value) { return a_value; }
[[nodiscard]] const key_type& get2(const RE::BSTTuple<const key_type, mapped_type>& a_value) { return a_value.first; }
[[nodiscard]] auto make1(key_type a_key, mapped_type) { return a_key; };
[[nodiscard]] auto make2(key_type a_key, mapped_type a_idx) { return std::make_pair(std::move(a_key), a_idx); };

BOOST_AUTO_TEST_CASE(test_hash_map)
{
	evaluate<RE::BSTHashMap<key_type, mapped_type>>(get2, make2, true);
	evaluate<RE::BSTHashMap<key_type, mapped_type, bad_hasher>>(get2, make2, true);
}

BOOST_AUTO_TEST_CASE(test_set)
{
	evaluate<RE::BSTSet<key_type>>(get1, make1, true);
	evaluate<RE::BSTSet<key_type, bad_hasher>>(get1, make1, true);
}

BOOST_AUTO_TEST_CASE(test_static_hash_map)
{
	evaluate<RE::BSTStaticHashMap<key_type, mapped_type, 1u << 5>>(get2, make2, false);
	evaluate<RE::BSTStaticHashMap<key_type, mapped_type, 1u << 5, bad_hasher>>(get2, make2, false);
}

BOOST_AUTO_TEST_CASE(test_scrap_hash_map)
{
	evaluate<RE::BSTScrapHashMap<key_type, mapped_type>>(get2, make2, false);
	evaluate<RE::BSTScrapHashMap<key_type, mapped_type, bad_hasher>>(get2, make2, false);
}

BOOST_AUTO_TEST_SUITE_END();
