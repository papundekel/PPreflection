#pragma once
#include "get_cv.hpp"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_cv_qualifiable_type : public Base
	{
	public:
		constexpr PP::cv_qualifier get_cv_qualifier() const noexcept override final
		{
			return *PP::get_cv_value_t(PP::type<T>);
		}
	};
}
