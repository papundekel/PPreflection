#pragma once
#include <cstddef>
#include <concepts>

#include "concepts/same_except_cvref.hpp"
#include "scoped.hpp"
#include "unique.hpp"

class complete_object_type;
class dynamic_reference;

class dynamic_object
{
public:
	enum class invalid_code
	{
		none,

		implicit_conversion_error,
		indestructible_return_value,
	};

private:	
	struct void_tag {};

	union data
	{
		alignas(std::max_align_t) std::byte* ptr;
		invalid_code code;

		constexpr data() noexcept
			: ptr(nullptr)
		{}
		explicit constexpr data(invalid_code code) noexcept
			: code(code)
		{}
		explicit constexpr data(std::byte* ptr) noexcept
			: ptr(ptr)
		{}
	};

	struct deleter
	{	
		PP::unique<const complete_object_type*> type_;

		constexpr void operator()(PP::unique<data>& u) const;
	};

	PP::scoped<PP::unique<data>, deleter> x;

	template <bool reference>
	constexpr void* get_address_helper() noexcept;
	template <bool reference>
	constexpr const void* get_address_helper() const noexcept;

	constexpr void* get_address() noexcept;
	constexpr const void* get_address() const noexcept;

	template <bool reference>
	static constexpr void* get_address(PP::unique<data>& p, const complete_object_type& t) noexcept;
	template <bool reference>
	static constexpr const void* get_address(const PP::unique<data>& p, const complete_object_type& t) noexcept;

	template <bool rvalue>
	constexpr dynamic_reference reference_cast_helper() noexcept;
	template <bool rvalue>
	constexpr dynamic_reference reference_cast_helper() const noexcept;

	template <typename Initializer>
	static constexpr std::byte* allocate_and_initialize(Initializer&& i) noexcept;

	explicit constexpr dynamic_object(invalid_code code) noexcept;

	constexpr const complete_object_type* get_type_helper() const noexcept;

	constexpr bool invalid_check_helper(invalid_code code) const noexcept;

public:
	static constexpr dynamic_object create_invalid(invalid_code code) noexcept;
	static constexpr dynamic_object create_void() noexcept;

	template <typename T, typename... Args>
	static constexpr dynamic_object create(Args&&... args);

	constexpr dynamic_object() = default;

	constexpr const complete_object_type& get_type() const noexcept;

	constexpr operator dynamic_reference() &  noexcept;
	constexpr operator dynamic_reference() && noexcept;
	constexpr operator dynamic_reference() const&  noexcept;
	constexpr operator dynamic_reference() const&& noexcept;

	constexpr explicit operator bool() const noexcept;
	constexpr invalid_code get_error_code() const noexcept;
	constexpr bool is_void() const noexcept;

	template <std::invocable Initializer>
	explicit constexpr dynamic_object(Initializer&& initializer);
};

static constexpr std::string_view code_to_string(dynamic_object::invalid_code code) noexcept
{
	switch (code)
	{
	case dynamic_object::invalid_code::none:
		return "none";
	case dynamic_object::invalid_code::implicit_conversion_error:
		return "implicit_conversion_error";
	case dynamic_object::invalid_code::indestructible_return_value:
		return "indestructible_return_value";
	default:
		return "";
	}
}
