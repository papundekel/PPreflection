#pragma once
#include "PP/remove_pointer.hpp"

#include "basic_function.h"

namespace PPreflection::detail
{
	template <auto f, typename Base>
	class basic_static_function : public basic_function<PP::apply_transform_t<PP::remove_pointer, decltype(f)>, Base>
	{
	protected:
		dynamic_variable invoke_unsafe(PP::any_iterator<PP::iterator_category::ra, const dynamic_reference&> arg_iterator) const noexcept override final
		{
			return this->invoke_helper(f, arg_iterator, this->parameter_types);
		}
	};
}
