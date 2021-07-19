#include "member_function.hpp"

#include "PP/iterator.hpp"

#include "../descriptor.hpp"
#include "../dynamic_object.hpp"
#include "../parent_descriptor_reference.hpp"
#include "../parent_descriptor_reference_strong.hpp"
#include "../types/cv_type.hpp"
#include "../types/non_user_defined_type.hpp"
#include "../types/reference_type.hpp"
#include "function.hpp"

PPreflection::dynamic_variable PPreflection::member_function::invoke_unsafe(
	PP::any_iterator<PP::iterator_category::ra, dynamic_reference> arg_iterator,
	void*) const
{
	return invoke_unsafe(*arg_iterator, PP::iterator_next(arg_iterator));
}
