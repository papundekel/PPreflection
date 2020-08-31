#pragma once
#include <type_traits>
#include "../Papo/PP/different_cvref.hpp"

class type;

class dynamic_reference
{
	friend class dynamic_object;

	void* ptr;
	const type& t;

	constexpr dynamic_reference(void* ptr, const type& t) noexcept;

public:
	constexpr dynamic_reference(const dynamic_reference&) noexcept = default;

	template <PP::different_cvref<dynamic_reference> R>
	constexpr dynamic_reference(R&& reference) noexcept;

	constexpr const type& get_type() const noexcept;

	template <typename T>
	constexpr T&& cast_unsafe() const;

	template <typename T>
	constexpr T&& cast() const;

	template <typename T>
	T* get_ptr() const;

	template <typename T>
	T& get_ref() const&;

	template <typename T>
	T&& get_ref() const&&;

	dynamic_reference move() const;
};
