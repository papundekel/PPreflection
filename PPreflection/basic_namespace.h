#pragma once
#include "Namespace.h"
#include "reflect.h"
#include "tuple_map.hpp"

namespace detail
{
	template <typename ID>
	class basic_namespace : public Namespace
	{
		static constexpr auto types =
			PP::tuple_map_to_array(::reflect, ::reflect(PP::type_v<reflection::types<ID>>), PP::type_v<const user_defined_type&>);

		static constexpr auto namespaces =
			PP::tuple_map_to_array(::reflect, ::reflect(PP::type_v<reflection::namespaces<ID>>), PP::type_v<const Namespace&>);

		static constexpr auto functions =
			PP::tuple_map_to_array(::reflect, ::reflect(PP::type_v<reflection::functions<ID>>), PP::type_v<const overloaded_namespace_function&>);

	public:
		constexpr const Namespace* get_parent() const noexcept override final
		{
			if constexpr (!std::is_same_v<ID, Namespace::global>)
				return &::reflect(::reflect(PP::type_v<reflection::parent<ID>>));
			else
				return nullptr;
		}
		constexpr PP::any_view<const Namespace&> get_namespaces() const noexcept override final
		{
			return namespaces;
		}
		constexpr PP::any_view<const user_defined_type&> get_types() const noexcept override final
		{
			return types;
		}
		constexpr PP::any_view<const overloaded_namespace_function&> get_functions() const noexcept override final
		{
			return functions;
		}
		constexpr std::string_view get_name() const noexcept override final
		{
			return descriptor::reflect_name(PP::type_v<ID>);
		}
	};
}
