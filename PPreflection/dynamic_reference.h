#pragma once
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

		union 
		{
			void* ptr_object;
			void(*ptr_function)();
		};
		
		cv_type_ptr<referencable_type> referenced_type_cv;
		int
			is_lvalue : 1,
			is_function : 1;

	public:
		dynamic_reference(const dynamic_reference&) = default;

		constexpr dynamic_reference(auto&& r) noexcept
		requires 
			PP::concepts::different_except_cvref<decltype(r), dynamic_reference> &&
			PP::concepts::different_except_cvref<decltype(r), dynamic_object> &&
			PP::concepts::different_except_cvref<decltype(r), dynamic_variable>;

	private:
		constexpr dynamic_reference(const volatile void* ptr, const reference_type& t) noexcept
			: dynamic_reference(PP::placeholder, const_cast<void*>(ptr), t)
		{}

		template <typename Return, typename... Parameters>
		constexpr dynamic_reference(Return (*ptr)(Parameters...), const reference_type& t) noexcept
			: dynamic_reference(PP::placeholder, (void(*)())ptr, t)
		{}

		template <typename T>
		constexpr dynamic_reference(PP::placeholder_t, T* ptr, const reference_type& t) noexcept
			: ptr_object(nullptr)
			, referenced_type_cv(&t.remove_reference())
			, is_lvalue(t.is_lvalue())
			, is_function(PP::concepts::function<T>)
		{
			if constexpr (PP::concepts::function<T>)
				ptr_function = ptr;
			else
				ptr_object = ptr;
		}

	public:
		dynamic_reference& operator=(const dynamic_reference&) = default;

		struct bad_cast_exception {};

		constexpr auto get_type() const noexcept
		{
			return dynamic_reference_type(*referenced_type_cv, is_lvalue);
		}

		inline auto cast_unsafe(PP::concepts::type auto t) const noexcept -> PP_GET_TYPE(t)&&;
		inline auto cast(PP::concepts::type auto t) const -> PP_GET_TYPE(t)&&;

		inline auto*  get_ptr(PP::concepts::type auto t) const;
		inline auto&  get_ref(PP::concepts::type auto t) const&;
		inline auto&& get_ref(PP::concepts::type auto t) const&&;

		inline decltype(auto) visit(PP::concepts::type auto t, auto&& f) const;
		inline decltype(auto) visit_ptr(PP::concepts::type auto t, auto&& f) const;

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
			if (is_function)
				return PP::reinterpret__cast(t, ptr_function);
			else
				return PP::reinterpret__cast(t, ptr_object);
		}
	};
}
