#pragma once
#include "dynamic_wrap.h"
#include "type.h"
#include "unique_ptr.h"
#include "dynamic_ptr.h"
#include "reflect.h"

constexpr const type& dynamic_wrap::get_type() noexcept
{
	return t_;
}

constexpr std::byte* dynamic_wrap::allocate() noexcept
{
	return new std::byte[t_.size()];
}

constexpr dynamic_wrap::dynamic_wrap() noexcept
	: buffer(nullptr)
	, t_(reflect<void, type>())
{}
constexpr dynamic_wrap::dynamic_wrap(dynamic_wrap&& other) noexcept
	: buffer(std::exchange(other.buffer, nullptr))
	, t_(other.t_)
{}

template <typename F>
constexpr dynamic_wrap::dynamic_wrap(const type& t, F&& f)
	: buffer(nullptr)
	, t_(t)
{
	if (t.is_reference())
		std::forward<F>(f)(&buffer);
	else
	{
		buffer = allocate();
		std::forward<F>(f)(buffer);
	}
}

template <typename T>
std::unique_ptr<T> dynamic_wrap::cast()
{
	static_assert(!std::is_reference_v<T>, "use ref_cast for reference casting");

	if (reflect<T, type>() == t_)
		return std::unique_ptr<T>(reinterpret_cast<T*>(std::exchange(buffer, nullptr)));
	else
		return {};
}

template <typename T>
constexpr T dynamic_wrap::ref_cast_helper()
{
	if ((t_.is_reference() ? t_.remove_reference() : t_).add_reference<std::is_rvalue_reference_v<T>>().can_reference_initialize(reflect<T, type>()))
		return std::forward<T>(*reinterpret_cast<std::remove_reference_t<T>*>(buffer));
	else
		throw 0;
}

template <typename T>
T& dynamic_wrap::ref_cast() &
{
	return ref_cast_helper<T&>();
}

template <typename T>
T&& dynamic_wrap::ref_cast() &&
{
	return ref_cast_helper<T&&>();
}

constexpr dynamic_wrap::operator dynamic_ptr() &
{
	return { buffer, t_.is_reference() ? t_.remove_reference().add_lreference() : t_.add_lreference() };
}
constexpr dynamic_wrap::operator dynamic_ptr() &&
{
	return { buffer, t_.is_reference() ? t_.remove_reference().add_rreference() : t_.add_rreference() };
}

constexpr dynamic_wrap::~dynamic_wrap()
{
	if (!t_.is_reference() && buffer)
	{
		t_.destroy(buffer);
		delete[] buffer;
	}
}
