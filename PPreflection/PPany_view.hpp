#pragma once
#include "PP/any_view.hpp"

namespace PPreflection
{
	class dynamic_reference;

	class Namespace;

	class function;
	class namespace_function;
	class member_function;
	class static_member_function;
	class conversion_function;
	class constructor;
	class one_parameter_converting_constructor;

	class reference_type;
	class user_defined_type;

	class parameter_type_reference;

	class enum_value;
}

extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::Namespace&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::function&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::namespace_function&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::conversion_function&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::member_function&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::static_member_function&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::constructor&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::one_parameter_converting_constructor&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::user_defined_type&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::reference_type&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::dynamic_reference&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::enum_value&>;
extern template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, PPreflection::parameter_type_reference>;
