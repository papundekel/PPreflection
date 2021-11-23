#pragma once
#include "PP/reference_wrapper.hpp"
#include "PP/small_optimized_vector.hpp"
#include "PP/transform_view.hpp"

#include "args_to_types.hpp"
#include "dynamic_object.h"
#include "dynamic_variable.h"
#include "functions/function.h"
#include "overload_resolution.h"

namespace PPreflection
{
///
/// @brief Represents a set of functions, which are the input of overload
/// resolution.
///
class candidate_functions
{
	using candidate_functions_container =
		PP::small_optimized_vector<PP::reference_wrapper<const function&>, 16>;

	candidate_functions_container functions;

public:
	///
	/// @brief Constructs candidate functions from a view of functions.
	///
	/// @param functions A @ref PP::concepts::view of functions.
	///
	explicit inline candidate_functions(PP::concepts::view auto&& functions)
		: functions(
			  candidate_functions_container::create_copy_view(PP_F(functions)))
	{}

	///
	/// @brief Filters functions from the set which don't have a certain
	/// name.
	///
	/// @param name The name.
	/// @return A reference to *this.
	///
	inline auto& trim_by_name(PP::string_view name)
	{
		functions.remove(
			[name](const function& f)
			{
				return !f.has_name(name);
			});

		return *this;
	}

	///
	/// @brief Filters functions from the set which don't have a certain
	/// argument count.
	///
	/// @param name The argument count.
	/// @return A reference to *this.
	///
	inline auto& trim_by_exact_argument_count(PP::size_t arg_count)
	{
		functions.remove(
			[arg_count](const function& f)
			{
				return PP::view_count(f.parameter_types_olr()) != arg_count;
			});

		return *this;
	}

	///
	/// @brief Runs the overload resolution on the set of functions with @p
	/// arguments. If the OR selects a function, invokes it
	///
	/// @param arguments A @ref PP::concepts::view of arguments.
	///
	/// @return A result of the dynamic call.
	/// @retval error The OR or the invocation failed.
	/// @retval void The selected function returned void.
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

	///
	/// @brief Returns a begin iterator of the candidate set.
	///
	/// @return The begin iterator.
	///
	auto begin() const
	{
		return functions.begin() & PP::transform(PP::unref);
	}

	///
	/// @brief Returns a end iterator of the candidate set.
	///
	/// @return The end iterator.
	///
	auto end() const
	{
		return functions.end();
	}

private:
	dynamic_variable invoke_impl(PP::concepts::view auto&& arguments) const
	{
		auto [f, error_code] = detail::overload_resolution::resolve(
			functions,
			args_to_types(PP_F(arguments)));

		if (f)
			return f->invoke(PP_F(arguments));
		else
			return dynamic_variable::create_invalid(
				dynamic_object::invalid_code::overload_resolution_error);
	}
};
}
