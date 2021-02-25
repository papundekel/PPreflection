#include "empty_tuple.hpp"
#include "PPany_view.hpp"
#include "reflect.hpp"

template <> constexpr inline auto PPreflection::detail::metadata<PPreflection::tags::functions<PPreflection::Namespace::global>> = PP::empty_tuple{};

template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::Namespace&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::function&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::overloaded_function&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::namespace_function&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::overloaded_namespace_function&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::reference_type&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::user_defined_type&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, const PPreflection::dynamic_reference&>;
template class PP::any_view_implementation<PP::value_t<PP::iterator_category::ra>, PPreflection::parameter_type_reference>;
