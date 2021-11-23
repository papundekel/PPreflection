#pragma once
#include <initializer_list>

#include "PP/reference_wrapper.hpp"
#include "PP/small_optimized_vector.hpp"
#include "PP/transform_view.hpp"
#include "PP/view_equal.hpp"

#include "args_to_types.hpp"
#include "overload_resolution.h"
#include "reflect.h"

namespace PPreflection
{
///
/// @brief An optimization class for invoking OR before invocation.
///
class viable_functions
{
	using argument_list_type =
		PP::small_optimized_vector<PP::reference_wrapper<const reference_type&>,
	                               8>;
	using pair = PP::tuple<argument_list_type,
	                       PP::optional<detail::viable_function<function>>>;

	PP::small_optimized_vector<pair, 8> arg_function_pairs;

	inline viable_functions(PP::placeholder_t,
	                        PP::concepts::view auto&& candidates,
	                        PP::concepts::view auto&& argument_lists)
		: arg_function_pairs()
	{
		for (auto&& argument_list : PP_F(argument_lists))
		{
			arg_function_pairs.push_back(PP::forward_as_tuple(
				argument_list_type::create_copy_view(PP_F(argument_list)),
				detail::overload_resolution::resolve(
					PP_F(candidates),
					PP_F(argument_list))[PP::value_0]));
		}
	}

public:
	///
	/// @brief Constructs the viable functions with @p candidates. Invokes
	/// the OR on all of @p argument_lists.
	///
	/// @param candidates A @ref PP::concepts::view of @p const @ref
	/// function @p &.
	/// @param argument_lists A view of views of @p const @ref
	/// reference_type @p &. Represents all
	/// the possible argument lists.
	///
	inline viable_functions(PP::concepts::view auto&& candidates,
	                        PP::concepts::view auto&& argument_lists)
		: viable_functions(PP::placeholder,
	                       PP_F(candidates),
	                       PP_F(argument_lists))
	{}

	///
	/// @brief Constructs the viable functions with @p candidates. Invokes
	/// the OR on all of @p argument_tuples.
	///
	/// @param candidates A @ref PP::concepts::view of @p const @ref
	/// function @p &.
	/// @param argument_tuples A tuple of tuples of types. Represents all
	/// the possible argument lists.
	///
	inline viable_functions(PP::concepts::view auto&& candidates,
	                        PP::concepts::tuple auto&&... argument_tuples)
		: viable_functions(
			  PP::placeholder,
			  PP_F(candidates),
			  PP::make_simple_view <
				  PP::tuple_map_forward_array * type::reflect +
					  PP::forward_as_tuple(PP_F(argument_tuples)...))
	{}

	///
	/// @brief Invokes the best function with @p arguments.
	///
	/// @retval void The argument types did not match any of the types
	/// provided at construction.
	///
	dynamic_variable invoke(PP::concepts::view auto&& arguments) const
	{
		return invoke_impl(PP_F(arguments));
	}
	///
	/// @see invoke()
	///
	dynamic_variable invoke(
		const std::initializer_list<dynamic_reference>& arguments) const
	{
		return invoke_impl(arguments);
	}

private:
	dynamic_variable invoke_impl(PP::concepts::view auto&& arguments) const
	{
		auto invoked_arg_types = args_to_types(PP_F(arguments));

		for (auto&& [arg_types, f] : arg_function_pairs)
		{
			if (PP::view_equal(arg_types | PP::transform(PP::unref),
			                   invoked_arg_types))
			{
				if (f)
					return f->invoke(PP_F(arguments));
				else
					return dynamic_variable::create_invalid(
						dynamic_object::invalid_code::
							overload_resolution_error);
			}
		}

		return dynamic_variable::create_invalid(
			dynamic_object::invalid_code::overload_resolution_error);
	}
};
}
