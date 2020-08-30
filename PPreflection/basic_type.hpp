#pragma once
#include <memory>
#include "basic_type.h"
#include "get_function_info.h"
#include "type.hpp"
#include "namespace_t.h"
#include "basic_namespace.h"
#include "get_unqualified_function.h"
#include "get_member_function_info.h"
#include "reflect.h"

template <typename T>
constexpr void detail::basic_type<T>::print_name_first(simple_ostream& out) const noexcept
{
	if constexpr (std::is_const_v<T>)
	{
		reflect<std::remove_const_t<T>, type>().print_name_first(out);
		out.write(" const");
	}
	else if constexpr (std::is_volatile_v<T>)
	{
		reflect<std::remove_volatile_t<T>, type>().print_name_first(out);
		out.write(" volatile");
	}
	else if constexpr (std::is_fundamental_v<T> || std::is_class_v<T>)
		out.write(descriptor::reflect_name<T>());
	else if constexpr (std::is_function_v<T>)
		reflect<typename get_function_info<T>::return_type, type>().print_name_first(out);
	else if constexpr (std::is_pointer_v<T>)
	{
		reflect<std::remove_pointer_t<T>, type>().print_name_first(out);
		out.write("(*");
	}
	else if constexpr (std::is_lvalue_reference_v<T>)
	{
		reflect<std::remove_reference_t<T>, type>().print_name_first(out);
		out.write("(&");
	}
	else if constexpr (std::is_rvalue_reference_v<T>)
	{
		reflect<std::remove_reference_t<T>, type>().print_name_first(out);
		out.write("(&&");
	}
	else if constexpr (std::is_array_v<T>)
		reflect<std::remove_extent_t<T>, type>().print_name_first(out);
}
template <typename T>
constexpr void detail::basic_type<T>::print_name_second(simple_ostream& out) const noexcept
{
	if constexpr (std::is_const_v<T> || std::is_volatile_v<T>)
		reflect<std::remove_cv_t<T>, type>().print_name_second(out);
	else if constexpr (std::is_function_v<T>)
	{
		out.write("(");
		const auto& parameters = reflect_many<typename get_function_info<T>::parameter_types, type>();
		if (!parameters.empty())
		{
			auto i = parameters.begin();
			(i++)->get().print_name(out);
			for (; i != parameters.end(); ++i)
			{
				out.write(", ");
				i->get().print_name(out);
			}
		}
		out.write(")");

		reflect<typename get_function_info<T>::return_type, type>().print_name_second(out);
	}
	else if constexpr (std::is_pointer_v<T>)
	{
		out.write(")");
		reflect<std::remove_pointer_t<T>, type>().print_name_second(out);
	}
	else if constexpr (std::is_reference_v<T>)
	{
		out.write(")");
		reflect<std::remove_reference_t<T>, type>().print_name_second(out);
	}
	else if constexpr (std::is_array_v<T>)
	{
		out.write("[");
		if constexpr (std::is_bounded_array_v<T>)
			out.write(std::extent_v<T>);
		out.write("]");
		reflect<std::remove_extent_t<T>, type>().print_name_second(out);
	}
}
template <typename T>
constexpr bool detail::basic_type<T>::has_name(std::string_view name) const noexcept
{
	if constexpr (!std::is_const_v<T> && !std::is_volatile_v<T> && (std::is_fundamental_v<T> || std::is_class_v<T> || std::is_enum_v<T>))
		return descriptor::reflect_name<T>() == name;
	else
		return false;
}
template <typename T>
constexpr ref_qualifier detail::basic_type<T>::get_ref_qualifier() const noexcept
{
	if constexpr (std::is_lvalue_reference_v<T>)
		return ref_qualifier::lvalue;
	else if constexpr (std::is_rvalue_reference_v<T>)
		return ref_qualifier::rvalue;
	else
		return ref_qualifier::none;
}
template <typename T>
constexpr bool detail::basic_type<T>::is_const() const noexcept
{
	return std::is_const_v<T>;
}
template <typename T>
constexpr bool detail::basic_type<T>::is_volatile() const noexcept
{
	return std::is_volatile_v<T>;
}
template <typename T>
constexpr std::size_t detail::basic_type<T>::size() const noexcept
{
	if constexpr (std::is_pointer_v<T> || std::is_reference_v<T>)
		return sizeof(void*);
	else if constexpr (!std::is_void_v<T> && !std::is_function_v<T> && !std::is_unbounded_array_v<T>)
		return sizeof(T);
	else
		return 0;
}
template <typename T>
void detail::basic_type<T>::destroy(void* ptr) const noexcept
{
	if constexpr (std::is_object_v<T> && !std::is_unbounded_array_v<T>)
		std::destroy_at(reinterpret_cast<T*>(ptr));
}
template <typename T>
constexpr pointer_view<const cref_t<type>> detail::basic_type<T>::get_direct_bases() const noexcept
{
	return {};
}
template <typename T>
constexpr const type& detail::basic_type<T>::remove_cv() const noexcept
{
	if constexpr (std::is_const_v<T> || std::is_volatile_v<T>)
		return reflect<std::remove_cv_t<T>, type>();
	else
		return *this;
}
template <typename T>
constexpr const type& detail::basic_type<T>::remove_reference() const noexcept
{
	if constexpr (std::is_reference_v<T>)
		return reflect<std::remove_reference_t<T>, type>();
	else
		return *this;
}
template <typename T>
constexpr const type& detail::basic_type<T>::remove_pointer() const noexcept
{
	return reflect<std::remove_pointer_t<T>, type>();
}
template <typename T>
constexpr const type& detail::basic_type<T>::member_pointer_type() const noexcept
{
	if constexpr (std::is_member_pointer_v<T>)
		return reflect<typename get_member_function_info<std::remove_cv_t<T>>::function_type, type>();
	else
		return *this;
}
template <typename T>
constexpr const type& detail::basic_type<T>::member_pointer_class() const noexcept
{
	if constexpr (std::is_member_pointer_v<T>)
		return reflect<typename get_member_function_info<std::remove_cv_t<T>>::class_, type>();
	else
		return *this;
}
template <typename T>
constexpr const type& detail::basic_type<T>::add_lreference() const noexcept
{
	if constexpr (!std::is_void_v<T>)
		return reflect<std::add_lvalue_reference_t<T>, type>();
	else
		return *this;
}
template <typename T>
constexpr const type& detail::basic_type<T>::add_rreference() const noexcept
{
	if constexpr (!std::is_void_v<T>)
		return reflect<std::add_rvalue_reference_t<T>, type>();
	else
		return *this;
}
template <typename T>
constexpr const type& detail::basic_type<T>::add_const() const noexcept
{
	if constexpr (!std::is_const_v<T>)
		return reflect<std::add_const_t<T>, type>();
	else
		return *this;
}
template <typename T>
constexpr const type& detail::basic_type<T>::add_volatile() const noexcept
{
	if constexpr (!std::is_volatile_v<T>)
		return reflect<std::add_volatile_t<T>, type>();
	else
		return *this;
}
template <typename T>
constexpr const type& detail::basic_type<T>::remove_const() const noexcept
{
	if constexpr (std::is_const_v<T>)
		return reflect<std::remove_const_t<T>, type>();
	else
		return *this;
}
template <typename T>
constexpr bool detail::basic_type<T>::is_void() const noexcept
{
	return std::is_void_v<T>;
}
template <typename T>
constexpr pointer_view<const cref_t<type>> detail::basic_type<T>::parameter_types() const noexcept
{
	if constexpr (std::is_function_v<T>)
		return reflect_many<typename get_function_info<T>::parameter_types, type>();
	else
		return {};
}
template <typename T>
constexpr const type& detail::basic_type<T>::return_type() const noexcept
{
	if constexpr (std::is_function_v<T>)
		return reflect<typename get_function_info<T>::return_type, type>();
	else
		return *this;
}
template <typename T>
std::size_t detail::basic_type<T>::get_id() const noexcept
{
	if constexpr (!std::is_const_v<T> && !std::is_volatile_v<T> && (std::is_fundamental_v<T> || std::is_class_v<T> || std::is_enum_v<T>))
		return ::reflect<detail::id_wrap<T>, std::size_t>();
	else
		return 0;
}

