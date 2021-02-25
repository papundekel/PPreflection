#pragma once
#include "Namespace.h"
#include "reflect.h"
#include "tuple_map_to_array.hpp"

namespace PPreflection
{
	namespace detail
	{
		template <typename ID>
		class basic_namespace : public Namespace
		{
			//static constexpr auto types =
			//	reflect_many(PPreflection::reflect(PP::type<tags::types<ID>>), PP::type<const user_defined_type&>);

			//static constexpr auto namespaces =
			//	reflect_many(PPreflection::reflect(PP::type<tags::namespaces<ID>>), PP::type<const Namespace&>);

			static constexpr auto functions = reflect_many(PPreflection::reflect(
				PP::type<tags::functions<ID>>),
				PP::type<const overloaded_namespace_function&>);

		public:
			constexpr const Namespace& get_parent() const noexcept override final
			{
				if constexpr (PP::type<ID> != PP::type<Namespace::global>)
					return PPreflection::reflect(PPreflection::reflect(PP::type<tags::parent<ID>>));
				else
					return *this;
			}
			//constexpr PP::any_view<PP::iterator_category::ra, const Namespace&> get_namespaces() const noexcept override final
			//{
			//	return namespaces;
			//}
			//constexpr PP::any_view<PP::iterator_category::ra, const user_defined_type&> get_types() const noexcept override final
			//{
			//	return types;
			//}
			constexpr PP::any_view<PP::iterator_category::ra, const overloaded_namespace_function&> get_functions() const noexcept override final
			{
				return functions;
			}
			constexpr PP::string_view get_name() const noexcept override final
			{
				return this->reflect_name(PP::type<ID>);
			}
		};
	}
}
