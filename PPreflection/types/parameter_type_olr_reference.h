#pragma once
#include "PP/variant.hpp"

#include "class_type.h"
#include "cv_type.h"
#include "parameter_type.h"

namespace PPreflection
{
class reference_type;
}

namespace PPreflection::detail
{
using parameter_type_olr_reference_base =
	PP::variant<const reference_type&,
                const non_array_object_type&,
                cv_type<class_type>>;

class parameter_type_olr_reference : public parameter_type_olr_reference_base
{
	static constexpr auto unwrap_parameter_type(parameter_type tr)
	{
		return PP::visit(
			[](const auto& t)
			{
				return parameter_type_olr_reference(t);
			},
			tr);
	}

public:
	constexpr parameter_type_olr_reference(const reference_type& t)
		: parameter_type_olr_reference_base(PP::placeholder, t)
	{}
	constexpr parameter_type_olr_reference(const non_array_object_type& t)
		: parameter_type_olr_reference_base(PP::placeholder, t)
	{}
	constexpr parameter_type_olr_reference(cv_type<class_type> t)
		: parameter_type_olr_reference_base(PP::placeholder, t)
	{}
	constexpr parameter_type_olr_reference(parameter_type tr)
		: parameter_type_olr_reference(unwrap_parameter_type(tr))
	{}
};
}
