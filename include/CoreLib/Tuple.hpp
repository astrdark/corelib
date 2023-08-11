#pragma once
#include <CoreLib/IntegerTypes.hpp>
#include <tuple>

/**
 * std::tuple extensions.
 */
namespace cl
{
	/**
	 *  Returns the tuple's first element as value if it's trivial, and the same ref-qualifiers otherwise.
	 */
	template<typename T, typename... Ts, std::enable_if_t<std::is_trivial_v<T>, bool> = true>
	constexpr T TupleHead(std::tuple<T, Ts...>&& t)
	{
		return std::get<0>(t);
	}

	template<typename T, typename... Ts, std::enable_if_t<std::is_trivial_v<T>, bool> = true>
	constexpr T TupleHead(const std::tuple<T, Ts...>& t)
	{
		return std::get<0>(t);
	}

	template<typename T, typename... Ts, std::enable_if_t<!std::is_trivial_v<T>, bool> = true>
	constexpr const T& TupleHead(const std::tuple<T, Ts...>& t)
	{
		return std::get<0>(t);
	}

	template<typename T, typename... Ts, std::enable_if_t<!std::is_trivial_v<T>, bool> = true>
	constexpr T&& TupleHead(std::tuple<T, Ts...>&& t)
	{
		return std::get<0>(t);
	}

	/**
	 * Creates a new tuple consisting of all elements but first of the original tuple.
	 */
	template<typename THead, typename... Ts>
	constexpr std::tuple<Ts...> TupleTail(const std::tuple<THead, Ts...>& tup)
	{
		return ([] <std::size_t... N> (std::index_sequence<N...>, const std::tuple<THead, Ts...>& tup)
		{
			return std::make_tuple(std::get<N+1u>(tup)...);
		})(std::make_index_sequence<sizeof...(Ts)>(), tup);
	}

	template<typename THead, typename... Ts>
	constexpr std::tuple<Ts...> TupleTail(std::tuple<THead, Ts...>&& tup)
	{
		return ([] <std::size_t... N> (std::index_sequence<N...>, std::tuple<THead, Ts...>&& tup)
		{
			return std::make_tuple(std::get<N+1u>(tup)...);
		})(std::make_index_sequence<sizeof...(Ts)>(), tup);
	}
}
