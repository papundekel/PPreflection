#pragma once
#include <cstddef>
#include "../PP/PP/scoped.hpp"
#include "../PP/PP/unique.hpp"


class type;
class dynamic_reference;

class dynamic_object
{
	struct deleter
	{
		struct defaulter
		{
			constexpr auto operator()() const noexcept;
		};

		PP::unique<const type*, defaulter> type_;

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

	static constexpr std::byte* allocate(const type& t) noexcept;

public:
	constexpr dynamic_object() = default;

	template <typename Initializer>
	constexpr dynamic_object(const type& type, Initializer&& initializer);

	constexpr const type& get_type() noexcept;

	constexpr operator dynamic_reference() & noexcept;
	constexpr operator dynamic_reference() && noexcept;
};
