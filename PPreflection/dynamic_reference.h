#pragma once
#include <type_traits>

class type;

class dynamic_reference
{
	friend class dynamic_object;

	void* ptr;
	const type& t;

	constexpr dynamic_reference(void* ptr, const type& t) noexcept;

public:
	constexpr dynamic_reference(const dynamic_reference&) noexcept = default;

	template <typename T>
	//requires (!std::is_same_v<std::remove_cvref_t<T>, dynamic_reference>)
	constexpr dynamic_reference(T&& rvalue) noexcept;

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
