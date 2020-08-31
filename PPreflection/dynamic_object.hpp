#pragma once
#include <utility>
#include "dynamic_object.h"
#include "type.h"
#include "dynamic_reference.h"
#include "reflect.h"

template <bool reference>
constexpr void* dynamic_object::get_address(PP::unique<std::byte*>& p, const type& t) noexcept
{
	void* ptr = nullptr;

	std::byte*& buffer = p.get();

	auto condition = [](const type& t)
	{
		if constexpr (reference)
		{
			if (t.is_reference())
				return false;
		}

		return t.size() <= sizeof(void*);
	};

	if (condition(t))
		ptr = &buffer;
	else
		ptr = buffer;

	return ptr;
}

constexpr auto dynamic_object::deleter::defaulter::operator()() const noexcept
{
	return &reflect<void, type>();
}

constexpr void dynamic_object::deleter::operator()(PP::unique<std::byte*>& u) const
{
	const type& t = *type_.get();
	auto ptr = get_address<false>(u, t);
	t.destroy(ptr);

	if (t.size() > sizeof(void*))
		delete[] u.get();
}

template <bool reference>
constexpr void* dynamic_object::get_address_helper() noexcept
{
	return get_address<reference>(x.get(), get_type());
}
constexpr std::byte* dynamic_object::allocate(const type& t) noexcept
{
	if (auto size = t.size(); size <= sizeof(void*))
		return nullptr;
	else
		return new std::byte[size];
}
template <typename Initializer>
constexpr dynamic_object::dynamic_object(const type& type, Initializer&& initializer)
	: x(allocate(type), deleter(&type))
{
	std::forward<Initializer>(initializer)(get_address_helper<false>());
}

constexpr const type& dynamic_object::get_type() noexcept
{
	return *x.get_destructor().type_.get();
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
