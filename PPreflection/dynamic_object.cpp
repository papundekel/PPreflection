#include "dynamic_object.hpp"

#include <cstring>

#include "dynamic_reference.hpp"
#include "parent_descriptor.hpp"
#include "types/cv_type.hpp"
#include "types/non_user_defined_type.hpp"
#include "types/reference_type.hpp"

PPreflection::dynamic_object PPreflection::dynamic_object::create_shallow_copy(
	dynamic_reference r) noexcept
{
	auto cv_type =
		r.get_type().remove_reference().cast(PP::type<complete_object_type>);
	const void* from_ptr = r.get_void_ptr();
	return dynamic_object(
		cv_type,
		allocate(cv_type.type)
			.initialize_and_get(
				[from_ptr, size = cv_type.type.size()](void* to_ptr)
				{
					std::memcpy(to_ptr, from_ptr, size);
				}));
}
