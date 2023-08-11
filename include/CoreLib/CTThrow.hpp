#pragma once

namespace cl
{
	/**
	 *  Throws compiler error when called during compile time evaluation.
	 *  Works even with `-fno-exceptions`.
	 *  During runtime does nothing.
	 */
	template<typename... Ty>
	inline void CTThrow(const Ty&...)
	{}
}
