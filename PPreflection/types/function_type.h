#pragma once
#include "PP/any_view.hpp"
#include "PP/tuple_map_to_array.hpp"

#include "../convertor.h"
#include "../print_cv.h"
#include "non_user_defined_type.h"
#include "parameter_type_olr_reference.h"
#include "referencable_type.h"
#include "return_type.h"

namespace PPreflection::detail
{
template <typename>
class basic_function_type;
}

namespace PPreflection
{
class function;
class pointer_to_member_type;
class pointer_type;

///
/// @brief Represents a function type.
///
class function_type : public detail::non_user_defined_type<referencable_type>
{
	template <typename>
	friend class detail::basic_function_type;
	template <typename>
	friend class cv_type;
	friend function;
	friend pointer_to_member_type;
	friend pointer_type;

public:
	///
	/// @brief Gets the return type of the function type.
	///
	constexpr virtual return_type get_return_type() const noexcept = 0;

	///
	/// @brief Gets a view of parameter types of the function type.
	///
	constexpr virtual PP::any_view<PP::iterator_category::ra, parameter_type>
	parameter_types() const noexcept = 0;

	///
	/// @brief @p noexcept check.
	///
	/// @retval true iff the type is noexcept.
	///
	constexpr virtual bool is_noexcept() const noexcept = 0;

	///
	/// @brief Gets the function type cv qualifier.
	///
	constexpr virtual PP::cv_qualifier get_function_cv_qualifier()
		const noexcept = 0;

	///
	/// @brief Gets the function type ref qualifier.
	///
	constexpr virtual PP::ref_qualifier get_function_ref_qualifier()
		const noexcept = 0;

	///
	/// @brief Compares two function types.
	///
	constexpr bool operator==(const function_type& other) const noexcept
	{
		return get_return_type() == other.get_return_type() &&
		       PP::view_equal(parameter_types(), other.parameter_types()) &&
		       is_noexcept() == other.is_noexcept() &&
		       get_function_cv_qualifier() ==
		           other.get_function_cv_qualifier() &&
		       get_function_ref_qualifier() ==
		           other.get_function_ref_qualifier();
	}

	constexpr bool has_name(PP::string_view) const noexcept override final
	{
		return true;
	}

	constexpr bool operator==(const type& other) const noexcept override final
	{
		return compare(*this, other);
	}

private:
	constexpr void print_name_prefix(
		PP::ostream& out) const noexcept override final
	{
		const type& return_type_ = get_return_type();
		return_type_.print_name_prefix(out);
	}
	constexpr void print_name_suffix(
		PP::ostream& out) const noexcept override final
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

		const type& return_type_ = get_return_type();
		return_type_.print_name_suffix(out);
	}

	static constexpr auto reflect_parameter_types(
		PP::concepts::tuple auto&& types)
	{
		return PP::tuple_map_to_array(PP::type<parameter_type>,
		                              type::reflect,
		                              PP_F(types));
	}
	static constexpr auto reflect_parameter_types_olr(
		PP::concepts::tuple auto&& types)
	{
		return PP::tuple_map_to_array(
			PP::type<detail::parameter_type_olr_reference>,
			type::reflect,
			PP_F(types));
	}

	constexpr virtual convertor_object function_to_pointer_conversion()
		const noexcept = 0;
	constexpr virtual convertor_object function_noexcept_conversion()
		const noexcept = 0;

	constexpr PP::variant<const function_type&, const object_type&> cast_down(
		PP::overload_tag<referencable_type>) const noexcept override final
	{
		return {PP::placeholder, *this};
	}

	constexpr virtual PP::any_view<PP::iterator_category::ra,
	                               detail::parameter_type_olr_reference>
	parameter_types_olr() const noexcept = 0;

	enum class convertible_rank
	{
		exact,
		Noexcept,
		invalid,
	};

	constexpr convertible_rank convertible_function_type(
		const function_type& target) const noexcept
	{
		bool necessary_matches =
			get_return_type() == target.get_return_type() &&
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

	constexpr detail::standard_conversion_sequence
	make_standard_conversion_sequence(
		const pointer_type& target) const noexcept;
	constexpr detail::standard_conversion_sequence
	make_standard_conversion_sequence(
		const non_array_object_type& target) const noexcept override final;
};
}
