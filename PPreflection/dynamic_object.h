#pragma once
#include <cstddef>
#include "../Papo/Papo/scoped.hpp"
#include "../Papo/Papo/unique.hpp"


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

		Papo::unique<const type*, defaulter> type_;

		constexpr void operator()(Papo::unique<std::byte*>& u) const;
	};

	Papo::scoped<Papo::unique<std::byte*>, deleter> x;

	template <bool reference>
	constexpr void* get_address_helper() noexcept;

	constexpr void* get_address() noexcept;

	template <bool reference>
	static constexpr void* get_address(Papo::unique<std::byte*>& p, const type& t) noexcept;

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
