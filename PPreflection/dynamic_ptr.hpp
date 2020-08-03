#pragma once
#include <utility>
#include "rvalue_reference_wrapper.hpp"
#include "reflect.hpp"
#include "type.hpp"

class dynamic_ptr
{
	void* ptr;
	const type& t;

public:
	template <typename T>
	constexpr dynamic_ptr(T& object) noexcept
		: ptr(&object)
		, t(reflect<T>)
	{}
	template <typename T>
	constexpr dynamic_ptr(std::reference_wrapper<T> lreference) noexcept
		: ptr(&lreference.get())
		, t(reflect<T&>)
	{}
	template <typename T>
	constexpr dynamic_ptr(rvalue_reference_wrapper<T> rreference) noexcept
		: ptr(&rreference.get())
		, t(reflect<T&&>)
	{}

	constexpr auto get_ptr() const noexcept
	{
		return ptr;
	}
	constexpr auto& get_type() const noexcept
	{
		return t;
	}
};
