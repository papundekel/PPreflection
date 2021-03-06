#pragma once
#include "PP/concepts/function.hpp"
#include "PP/function_info.hpp"

#include "../../dynamic_reference.h"
#include "../../dynamic_variable.h"
#include "../../reflect.h"
#include "../function_type.h"
#include "basic_referencable_type.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_function_type : public basic_referencable_type<T, function_type>
	{
		static_assert(PP::concepts::function<T>);

		static constexpr auto info = PP::get_function_info(PP::type<T>);

		static constexpr auto parameter_types_ = function_type::reflect_parameter_types(info.parameter_types);

		constexpr return_type_reference return_type() const noexcept override final
		{
			return type::reflect(info.return_type);
		}
		constexpr PP::any_view<PP::iterator_category::ra, parameter_type_reference> parameter_types() const noexcept override final
		{
			return parameter_types_;
		}
		constexpr bool is_noexcept() const noexcept override final
		{
			return info.Noexcept;
		}
		constexpr PP::cv_qualifier get_function_cv_qualifier() const noexcept override final
		{
			return info.cv;
		}
		constexpr PP::ref_qualifier get_function_ref_qualifier() const noexcept override final
		{
			return info.ref;
		}
		constexpr convertor_object function_to_pointer_conversion() const noexcept override final
		{
			if constexpr (info.cv == PP::cv_qualifier::none && info.ref == PP::ref_qualifier::none)
			{
				return create_convertor_object_to_value(PP::type<T>);
			}
			else
				return nullptr;
		}
	};
}
