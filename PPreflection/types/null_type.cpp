#include "null_type.hpp"

#include "../convertor.hpp"
#include "../descriptor.hpp"
#include "../dynamic_object.hpp"
#include "../parent_descriptor_reference.hpp"
#include "../parent_descriptor_reference_strong.hpp"
#include "arithmetic_type.hpp"
#include "arithmetic_type_strong.hpp"
#include "class_type.hpp"
#include "cv_type.hpp"
#include "known_bound_array_type.hpp"
#include "non_array_object_type.hpp"
#include "non_user_defined_type.hpp"
#include "pointer_to_member_type.hpp"
#include "reference_type.hpp"
#include "type.hpp"
#include "unknown_bound_array_type.hpp"

namespace
{
	constexpr auto null = PPreflection::null_type{};
}

PPreflection::dynamic_object PPreflection::null_type::create_instance() const noexcept
{
	return dynamic_object(null, []{ return nullptr; });
}
