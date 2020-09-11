#pragma once
#include <cstddef>
#include <concepts>
#include "../PP/PP/scoped.hpp"
#include "../PP/PP/unique.hpp"
#include "../PP/PP/different_cvref.hpp"

class complete_object_type;
class dynamic_reference;

class dynamic_object
{
	struct void_tag {};

	struct deleter
	{
		PP::unique<const complete_object_type*> type_;

		constexpr void operator()(PP::unique<std::byte*>& u) const;
	};

	PP::scoped<PP::unique<std::byte*>, deleter> x;

	template <bool reference>
	constexpr void* get_address_helper() noexcept;

	constexpr void* get_address() noexcept;

	template <bool reference>
	static constexpr void* get_address(PP::unique<std::byte*>& p, const complete_object_type& t) noexcept;

	template <bool rvalue>
	constexpr dynamic_reference reference_cast_helper() noexcept;

	template <typename Initializer>
	static constexpr std::byte* allocate_and_initialize(Initializer&& i) noexcept;

	explicit constexpr dynamic_object(std::size_t tag) noexcept;

	constexpr const complete_object_type* get_type_helper() const noexcept;

	constexpr bool invalid_check_helper(std::size_t tag) const noexcept;

public:
	static constexpr dynamic_object create_invalid() noexcept;
	static constexpr dynamic_object create_void() noexcept;

	template <typename T, typename... Args>
	static constexpr dynamic_object create(Args&&... args);

	constexpr dynamic_object() = default;

	constexpr const complete_object_type& get_type() const noexcept;

	constexpr operator dynamic_reference() & noexcept;
	constexpr operator dynamic_reference() && noexcept;

	constexpr explicit operator bool() const noexcept;
	constexpr bool is_void() noexcept;

	template <std::invocable Initializer>
	explicit constexpr dynamic_object(Initializer&& initializer);
};
