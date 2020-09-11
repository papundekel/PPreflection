#pragma once
#include <utility>
#include "dynamic_object.h"
#include "types/complete_object_type.h"
#include "dynamic_reference.h"
#include "reflect.h"

constexpr dynamic_object dynamic_object::create_invalid() noexcept
{
	return dynamic_object(0);
}
constexpr dynamic_object dynamic_object::create_void() noexcept
{
	return dynamic_object(1);
}
template <typename T, typename... Args>
constexpr dynamic_object dynamic_object::create(Args&&... args)
{
	return dynamic_object(reflect<T, type>(), [&args...](void* ptr) { new (ptr) T(std::forward<Args>(args)...); });
}

template <bool reference>
constexpr void* dynamic_object::get_address(PP::unique<std::byte*>& p, const complete_object_type& t) noexcept
{
	void* ptr = nullptr;

	std::byte*& buffer = p.get();

	if (t.size() <= sizeof(void*))
		ptr = &buffer;
	else
		ptr = buffer;

	return ptr;
}

constexpr void dynamic_object::deleter::operator()(PP::unique<std::byte*>& u) const
{
	const complete_object_type* t = type_.get();
	if (!t)
		return;

	auto ptr = get_address<false>(u, *t);
	t->destroy(ptr);

	if (t->size() > sizeof(void*))
		delete[] u.get();
}

template <bool reference>
constexpr void* dynamic_object::get_address_helper() noexcept
{
	return get_address<reference>(x.get(), get_type());
}
constexpr dynamic_object::dynamic_object(std::size_t tag) noexcept
	: x((std::byte*)tag, deleter(nullptr))
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
		ptr = new std::byte[sizeof(R)];
		allocate_memory = ptr;
	}

	new (allocate_memory) R(std::forward<Initializer>(i)());

	return ptr;
}

constexpr const complete_object_type* dynamic_object::get_type_helper() const noexcept
{
	return x.get_destructor().type_.get();
}
constexpr const complete_object_type& dynamic_object::get_type() const noexcept
{
	return *get_type_helper();
}

constexpr void* dynamic_object::get_address() noexcept
{
	return get_address_helper<true>();
}
template <bool rvalue>
constexpr dynamic_reference dynamic_object::reference_cast_helper() noexcept
{
	return { get_address(), get_type().make_reference<rvalue>() };
}
constexpr dynamic_object::operator dynamic_reference() & noexcept
{
	return reference_cast_helper<false>();
}
constexpr dynamic_object::operator dynamic_reference() && noexcept
{
	return reference_cast_helper<true>();
}
constexpr bool dynamic_object::invalid_check_helper(std::size_t tag) const noexcept
{
	return get_type_helper() && (std::size_t)(x.get().get()) == tag;
}
constexpr dynamic_object::operator bool() const noexcept
{
	return invalid_check_helper(0);
}
constexpr bool dynamic_object::is_void() noexcept
{
	return invalid_check_helper(1);
}

template <std::invocable Initializer>
constexpr dynamic_object::dynamic_object(Initializer&& i)
	: x(allocate_and_initialize(std::forward<Initializer>(i)), deleter(&type::reflect<decltype(std::forward<Initializer>(i)())>))
{}
