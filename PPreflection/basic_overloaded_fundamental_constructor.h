#pragma once
#include <array>
#include "overloaded_constructor.h"
#include "reflect.h"
#include "basic_fundamental_copy_constructor.h"
#include "basic_fundamental_default_constructor.h"

namespace detail
{
	template <typename T>
	class basic_overloaded_fundamental_constructor final : public overloaded_constructor
	{
		static constexpr auto default_constructor = basic_fundamental_default_constructor<T>{};
		static constexpr auto copy_constructor = basic_fundamental_copy_constructor<T>{};

		static constexpr std::array<cref_t<function>, 2> functions_overloads = { default_constructor, copy_constructor };
		static constexpr std::array<cref_t<constructor>, 2> constructor_overloads = { default_constructor, copy_constructor };
		static constexpr std::array<cref_t<one_parameter_converting_constructor>, 1> one_parameter_converting_constructor_overloads = { copy_constructor };

	public:
		constexpr pointer_view<const cref_t<function>> get_function_overloads() const noexcept override final
		{
			return functions_overloads;
		}
		constexpr pointer_view<const cref_t<constructor>> get_constructor_overloads() const noexcept override final
		{
			return constructor_overloads;
		}
		constexpr pointer_view<const cref_t<one_parameter_converting_constructor>> get_one_parameter_converting_constructor_overloads() const noexcept override final
		{
			return one_parameter_converting_constructor_overloads;
		}

		constexpr const type& get_enclosing_class() const noexcept override final
		{
			return reflect<T, type>();
		}
	};
}
