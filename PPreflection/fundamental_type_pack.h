#pragma once
#include "../PP/PP/type_pack.hpp"

using fundamental_type_pack = PP::type_pack<
	  void
	, decltype(nullptr)
	, float
	, double
	, long double
	, bool
	, char
	, signed char
	, unsigned char
	, wchar_t
	, short int
	, int
	, long int
	, long long int
	, unsigned short int
	, unsigned int
	, unsigned long int
	, unsigned long long int
#ifdef __cpp_char8_t
	, char8_t
#endif
#ifdef __cpp_unicode_characters
	, char16_t
	, char32_t
#endif
>;
