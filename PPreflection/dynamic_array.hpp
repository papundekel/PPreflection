#pragma once

template <typename T>
class dynamic_array
{
public:
	constexpr virtual const T* begin() const = 0;
	constexpr virtual const T* end() const = 0;
};
