#pragma once

template <typename T>
class unique_raw_pointer
{
	T* ptr;

public:
	constexpr unique_raw_pointer(T* ptr) noexcept;
	constexpr unique_raw_pointer(const unique_raw_pointer&) = delete;
	constexpr unique_raw_pointer(unique_raw_pointer&&) noexcept;
	constexpr unique_raw_pointer& operator=(const unique_raw_pointer&) = delete;
	constexpr unique_raw_pointer& operator=(unique_raw_pointer&&) noexcept;
	constexpr ~unique_raw_pointer() = default;

	constexpr T* get() const noexcept;
};
