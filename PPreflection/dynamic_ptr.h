#pragma once
#include <type_traits>

class type;

class dynamic_ptr
{
	friend class dynamic_wrap;

	void* ptr;
	const type& t;

	constexpr dynamic_ptr(void* ptr, const type& t) noexcept;

public:
	constexpr dynamic_ptr(const dynamic_ptr&) noexcept = default;

	template <typename T>
	//requires (!std::is_same_v<std::remove_cvref_t<T>, dynamic_ptr>)
	constexpr dynamic_ptr(T&& rvalue) noexcept;

	constexpr const type& get_type() const noexcept;

	constexpr bool lvalue() const noexcept;

	template <typename T>
	decltype(auto) cast() const;
};
