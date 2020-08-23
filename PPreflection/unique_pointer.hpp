#pragma once
#include "unique_pointer.h"

template <typename T, typename Deleter>
constexpr void unique_pointer<T, Deleter>::delete_ptr() noexcept
{
	if (get())
		get_deleter()(get());
}

template <typename T, typename Deleter>
constexpr unique_pointer<T, Deleter>::unique_pointer() noexcept
	: p{ nullptr, {} }
{}

template <typename T, typename Deleter>
constexpr unique_pointer<T, Deleter>::unique_pointer(ptr_base_t* ptr) noexcept
	: p{ ptr, {} }
{}

template <typename T, typename Deleter>
template <typename D>
constexpr unique_pointer<T, Deleter>::unique_pointer(ptr_base_t* ptr, D&& deleter) noexcept
	: p{ ptr, std::forward<D>(deleter) }
{}

template <typename T, typename Deleter>
constexpr auto& unique_pointer<T, Deleter>::operator=(unique_pointer&& other) noexcept
{
	delete_ptr();
	p = std::move(other.p);
	return *this;
}

template <typename T, typename Deleter>
constexpr unique_pointer<T, Deleter>::ptr_base_t* unique_pointer<T, Deleter>::get() const noexcept
{
	return p.first.get();
}

template <typename T, typename Deleter>
constexpr auto& unique_pointer<T, Deleter>::get_deleter() const noexcept
{
	return p.second;
}

template <typename T, typename Deleter>
constexpr auto unique_pointer<T, Deleter>::release() noexcept
{
	auto ptr = get();
	p.first = nullptr;
	return ptr;
}

template <typename T, typename Deleter>
constexpr unique_pointer<T, Deleter>::operator bool() const noexcept
{
	return get();
}

template <typename T, typename Deleter>
constexpr auto& unique_pointer<T, Deleter>::operator*() const noexcept
{
	return *get();
}

template <typename T, typename Deleter>
constexpr auto unique_pointer<T, Deleter>::operator->() const noexcept
{
	return get();
}

template <typename T, typename Deleter>
constexpr decltype(auto) unique_pointer<T, Deleter>::operator[](std::size_t index) const noexcept
{
	return get()[index];
}

template <typename T, typename Deleter>
constexpr unique_pointer<T, Deleter>::~unique_pointer()
{
	delete_ptr();
}
