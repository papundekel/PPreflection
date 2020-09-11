#pragma once
#include <type_traits>
#include "../descriptor.h"
#include "../type_disjunction_reference.hpp"
#include "../../PP/PP/view.hpp"

class void_type;
class reference_type;
class function_type;
class unknown_bound_array_type;
class known_bound_array_type;
class non_void_fundamental_type;
class pointer_type;
class pointer_to_member_type;
class class_type;
class union_type;
class enum_type;

class pointable_type;

class type : public descriptor
{
	template <typename T>
	static constexpr auto get_class_helper() noexcept
	{
		struct error {};

		if constexpr (std::is_reference_v<T>)
			return PP::type_t<reference_type>{};
		else if constexpr (std::is_void_v<T>)
			return PP::type_t<void_type>{};
		else if constexpr (std::is_function_v<T>)
			return PP::type_t<function_type>{};
		else if constexpr (std::is_unbounded_array_v<T>)
			return PP::type_t<unknown_bound_array_type>{};
		else if constexpr (std::is_bounded_array_v<T>)
			return PP::type_t<known_bound_array_type>{};
		else if constexpr (std::is_fundamental_v<T>)
			return PP::type_t<non_void_fundamental_type>{};
		else if constexpr (std::is_pointer_v<T>)
			return PP::type_t<pointer_type>{};
		else if constexpr (std::is_member_pointer_v<T>)
			return PP::type_t<pointer_to_member_type>{};
		else if constexpr (std::is_class_v<T>)
			return PP::type_t<class_type>{};
		else if constexpr (std::is_union_v<T>)
			return PP::type_t<union_type>{};
		else if constexpr (std::is_enum_v<T>)
			return PP::type_t<enum_type>{};
		else
			return error{};
	}

	constexpr virtual void print_name_prefix(PP::simple_ostream& out) const noexcept = 0;
	constexpr virtual void print_name_suffix(PP::simple_ostream& out) const noexcept = 0;

public:
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
			auto i = PP::begin(parameter_types);
			(i++)->print_name(out);
			for (; i != PP::end(parameter_types); ++i)
			{
				out.write(", ");
				i->print_name(out);
			}
		}
		out.write(")");
	}

	template <typename T>
	using get_class = PP::get_type<decltype(get_class_helper<T>())>;

	template <typename T>
	static constexpr const get_class<T>& reflect() noexcept;
};
