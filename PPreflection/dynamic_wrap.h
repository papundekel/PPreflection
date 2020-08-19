#pragma once
#include <cstddef>
#include <memory>
#include <type_traits>

class type;
class dynamic_ptr;

class dynamic_wrap
{
	std::byte* buffer;
	const type& t_;

	constexpr const type& get_type() noexcept;

	constexpr std::byte* allocate() noexcept;

	template <typename T>
	constexpr T ref_cast_helper();

public:
	constexpr dynamic_wrap() noexcept;
	constexpr dynamic_wrap(const dynamic_wrap&) = delete;
	constexpr dynamic_wrap(dynamic_wrap&& other) noexcept;
	template <typename F>
	constexpr dynamic_wrap(const type& t, F&& f);

	template <typename T>
	std::unique_ptr<T> cast();

	template <typename T>
	T& ref_cast() &;

	template <typename T>
	T&& ref_cast() &&;

	constexpr operator dynamic_ptr() &;
	constexpr operator dynamic_ptr() &&;

	constexpr ~dynamic_wrap();
};
