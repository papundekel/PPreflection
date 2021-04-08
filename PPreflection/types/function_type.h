#pragma once
#include "PP/any_iterator.hpp"
#include "PP/tuple_map_to_array.hpp"

#include "../convertor.h"
#include "../print_cv.h"
#include "non_user_defined_type.h"
#include "parameter_type_olr_reference.h"
#include "referencable_type.h"
#include "return_type_reference.h"

namespace PPreflection
{
	class pointer_type;

	class function_type : public detail::non_user_defined_type<referencable_type>
	{
	public:
		constexpr PP::variant<const function_type&, const object_type&> cast_down(PP::overload_tag<referencable_type>) const noexcept override final
		{
			return {PP::placeholder, *this};
		}

		constexpr virtual return_type_reference return_type() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, parameter_type_reference> parameter_types() const noexcept = 0;
		constexpr virtual PP::any_view<PP::iterator_category::ra, parameter_type_olr_reference> parameter_types_olr() const noexcept = 0;
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
		static constexpr auto reflect_parameter_types_olr(PP::concepts::tuple auto&& types)
		{
			return PP::tuple_map_to_array(PP::type<parameter_type_olr_reference>, type::reflect, PP_FORWARD(types));
		}

		constexpr virtual convertor_object function_to_pointer_conversion() const noexcept = 0;
		constexpr virtual convertor_object function_noexcept_conversion() const noexcept = 0;

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

		enum class convertible_rank
		{
			exact,
			Noexcept,
			invalid,
		};

		constexpr convertible_rank convertible_function_type(const function_type& target) const noexcept
		{
			bool necessary_matches =
				return_type() == target.return_type() &&
				PP::view_equal(parameter_types(), target.parameter_types()) &&
				get_function_cv_qualifier() == target.get_function_cv_qualifier() &&
				get_function_ref_qualifier() == target.get_function_ref_qualifier();

			if (necessary_matches)
			{
				if (is_noexcept() == target.is_noexcept())
					return convertible_rank::exact;
				else if (is_noexcept())
					return convertible_rank::Noexcept;
				else
					return convertible_rank::invalid;
			}
			else
				return convertible_rank::invalid;
		}

		constexpr virtual const pointer_type& get_pointer_type() const noexcept = 0;

		constexpr standard_conversion_sequence make_standard_conversion_sequence(const pointer_type& target) const noexcept;
		constexpr standard_conversion_sequence make_standard_conversion_sequence(const non_array_object_type& target) const noexcept override final;
	};
}
