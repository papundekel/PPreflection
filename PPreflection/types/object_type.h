#pragma once
#include "PP/size_t.hpp"

#include "referencable_type.h"

namespace PPreflection
{
	class complete_object_type;
	class unknown_bound_array_type;

	///
	/// @brief Represents an object type.
	///
	class object_type : public referencable_type
	{
	public:
		///
		/// @brief Gets the return type of the function type.
		///
		constexpr virtual PP::variant<const unknown_bound_array_type&,
		                              const complete_object_type&>
			cast_down(PP::overload_tag<object_type> = {}) const noexcept = 0;

		///
		/// @brief Gets the alignment of the object type.
		///
		constexpr virtual PP::size_t alignment() const noexcept = 0;

	private:
		constexpr PP::variant<const function_type&, const object_type&>
			cast_down(PP::overload_tag<referencable_type>)
				const noexcept override final
		{
			return {PP::placeholder, *this};
		}
	};
}
