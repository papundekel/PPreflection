#pragma once
#include "dynamic_object.h"
#include "pointer_view.h"
#include "descriptor.h"
#include "../PP/PP/transform_view.hpp"
#include "../PP/PP/id.hpp"

class overloaded_function : public descriptor
{
protected:
	constexpr virtual any_view<const function&> get_function_overloads() const noexcept = 0;

public:
	constexpr dynamic_object invoke(pointer_view<const dynamic_reference> args = {}) const;

	constexpr PP::view auto get_overloads() const noexcept
	{
		return get_function_overloads();
	}

	template <PP::view View>
	constexpr const function* select_overload(View&& argument_types) const noexcept
	{
		for (const function& f : get_overloads())
			if (f.can_invoke(std::forward<View>(argument_types)))
				return &f;

		return nullptr;
	}
};
