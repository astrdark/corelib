#pragma once
#include <CoreLib/IntegerTypes.hpp>
#include <algorithm>
#include <string_view>

namespace cl
{
	/**
	 * Compile-time string with its own storage.
	 */
	template <size_t N>
	struct FixedString
	{
		constexpr FixedString(const char(&str)[N + 1]) noexcept
		{
			std::copy_n(str, N + 1, data);
		}

		constexpr FixedString(std::string_view sv) noexcept
		{
			std::copy_n(sv.data(), N, data);
		}

		[[nodiscard]]
		constexpr auto operator<=>(const FixedString&) const = default;

		[[nodiscard]]
		constexpr operator std::string_view() const
		{
			return { std::data(data), N };
		}

		[[nodiscard]]
		constexpr size_t size() const
		{
			return N;
		}

		char data[N + 1]{};
	};

	template <size_t N>
	FixedString(const char(&str)[N]) -> FixedString<N - 1>;
}
