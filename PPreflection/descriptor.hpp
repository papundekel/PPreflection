#pragma once
#include "descriptor.h"

#include "parent_descriptor_reference.h"
#include "reflect.h"
#include "types/types.h"

constexpr void PPreflection::descriptor::print_name(PP::simple_ostream& out) const noexcept
{
	print_name_before_parent(out);

	PP::simple_vector<const descriptor*> descriptors(2);

	for (const descriptor* parent = get_parent().as_descriptor(); parent != nullptr; parent = parent->get_parent().as_descriptor())
		descriptors.push_back(parent);

	for (auto i = descriptors.end(); i != descriptors.begin();)
	{
		--i;
		(*i)->print_name_after_parent(out);
		out.write("::");
	}
	print_name_after_parent(out);
}

constexpr PP::string_view PPreflection::descriptor::reflect_name(PP::concepts::type auto t) noexcept
{
	return reflect(PP::type<tags::name<PP_GET_TYPE(t)>>);
}
