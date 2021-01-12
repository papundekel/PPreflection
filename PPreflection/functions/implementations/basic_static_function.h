#pragma once
#include <type_traits>
#include "basic_function.h"

namespace detail
{
	template <auto f, typename Base>
	class basic_static_function : public basic_function<std::remove_pointer_t<decltype(f)>, Base>
	{
	protected:
		dynamic_variable invoke_unsafe(PP::any_iterator<const dynamic_reference&> arg_iterator) const noexcept override final
		{
			return this->invoke_helper(f, arg_iterator, this->parameter_types);
		}
	};
}
