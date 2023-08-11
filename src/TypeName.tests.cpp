#include <CoreLib/TypeName.hpp>

struct Foo {};

template<typename T>
struct Bar {};

static_assert(([] () -> bool {
	static_assert(cl::FixedString("Foo") == cl::GetTypeName<Foo>(), "Non-templated type failed");
	static_assert(cl::FixedString("Bar<Foo>") == cl::GetTypeName<Bar<Foo>>(), "Non-templated type failed");

	return true;
})());
