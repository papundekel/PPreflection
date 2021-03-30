#pragma once
#include "dynamic_object.h"

#include <new>
#include <cstring>

#include "PP/concepts/rvalue_reference.hpp"

#include "dynamic_reference.h"
#include "reflect.h"
#include "types/complete_object_type.h"
#include "types/cv_type.h"
#include "types/make_reference_type.h"

constexpr PPreflection::dynamic_object::deleter::deleter(cv_type<complete_object_type> t) noexcept
	: type_(PP::unique_default_releaser_tag, &t.type)
	, cv(t.cv)
{}

constexpr const PPreflection::complete_object_type& PPreflection::dynamic_object::deleter::get_type() const
{
	return *type_.get_object();
}

constexpr PP::cv_qualifier PPreflection::dynamic_object::deleter::get_cv() const
{
	return cv;
}

constexpr PPreflection::dynamic_object::dynamic_object(PP::concepts::invocable auto&& i)
	: dynamic_object(type::reflect_cv(PP_DECLTYPE(PP_FORWARD(i)())), allocate_and_initialize(PP_FORWARD(i)))
{}

constexpr PPreflection::dynamic_object::dynamic_object(cv_type<complete_object_type> cv_type, void* data) noexcept
	: x(PP::in_place_tag, cv_type, PP::unique_default_releaser_tag, data)
{}

constexpr PPreflection::dynamic_object PPreflection::dynamic_object::create(PP::concepts::type auto t, auto&&... args)
{
	return dynamic_object([&args...]() { return PP_GET_TYPE(t)(PP_FORWARD(args)...); });
}

constexpr PPreflection::dynamic_object PPreflection::dynamic_object::create_copy(auto&& arg)
{
	using T = PP_GET_TYPE(~PP_DECLTYPE(arg));
	return dynamic_object([&arg]() { return T(PP_FORWARD(arg)); });
}

constexpr PPreflection::dynamic_object PPreflection::dynamic_object::create_shallow_copy(dynamic_reference r) noexcept
{
	auto cv_type = r.get_type().remove_reference().cast(PP::type<complete_object_type>);
	const void* from_ptr = r.get_void_ptr();
	return dynamic_object(cv_type, allocate(cv_type.type).initialize_and_get([from_ptr, size = cv_type.type.size()]
		(void* to_ptr)
		{
			std::memcpy(to_ptr, from_ptr, size);
		}));
}

constexpr PPreflection::cv_type<PPreflection::complete_object_type> PPreflection::dynamic_object::get_cv_type() const noexcept
{
	return {get_type(), x.get_destructor().get_cv()};
}

constexpr const PPreflection::complete_object_type& PPreflection::dynamic_object::get_type() const noexcept
{
	return x.get_destructor().get_type();
}

constexpr PPreflection::dynamic_object::operator dynamic_reference() const
{
	return reference_cast_helper(PP::value_true);
}

constexpr PPreflection::dynamic_reference PPreflection::dynamic_object::move() const
{
	return reference_cast_helper(PP::value_false);
}

constexpr PPreflection::dynamic_object::operator bool() const noexcept
{
	return get_error_code() == invalid_code::none;
}

constexpr PPreflection::dynamic_object::invalid_code PPreflection::dynamic_object::get_error_code() const noexcept
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

constexpr void* PPreflection::dynamic_object::get_address(auto& unique, const complete_object_type& t) noexcept
{
	void*& buffer = unique.get_object().ptr;

	void* ptr = &buffer;

	if (t.size() > sizeof(void*) || t.alignment() > alignof(max_align_t))
		ptr = buffer;

	return ptr;
}

constexpr void* PPreflection::dynamic_object::get_address() const noexcept
{
	return get_address(x.get_object(), get_cv_type().type);
}

constexpr PPreflection::dynamic_reference PPreflection::dynamic_object::reference_cast_helper(PP::concepts::value auto lvalue) const
{
	if (*this)
	{
		auto cv_type = get_cv_type();
		return dynamic_reference(get_address(), cv_type.type.get_reference_type(*lvalue, cv_type.cv));
	}
	else
		throw 0;
}

constexpr PPreflection::dynamic_object::allocated_ptr PPreflection::dynamic_object::allocate(const complete_object_type& t) noexcept
{
	auto size = t.size();
	auto alignment = t.alignment();

	if (size > sizeof(void*) || alignment > alignof(max_align_t))
		return {operator new(size, std::align_val_t{alignment})};
	else
		return {};
}

constexpr void* PPreflection::dynamic_object::allocate_and_initialize(PP::concepts::invocable auto&& i) noexcept
{
	using R = decltype(PP_FORWARD(i)());
	
	return allocate(type::reflect(PP::type<R>)).initialize_and_get([&i]
		(void* ptr)
		{
			new (ptr) R(PP_FORWARD(i)());
		});
}

constexpr void PPreflection::dynamic_object::deleter::operator()(PP::unique<data, PP::default_releaser>& u) const
{
	auto type_p = type_.get_object();
	if (!type_p)
		return;

	auto& type = *type_p;

	auto* ptr = get_address(u, type);
	type.destroy(ptr);

	if (type.size() > sizeof(void*)|| type.alignment() > alignof(max_align_t))
		operator delete(u.get_object().ptr);
}
