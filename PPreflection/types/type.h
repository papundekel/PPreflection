#pragma once
#include <type_traits>
#include "../descriptor.h"
#include "../type_disjunction_reference.hpp"
#include "view.hpp"
#include "get_type.hpp"
#include "tuple_get.hpp"
#include "type_tuple.hpp"
#include "../get_type_class.hpp"
#include "tuple_map_to_array.hpp"
#include "same.hpp"
#include "tuple_filter.hpp"
#include "tuple_foldr.hpp"
#include "tuple_map.hpp"

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

struct super_class_type {};

constexpr inline auto type_classes = PP::type_tuple_v<
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


constexpr inline auto get_type_class_type =
	[]<typename T>(T)
	{
		return get(PP::value_v<get_type_class(T{})>, type_classes);
	};

constexpr inline auto common_type_class =
	[]<typename T, typename U>(PP::type_t<T> a, PP::type_t<U> b)
	{
		if constexpr (PP::concepts::same<super_class_type, T>)
			return b;
		else if constexpr (PP::concepts::same<super_class_type, U>)
			return a;
		else if constexpr (PP::concepts::same<T, U>)
			return a;
		else
		{
			auto filtered =
				PP::tuple_filter < []<typename X>(X)
			{
				using Y = PP::get_type<X>;
				return std::is_base_of_v<Y, T> && std::is_base_of_v<Y, U>;
			} > (type_classes);

			return get(PP::value_v<0>, filtered);
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

	static constexpr void print_parameter_types(PP::simple_ostream& out, PP::view auto&& parameter_types) noexcept
	{
		out.write("(");
		if (!PP::empty(parameter_types))
		{
			auto [i, end] = PP::begin_end(PP_FORWARD(parameter_types));
			(i++)->print_name(out);
			for (; i != end; ++i)
			{
				out.write(", ");
				i->print_name(out);
			}
		}
		out.write(")");
	}

	template <typename T>
	using get_class = PP::get_type<decltype(get(PP::value_v<(std::size_t)get_type_class(PP::type_v<T>)>, type_classes))>;

	template <typename T>
	static constexpr const get_class<T>& reflect_helper(PP::type_t<T>) noexcept;

	static constexpr auto reflect_helper(PP::tuple_like auto&& types) noexcept
	{
		constexpr auto super_class = PP::type_v<super_class_type>;
		auto class_types = PP::tuple_map(get_type_class_type, PP_FORWARD(types));
		auto common_class = PP::tuple_foldr(common_type_class, super_class, class_types);

		if constexpr (decltype(common_class){} == super_class)
			return std::array<int, 0>{};
		else
			return PP::tuple_map_to_array(
				[](auto&& x) -> decltype(auto)
				{
					return reflect_helper(PP_FORWARD(x));
				}, PP_FORWARD(types),
					PP::map_v(PP::template_v<std::add_lvalue_reference>, PP::map_v(PP::template_v<std::add_const>, common_class)));
	}

	static constexpr auto reflect = [](auto&& x) -> decltype(auto) { return reflect_helper(PP_FORWARD(x)); };
};
