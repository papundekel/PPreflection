#pragma once
#include "../descriptor.h"
#include "../get_type_class.hpp"
#include "../type_disjunction_reference.hpp"
#include "concepts/derived_from.hpp"
#include "get_type.hpp"
#include "same.hpp"
#include "tuple_find_dynamic.hpp"
#include "tuple_fold.hpp"
#include "tuple_get.hpp"
#include "tuple_make_array.hpp"
#include "tuple_map.hpp"
#include "type_tuple.hpp"
#include "value_t_static_cast.hpp"
#include "view.hpp"

namespace PPreflection
{
	class reference_type;
	class void_type;
	class function_type;
	class unknown_bound_array_type;
	class known_bound_array_type;
	class non_void_fundamental_type;
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

	constexpr inline auto type_classes = PP::type_tuple<
		reference_type,
		void_type,
		function_type,
		unknown_bound_array_type,
		known_bound_array_type,
		non_void_fundamental_type,
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


	PP_FUNCTOR(get_type_class_type, PP::concepts::type auto t)
	{
		return type_classes[PP::value_t_static_cast(PP::type_size_t, get_type_class_value_t(t))];
	});

	constexpr inline auto common_type_class =
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
			constexpr auto i = PP::tuple_find_dynamic([T, U]
				(PP::concepts::type auto V)
				{
					return PP::is_derived_from(T, V) && PP::is_derived_from(U, V);
				}, type_classes);

			return type_classes[PP::value<i>];
		}
	};

	class type : public descriptor
	{
		friend pointer_type;
		friend reference_type;

	public:
		constexpr virtual void print_name_prefix(PP::simple_ostream& out) const noexcept = 0;
		constexpr virtual void print_name_suffix(PP::simple_ostream& out) const noexcept = 0;

		constexpr void print_name_before_parent(PP::simple_ostream& out) const noexcept override final
		{}
		constexpr void print_name_after_parent(PP::simple_ostream& out) const noexcept override final
		{
			print_name_prefix(out);
			print_name_suffix(out);
		}

		constexpr virtual type_disjunction_reference<reference_type, pointable_type> reference_or_pointable() const noexcept = 0;

		static constexpr void print_parameter_types(PP::simple_ostream& out, PP::concepts::view auto&& parameter_types) noexcept
		{
			out.write("(");

			if (auto [i, end] = PP::view_begin_end(PP_FORWARD(parameter_types)); i != end)
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

	private:
		static constexpr auto get_class =
			PP::tuple_get(PP::partial_tag, PP::value_1, type_classes) |
			PP::value_t_static_cast * PP::type_size_t |
			get_type_class_value_t;

		static constexpr auto reflect_helper(PP::concepts::type auto t) noexcept -> const PP_APPLY_TRANSFORM(get_class, t)&;
		static constexpr auto reflect_helper(PP::concepts::tuple auto&& types) noexcept;

	public:
		static PP_FUNCTOR(reflect, auto&& x) -> decltype(auto)
		{
			return reflect_helper(PP_FORWARD(x));
		});		
	};
}

constexpr auto PPreflection::type::reflect_helper(PP::concepts::tuple auto&& types) noexcept
{
	constexpr auto super_class = PP::type<super_class_type>;
	auto class_types = PP::tuple_map(get_type_class_type, PP_FORWARD(types));
	constexpr auto common_class = PP_COPY_TYPE(PP::tuple_foldr(common_type_class, super_class, class_types));

	static_assert(common_class != super_class, "type::reflect: the types dont have a common type category");

	return PP::tuple_make_array(common_class + PP::add_const_tag + PP::add_lvalue_tag, type::reflect, PP_FORWARD(types));
}
