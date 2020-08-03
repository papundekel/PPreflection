#pragma once
#include <array>
#include "dynamic_array.hpp"

template <typename T, std::size_t count>
class static_array : public dynamic_array<T>
{
	std::array<T, count> data;

public:
	template <typename... U>
	constexpr static_array(U&&... elements)
		: data{ std::forward<U>(elements)... }
	{}

	constexpr const T* begin() const override
	{
		return data.data();
	}
	constexpr const T* end() const override
	{
		return begin() + data.size();
	}
};
