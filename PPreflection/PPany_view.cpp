#include "PPany_view.hpp"

#include "PP/empty_tuple.hpp"

#include "reflect_dummy.hpp"

template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::Namespace&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::function&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::overloaded_function&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::namespace_function&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::overloaded_namespace_function&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::conversion_function&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::member_function&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::overloaded_member_function&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::static_member_function&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::overloaded_static_member_function&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::constructor&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::one_parameter_converting_constructor&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::reference_type&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::user_defined_type&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::dynamic_reference&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::enum_value&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, PPreflection::parameter_type_reference>;
