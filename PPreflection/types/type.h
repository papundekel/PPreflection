#pragma once
#include <typeindex>
#include <array>
#include "../descriptor.h"
#include "../type_disjunction_reference.hpp"

class reference_type;
class pointable_type;

class type : public descriptor
{
	constexpr virtual void print_name_prefix(PP::simple_ostream& out) const noexcept = 0;
	constexpr virtual void print_name_suffix(PP::simple_ostream& out) const noexcept = 0;

public:
	constexpr void print_name_before_parent(PP::simple_ostream& out) const noexcept override final
	{}
	constexpr void print_name_after_parent(PP::simple_ostream& out) const noexcept override final
	{
		print_name_prefix(out);
		print_name_suffix(out);
	}

	constexpr virtual type_disjunction_reference<reference_type, pointable_type> reference_or_pointable() const noexcept = 0;
};
