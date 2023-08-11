#include <CoreLib/Tuple.hpp>

struct NonTrivial
{
	constexpr NonTrivial() noexcept {}

	constexpr NonTrivial(const NonTrivial&) = delete;
	constexpr NonTrivial(NonTrivial&&) noexcept {}

	constexpr NonTrivial& operator=(const NonTrivial&) = delete;
	constexpr NonTrivial& operator=(NonTrivial&&) noexcept { return *this; };
};

static_assert(([] () -> bool {
	std::tuple<NonTrivial, i32, float, bool> test = { NonTrivial{}, 1, 1.2f, false };

	static_assert(std::is_same_v<const NonTrivial&, decltype(cl::TupleHead(test))>, "cl::TupleHead failed");
	static_assert(std::is_same_v<NonTrivial&&, decltype(cl::TupleHead(std::move(test)))>, "cl::TupleHead failed");
	static_assert(std::is_same_v<std::tuple<i32, float, bool>, decltype(cl::TupleTail(test))>, "cl::TupleTail failed");

	return true;
})());
