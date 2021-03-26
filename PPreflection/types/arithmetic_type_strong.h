#pragma once
#include "PP/apply_transform.hpp"
#include "PP/concepts/non_void_fundamental.hpp"
#include "PP/concepts/same.hpp"
#include "PP/promotion_type.hpp"

#include "../basic_named_descriptor.h"
#include "arithmetic_type.h"
#include "implementations/basic_non_array_object_type.hpp"

namespace PPreflection
{
	template <typename T>
	class arithmetic_type_strong : public detail::basic_non_array_object_type<T, detail::basic_named_descriptor<T, arithmetic_type>>
	{
		static_assert(PP::concepts::non_void_fundamental<T> && !PP::concepts::same<T, decltype(nullptr)>);

	public:
		constexpr convertor_object promotion() const noexcept
		{
			using promoted_type = PP::apply_transform_t<PP::get_promotion_type, T>;

			return create_convertor_object(PP::type<const T>, PP::value<[]
				(const auto& x) -> promoted_type
				{
					return x;
				}>);
		}
		constexpr bool operator==(const arithmetic_type_strong&) const noexcept
		{
			return true;
		}
		constexpr bool operator==(const type& other) const noexcept override final
		{
			return type::compare(*this, other);
		}

		inline dynamic_object create_instance() const noexcept override final;
	};
}
