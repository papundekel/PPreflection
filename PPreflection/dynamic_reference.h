#pragma once
#include "concepts/same_except_cvref.hpp"
#include "get_type.hpp"
#include "type_t.hpp"
#include "types/dynamic_reference_type.h"

namespace PPreflection
{
	class dynamic_variable;
	class dynamic_object;

	class dynamic_reference
	{
		friend class dynamic_object;

		void* ptr;
		dynamic_reference_type type_;

		constexpr dynamic_reference(const void* ptr, const reference_type& t) noexcept
			: ptr(const_cast<void*>(ptr))
			, type_(t)
		{}

	public:
		struct bad_cast_exception {};

		constexpr const reference_type& get_type() const noexcept
		{
			return type_;
		}

		constexpr auto cast_unsafe(PP::concepts::type auto t) const noexcept -> PP_GET_TYPE(t)&&;
		constexpr auto cast(PP::concepts::type auto t) const -> PP_GET_TYPE(t)&&;

		auto*  get_ptr(PP::concepts::type auto t) const;
		auto&  get_ref(PP::concepts::type auto t) const&;
		auto&& get_ref(PP::concepts::type auto t) const&&;

		constexpr dynamic_reference(auto&& r) noexcept
			requires ((
				!PP::is_same_except_cvref * PP::type<dynamic_reference> &&
				!PP::is_same_except_cvref * PP::type<dynamic_object> &&
				!PP::is_same_except_cvref * PP::type<dynamic_variable>)(PP_DECLTYPE(r)));
	};
}
