#pragma once
#include "descriptor.h"

#include "PP/ostream.hpp"
#include "PP/small_optimized_vector.hpp"

#include "parent_descriptor.h"
#include "reflect.h"

constexpr void PPreflection::descriptor::print_name(
	PP::ostream& out) const noexcept
{
	print_name_before_parent(out);

	PP::small_optimized_vector<const descriptor*, 4> descriptors;

	for (const descriptor* parent = get_parent().as_descriptor();
	     parent != nullptr;
	     parent = parent->get_parent().as_descriptor())
		descriptors.push_back(parent);

	for (auto i = descriptors.end(); i != descriptors.begin();)
	{
		--i;
		(*i)->print_name_after_parent(out);
		out.write("::");
	}
	print_name_after_parent(out);
}

constexpr PP::string_view PPreflection::descriptor::reflect_name(
	PP::concepts::type auto t) noexcept
{
	return reflect(PP::type<tags::name<PP_GT(t)>>);
}
