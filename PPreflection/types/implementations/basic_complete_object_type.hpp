#pragma once
#include "../complete_object_type.h"
#include "basic_object_type.hpp"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_complete_object_type : public basic_object_type<T, Base>
	{
		constexpr const reference_type& get_reference_type(bool lvalue, PP::cv_qualifier cv) const noexcept override final
		{
			if (lvalue)
			{
				switch (cv)
				{
				default:
					[[fallthrough]];
				case PP::cv_qualifier::none:
					return type::reflect(PP::type<T&>);
				case PP::cv_qualifier::Const:
					return type::reflect(PP::type<const T&>);
				case PP::cv_qualifier::Volatile:
					return type::reflect(PP::type<volatile T&>);
				case PP::cv_qualifier::const_volatile:
					return type::reflect(PP::type<const volatile T&>);
				}
			}
			else
			{
				switch (cv)
				{
				default:
					[[fallthrough]];
				case PP::cv_qualifier::none:
					return type::reflect(PP::type<T&&>);
				case PP::cv_qualifier::Const:
					return type::reflect(PP::type<const T&&>);
				case PP::cv_qualifier::Volatile:
					return type::reflect(PP::type<volatile T&&>);
				case PP::cv_qualifier::const_volatile:
					return type::reflect(PP::type<const volatile T&&>);
				}
			}
		}
	};
}
