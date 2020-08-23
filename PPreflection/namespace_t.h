#pragma once
#include <string_view>
#include "descriptor.h"
#include "simple_range.h"
#include "cref_t.h"

class type;
class overloaded_namespace_function;

class namespace_t : public descriptor
{
public:
	constexpr virtual simple_range<const cref_t<type>> get_types() const noexcept = 0;
	constexpr virtual simple_range<const cref_t<overloaded_namespace_function>> get_functions() const noexcept = 0;

	constexpr const type* get_type(std::string_view name) const noexcept;
	constexpr const overloaded_namespace_function* get_function(std::string_view name) const noexcept;

	struct global {};
};
