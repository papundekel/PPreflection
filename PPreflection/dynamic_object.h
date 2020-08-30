#pragma once
#include <cstddef>

class type;
class dynamic_reference;

class dynamic_object
{
	std::byte* buffer;
	const type* type_;

	constexpr void* get_address() noexcept;

public:
	constexpr dynamic_object() noexcept;
	constexpr dynamic_object(const dynamic_object&) = delete;
	constexpr dynamic_object(dynamic_object&& other) noexcept;
	template <typename Initializer>
	constexpr dynamic_object(const type& type, Initializer&& initializer);

	constexpr const type& get_type() noexcept;

	constexpr operator dynamic_reference() & noexcept;
	constexpr operator dynamic_reference() && noexcept;

	constexpr ~dynamic_object();
};
