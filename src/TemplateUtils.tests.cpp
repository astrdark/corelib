#include <CoreLib/TemplateUtils.hpp>
#include <vector>

static_assert(([] () -> bool {
	using TVectorInt = std::vector<int>;
	using TTraits = cl::TemplateTraits<TVectorInt>;

	static_assert(std::is_same_v<TTraits::NthType<0>, int>, "cl::TemplateTraits<>::NthType<0> failed");
	static_assert(std::is_same_v<TTraits::NthType<1>, std::allocator<int>>, "cl::TemplateTraits<>::NthType<1> failed"); // implicit

	static_assert( TTraits::IsInstanceOf<std::vector>(), "cl::TemplateTraits<T>::IsInstanceOf<T>() failed");
	static_assert(!TTraits::IsInstanceOf<std::tuple>(), "cl::TemplateTraits<T>::IsInstanceOf<U>() failed");

	return true;
})(), "Tests failed");
