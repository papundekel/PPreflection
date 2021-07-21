#pragma once
#include "PP/any_iterator.hpp"
#include "PP/id.hpp"
#include "PP/transform_view.hpp"
#include "PP/tuple_count.hpp"
#include "PP/tuple_value_sequence_for.hpp"
#include "PP/tuple_zip_with.hpp"
#include "PP/type_tuple.hpp"
#include "PP/utility/forward.hpp"
#include "PP/view_tuple.hpp"

#include "../descriptor.h"
#include "../dynamic_variable.h"
#include "../types/function_type.h"
#include "../types/parameter_type_olr_reference.h"
#include "../types/return_type_reference.h"

namespace PPreflection::detail
{
template <auto>
class basic_conversion_function;
template <auto>
class basic_non_conversion_member_function;
template <auto, typename>
class basic_static_function;
class overload_resolution;
template <typename>
class viable_function;
}

namespace PPreflection
{
class dynamic_reference;
class type;

///
/// @brief Represents a function.
///
class function : public descriptor
{
	template <auto>
	friend class detail::basic_conversion_function;
	template <auto, typename>
	friend class detail::basic_static_function;
	template <auto>
	friend class detail::basic_non_conversion_member_function;
	friend class candidate_functions;
	friend class member_function;
	friend class Namespace;
	friend detail::overload_resolution;
	template <typename>
	friend class detail::viable_function;

public:
	///
	/// @brief Invokes the function.
	///
	/// @param arg_iterator Iterator pointing to the dynamic reference to
	/// the first argument.
	///
	virtual dynamic_variable invoke_unsafe(
		PP::any_iterator<PP::iterator_category::ra, dynamic_reference>
			arg_iterator,
		void* = nullptr) const = 0;

	///
	/// @brief Gets the type of the function.
	///
	constexpr virtual const function_type& get_function_type()
		const noexcept = 0;

	///
	/// @brief Gets the parent entity descriptor.
	///
	/// @retval Either a class or a namespace.
	///
	constexpr virtual class_or_namespace get_parent(int = 0) const noexcept = 0;

	///
	/// @brief Gets the return type of the function.
	///
	constexpr return_type_reference return_type() const noexcept
	{
		return get_function_type().return_type();
	}

	///
	/// @brief Gets the parameter types of the function.
	///
	constexpr auto parameter_types() const noexcept
	{
		return get_function_type().parameter_types();
	}

	///
	/// @brief Returns whether the function is @p noexcept.
	///
	constexpr bool is_noexcept() const noexcept
	{
		return get_function_type().is_noexcept();
	}

	constexpr parent_descriptor get_parent(void*) const noexcept override final
	{
		return get_parent();
	}

private:
	static constexpr decltype(auto) call_with_arguments_cast_to_parameter_types(
		auto&& f,
		auto arg_iterator,
		auto parameter_types)
	{
		auto args = PP::tuple_zip_with_pack(
			[](dynamic_reference ref, PP::concepts::type auto t) -> auto&&
			{
				return ref.cast_unsafe(t);
			},
			!make_view_tuple(PP::tuple_count_value_t(parameter_types),
		                     PP::move(arg_iterator)),
			parameter_types);

		return PP::tuple_apply(PP_F(f), PP::move(args));
	}

	static inline dynamic_variable invoke_helper(auto&& f,
	                                             auto arg_iterator,
	                                             auto parameter_types)
	{
		return dynamic_variable::create(
			[&f,
		     i = PP::move(arg_iterator),
		     parameter_types]() -> decltype(auto)
			{
				return call_with_arguments_cast_to_parameter_types(
					PP_F(f),
					PP::move(i),
					parameter_types);
			});
	}

	constexpr virtual void print_name_implementation(
		PP::ostream& out) const noexcept = 0;
	constexpr void print_name_basic(PP::ostream& out) const noexcept;
	constexpr void print_noexcept(PP::ostream& out) const noexcept;

	constexpr void print_name_before_parent(
		PP::ostream& out) const noexcept override final;
	constexpr void print_name_after_parent(
		PP::ostream& out) const noexcept override;

	constexpr virtual PP::any_view<PP::iterator_category::ra,
	                               detail::parameter_type_olr_reference>
	parameter_types_olr() const noexcept
	{
		return get_function_type().parameter_types_olr();
	}
};
}
