#pragma once
#include "PP/add_cv_ref.hpp"
#include "PP/apply_template.hpp"
#include "PP/apply_transform.hpp"
#include "PP/conditional.hpp"
#include "PP/pointer_to_member_info.hpp"
#include "PP/template_t.hpp"
#include "PP/utility/forward.hpp"

#include "../../types/non_union_class_type.h"
#include "../../types/parameter_type_olr_reference.h"
#include "../member_function.h"
#include "basic_function.h"

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

		static constexpr auto make_implicit_parameter() noexcept
		{
			if constexpr (basic_member_function::ref == PP::ref_qualifier::none)
				return cv_type<class_type>(type::reflect(class_type_), basic_member_function::cv);
			else
				return type::reflect(PP::add_cv_ref(PP::value<basic_member_function::cv>, PP::value<basic_member_function::ref>, class_type_));
		}

		static constexpr auto parameter_types_olr_tail = type::reflect + basic_member_function::parameter_types;
		static constexpr auto parameter_types_olr_ = PP::type<parameter_type_olr_reference> & PP::tuple_prepend(make_implicit_parameter(), parameter_types_olr_tail);

	private:
		constexpr const class_type& get_parent() const noexcept override final
		{
			return type::reflect(class_type_);
		}

		constexpr PP::any_view<PP::iterator_category::ra, parameter_type_olr_reference> parameter_types_olr() const noexcept override final
		{
			return this->parameter_types_olr_;
		}
	};
}
