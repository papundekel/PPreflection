#pragma once
#include <type_traits>
#include "cv_qualifier.hpp"

namespace detail
{
	template <typename T, typename Base>
	class basic_cv_qualifiable_type : public Base
	{
	public:
		constexpr PP::cv_qualifier get_cv_qualifier() const noexcept override final
		{
			if constexpr (std::is_const_v<T> && std::is_volatile_v<T>)
				return PP::cv_qualifier::const_volatile;
			else if constexpr (std::is_const_v<T>)
				return PP::cv_qualifier::Const;
			else if constexpr (std::is_volatile_v<T>)
				return PP::cv_qualifier::Volatile;
			else
				return PP::cv_qualifier::none;
		}
	};
}
