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
			int c = PP::is_const_v(PP::type<T>);
			int v = PP::is_volatile_v(PP::type<T>) << 1;
			return PP::cv_qualifier(c | v);
		}
	};
}
