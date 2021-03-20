#pragma once
#include "PP/concepts/derived_from.hpp"
#include "PP/cv_qualifier.hpp"

#include "../convertor.h"
#include "../descriptor.h"
#include "cv_type.h"
#include "non_user_defined_type.h"
#include "object_type.h"

namespace PPreflection
{
	class complete_object_type;

	namespace detail
	{
		template <typename Base>
		class array_type : public non_user_defined_type<Base>
		{
			static_assert(PP::concepts::derived_from<Base, object_type>);

		public:
			constexpr virtual cv_type<complete_object_type> remove_extent() const noexcept = 0;

			constexpr PP::size_t alignment() const noexcept override final
			{
				return remove_extent().type.alignment();
			}

			constexpr virtual convertor_object array_to_pointer_conversion() const noexcept = 0;
		};
	}
}
