#pragma once
#include <utility>
#include "dynamic_object.h"
#include "types/complete_object_type.h"
#include "dynamic_reference.h"
#include "reflect.h"

constexpr dynamic_object dynamic_object::create_invalid(invalid_code code) noexcept
{
	return dynamic_object(code);
}
constexpr dynamic_object dynamic_object::create_void() noexcept
{
	return dynamic_object(invalid_code::none);
}
template <typename T, typename... Args>
constexpr dynamic_object dynamic_object::create(Args&&... args)
{
	return dynamic_object([&args...]() { return T(std::forward<Args>(args)...); });
}

template <bool reference>
constexpr void* dynamic_object::get_address(PP::unique<data>& p, const complete_object_type& t) noexcept
{
	void* ptr = nullptr;

	std::byte*& buffer = p.inner().ptr;

	if (t.size() <= sizeof(void*))
		ptr = &buffer;
	else
		ptr = buffer;

	return ptr;
}
template <bool reference>
constexpr const void* dynamic_object::get_address(const PP::unique<data>& p, const complete_object_type& t) noexcept
{
	const void* ptr = nullptr;

	std::byte* const& buffer = p.inner().ptr;

	if (t.size() <= sizeof(void*))
		ptr = &buffer;
	else
		ptr = buffer;

	return ptr;
}

constexpr void dynamic_object::deleter::operator()(PP::unique<data>& u) const
{
	const complete_object_type* t = type_.inner();
	if (!t)
		return;

	auto ptr = get_address<false>(u, *t);
	t->destroy(ptr);

	if (t->size() > sizeof(void*))
		operator delete(u.inner().ptr);
}

template <bool reference>
constexpr void* dynamic_object::get_address_helper() noexcept
{
	return get_address<reference>(x.inner(), get_type());
}
template <bool reference>
constexpr const void* dynamic_object::get_address_helper() const noexcept
{
	return get_address<reference>(x.inner(), get_type());
}
constexpr dynamic_object::dynamic_object(invalid_code code) noexcept
	: x(data(code), deleter(nullptr))
{}
template <typename Initializer>
constexpr std::byte* dynamic_object::allocate_and_initialize(Initializer&& i) noexcept
{
	using R = decltype(std::forward<Initializer>(i)());

	std::byte* ptr = nullptr;

	void* allocate_memory = nullptr;

	if constexpr (sizeof(R) <= sizeof(void*))
		allocate_memory = &ptr;
	else
	{
		ptr = operator new(sizeof(R), std::align_val_t{ alignof(R) });
		allocate_memory = ptr;
	}

	new (allocate_memory) R(std::forward<Initializer>(i)());

	return ptr;
}

constexpr const complete_object_type* dynamic_object::get_type_helper() const noexcept
{
	return x.get_destructor().type_.inner();
}
constexpr const complete_object_type& dynamic_object::get_type() const noexcept
{
	return *get_type_helper();
}
constexpr void* dynamic_object::get_address() noexcept
{
	return get_address_helper<true>();
}
constexpr const void* dynamic_object::get_address() const noexcept
{
	return get_address_helper<true>();
}
template <bool rvalue>
constexpr dynamic_reference dynamic_object::reference_cast_helper() noexcept
{
	return dynamic_reference(get_address(), get_type().make_reference<rvalue>());
}
template <bool rvalue>
constexpr dynamic_reference dynamic_object::reference_cast_helper() const noexcept
{
	return dynamic_reference(get_address(), get_type().make_reference<rvalue>());
}
constexpr dynamic_object::operator dynamic_reference() &  noexcept
{
	return reference_cast_helper<false>();
}
constexpr dynamic_object::operator dynamic_reference() && noexcept
{
	return reference_cast_helper<true>();
}
constexpr dynamic_object::operator dynamic_reference() const&  noexcept
{
	return reference_cast_helper<false>();
}
constexpr dynamic_object::operator dynamic_reference() const&& noexcept
{
	return reference_cast_helper<true>();
}
constexpr dynamic_object::operator bool() const noexcept
{
	return get_error_code() == invalid_code::none;
}
constexpr dynamic_object::invalid_code dynamic_object::get_error_code() const noexcept
{
	if (get_type_helper())
		return invalid_code::none;
	else
		return x.inner().inner().code;
}
constexpr bool dynamic_object::is_void() const noexcept
{
	return !get_type_helper() && (bool)*this;
}

template <std::invocable Initializer>
constexpr dynamic_object::dynamic_object(Initializer&& i)
	: x(data(allocate_and_initialize(std::forward<Initializer>(i))), deleter(&type::reflect(PP::type_v<decltype(std::forward<Initializer>(i)())>)))
{}
