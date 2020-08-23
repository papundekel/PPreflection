#pragma once
#include <memory>
#include "../Papo/Papo/Papo.hpp"
#include "unique_raw_pointer.h"

template <typename T, typename Deleter = std::default_delete<T>>
class unique_pointer
{
	using ptr_base_t = std::conditional_t<std::is_array_v<T>, std::remove_extent_t<T>, T>;

	Papo::compressed_pair<unique_raw_pointer<ptr_base_t>, Deleter> p;

	constexpr void delete_ptr() noexcept;

public:
	constexpr unique_pointer() noexcept;

	constexpr unique_pointer(ptr_base_t* ptr) noexcept;

	template <typename D>
	constexpr unique_pointer(ptr_base_t* ptr, D&& deleter) noexcept;

	constexpr unique_pointer(const unique_pointer&) = delete;
	constexpr unique_pointer(unique_pointer&& other) = default;

	constexpr void operator=(const unique_pointer&) = delete;
	constexpr auto& operator=(unique_pointer&& other) noexcept;

	constexpr ptr_base_t* get() const noexcept;
	constexpr auto& get_deleter() const noexcept;

	constexpr auto release() noexcept;

	constexpr explicit operator bool() const noexcept;

	constexpr auto& operator*() const noexcept;
	constexpr auto operator->() const noexcept;
	constexpr decltype(auto) operator[](std::size_t index) const noexcept;
	constexpr ~unique_pointer();
};
