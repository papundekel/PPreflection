#pragma once
#include <cstddef>
#include "unique_pointer.h"

template <typename T>
class dynamic_block
{
	using b = std::byte;

	std::size_t count_;
	unique_pointer<b[]> buffer;

	constexpr T* begin_helper() const noexcept;
	constexpr T* end_helper() const noexcept;

public:
	explicit constexpr dynamic_block(std::size_t count) noexcept;
	constexpr dynamic_block(const dynamic_block&) = delete;
	constexpr dynamic_block(dynamic_block&&) = default;
	constexpr ~dynamic_block() = default;

	constexpr dynamic_block& operator=(const dynamic_block&) = delete;
	constexpr dynamic_block& operator=(dynamic_block&&) = default;

	constexpr T* begin() noexcept;
	constexpr const T* begin() const noexcept;
	constexpr T* end() noexcept;
	constexpr const T* end() const noexcept;

	constexpr std::size_t count() const noexcept;
};
