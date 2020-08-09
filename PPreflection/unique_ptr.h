#pragma once
#include "../Papo/Papo/Papo.hpp"

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr
{
	using ptr_base_t = std::conditional_t<std::is_array_v<T>, std::remove_extent_t<T>, T>;

	Papo::compressed_pair<ptr_base_t*, Deleter> p;

	constexpr void delete_ptr() noexcept;

public:
	constexpr unique_ptr() noexcept;

	constexpr unique_ptr(ptr_base_t* ptr) noexcept;
	template <typename D>
	constexpr unique_ptr(ptr_base_t* ptr, D&& deleter) noexcept;

	constexpr unique_ptr(const unique_ptr&) = delete;
	constexpr void operator=(const unique_ptr&) = delete;

	constexpr unique_ptr(unique_ptr&& other) noexcept;

	constexpr auto& operator=(unique_ptr&& other) noexcept;

	constexpr auto get() const noexcept;
	constexpr auto& get_deleter() const noexcept;

	constexpr auto release() noexcept;

	constexpr explicit operator bool() const noexcept;

	constexpr auto& operator*() const noexcept;
	constexpr auto operator->() const noexcept;
	constexpr decltype(auto) operator[](std::size_t index) const noexcept;
	constexpr ~unique_ptr();
};
