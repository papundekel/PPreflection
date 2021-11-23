#pragma once
#include "class_type.h"

namespace PPreflection
{
	///
	/// @brief Represents a union type.
	///
	class union_type : public class_type
	{
		constexpr const non_union_class_type* as_non_union_class()
			const noexcept override final
		{
			return nullptr;
		}
	};
}
