#pragma once
#include <CoreLib/IntegerTypes.hpp>
#include <tuple>
#include <type_traits>

namespace cl
{
	template<typename...>
	struct TemplateTraits;

	template<template<typename...> class T, typename... Ty>
	struct TemplateTraits<T<Ty...>>
	{
		template<typename U>
		static consteval bool IsInstanceOf()
		{
			// always false cond to delay evaluation
			static_assert(std::is_same_v<U, int> && std::is_same_v<U, bool>, "Argument to IsInstanceOf() must be template type without arguments");
			return false;
		}

		template<template<typename...> class U>
		static consteval bool IsInstanceOf()
		{
			return InstanceOfMatcher<U>::value;
		}

		using ArgTypes = std::tuple<Ty...>;

		template<size_t I> requires (I < sizeof...(Ty))
		using NthType = std::tuple_element_t<I, ArgTypes>;

	private:
		template<template<typename...> class U, typename... Ts>
		struct InstanceOfMatcher : std::false_type {};

		template<typename... Ts>
		struct InstanceOfMatcher<T, Ts...> : std::true_type {};
	};
}