template <typename T>
constexpr const namespace_t* detail::basic_type<T>::get_namespace() const noexcept
{
	if constexpr (!std::is_const_v<T> && !std::is_volatile_v<T> && std::is_fundamental_v<T>)
		return &::reflect<namespace_t::global, namespace_t>();
	else
		return nullptr;
}
template <typename T>
constexpr std::size_t detail::basic_type<T>::get_extent() const noexcept
{
	return std::extent_v<T>;
}
template <typename T>
constexpr const type& detail::basic_type<T>::remove_extent() const noexcept
{
	return reflect<std::remove_extent_t<T>, type>();
}

template <typename T>
constexpr cv_qualifier detail::basic_type<T>::get_function_cv_qualifier() const noexcept
{
	if constexpr (std::is_function_v<T>)
		return get_function_info<T>::cv;
	else
		return cv_qualifier::none;
}
template <typename T>
constexpr ref_qualifier detail::basic_type<T>::get_function_ref_qualifier() const noexcept
{
	if constexpr (std::is_function_v<T>)
		return get_function_info<T>::ref;
	else
		return ref_qualifier::none;
}

template <typename T>
constexpr type::compound_category detail::basic_type<T>::get_category() const noexcept
{
	if constexpr (std::is_fundamental_v<T> || std::is_class_v<T> || std::is_enum_v<T>)
		return compound_category::basic;
	else if constexpr (std::is_reference_v<T>)
		return compound_category::reference;
	else if constexpr (std::is_pointer_v<T>)
		return compound_category::pointer;
	else if constexpr (std::is_member_pointer_v<T>)
		return compound_category::pointer_to_member;
	else if constexpr (std::is_function_v<T>)
		return compound_category::function;
	else
		return compound_category::array;
}

template <typename T>
constexpr pointer_view<const cref_t<overloaded_member_function>> detail::basic_type<T>::get_member_functions() const noexcept
{
	return {};
}
