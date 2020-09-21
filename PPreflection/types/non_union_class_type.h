#pragma once
#include "class_type.h"

class non_union_class_type : public class_type
{
public:
	constexpr virtual PP::any_view<const non_union_class_type&> get_base_classes() const noexcept = 0;
};
