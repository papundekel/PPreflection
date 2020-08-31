#pragma once
#include "ref_qualifier.h"
#include "cv_qualifier.h"
#include "conversion_function.h"
#include "basic_typed_function.h"
#include <type_traits>

template <typename C, typename R, cv_qualifier c, ref_qualifier r>
struct conversion_function_tag
{
	using Class = C;
	using Result = R;
	static constexpr auto cv = c;
	static constexpr auto ref = r;

	static constexpr bool Noexcept = std::is_nothrow_invocable<
};

template <typename Overload, typename ID>
class basic_conversion_function : public basic_typed_function<Overload, typename ID::Result(), conversion_function>
{
protected:
	constexpr void invoke_implementation_conversion(void* result, const dynamic_reference& caller) const noexcept override final;
};
