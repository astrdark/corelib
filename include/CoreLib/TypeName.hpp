#pragma once
#include <CoreLib/FixedString.hpp>

namespace cl
{
	/**
	 *  Returns expanded type `T` as FixedString<>.
	 *  Does not consume any more `.data` memory than required.
	 *
	 *  Relies on compiler's __PRETTY_FUNCTION__ so compiler-dependent.
	 */
	template<typename T>
	consteval auto GetTypeName() /* -> FixedString<N> */
	{
		constexpr const char* funcsig = __PRETTY_FUNCTION__ + 28;
		constexpr size_t len = __builtin_strlen(funcsig) - 1;

		return cl::FixedString<len>(std::string_view(funcsig));
	}
}
