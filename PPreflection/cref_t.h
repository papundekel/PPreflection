#pragma once

template <typename T>
struct cref_t
{
	const T* ptr;

	constexpr cref_t(const T& ref) noexcept;
	constexpr const T& get() const noexcept;
	constexpr operator const T& () const noexcept;
};
