#pragma once
#include <variant>

#include "PP/concepts/same_except_cvref.hpp"
#include "PP/get_type.hpp"
#include "PP/reinterpret_cast.hpp"

#include "types/dynamic_reference_type.h"

namespace PPreflection
{
	class dynamic_variable;
	class dynamic_object;

	class dynamic_reference
	{
		friend class dynamic_object;

		std::variant<void*, void(*)()> ptr;
		cv_type_ptr<referencable_type> referenced_type_cv;
		bool is_lvalue;

	public:
		dynamic_reference(const dynamic_reference&) = default;

		constexpr dynamic_reference(auto&& r) noexcept
		requires 
			PP::concepts::different_except_cvref<decltype(r), dynamic_reference> &&
			PP::concepts::different_except_cvref<decltype(r), dynamic_object> &&
			PP::concepts::different_except_cvref<decltype(r), dynamic_variable>;

	private:
		constexpr dynamic_reference(const void* ptr, const reference_type& t) noexcept
			: ptr(const_cast<void*>(ptr))
			, referenced_type_cv(&t.remove_reference())
			, is_lvalue(t.is_lvalue())
		{}
		template <typename Return, typename... Parameters>
		constexpr dynamic_reference(Return (*ptr)(Parameters...), const reference_type& t) noexcept
			: ptr((void(*)())ptr)
			, referenced_type_cv(&t.remove_reference())
			, is_lvalue(t.is_lvalue())
		{}

	public:
		dynamic_reference& operator=(const dynamic_reference&) = default;

		struct bad_cast_exception {};

		constexpr dynamic_reference_type get_type() const noexcept
		{
			return {*referenced_type_cv, is_lvalue};
		}

		inline auto cast_unsafe(PP::concepts::type auto t) const noexcept -> PP_GET_TYPE(t)&&;
		inline auto cast(PP::concepts::type auto t) const -> PP_GET_TYPE(t)&&;

		inline auto*  get_ptr(PP::concepts::type auto t) const;
		inline auto&  get_ref(PP::concepts::type auto t) const&;
		inline auto&& get_ref(PP::concepts::type auto t) const&&;

		inline decltype(auto) visit(PP::concepts::type auto t, auto&& f) const;

		constexpr void* get_void_ptr() const;

		constexpr dynamic_reference with_cv_ref(PP::cv_qualifier cv, bool is_lvalue) const noexcept
		{
			auto copy = *this;
			copy.referenced_type_cv.cv = cv;
			copy.is_lvalue = is_lvalue;
			return copy;
		}

	private:
		constexpr auto* reinterpret(PP::concepts::type auto t) const
		{
			return std::visit([t](auto* p) -> decltype(auto) { return PP::reinterpret__cast(t, p); }, ptr);
		}
	};
}
