#pragma once
#include "dynamic_object.h"

#include <new>

#include "PP/concepts/rvalue_reference.hpp"
#include "PP/to_void_ptr.hpp"

#include "dynamic_reference.h"
#include "reflect.h"
#include "types/complete_object_type.h"

constexpr PPreflection::dynamic_object PPreflection::dynamic_object::create(PP::concepts::type auto t, auto&&... args)
{
	return dynamic_object([&args...]() { return PP_GET_TYPE(t)(PP_FORWARD(args)...); });
}

constexpr PPreflection::dynamic_object::dynamic_object(invalid_code code) noexcept
	: x(PP::in_place_tag, nullptr, PP::unique_default_releaser_tag,	code)
{}
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

constexpr const PPreflection::complete_object_type* PPreflection::dynamic_object::get_type_helper() const noexcept
{
	return x.get_destructor().get_type();
}
constexpr const PPreflection::complete_object_type& PPreflection::dynamic_object::get_type() const noexcept
{
	return *get_type_helper();
}
constexpr auto* PPreflection::dynamic_object::get_address(auto& p, const complete_object_type& t) noexcept
{
	auto& buffer = p.get_object().ptr;

	auto* ptr = PP::to_void_ptr(buffer);

	if (t.size() > sizeof(void*))
		ptr = buffer;

	return ptr;
}
constexpr auto* PPreflection::dynamic_object::get_address(auto& r) noexcept
{
	return get_address(r.x.get_object(), r.get_type());
}
constexpr PPreflection::dynamic_reference PPreflection::dynamic_object::reference_cast_helper(auto&& r) noexcept
{
	return dynamic_reference(get_address(r), r.get_type().make_reference(PP::value<PP::is_rvalue_reference(PP_DECLTYPE(r))>));
}

constexpr PPreflection::dynamic_object::operator dynamic_reference()      &  noexcept { return reference_cast_helper(         *this ); }
constexpr PPreflection::dynamic_object::operator dynamic_reference() const&  noexcept {	return reference_cast_helper(         *this ); }
constexpr PPreflection::dynamic_object::operator dynamic_reference()      && noexcept {	return reference_cast_helper(PP::move(*this)); }
constexpr PPreflection::dynamic_object::operator dynamic_reference() const&& noexcept {	return reference_cast_helper(PP::move(*this)); }

constexpr PPreflection::dynamic_object::operator bool() const noexcept
{
	return get_error_code() == invalid_code::none;
}
constexpr PPreflection::dynamic_object::invalid_code PPreflection::dynamic_object::get_error_code() const noexcept
{
	if (get_type_helper())
		return invalid_code::none;
	else
		return x.get_object().get_object().code;
}
constexpr bool PPreflection::dynamic_object::is_void() const noexcept
{
	return !get_type_helper() && (bool)*this;
}

constexpr PPreflection::dynamic_object::dynamic_object(PP::concepts::invocable auto&& i)
	: x(PP::in_place_tag, &type::reflect(PP_DECLTYPE(PP_FORWARD(i)())), PP::unique_default_releaser_tag, allocate_and_initialize(PP_FORWARD(i)))
{}

constexpr void PPreflection::dynamic_object::deleter::operator()(auto& u) const
{
	const complete_object_type* t = type_.get_object();
	if (!t)
		return;

	auto ptr = get_address(u, *t);
	t->destroy(ptr);

	if (t->size() > sizeof(void*))
		operator delete(u.get_object().ptr);
}
