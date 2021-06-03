#pragma once
#include "PP/add_cv.hpp"
#include "PP/add_reference.hpp"
#include "PP/concepts/derived_from.hpp"
#include "PP/cv_qualifier.hpp"
#include "PP/dynamic_cast.hpp"
#include "PP/variant.hpp"

#include "../print_cv.h"
#include "type.h"

namespace PPreflection
{
	template <typename>
	class cv_type;

	template <typename Type>
	struct cv_type_ptr
	{
		const Type* type_ptr;
		PP::cv_qualifier cv;

		template <typename OtherType>
		requires PP::concepts::derived_from<Type, OtherType> constexpr
		operator cv_type_ptr<OtherType>() const noexcept
		{
			return { type_ptr, cv };
		}

		constexpr cv_type<Type> operator*() const noexcept;
	};

	template <typename Type>
	struct cv_type
		: public type
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

		constexpr auto to_type_ptr() const noexcept
		{
			return cv_type_ptr<Type>{ &type, cv };
		}

		operator const Type&() const noexcept
		{
			return type;
		}

		template <typename OtherType>
		requires PP::concepts::derived_from<Type, OtherType> constexpr
		operator cv_type<OtherType>() const noexcept
		{
			return { type, cv };
		}

		constexpr auto operator&() const noexcept
		{
			return cv_type_ptr<Type>{ &type, cv };
		}

		constexpr bool operator==(cv_type other) const noexcept
		{
			return cv == other.cv && type == other.type;
		}

		template <typename OtherType>
		constexpr auto operator<=>(cv_type<OtherType> other) const noexcept
		{
			return cv <=> other.cv;
		}

		constexpr virtual bool has_name(
			PP::string_view name) const noexcept override final
		{
			return type.has_name(name);
		}

		constexpr parent_descriptor_reference get_parent(
			void*) const noexcept override final;

		constexpr PP::variant<const reference_type&, const pointable_type&>
			cast_down(PP::overload_tag<PPreflection::type>)
				const noexcept override final
		{
			if constexpr (PP::type<Type> != PP::type<PPreflection::type>)
				return { PP::placeholder, type };
			else
				return type.cast_down();
		}
		constexpr bool operator==(
			const PPreflection::type& other) const noexcept override final
		{
			return type == other;
		}

		constexpr void print_name_prefix(
			PP::simple_ostream& out) const noexcept override final
		{
			type.print_name_prefix(out);
			print_cv(cv, out);
		}
		constexpr void print_name_suffix(
			PP::simple_ostream& out) const noexcept override final
		{
			type.print_name_suffix(out);
		}

		constexpr cv_type with_added_cv(PP::cv_qualifier cv_to_add) const
		{
			return { type, cv | cv_to_add };
		}

		constexpr auto cast(PP::concepts::type auto t) const
		{
			return PP::Template<cv_type>(t)(
				PP::dynamic__cast(t + PP::add_const_tag + PP::add_lvalue_tag,
								  type),
				cv);
		}
	};
	template <typename Type>
	cv_type(const Type&, PP::cv_qualifier) -> cv_type<Type>;
	template <typename Type>
	cv_type(const Type&) -> cv_type<Type>;
}

template <typename Type>
constexpr PPreflection::cv_type<Type>
PPreflection::cv_type_ptr<Type>::operator*() const noexcept
{
	return { *type_ptr, cv };
}
