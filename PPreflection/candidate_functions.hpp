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
	class candidate_functions
	{
		using candidate_functions_container = PP::small_optimized_vector<PP::reference_wrapper<const function&>, 16>;

		candidate_functions_container functions;

	public:
		explicit constexpr candidate_functions(PP::concepts::view auto&& functions)
			: functions(candidate_functions_container::create_copy_view(PP_FORWARD(functions)))
		{}

		constexpr auto& trim_by_name(PP::string_view name)
		{
			functions.remove([name]
				(const function& f)
				{
					return !f.has_name(name);
				});

			return *this;
		}

		constexpr auto& trim_by_exact_argument_count(PP::size_t arg_count)
		{
			functions.remove([arg_count]
				(const function& f)
				{
					return PP::view_count(f.parameter_types_olr()) != arg_count;
				});
			
			return *this;
		}

		dynamic_variable invoke(PP::concepts::view auto&& arguments) const
		{
			return invoke_impl(PP_FORWARD(arguments));
		}

		dynamic_variable invoke(const std::initializer_list<dynamic_reference>& arguments) const
		{
			return invoke_impl(arguments);
		}

		auto begin() const
		{
			return functions.begin() & PP::transform(PP::unref);
		}

		auto end() const
		{
			return functions.end();
		}

	private:
		dynamic_variable invoke_impl(PP::concepts::view auto&& arguments) const
		{
			auto [f, error_code] = overload_resolution(functions, args_to_types(PP_FORWARD(arguments)));

			if (f)
				return f->invoke(PP_FORWARD(arguments));
			else
				return dynamic_variable::create_invalid(dynamic_object::invalid_code::overload_resolution_error);
		}
	};
}
