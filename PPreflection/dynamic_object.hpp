#pragma once
#include "dynamic_object.h"

#include <new>

#include "PP/alignment_of.hpp"
#include "PP/concepts/rvalue_reference.hpp"
#include "PP/size_of.hpp"
#include "PP/to_void_ptr.hpp"

#include "dynamic_reference.h"
#include "types/complete_object_type.h"
#include "types/cv_type.h"
#include "types/dynamic_reference_type.h"

namespace PPreflection::detail
{
static constexpr auto get_alignment_impl(
	const PPreflection::complete_object_type& t) noexcept
{
	return t.alignment();
}
static constexpr auto get_alignment_impl(PP::concepts::type auto t) noexcept
{
	return PP::alignment_of(t);
}
static constexpr auto get_alignment(const auto& t) noexcept
{
	return std::align_val_t{get_alignment_impl(t)};
}
static constexpr auto get_size(
	const PPreflection::complete_object_type& t) noexcept
{
	return t.size();
}
static constexpr auto get_size(PP::concepts::type auto t) noexcept
{
	return PP::size_of(t);
}
static constexpr bool is_small_type(const auto& t) noexcept
{
	return get_alignment_impl(t) <= alignof(max_align_t) &&
	       get_size(t) <= sizeof(void*);
}
}

constexpr PPreflection::dynamic_object::deleter::deleter(
	cv_type<complete_object_type> t) noexcept
	: type_(PP::movable_default_releaser_tag, &t.type)
	, cv(t.cv)
{}

constexpr const PPreflection::complete_object_type&
PPreflection::dynamic_object::deleter::get_type() const
{
	return *type_.get_object();
}

constexpr PP::cv_qualifier PPreflection::dynamic_object::deleter::get_cv() const
{
	return cv;
}

constexpr PPreflection::dynamic_object::dynamic_object(
	PP::concepts::invocable auto&& i)
	: dynamic_object(type::reflect_cv(PP_DECLTYPE(PP_F(i)())), PP_F(i))
{}

constexpr PPreflection::dynamic_object::dynamic_object(
	cv_type<complete_object_type> cv_type,
	PP::concepts::invocable auto&& i) noexcept
	: dynamic_object(cv_type, allocate_and_initialize(PP_F(i)))
{}

constexpr PPreflection::dynamic_object::dynamic_object(
	cv_type<complete_object_type> cv_type,
	data data) noexcept
	: x(PP::in_place_tag, cv_type, PP::movable_default_releaser_tag, data)
{}

constexpr PPreflection::dynamic_object PPreflection::dynamic_object::create(
	PP::concepts::type auto t,
	auto&&... args)
{
	return dynamic_object(
		[&args...]()
		{
			return PP_GT(t)(PP_F(args)...);
		});
}

constexpr PPreflection::dynamic_object
PPreflection::dynamic_object::create_copy(auto&& arg)
{
	using T = PP_GT(~PP_DECLTYPE(arg));
	return dynamic_object(
		[&arg]()
		{
			return T(PP_F(arg));
		});
}

constexpr PPreflection::cv_type<PPreflection::complete_object_type>
PPreflection::dynamic_object::get_cv_type() const noexcept
{
	return {get_type(), x.get_destructor().get_cv()};
}

constexpr const PPreflection::complete_object_type&
PPreflection::dynamic_object::get_type() const noexcept
{
	return x.get_destructor().get_type();
}

constexpr PPreflection::dynamic_object::operator dynamic_reference() const
{
	return reference_cast_helper(PP::value_true);
}

constexpr PPreflection::dynamic_reference PPreflection::dynamic_object::move()
	const
{
	return reference_cast_helper(PP::value_false);
}

constexpr PPreflection::dynamic_object::operator bool() const noexcept
{
	return get_error_code() == invalid_code::none;
}

constexpr PPreflection::dynamic_object::invalid_code
PPreflection::dynamic_object::get_error_code() const noexcept
{
	if (has_valid_type())
		return invalid_code::none;
	else
		return x.get_object().get_object().code;
}

constexpr bool PPreflection::dynamic_object::is_void() const noexcept
{
	return !has_valid_type() && (bool)*this;
}

constexpr auto* PPreflection::dynamic_object::get_address(
	auto& unique,
	const complete_object_type& t) noexcept
{
	auto& data = unique.get_object();

	auto* ptr = PP::to_void_ptr(&data.small_bytes);

	if (t.size() > sizeof(void*) || t.alignment() > alignof(max_align_t))
		ptr = data.ptr;

	return ptr;
}

constexpr const void* PPreflection::dynamic_object::get_address() const noexcept
{
	return get_address(x.get_object(), get_cv_type().type);
}

constexpr PPreflection::dynamic_reference
PPreflection::dynamic_object::reference_cast_helper(
	PP::concepts::value auto lvalue) const
{
	if (*this)
	{
		auto cv_type = get_cv_type();
		return dynamic_reference(
			get_address(),
			detail::dynamic_reference_type(cv_type, *lvalue));
	}
	else
		throw 0;
}

constexpr PPreflection::dynamic_object::allocated_ptr
PPreflection::dynamic_object::allocate(const auto& t) noexcept
{
	if (detail::is_small_type(t))
		return {};
	else
		return {operator new(detail::get_size(t), detail::get_alignment(t))};
}

constexpr PPreflection::dynamic_object::data
PPreflection::dynamic_object::allocate_and_initialize(
	PP::concepts::invocable auto&& i) noexcept
{
	using R = decltype(PP_F(i)());

	return allocate(PP::type<R>)
	    .initialize_and_get(
			[&i](void* ptr)
			{
				new (ptr) R(PP_F(i)());
			});
}

constexpr void PPreflection::dynamic_object::deleter::operator()(
	PP::movable<data, PP::default_releaser>& u) const
{
	auto type_p = type_.get_object();
	if (!type_p)
		return;

	auto& type = *type_p;

	void* ptr = get_address(u, type);
	type.destroy(ptr);

	if (!detail::is_small_type(type))
		operator delete(ptr, detail::get_alignment(type));
}
