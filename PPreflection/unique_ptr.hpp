#pragma once
#include "unique_ptr.h"

template <typename T, typename Deleter>
constexpr void unique_ptr<T, Deleter>::delete_ptr() noexcept
{
	if (get())
		get_deleter()(get());
}

template <typename T, typename Deleter>
constexpr unique_ptr<T, Deleter>::unique_ptr() noexcept
	: p{ nullptr, {} }
{}

template <typename T, typename Deleter>
constexpr unique_ptr<T, Deleter>::unique_ptr(ptr_base_t* ptr) noexcept
	: p{ ptr, {} }
{}

template <typename T, typename Deleter>
template <typename D>
constexpr unique_ptr<T, Deleter>::unique_ptr(ptr_base_t* ptr, D&& deleter) noexcept
	: p{ ptr, std::forward<D>(deleter) }
{}

template <typename T, typename Deleter>
constexpr unique_ptr<T, Deleter>::unique_ptr(unique_ptr&& other) noexcept
	: p{ std::exchange(other.p.first, nullptr), std::move(other.get_deleter()) }
{}

template <typename T, typename Deleter>
constexpr auto& unique_ptr<T, Deleter>::operator=(unique_ptr&& other) noexcept
{
	delete_ptr();
	p = { std::exchange(other.p.first, nullptr), std::move(other.get_deleter()) };
	return *this;
}

template <typename T, typename Deleter>
constexpr auto unique_ptr<T, Deleter>::get() const noexcept
{
	return p.first;
}

template <typename T, typename Deleter>
constexpr auto& unique_ptr<T, Deleter>::get_deleter() const noexcept
{
	return p.second;
}

template <typename T, typename Deleter>
constexpr auto unique_ptr<T, Deleter>::release() noexcept
{
	auto ptr = get();
	p.first = nullptr;
	return ptr;
}

template <typename T, typename Deleter>
constexpr unique_ptr<T, Deleter>::operator bool() const noexcept
{
	return get();
}

template <typename T, typename Deleter>
constexpr auto& unique_ptr<T, Deleter>::operator*() const noexcept
{
	return *get();
}

template <typename T, typename Deleter>
constexpr auto unique_ptr<T, Deleter>::operator->() const noexcept
{
	return get();
}

template <typename T, typename Deleter>
constexpr decltype(auto) unique_ptr<T, Deleter>::operator[](std::size_t index) const noexcept
{
	return get()[index];
}

template <typename T, typename Deleter>
constexpr unique_ptr<T, Deleter>::~unique_ptr()
{
	delete_ptr();
}
