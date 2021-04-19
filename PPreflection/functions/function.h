#pragma once
#include "PP/any_iterator.hpp"
#include "PP/functional/id.hpp"
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

namespace PPreflection
{
	class type;
	class dynamic_reference;

	class function : public descriptor
	{
		friend class Namespace;
		friend class viable_function;

	protected:
		static constexpr decltype(auto) call_with_arguments_cast_to_parameter_types(auto&& f, auto arg_iterator, auto parameter_types)
		{
			auto args = PP::tuple_zip_with_pack([]
				(dynamic_reference ref, PP::concepts::type auto t) -> auto&&
				{
					return ref.cast_unsafe(t);
				}, !make_view_tuple(PP::tuple_count_value_t(parameter_types), arg_iterator), parameter_types);

			return PP::tuple_apply(PP_FORWARD(f), PP::move(args));
		}

		static inline dynamic_variable invoke_helper(auto&& f, auto arg_iterator, auto parameter_types)
		{
			return dynamic_variable::create([&f, arg_iterator, parameter_types]
				() -> decltype(auto)
				{
					return call_with_arguments_cast_to_parameter_types(PP_FORWARD(f), arg_iterator, parameter_types);
				});
		}

		constexpr virtual void print_name_implementation(PP::simple_ostream& out) const noexcept = 0;
		constexpr void print_name_basic(PP::simple_ostream& out) const noexcept;
		constexpr void print_noexcept(PP::simple_ostream& out) const noexcept;

		constexpr void print_name_before_parent(PP::simple_ostream& out) const noexcept override final;
		constexpr void print_name_after_parent(PP::simple_ostream& out) const noexcept override;

	public:
		virtual dynamic_variable invoke_unsafe(PP::any_iterator<PP::iterator_category::ra, dynamic_reference> arg_iterator, void* = nullptr) const = 0;
		constexpr virtual const function_type& get_function_type() const noexcept = 0;

		constexpr return_type_reference return_type() const noexcept
		{
			return get_function_type().return_type();
		}
		constexpr auto parameter_types() const noexcept
		{
			return get_function_type().parameter_types();
		}
		constexpr bool is_noexcept() const noexcept
		{
			return get_function_type().is_noexcept();
		}

		constexpr virtual PP::any_view<PP::iterator_category::ra, parameter_type_olr_reference> parameter_types_olr() const noexcept
		{
			return get_function_type().parameter_types_olr();
		}

		inline dynamic_variable invoke(PP::any_view<PP::iterator_category::ra, dynamic_reference> args = {}, void* = nullptr) const;

		constexpr virtual parent_descriptor_reference_strong get_parent(int = 0) const noexcept = 0;
		constexpr parent_descriptor_reference get_parent(void*) const noexcept override final
		{
			return get_parent();
		}
	};
}
