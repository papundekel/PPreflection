#pragma once
#include "any_iterator.hpp"
#include "parameter_type_reference.h"
#include "referencable_type.h"
#include "return_type_reference.h"
#include "tuple_map_to_array.hpp"

namespace PPreflection
{
	class function_type : public referencable_type
	{
	public:
		constexpr virtual return_type_reference return_type() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, parameter_type_reference> parameter_types() const noexcept = 0;
		constexpr virtual bool is_noexcept() const noexcept = 0;
		constexpr virtual PP::cv_qualifier get_cv_qualifier() const noexcept = 0;
		constexpr virtual PP::ref_qualifier get_ref_qualifier() const noexcept = 0;

		constexpr const descriptor* get_parent_implementation() const noexcept override
		{
			return nullptr;
		}

		constexpr bool has_name(PP::string_view name) const noexcept override final
		{
			return false;
		}
		constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final
		{
			return_type().visit([&out](const type& t) { t.print_name_prefix(out); });
		}
		constexpr void print_name_suffix(PP::simple_ostream& out) const noexcept override final
		{
			type::print_parameter_types(out, parameter_types());

			{
				auto cv = get_cv_qualifier();
				if (PP::cv_is_const(cv))
					out.write(" const");
				if (PP::cv_is_volatile(cv))
					out.write(" volatile");
			}

			{
				auto ref = get_ref_qualifier();
				if (ref != PP::ref_qualifier::none)
					out.write("&");
				if (ref == PP::ref_qualifier::rvalue)
					out.write("&");
			}

			if (is_noexcept())
				out.write(" noexcept");

			return_type().visit([&out](const type& t) { t.print_name_suffix(out); });
		}

		static constexpr auto reflect_parameter_types(PP::concepts::tuple auto&& types)
		{
			return PP::tuple_map_to_array(PP::type<parameter_type_reference>, type::reflect, PP_FORWARD(types));
		}
	};
}
