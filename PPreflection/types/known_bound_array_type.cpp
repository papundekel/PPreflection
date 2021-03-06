#include "known_bound_array_type.hpp"

#include "../descriptor.hpp"
#include "../dynamic_object.hpp"
#include "../functions/functions.hpp"
#include "../parent_descriptor_reference.hpp"
#include "../parent_descriptor_reference_strong.hpp"
#include "types.hpp"

void PPreflection::known_bound_array_type::destroy(void* ptr) const noexcept
{
	const complete_object_type& element_type = remove_extent();
	char* p = static_cast<char*>(ptr);
	for (char* i = p; i != p + size(); i += element_type.size())
		element_type.destroy(i);
}
