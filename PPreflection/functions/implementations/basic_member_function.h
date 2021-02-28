#pragma once
#include "../member_function.h"
#include "add_reference.hpp"
#include "apply_template.hpp"
#include "apply_transform.hpp"
#include "basic_function.h"
#include "conditional.hpp"
#include "pointer_to_member_info.hpp"
#include "template_t.hpp"
#include "utility/forward.hpp"

namespace PPreflection::detail
{
	template <auto mf, typename Base>
	using basic_member_function_helper = PP_GET_TYPE(PP::Template<basic_function>(
		PP::get_pointer_to_member_member_type(PP_DECLTYPE(mf)),
		PP::type<Base>));

	template <auto mf, typename Base>
	class basic_member_function : public basic_member_function_helper<mf, Base>
	{
	protected:
		static constexpr auto class_type_ = PP::get_pointer_to_member_info(PP_DECLTYPE(mf)).class_type;

		static constexpr auto caller_type = PP::conditional(PP::value<basic_member_function::ref != PP::ref_qualifier::rvalue>, class_type_ + PP::add_lvalue_tag, class_type_);

	private:
		constexpr const class_type& get_parent() const noexcept override final
		{
			return type::reflect(class_type_);
		}

		constexpr const Base::overloaded& get_overloaded_function() const noexcept override final
		{
			return reflect(reflect(PP::type<tags::overloads<PP::value_t<mf>>>));
		}
	};
}
