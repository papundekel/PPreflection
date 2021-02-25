#pragma once
#include "any_view.hpp"

namespace PPreflection
{
	class dynamic_reference;

	class Namespace;

	class function;
	class overloaded_function;
	class namespace_function;
	class overloaded_namespace_function;

	class reference_type;
	class user_defined_type;

	class parameter_type_reference;
}

extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::Namespace&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::function&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::overloaded_function&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::namespace_function&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::overloaded_namespace_function&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::user_defined_type&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::reference_type&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::dynamic_reference&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, PPreflection::parameter_type_reference>;
