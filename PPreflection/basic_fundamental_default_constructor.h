#pragma once
#include "basic_class_constructor.h"
#include "type_pack.h"
#include "constructor.h"

namespace detail
{
	template <typename T>
	class basic_fundamental_default_constructor final : public basic_constructor_base<T, type_pack<>, constructor>
	{
	protected:
		constexpr void invoke_implementation(void* result, const dynamic_reference*) const noexcept override final
		{
			new (result) T();
		}

	public:
		constexpr bool is_explicit() const noexcept override final
		{
			return false;
		}
	};
}
