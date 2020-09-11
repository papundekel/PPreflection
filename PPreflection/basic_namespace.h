#pragma once
#include "namespace_t.h"
#include "reflect.h"

namespace detail
{
	template <typename ID, typename ParentNamespace, typename Types, typename Functions>
	class basic_namespace : public namespace_t
	{
	public:
		constexpr const namespace_t* get_parent() const noexcept override final
		{
			if constexpr (!std::is_same_v<ID, ParentNamespace>)
				return &reflect<ParentNamespace, const namespace_t&>();
			else
				return nullptr;
		}
		constexpr PP::any_view<const type&> get_types() const noexcept override final
		{
			return reflect_many<Types, const type&>();
		}
		constexpr PP::any_view<const overloaded_namespace_function&> get_functions() const noexcept override final
		{
			return reflect_many<Functions, const overloaded_namespace_function&>();
		}
		constexpr void print_name_after_parent(PP::simple_ostream& out) const noexcept override final
		{
			out.write(descriptor::reflect_name<ID>());
		}
		constexpr bool has_name(std::string_view name) const noexcept override final
		{
			return descriptor::reflect_name<ID>() == name;
		}
	};
}
