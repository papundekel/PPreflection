#pragma once
#include "../pointer_base_type.h"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_pointer_base_type : public Base
	{
		constexpr convertor_object bool_conversion() const noexcept override final
		{
			return create_convertor_object(PP::type<T>, PP::value<[]
				(auto p) -> bool
				{
					return p;
				}>);
		}

		constexpr convertor_object null_pointer_conversion() const noexcept override final
		{
			return [](dynamic_reference) { return dynamic_object::create(PP::type<T>, nullptr); };
		}
	};
}
