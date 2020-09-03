#pragma once
#include "dynamic_object.h"
#include "pointer_view.h"
#include "descriptor.h"
#include "../PP/PP/transform_view.hpp"
#include "../PP/PP/id.hpp"

class overloaded_function : public descriptor
{
	constexpr virtual pointer_view<const cref_t<function>> get_function_overloads() const noexcept = 0;

public:
	constexpr dynamic_object invoke(pointer_view<const dynamic_reference> args = {}) const;

	/*constexpr const Function* select_overload(pointer_view<const type> arg_types = {}) const noexcept
	{
		for (const function& f : get_overloads())
			if (f.can_invoke(args))
				return f.invoke_unsafe(args);

		throw 0;
	}*/
protected:
	template <typename Function, PP::view View>
	static constexpr PP::view auto get_overloads_helper(View&& v) noexcept
	{
		return std::forward<View>(v) | PP::transform(PP::id<const Function&>);
	}
public:
	constexpr PP::view auto get_overloads() const noexcept
	{
		return get_overloads_helper<function>(get_function_overloads());
	}
};
