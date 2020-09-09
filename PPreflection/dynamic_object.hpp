#pragma once
#include <utility>
#include "dynamic_object.h"
#include "types/object_type.h"
#include "dynamic_reference.h"
#include "reflect.h"

constexpr dynamic_object dynamic_object::create_invalid() noexcept
{
	return dynamic_object(nullptr);
}
constexpr dynamic_object dynamic_object::create_void() noexcept
{
	return dynamic_object(&reflect<void, type>());
}
template <typename T, typename... Args>
constexpr dynamic_object dynamic_object::create(Args&&... args)
{
	return dynamic_object(reflect<T, type>(), [&args...](void* ptr) { new (ptr) T(std::forward<Args>(args)...); });
}

template <bool reference>
constexpr void* dynamic_object::get_address(PP::unique<std::byte*>& p, const object_type& t) noexcept
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
	const object_type* t = type_.get();
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
constexpr dynamic_object::dynamic_object(const object_type* t) noexcept
	: x({}, deleter(t))
{}
constexpr std::byte* dynamic_object::allocate(const object_type& type) noexcept
{
	std::byte* ptr;

	if (auto size = type.size(); size <= sizeof(void*))
		return nullptr;
	else
		return new std::byte[size];

	return ptr;
}

template <typename Initializer>
constexpr dynamic_object::dynamic_object(const object_type& type, Initializer&& i)
	: x(allocate(type), deleter(&type))
{
	std::forward<Initializer>(i)(get_address_helper<false>());
}
constexpr const object_type* dynamic_object::get_type_helper() noexcept
{
	return x.get_destructor().type_.get();
}
constexpr const object_type& dynamic_object::get_type() noexcept
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
constexpr dynamic_object::operator bool() noexcept
{
	return get_type_helper();
}
