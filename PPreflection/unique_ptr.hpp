#pragma once
#include <utility>

template <typename T>
class unique_ptr
{
	static constexpr bool is_array_type = std::is_array_v<T>;

	using ptr_base_t = std::conditional_t<is_array_type, std::remove_extent_t<T>, T>;

	ptr_base_t* ptr;

	constexpr void delete_ptr() noexcept
	{
		if constexpr (!is_array_type)
			delete ptr;
		else
			delete[] ptr;
	}

public:
	constexpr unique_ptr(ptr_base_t* ptr) noexcept
		: ptr(ptr)
	{}

	unique_ptr(const unique_ptr&) = delete;
	void operator=(const unique_ptr&) = delete;

	constexpr unique_ptr(unique_ptr&& other) noexcept
		: ptr(std::exchange(other.ptr, nullptr))
	{}

	auto& operator=(unique_ptr&& other) noexcept
	{
		delete_ptr();
		ptr = std::exchange(other.ptr, nullptr);
		return *this;
	}

	constexpr auto get() const noexcept
	{
		return ptr;
	}

	constexpr auto& operator*() const noexcept
	{
		return *ptr;
	}
	constexpr auto operator->() const noexcept
	{
		return ptr;
	}
	constexpr decltype(auto) operator[](std::size_t index) const noexcept
	{
		return ptr[index];
	}
	constexpr ~unique_ptr()
	{
		delete_ptr();
	}
};
