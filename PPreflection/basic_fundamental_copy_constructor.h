#pragma once
#include "one_parameter_converting_constructor.h"
#include "basic_class_constructor.h"
#include "type_pack.h"

namespace detail
{
	template <typename T>
	class basic_fundamental_copy_constructor final : public basic_constructor_base<T, type_pack<const T&>, one_parameter_converting_constructor>
	{
	protected:
		constexpr void invoke_implementation_one_parameter(void* result, dynamic_reference arg) const noexcept override final
		{
			new (result) T(arg.cast_unsafe<const T&>());
		}

	public:
		constexpr const type& get_parameter_type() const noexcept override final
		{
			return reflect<const T&, type>();
		}
	};
}
