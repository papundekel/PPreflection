#pragma once
#include <vector>
#include "function_type.h"
#include "view.hpp"

class dynamic_function_type final : public function_type
{
	return_type_reference return_type_;
	std::vector<parameter_type_reference> parameter_types_;
	PP::cv_qualifier cv;
	PP::ref_qualifier ref;
	bool Noexcept;

public:
	constexpr dynamic_function_type(
			return_type_reference return_type,
			PP::concepts::view auto&& parameter_types,
			bool Noexcept = false,
			PP::cv_qualifier cv = PP::cv_qualifier::none,
			PP::ref_qualifier ref = PP::ref_qualifier::none) noexcept
		: return_type_(return_type)
		, parameter_types_(
			PP::begin(PP_FORWARD(parameter_types)),
			PP::end  (PP_FORWARD(parameter_types)))
		, cv(cv)
		, ref(ref)
		, Noexcept(Noexcept)
	{}

	constexpr return_type_reference return_type() const noexcept override final
	{
		return return_type_;
	}
	constexpr PP::any_view<parameter_type_reference> parameter_types() const noexcept override final
	{
		return parameter_types_;
	}
	constexpr bool is_noexcept() const noexcept override final
	{
		return Noexcept;
	}
	constexpr PP::cv_qualifier get_cv_qualifier() const noexcept override final
	{
		return cv;
	}
	constexpr PP::ref_qualifier get_ref_qualifier() const noexcept override final
	{
		return ref;
	}
};
