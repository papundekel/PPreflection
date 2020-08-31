#pragma once
#include "dynamic_object.h"
#include "pointer_view.hpp"
#include "descriptor.h"
#include "../Papo/Papo/transform_view.hpp"

template <typename Function>
class overloaded_function : public descriptor
{
public:
	using overload_type = Function;

	constexpr virtual pointer_view<const cref_t<Function>> get_overloads() const noexcept = 0;

	constexpr dynamic_object invoke(pointer_view<const dynamic_reference> args = {}) const;

	/*constexpr const Function* select_overload(pointer_view<const type> arg_types = {}) const noexcept
	{
		for (const function& f : get_overloads())
			if (f.can_invoke(args))
				return f.invoke_unsafe(args);

		throw 0;
	}*/
};
