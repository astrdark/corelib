#include <CoreLib/Tuple.hpp>
#include <CoreLib/TemplateUtils.hpp>
#include <vector>
#include <iostream>

#include <CoreLib/TypeName.hpp>

struct Error
{
	enum : u32 {
		VALUE_1,
		VALUE_2
	} value;

	constexpr Error(decltype(value) val) : value(val)
	{}
};

template<typename T>
struct ScopedEnum
{
	template<typename U = T>
	constexpr ScopedEnum(decltype(std::declval<U>().value) val)
	{
		(*(U*)this).value = val;
	};

	template<typename U = T>
	constexpr U operator&(U rhs)
	{
		using UT = std::underlying_type_t<decltype(std::declval<U>().value)>;

		return std::bit_cast<U>(static_cast<UT>((*(U*)this).value) & static_cast<UT>(rhs.value));
	}
};

struct AA : ScopedEnum<AA>
{
	enum : u32 {
		VALUE_1,
		VALUE_2
	} value;

	using ScopedEnum<AA>::ScopedEnum;
};

int main()
{
	AA a = AA::VALUE_1;
	AA b = AA::VALUE_2;
	AA c = a & b;

	constexpr auto fs = cl::GetTypeName<std::string_view>();
	std::cout << fs.operator std::string_view();
}
