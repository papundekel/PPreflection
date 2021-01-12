#pragma once
#include "../member_function.h"
#include "basic_function.h"
#include "pointer_to_member_info.hpp"
#include "forward.hpp"
#include "apply_transform.hpp"
#include "template_t.hpp"
#include "apply_template.hpp"

class S;

namespace detail
{
	template <auto mf, typename Base>
	using basic_member_function_helper = basic_function
		< PP::apply_transform_t<PP::get_pointer_to_member_member_type, decltype(mf)>
		, Base>;

	template <auto mf, typename Base>
	class basic_member_function_base : public basic_member_function_helper<mf, Base>
	{
		using base = basic_member_function_helper<mf, Base>;

	protected:
		static constexpr auto class_type_ = PP::get_pointer_to_member_info(PP_DECLTYPE(mf)).class_type;

		static constexpr auto caller_type = []()
		{
			if constexpr (base::ref != PP::ref_qualifier::rvalue)
				return PP::template_v<std::add_lvalue_reference> / class_type_;
			else
				return class_type_;
		}();

	private:
		constexpr const class_type& get_parent() const noexcept override final
		{
			return type::reflect(PP::type_v<S>);
			//return type::reflect(class_type_);
		}

		constexpr const Base::overloaded& get_overloaded_function() const noexcept override final
		{
			return reflect(reflect(PP::type_v<reflection::overloads<PP::value_t<mf>>>));
		}
	};

	template <auto mf>
	class basic_member_function : public basic_member_function_base<mf, member_function>
	{
		dynamic_variable invoke_unsafe_member(dynamic_reference caller, PP::any_iterator<const dynamic_reference&> arg_iterator) const noexcept override final
		{
			return this->invoke_helper(
				[this, caller](auto&&... args) -> decltype(auto)
				{
					return (caller.cast_unsafe(this->caller_type).*mf)(PP_FORWARD(args)...);
				}, arg_iterator, this->parameter_types);
		}
	};
}
