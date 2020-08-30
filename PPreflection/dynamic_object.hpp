#pragma once
#include <utility>
#include "dynamic_object.h"
#include "type.h"
#include "unique_pointer.h"
#include "dynamic_reference.h"
#include "reflect.h"

constexpr dynamic_object::dynamic_object() noexcept
	: buffer(nullptr)
	, type_(&reflect<void, type>())
{}
constexpr dynamic_object::dynamic_object(dynamic_object&& other) noexcept
	: buffer(std::exchange(other.buffer, nullptr))
	, type_(std::exchange(other.type_, &reflect<void, type>()))
{}

template <typename Initializer>
constexpr dynamic_object::dynamic_object(const type& type, Initializer&& initializer)
	: buffer(nullptr)
	, type_(&type)
{
	void* ptr;

	if (std::size_t size = type_->size(); size <= sizeof(void*))
		ptr = &buffer; 
	else
		ptr = (buffer = new std::byte[size]);

	std::forward<Initializer>(initializer)(ptr);
}

constexpr const type& dynamic_object::get_type() noexcept
{
	return *type_;
}

constexpr void* dynamic_object::get_address() noexcept
{
	void* ptr;

	if (!type_->is_reference() && type_->size() <= sizeof(void*))
		ptr = &buffer;
	else
		ptr = buffer;

	return ptr;
}

constexpr dynamic_object::operator dynamic_reference() & noexcept
{
	return { get_address(), type_->make_reference<false>() };
}
constexpr dynamic_object::operator dynamic_reference() && noexcept
{
	return { get_address(), type_->make_reference<true>() };
}

constexpr dynamic_object::~dynamic_object()
{
	if (type_->size() <= sizeof(void*))
		type_->destroy(&buffer);
	else
	{
		type_->destroy(buffer);
		delete[] buffer;
	}
}
