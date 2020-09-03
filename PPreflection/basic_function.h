#pragma once
#include <string_view>
#include <type_traits>
#include "simple_ostream.h"
#include "cref_t.h"
#include "get_member_function_info.h"

class type;

namespace detail
{
	template <typename Overload, typename P, typename R, bool Noexcept, typename Base>
	class basic_function : public Base
	{
	protected:
		using ParameterTypes = P;
		using ReturnType = R;

		using OverloadedType
			= std::remove_cvref_t<
				typename get_function_info<
					typename get_member_function_info<
						decltype(&Base::get_overloaded_function)
					>::function_type
				>::return_type>;


	public:
		constexpr const type& return_type() const noexcept override final
		{
			return reflect<ReturnType, type>();
		}
		constexpr pointer_view<const cref_t<type>> parameter_types() const noexcept override final
		{
			return reflect_many<ParameterTypes, type>();
		}

		constexpr bool is_noexcept() const noexcept override final
		{
			return Noexcept;
		}

		constexpr const OverloadedType& get_overloaded_function() const noexcept override final
		{
			return reflect<Overload, OverloadedType>();
		}
	};
}
