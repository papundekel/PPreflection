#pragma once
#include "cv_qualifier.hpp"

namespace PPreflection
{
	namespace detail
	{
		template <typename Base>
		class dynamic_cv_qualifiable_type : public Base
		{
			PP::cv_qualifier cv;

		public:
			constexpr explicit dynamic_cv_qualifiable_type(PP::cv_qualifier cv = PP::cv_qualifier::none) noexcept
				: cv(cv)
			{}

			constexpr PP::cv_qualifier get_cv_qualifier() const noexcept override final
			{
				return cv;
			}
		};
	}
}
