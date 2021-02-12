#pragma once
#include "type_disjunction_reference.hpp"
#include "types/class_type.h"
#include "Namespace.h"
#include "functional/id.hpp"
#include "overloaded.hpp"

namespace PPreflection
{
	namespace detail
	{
		using parent_descriptor_reference_base = type_disjunction_reference<class_type, Namespace>;
	}

	class parent_descriptor_reference : public detail::parent_descriptor_reference_base
	{
	public:
		using detail::parent_descriptor_reference_base::parent_descriptor_reference_base;

		constexpr operator const descriptor&() const noexcept
		{
			return visit(PP::id_typed * PP::type<const descriptor&>);
		}
		constexpr const Namespace* as_namespace() const noexcept
		{
			return visit(PP::overloaded{
				[](const Namespace& n) { return &n;	},
				[](const class_type&) { return (const Namespace*)(nullptr); } });
		}
		constexpr const class_type* as_class() const noexcept
		{
			return visit(PP::overloaded{
				[](const Namespace&) { return (const class_type*)(nullptr);	},
				[](const class_type& c) { return &c; } });
		}
	};
}
