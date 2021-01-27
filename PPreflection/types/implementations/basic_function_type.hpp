#pragma once
#include <type_traits>
#include "basic_referencable_type.hpp"
#include "../function_type.h"
#include "function_info.hpp"
#include "../../reflect.h"

namespace detail
{
	template <typename T>
	class basic_function_type : public basic_referencable_type<T, function_type>
	{
		static_assert(std::is_function_v<T>);

		static constexpr auto info = PP::get_function_info(PP::type<T>);

		static constexpr auto parameter_types_ = function_type::reflect_parameter_types(info.parameter_types);

		constexpr return_type_reference return_type() const noexcept override final
		{
			return type::reflect(info.return_type);
		}
		constexpr PP::any_view<parameter_type_reference> parameter_types() const noexcept override final
		{
			return parameter_types_;
		}
		constexpr bool is_noexcept() const noexcept override final
		{
			return info.Noexcept;
		}
		constexpr PP::cv_qualifier get_cv_qualifier() const noexcept override final
		{
			return info.cv;
		}
		constexpr PP::ref_qualifier get_ref_qualifier() const noexcept override final
		{
			return info.ref;
		}
	};
}
