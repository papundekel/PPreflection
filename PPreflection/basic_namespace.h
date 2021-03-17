#pragma once
#include "PP/template_t.hpp"
#include "PP/tuple_map_to_array.hpp"

#include "basic_named_descriptor.h"
#include "Namespace.h"
#include "reflect.h"

namespace PPreflection
{
	namespace detail
	{
		template <typename ID>
		class basic_namespace : public basic_named_descriptor<ID, Namespace>
		{
			static constexpr auto reflector = reflect_many_helper * PP::type<ID>;

			static constexpr auto namespaces = reflector(PP::Template<PPreflection::tags::namespaces>, PP::type<const Namespace&>);
			static constexpr auto types = reflector(PP::Template<PPreflection::tags::types>, PP::type<const user_defined_type&>);
			static constexpr auto functions = reflector(PP::Template<PPreflection::tags::functions>, PP::type<const namespace_function&>);

			constexpr const Namespace& get_parent() const noexcept override final
			{
				if constexpr (PP::type<ID> != PP::type<tags::global>)
					return PPreflection::reflect(PPreflection::reflect(PP::type<tags::parent<ID>>));
				else
					return *this;
			}
			constexpr PP::any_view<PP::iterator_category::ra, const Namespace&> get_namespaces() const noexcept override final
			{
				return namespaces;
			}
			constexpr PP::any_view<PP::iterator_category::ra, const user_defined_type&> get_types() const noexcept override final
			{
				return types;
			}
			constexpr PP::any_view<PP::iterator_category::ra, const namespace_function&> get_functions() const noexcept override final
			{
				return functions;
			}
		};
	}
}
