#pragma once
#include "PP/concepts/reference.hpp"
#include "PP/get_cv.hpp"

#include "../reference_type.hpp"
#include "basic_type.hpp"

namespace PPreflection::detail
{
	template <typename T>
	class basic_reference_type final : public basic_type<T, reference_type>
	{
		static_assert(PP::concepts::reference<T>);

		constexpr cv_type<referencable_type> remove_reference()
			const noexcept override final
		{
			return type::reflect_cv(!PP::type<T>);
		}

		constexpr bool is_lvalue() const noexcept override final
		{
			return PP::concepts::lvalue_reference<T>;
		}
	};
}
