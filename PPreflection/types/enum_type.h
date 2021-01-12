#pragma once
#include "user_defined_type.h"
#include "any_iterator.hpp"

class enum_value
{
public:
	constexpr virtual std::string_view get_name() const noexcept = 0;
	constexpr virtual std::int64_t get_value() const noexcept = 0;
};

class enum_type : public user_defined_type
{
public:
	constexpr virtual PP::any_view<const enum_value&> get_values() const noexcept = 0;
	constexpr void destroy(void* ptr) const noexcept override final
	{}
};
