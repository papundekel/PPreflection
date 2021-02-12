#include "known_bound_array_type.h"

void PPreflection::known_bound_array_type::destroy(void* ptr) const noexcept
{
	const auto& element_type = remove_extent();
	char* p = static_cast<char*>(ptr);
	for (char* i = p; i != p + size(); i += element_type.size())
		element_type.destroy(i);
}
