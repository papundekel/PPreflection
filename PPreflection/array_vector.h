#pragma once
#include <cstddef>
#include <type_traits>

template <typename T, std::size_t capacity_>
class array_vector
{
	std::byte buffer[capacity_ * sizeof(T)];
	std::size_t count_;

	constexpr T* begin_helper() noexcept;
	constexpr T* end_helper() noexcept;

	constexpr void destroy_all() noexcept;

public:
	constexpr array_vector() noexcept;

	constexpr array_vector(const array_vector& other) noexcept(std::is_nothrow_copy_constructible_v<T>);
	constexpr array_vector(array_vector&& other) noexcept(std::is_nothrow_move_constructible_v<T>);

	constexpr ~array_vector();

	constexpr T* begin() noexcept;
	constexpr const T* begin() const noexcept;
	constexpr T* end() noexcept;
	constexpr const T* end() const noexcept;

	constexpr bool empty() const noexcept;

	constexpr void clear() noexcept;

	template <typename U>
	constexpr void push_back(U&& object) noexcept(std::is_nothrow_constructible_v<T, U>);

	constexpr void pop_back() noexcept;
};
