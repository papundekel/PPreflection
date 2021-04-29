#pragma once
#include "dynamic_specific_reference_type_base.h"

namespace PPreflection
{
	class dynamic_reference_type : public detail::dynamic_specific_reference_type_base
	{
		bool lvalue_;

	public:
		constexpr dynamic_reference_type(cv_type<referencable_type> referenced_type, bool lvalue) noexcept
			: dynamic_specific_reference_type_base(referenced_type)
			, lvalue_(lvalue)
		{}
		constexpr dynamic_reference_type(const reference_type& type) noexcept
			: dynamic_specific_reference_type_base(type.remove_reference())
			, lvalue_(type.is_lvalue())
		{}
		constexpr dynamic_reference_type(const referencable_type& type) noexcept
			: dynamic_specific_reference_type_base({type, PP::cv_qualifier::none})
			, lvalue_(false)
		{}

		constexpr bool is_lvalue() const noexcept override final
		{
			return lvalue_;
		}
	};
}
