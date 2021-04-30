#pragma once
#include <algorithm>
#include <typeindex>

#include "PP/reference_wrapper.hpp"
#include "PP/size_t.hpp"
#include "PP/tuple.hpp"
#include "PP/tuple_map_to_array.hpp"
#include "PP/type_id.hpp"
#include "PP/type_tuple.hpp"

#include "reflect.h"

namespace PPreflection
{
	class non_union_class_type;

	template <PP::size_t Count>
	class type_info_map
	{
		using pair =
			PP::tuple<std::type_index,
					  PP::reference_wrapper<const non_union_class_type&>>;

		pair key_values[Count];

	public:
		template <typename... T>
		explicit type_info_map(PP::type_tuple_t<T...>)
			: key_values{
				pair(PP::placeholder, typeid(T), reflect(PP::type<T>))...
			}
		{
			std::sort(key_values,
					  key_values + Count,
					  [](const pair& a, const pair& b)
					  {
						  return a[PP::value_0] < b[PP::value_0];
					  });
		}

		const non_union_class_type& get(std::type_index type) const
		{
			auto i = std::lower_bound(key_values,
									  key_values + Count,
									  type,
									  [](const pair& p, std::type_index type)
									  {
										  return p[PP::value_0] < type;
									  });

			if (i != key_values + Count)
				return (*i)[PP::value_1];
			else
				throw 666;
		}
	};
	template <typename... T>
	type_info_map(PP::type_tuple_t<T...>) -> type_info_map<sizeof...(T)>;
}
