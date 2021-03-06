#pragma once
#include "dynamic_object.h"

#include <new>

#include "PP/concepts/rvalue_reference.hpp"
#include "PP/to_void_ptr.hpp"

#include "dynamic_reference.h"
#include "reflect.h"
#include "types/complete_object_type.h"
#include "types/cv_type.h"
#include "types/make_reference_type.h"

constexpr PPreflection::dynamic_object PPreflection::dynamic_object::create(PP::concepts::type auto t, auto&&... args)
{
	return dynamic_object([&args...]() { return PP_GET_TYPE(t)(PP_FORWARD(args)...); });
}

constexpr char* PPreflection::dynamic_object::allocate_and_initialize(PP::concepts::invocable auto&& i) noexcept
{
	using R = decltype(PP_FORWARD(i)());

	char* ptr = nullptr;

	void* allocated_memory = nullptr;

	if constexpr (sizeof(R) <= sizeof(ptr))
		allocated_memory = &ptr;
	else
	{
		ptr = operator new(sizeof(R), std::align_val_t{alignof(R)});
		allocated_memory = ptr;
	}
	
	new (allocated_memory) R(PP_FORWARD(i)());

	return ptr;
}

constexpr PPreflection::cv_type<PPreflection::complete_object_type> PPreflection::dynamic_object::get_cv_type()       noexcept
{
	return x.get_destructor().get_cv_type();
}
constexpr PPreflection::cv_type<PPreflection::complete_object_type> PPreflection::dynamic_object::get_cv_type() const noexcept
{
	auto inner_cv_type = x.get_destructor().get_cv_type();
	return inner_cv_type.add_cv(PP::cv_qualifier::Const);
}
constexpr auto* PPreflection::dynamic_object::get_address(auto& p, const complete_object_type& t) noexcept
{
	auto& buffer = p.get_object().ptr;

	auto* ptr = PP::to_void_ptr(buffer);

	if (t.size() > sizeof(void*))
		ptr = buffer;

	return ptr;
}
constexpr auto* PPreflection::dynamic_object::get_address(auto& o) noexcept
{
	return get_address(o.x.get_object(), o.get_cv_type().type);
}
constexpr PPreflection::dynamic_reference PPreflection::dynamic_object::reference_cast_helper(auto& o) noexcept
{
	return dynamic_reference(get_address(o), make_reference_type(PP::value<PP::is_rvalue_reference(PP_DECLTYPE(o))>, o.get_cv_type()));
}

constexpr PPreflection::dynamic_object::operator dynamic_reference()       noexcept { return reference_cast_helper(*this); }
constexpr PPreflection::dynamic_object::operator dynamic_reference() const noexcept { return reference_cast_helper(*this); }

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

constexpr PPreflection::dynamic_object::dynamic_object(invalid_code code) noexcept
	: x(PP::in_place_tag, 0, PP::unique_default_releaser_tag, code)
{}
constexpr PPreflection::dynamic_object::dynamic_object(PP::concepts::invocable auto&& i)
	: x(PP::in_place_tag, type::reflect_cv(PP_DECLTYPE(PP_FORWARD(i)())), PP::unique_default_releaser_tag, allocate_and_initialize(PP_FORWARD(i)))
{}

constexpr PPreflection::dynamic_object::deleter::deleter(cv_type<complete_object_type> t) noexcept
	: type_(PP::unique_default_releaser_tag, &t.type, t.cv)
{}
constexpr void PPreflection::dynamic_object::deleter::operator()(PP::unique<data, PP::default_releaser>& u) const
{
	auto o_cv_type = type_.get_object();
	if (!o_cv_type.type)
		return;

	auto& type = *o_cv_type.type;

	auto ptr = get_address(u, type);
	type.destroy(ptr);

	if (type.size() > sizeof(void*))
		operator delete(u.get_object().ptr);
}
constexpr PPreflection::cv_type<PPreflection::complete_object_type> PPreflection::dynamic_object::deleter::get_cv_type() const
{
	auto ct = type_.get_object();
	return {*ct.type, ct.cv};
}
