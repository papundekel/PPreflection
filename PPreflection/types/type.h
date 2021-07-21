#pragma once
#include "PP/concepts/derived_from.hpp"
#include "PP/constant.hpp"
#include "PP/get_type.hpp"
#include "PP/ostream.hpp"
#include "PP/overload_tag.hpp"
#include "PP/same.hpp"
#include "PP/tuple_find_dynamic.hpp"
#include "PP/tuple_fold.hpp"
#include "PP/tuple_get.hpp"
#include "PP/tuple_map.hpp"
#include "PP/tuple_map_to_array.hpp"
#include "PP/type_tuple.hpp"
#include "PP/value_t_static_cast.hpp"
#include "PP/view.hpp"

#include "../descriptor.h"
#include "../get_type_class.hpp"

namespace PP
{
template <typename...>
class variant;
}

namespace PPreflection
{
class reference_type;
class void_type;
class function_type;
class unknown_bound_array_type;
class known_bound_array_type;
class null_type;
class integral_type;
class arithmetic_type;
class pointer_type;
class pointer_to_member_type;
class non_union_class_type;
class union_type;
class enum_type;

class type;
class pointable_type;
class referencable_type;
class object_type;
class complete_object_type;
class non_array_object_type;
class user_defined_type;
class class_type;

class super_class_type;

class function;
class member_function;

template <typename>
class cv_type;

namespace detail
{
class type_helper
{
	friend type;

	static constexpr auto type_classes =
		PP::type_tuple<reference_type,
	                   void_type,
	                   function_type,
	                   unknown_bound_array_type,
	                   known_bound_array_type,
	                   null_type,
	                   integral_type,
	                   arithmetic_type,
	                   pointer_type,
	                   pointer_to_member_type,
	                   non_union_class_type,
	                   union_type,
	                   enum_type,

	                   class_type,
	                   user_defined_type,
	                   non_array_object_type,
	                   type,
	                   complete_object_type,
	                   object_type,
	                   referencable_type,
	                   pointable_type,
	                   super_class_type>;

	static PP_FUNCTOR(get_type_class_type, PP::concepts::type auto t)
	{
		return type_classes[PP::value_t_static_cast(PP::type_size_t,
		                                            get_type_class_value_t(t))];
	});

	static constexpr auto common_type_class =
		[](PP::concepts::type auto t, PP::concepts::type auto u)
	{
		constexpr auto T = PP_COPY_TYPE(t);
		constexpr auto U = PP_COPY_TYPE(u);

		if constexpr (T == PP::type<super_class_type>)
			return u;
		else if constexpr (U == PP::type<super_class_type>)
			return t;
		else if constexpr (T == U)
			return t;
		else
		{
			constexpr auto i = PP::tuple_find_dynamic(
				[T, U](PP::concepts::type auto V)
				{
					return PP::is_derived_from(T, V) &&
				           PP::is_derived_from(U, V);
				},
				type_classes);

			return type_classes[PP::value<i>];
		}
	};

	static constexpr auto get_class =
		PP::tuple_get(PP::partial_tag, PP::value_1, type_classes) |
		PP::value_t_static_cast * PP::type_size_t | get_type_class_value_t;

	static constexpr auto reflect_helper(PP::concepts::type auto t) noexcept
		-> const PP_APPLY_TRANSFORM(get_class, t) &;

	static constexpr auto reflect_helper(
		PP::concepts::tuple auto&& types) noexcept;

	static constexpr auto reflect_cv_helper(PP::concepts::type auto t) noexcept
		-> PP_GT(PP::Template<cv_type>(~PP_DECLTYPE(reflect_helper(t))));
};
}

///
/// @brief Representes all types.
///
class type : public descriptor
{
	friend function;
	friend function_type;
	friend known_bound_array_type;
	friend member_function;
	friend null_type;
	friend pointer_to_member_type;
	friend pointer_type;
	friend reference_type;
	friend unknown_bound_array_type;
	friend user_defined_type;
	friend void_type;
	template <typename>
	friend class arithmetic_type_strong;
	template <typename>
	friend class cv_type;

public:
	///
	/// @brief Casts to a sum type of immediate descendants.
	///
	constexpr virtual PP::variant<const reference_type&, const pointable_type&>
		cast_down(PP::overload_tag<type> = {}) const noexcept = 0;

	///
	/// @brief Reflects the type @p t as a proper type descriptor.
	///
	static PP_FUNCTOR(reflect, auto&& t) -> decltype(auto)
	{
		return detail::type_helper::reflect_helper(PP_F(t));
	});

	///
	/// @brief Reflects the type t as a @ref cv_type.
	///
	static PP_FUNCTOR(reflect_cv, PP::concepts::type auto t)
	{
		return detail::type_helper::reflect_cv_helper(t);
	});

	///
	/// @brief Compares two type descriptors.
	///
	constexpr virtual bool operator==(const type& other) const noexcept = 0;

private:
	constexpr void print_name_before_parent(
		PP::ostream&) const noexcept override final
	{}

	constexpr void print_name_after_parent(
		PP::ostream& out) const noexcept override final
	{
		print_name_prefix(out);
		print_name_suffix(out);
	}

	constexpr virtual void print_name_prefix(
		PP::ostream& out) const noexcept = 0;

	constexpr virtual void print_name_suffix(
		PP::ostream& out) const noexcept = 0;

	static constexpr bool compare(const auto& this_, const type& other) noexcept
	{
		if (auto p = dynamic_cast<decltype(&this_)>(&other); p)
			return this_ == *p;
		else
			return false;
	}

	static constexpr void print_parameter_types(
		PP::ostream& out,
		PP::concepts::view auto&& parameter_types) noexcept
	{
		out.write("(");

		if (auto [i, end] = PP::view_begin_end(PP_F(parameter_types)); i != end)
		{
			i->print_name(out);
			++i;

			for (; i != end; ++i)
			{
				out.write(", ");
				i->print_name(out);
			}
		}

		out.write(")");
	}
};
}

constexpr auto PPreflection::detail::type_helper::reflect_helper(
	PP::concepts::tuple auto&& types) noexcept
{
	constexpr auto common_class =
		PP_COPY_TYPE(PP::tuple_foldr(common_type_class,
	                                 constant(PP::type<super_class_type>),
	                                 get_type_class_type + PP_F(types)));

	static_assert(common_class != PP::type<super_class_type>,
	              "type::reflect: the types don't have a common type category");

	return PP::tuple_map_to_array(common_class + PP::add_const_tag +
	                                  PP::add_lvalue_tag,
	                              type::reflect,
	                              PP_F(types));
}
