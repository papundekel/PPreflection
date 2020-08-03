#pragma once
#include <array>

template <typename T>
class simple_range
{
	T* begin_;
	T* end_;

public:
	constexpr simple_range() noexcept
		: begin_(nullptr)
		, end_(nullptr)
	{}

	template <std::size_t count>
	constexpr simple_range(const std::array<std::remove_const_t<T>, count>& array) noexcept
		: begin_(array.data())
		, end_(array.data() + array.size())
	{}

	constexpr auto begin() noexcept
	{
		return begin_;
	}
	constexpr auto end() noexcept
	{
		return end_;
	}
	constexpr auto& operator[](std::size_t index) noexcept
	{
		return begin()[index];
	}
};

template <typename T, std::size_t count>
simple_range(const std::array<T, count>&) -> simple_range<const T>;
