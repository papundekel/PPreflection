#pragma once
#include "PP/any_iterator.hpp"
#include "PP/tuple_map_to_array.hpp"

#include "../convertor.h"
#include "../print_cv.h"
#include "non_user_defined_type.h"
#include "parameter_type_reference.h"
#include "referencable_type.h"
#include "return_type_reference.h"

namespace PPreflection
{
	class function_type : public detail::non_user_defined_type<referencable_type>
	{
	public:
		constexpr virtual return_type_reference return_type() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, parameter_type_reference> parameter_types() const noexcept = 0;
		constexpr virtual bool is_noexcept() const noexcept = 0;
		constexpr virtual PP::cv_qualifier get_function_cv_qualifier() const noexcept = 0;
		constexpr virtual PP::ref_qualifier get_function_ref_qualifier() const noexcept = 0;

		constexpr bool has_name(PP::string_view) const noexcept override final
		{
			return false; //TODO
		}
		constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final
		{
			const type& return_type_ = return_type();
			return_type_.print_name_prefix(out);
		}
		constexpr void print_name_suffix(PP::simple_ostream& out) const noexcept override final
		{
			type::print_parameter_types(out, parameter_types());

			print_cv(get_function_cv_qualifier(), out);

			{
				auto ref = get_function_ref_qualifier();
				if (ref != PP::ref_qualifier::none)
					out.write("&");
				if (ref == PP::ref_qualifier::rvalue)
					out.write("&");
			}

			if (is_noexcept())
				out.write(" noexcept");

			const type& return_type_ = return_type();
			return_type_.print_name_suffix(out);
		}

		static constexpr auto reflect_parameter_types(PP::concepts::tuple auto&& types)
		{
			return PP::tuple_map_to_array(PP::type<parameter_type_reference>, type::reflect, PP_FORWARD(types));
		}

		constexpr virtual convertor_object function_to_pointer_conversion() const noexcept = 0;

		constexpr bool operator==(const function_type& other) const noexcept
		{
			return
				return_type() == other.return_type() &&
				PP::view_equal(parameter_types(), other.parameter_types()) &&
				is_noexcept() == other.is_noexcept() &&
				get_function_cv_qualifier() == other.get_function_cv_qualifier() &&
				get_function_ref_qualifier() == other.get_function_ref_qualifier();
		}
		constexpr bool operator==(const type& other) const noexcept override final
		{
			return compare(*this, other);
		}
	};
}
