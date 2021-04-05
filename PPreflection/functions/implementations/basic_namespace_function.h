#pragma once
#include "../../basic_named_descriptor.h"
#include "../static_function.h"
#include "basic_static_function.h"

namespace PPreflection::detail
{
	template <auto f>
	class basic_namespace_function : public basic_static_function<f, basic_named_descriptor<PP::value_t<f>, namespace_function>>
	{
		constexpr void print_name_implementation(PP::simple_ostream& out) const noexcept override final
		{
			out.write(this->get_name());
		}
		constexpr const Namespace& get_parent() const noexcept override final
		{
			return reflect(reflect(PP::type<tags::parent<PP::value_t<f>>>));
		}
	};
}
