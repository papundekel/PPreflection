#pragma once
#include "PP/apply_transform.hpp"
#include "PP/concepts/non_void_fundamental.hpp"
#include "PP/concepts/same.hpp"
#include "PP/conditional.hpp"
#include "PP/fundamental_types.hpp"
#include "PP/promotion_type.hpp"
#include "PP/tuple_find_dynamic.hpp"
#include "PP/tuple_map_to_array.hpp"
#include "PP/tuple_split.hpp"

#include "../basic_named_descriptor.h"
#include "arithmetic_type.h"
#include "implementations/basic_non_array_object_type.hpp"
#include "integral_type.h"

namespace PPreflection
{
	namespace detail
	{
		template <typename T>
		using arithmetic_type_strong_base =
			PP_GT(PP::conditional(PP::value<PP::concepts::integral<T>>,
		                          PP::type<integral_type>,
		                          PP::type<arithmetic_type>));
	}

	template <typename T>
	class arithmetic_type_strong
		: public detail::basic_non_array_object_type<
			  T,
			  detail::basic_named_descriptor<
				  T,
				  detail::arithmetic_type_strong_base<T>>>
	{
		static_assert(PP::concepts::non_void_fundamental<T> &&
		              PP::concepts::different<T, decltype(nullptr)>);

	public:
		constexpr const arithmetic_type& promoted_type()
			const noexcept override final
		{
			return type::reflect <<= PP::promotion_type <<= PP::type<T>;
		}

		constexpr convertor_object conversion(
			const arithmetic_type& target) const noexcept override final;

		constexpr bool operator==(const arithmetic_type_strong&) const noexcept
		{
			return true;
		}
		constexpr bool operator==(
			const type& other) const noexcept override final
		{
			return type::compare(*this, other);
		}

		inline dynamic_object create_instance() const noexcept override final;
	};
}
