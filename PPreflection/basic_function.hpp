#pragma once
#include "basic_function.h"
#include "reflect.h"

template <typename Overload, typename ParameterTypes, typename ReturnType, bool Noexcept, typename Base>
constexpr void detail::basic_function<Overload, ParameterTypes, ReturnType, Noexcept, Base>::print_name(simple_ostream& out) const noexcept
{
	out.write(descriptor::reflect_name<Overload>());
}
template <typename Overload, typename ParameterTypes, typename ReturnType, bool Noexcept, typename Base>
constexpr bool detail::basic_function<Overload, ParameterTypes, ReturnType, Noexcept, Base>::has_name(std::string_view name) const noexcept
{
	return descriptor::reflect_name<Overload>() == name;
}
template <typename Overload, typename ParameterTypes, typename ReturnType, bool Noexcept, typename Base>
constexpr const type& detail::basic_function<Overload, ParameterTypes, ReturnType, Noexcept, Base>::return_type() const noexcept
{
	return reflect<ReturnType, type>();
}
template <typename Overload, typename ParameterTypes, typename ReturnType, bool Noexcept, typename Base>
constexpr simple_range<const cref_t<type>> detail::basic_function<Overload, ParameterTypes, ReturnType, Noexcept, Base>::parameter_types() const noexcept
{
	return reflect_many<ParameterTypes, type>();
}
template <typename Overload, typename ParameterTypes, typename ReturnType, bool Noexcept, typename Base>
constexpr bool detail::basic_function<Overload, ParameterTypes, ReturnType, Noexcept, Base>::is_noexcept() const noexcept
{
	return Noexcept;
}
