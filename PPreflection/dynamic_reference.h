#pragma once
#include "concepts/same_except_cvref.hpp"
#include "types/dynamic_reference_type.h"
#include "type_t.hpp"

class reference_type;
class dynamic_variable;

class dynamic_reference
{
	friend class dynamic_object;

	void* ptr;
	dynamic_reference_type t;

	constexpr dynamic_reference(const void* ptr, const reference_type& t) noexcept;

public:
	struct bad_cast_exception {};

	constexpr const reference_type& get_type() const noexcept;

	template <typename T>
	constexpr T&& cast_unsafe(PP::type_t<T> = {}) const noexcept;

	template <typename T>
	constexpr T&& cast(PP::type_t<T> = {}) const;

	template <typename T>
	T* get_ptr() const;

	template <typename T>
	T& get_ref() const&;

	template <typename T>
	T&& get_ref() const&&;

	constexpr dynamic_reference(auto&& reference) noexcept
		requires
		PP::concepts::different_except_cvref<dynamic_reference>, R> &&
		PP::concepts::different_except_cvref<dynamic_object>, R> &&
		PP::concepts::different_except_cvref<dynamic_variable>, R>;
};
