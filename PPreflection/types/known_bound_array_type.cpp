#include "known_bound_array_type.hpp"

#include "../descriptor.hpp"
#include "../dynamic_object.hpp"
#include "../parent_descriptor_reference.hpp"
#include "../parent_descriptor_reference_strong.hpp"
#include "array_type.hpp"
#include "class_type.hpp"
#include "cv_type.hpp"
#include "non_array_object_type.hpp"
#include "non_user_defined_type.hpp"
#include "pointer_to_member_type.hpp"
#include "reference_type.hpp"
#include "unknown_bound_array_type.hpp"

void PPreflection::known_bound_array_type::destroy(void* ptr) const noexcept
{
	const complete_object_type& element_type = remove_extent();
	char* p = static_cast<char*>(ptr);
	for (char* i = p; i != p + size(); i += element_type.size())
		element_type.destroy(i);
}
