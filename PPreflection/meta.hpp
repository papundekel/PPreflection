#ifndef PPREFLECTOR_GUARD

#include "PP/value_tuple.hpp"

#include "PPreflection.hpp"
#include "basic_namespace.h"
#include "functions/implementations/implementations.hpp"
#include "overload_cast.h"
#include "type_info_map.hpp"
#include "types/implementations/implementations.hpp"

namespace PPreflection::detail
{
	using CV = PP::cv_qualifier;
	using REF = PP::ref_qualifier;
}

#endif
