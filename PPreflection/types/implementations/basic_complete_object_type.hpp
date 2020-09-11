#pragma once
#include <>
#include "basic_object_type.hpp"
#include "../complete_object_type.h"

namespace detail
{
	template <typename T, typename Base>
	class basic_complete_object_type : public basic_object_type<T, Base>
	{
		constexpr std::size_t size() const noexcept override final
		{
			return sizeof(T);
		}
		constexpr void destroy(void* ptr) const noexcept override final
		{
			std::destroy_at(reinterpret_cast<T*>(ptr));
		}
	};
}
