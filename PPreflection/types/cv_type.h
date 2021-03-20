#pragma once
#include "PP/concepts/derived_from.hpp"
#include "PP/cv_qualifier.hpp"
#include "PP/dynamic_cast.hpp"
#include "PP/add_cv.hpp"
#include "PP/add_reference.hpp"

#include "../print_cv.h"
#include "type.h"

namespace PPreflection
{
	template <typename Type>
	struct cv_type : public type
	{
		const Type& type;
		PP::cv_qualifier cv;

		constexpr cv_type(const Type& type, PP::cv_qualifier cv)
			: type(type)
			, cv(cv)
		{}
		constexpr cv_type(const Type& type)
			: type(type)
			, cv(PP::cv_qualifier::none)
		{}

		operator const Type&() const noexcept
		{
			return type;
		}

		template <typename OtherType>
		requires PP::concepts::derived_from<Type, OtherType>
		constexpr operator cv_type<OtherType>() const noexcept
		{
			return {type, cv};
		}

		constexpr bool operator==(cv_type other) const noexcept
		{
			return
				cv == other.cv &&
				type == other.type;
		}

		constexpr virtual bool has_name(PP::string_view name) const noexcept override final
		{
			return type.has_name(name);
		}

		constexpr parent_descriptor_reference get_parent(void*) const noexcept override final;

		constexpr PP::type_disjunction_reference<reference_type, pointable_type> reference_or_pointable() const noexcept override final
		{
			return type.reference_or_pointable();
		}
		constexpr bool operator==(const PPreflection::type& other) const noexcept override final
		{
			return type == other;
		}

		constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final
		{
			type.print_name_prefix(out);
			print_cv(cv, out);
		}
		constexpr void print_name_suffix(PP::simple_ostream& out) const noexcept override final
		{
			type.print_name_suffix(out);
		}

		constexpr cv_type with_added_cv(PP::cv_qualifier cv_to_add) const
		{
			return {type, cv | cv_to_add};
		}

		constexpr auto cast(PP::concepts::type auto t) const
		{
			return PP::Template<cv_type>(t)(PP::dynamic__cast(t + PP::add_const_tag + PP::add_lvalue_tag, type), cv);
		}
	};
	template <typename Type>
	cv_type(const Type&, PP::cv_qualifier) -> cv_type<Type>;
	template <typename Type>
	cv_type(const Type&) -> cv_type<Type>;
}
