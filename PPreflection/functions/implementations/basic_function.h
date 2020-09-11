#pragma once
#include <string_view>
#include <type_traits>
#include "get_member_function_info.hpp"

class type;

namespace detail
{
	template <typename Overload, typename P, typename R, bool N, typename Base>
	class basic_function : public Base
	{
	protected:
		using ParameterTypes = P;
		using ReturnType = R;

		using OverloadedType
			= std::remove_cvref_t<
				typename PP::get_function_info<
					typename PP::get_member_function_info<
						decltype(&Base::get_overloaded_function)
					>::Function
				>::return_type>;

		static constexpr bool Noexcept = N;

	public:
		constexpr bool is_noexcept() const noexcept override final
		{
			return Noexcept;
		}

		constexpr const OverloadedType& get_overloaded_function() const noexcept override final
		{
			return reflect<Overload, const OverloadedType&>();
		}
	};
}
