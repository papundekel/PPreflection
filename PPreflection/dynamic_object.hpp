#pragma once
#include <new>

#include "dynamic_object.h"
#include "dynamic_reference.h"
#include "reflect.h"
#include "types/complete_object_type.h"

template <typename T, typename... Args>
constexpr PPreflection::dynamic_object PPreflection::dynamic_object::create(Args&&... args)
{
	return dynamic_object([&args...]() { return T(PP_FORWARD(args)...); });
}

constexpr void* PPreflection::dynamic_object::get_address(PP::concepts::value auto reference, PP::unique<data>& p, const complete_object_type& t) noexcept
{
	void* ptr = nullptr;

	char*& buffer = p.inner().ptr;

	if (t.size() <= sizeof(void*))
		ptr = &buffer;
	else
		ptr = buffer;

	return ptr;
}
constexpr const void* PPreflection::dynamic_object::get_address(PP::concepts::value auto reference, const PP::unique<data>& p, const complete_object_type& t) noexcept
{
	const void* ptr = nullptr;

	char* const& buffer = p.inner().ptr;

	if (t.size() <= sizeof(void*))
		ptr = &buffer;
	else
		ptr = buffer;

	return ptr;
}

constexpr void PPreflection::dynamic_object::deleter::operator()(PP::unique<data>& u) const
{
	const complete_object_type* t = type_.inner();
	if (!t)
		return;

	auto ptr = get_address(PP::value_false, u, *t);
	t->destroy(ptr);

	if (t->size() > sizeof(void*))
		operator delete(u.inner().ptr);
}

constexpr void* PPreflection::dynamic_object::get_address_helper(PP::concepts::value auto reference) noexcept
{
	return get_address(reference, x.inner(), get_type());
}
constexpr const void* PPreflection::dynamic_object::get_address_helper(PP::concepts::value auto reference) const noexcept
{
	return get_address(reference, x.inner(), get_type());
}
constexpr PPreflection::dynamic_object::dynamic_object(invalid_code code) noexcept
	: x(PP::make_unique_default(data(code)), deleter(nullptr))
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
constexpr void* PPreflection::dynamic_object::get_address() noexcept
{
	return get_address_helper(PP::value_true);
}
constexpr const void* PPreflection::dynamic_object::get_address() const noexcept
{
	return get_address_helper(PP::value_true);
}
constexpr PPreflection::dynamic_reference PPreflection::dynamic_object::reference_cast_helper(PP::concepts::value auto rvalue) noexcept
{
	return dynamic_reference(get_address(), get_type().make_reference(rvalue));
}
constexpr PPreflection::dynamic_reference PPreflection::dynamic_object::reference_cast_helper(PP::concepts::value auto rvalue) const noexcept
{
	return dynamic_reference(get_address(), get_type().make_reference(rvalue));
}
constexpr PPreflection::dynamic_object::operator dynamic_reference() &  noexcept
{
	return reference_cast_helper(PP::value_false);
}
constexpr PPreflection::dynamic_object::operator dynamic_reference() && noexcept
{
	return reference_cast_helper(PP::value_true);
}
constexpr PPreflection::dynamic_object::operator dynamic_reference() const&  noexcept
{
	return reference_cast_helper(PP::value_false);
}
constexpr PPreflection::dynamic_object::operator dynamic_reference() const&& noexcept
{
	return reference_cast_helper(PP::value_true);
}
constexpr PPreflection::dynamic_object::operator bool() const noexcept
{
	return get_error_code() == invalid_code::none;
}
constexpr PPreflection::dynamic_object::invalid_code PPreflection::dynamic_object::get_error_code() const noexcept
{
	if (get_type_helper())
		return invalid_code::none;
	else
		return x.inner().inner().code;
}
constexpr bool PPreflection::dynamic_object::is_void() const noexcept
{
	return !get_type_helper() && (bool)*this;
}

constexpr PPreflection::dynamic_object::dynamic_object(PP::concepts::invocable auto&& i)
	: x(PP::make_unique_default(data(allocate_and_initialize(PP_FORWARD(i)))), deleter(&type::reflect(PP_DECLTYPE(PP_FORWARD(i)()))))
{}
