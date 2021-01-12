#pragma once
#include "cv_qualifier.hpp"

namespace detail
{
	template <typename Base>
	class cv_qualifiable_type : public Base
	{
	public:
		constexpr virtual PP::cv_qualifier get_cv_qualifier() const noexcept = 0;
	};
}
