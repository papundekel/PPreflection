#pragma once
#include <cstddef>
#include "../PP/PP/scoped.hpp"
#include "../PP/PP/unique.hpp"

class type;
class dynamic_reference;

class dynamic_object
{
	struct void_tag {};

	struct deleter
	{
		PP::unique<const type*> type_;

		constexpr void operator()(PP::unique<std::byte*>& u) const;
	};

	PP::scoped<PP::unique<std::byte*>, deleter> x;

	template <bool reference>
	constexpr void* get_address_helper() noexcept;

	constexpr void* get_address() noexcept;

	template <bool reference>
	static constexpr void* get_address(PP::unique<std::byte*>& p, const type& t) noexcept;

	template <bool rvalue>
	constexpr dynamic_reference reference_cast_helper() noexcept;

	static constexpr std::byte* allocate(const type& type) noexcept;

	template <typename Initializer>
	constexpr void initialize(Initializer&& initializer) noexcept;

	explicit constexpr dynamic_object(const type* t) noexcept;

	constexpr const type* get_type_helper() noexcept;

public:
	static constexpr dynamic_object create_invalid() noexcept;
	static constexpr dynamic_object create_void() noexcept;

	template <typename T, typename... Args>
	static constexpr dynamic_object create(Args&&... args);

	constexpr dynamic_object() = default;

	template <typename Initializer>
	constexpr dynamic_object(const type& type, Initializer&& initializer);

	constexpr const type& get_type() noexcept;

	constexpr operator dynamic_reference() & noexcept;
	constexpr operator dynamic_reference() && noexcept;

	constexpr explicit operator bool() noexcept;
};
