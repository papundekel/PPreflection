#pragma once
#include "basic_class_type.h"
#include "type.h"
#include "namespace_t.h"
#include "function.h"

template <typename Namespace, typename T, typename MemberFunctions, typename Bases>
constexpr pointer_view<const cref_t<type>> detail::basic_class_type<Namespace, T, MemberFunctions, Bases>::get_direct_bases() const noexcept
{
	return reflect_many<Bases, type>();
}
template <typename Namespace, typename T, typename MemberFunctions, typename Bases>
constexpr const namespace_t* detail::basic_class_type<Namespace, T, MemberFunctions, Bases>::get_namespace() const noexcept
{
	return &reflect<Namespace, namespace_t>();
}
template <typename Namespace, typename T, typename MemberFunctions, typename Bases>
constexpr pointer_view<const cref_t<overloaded_member_function>> detail::basic_class_type<Namespace, T, MemberFunctions, Bases>::get_member_functions() const noexcept
{
	return reflect_many<MemberFunctions, overloaded_member_function>();
}
