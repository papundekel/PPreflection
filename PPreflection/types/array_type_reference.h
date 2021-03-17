#pragma once
#include "PP/type_disjunction_reference.hpp"

#include "known_bound_array_type.h"
#include "unknown_bound_array_type.h"

namespace PPreflection
{
	namespace detail
	{
		using array_type_reference_helper = PP::type_disjunction_reference<known_bound_array_type, unknown_bound_array_type>;
	}

	class array_type_reference
		: public detail::array_type_reference_helper
		, public detail::array_type<object_type>
	{
	public:
		using detail::array_type_reference_helper::array_type_reference_helper;

	private:
		static constexpr array_type_reference create(const object_type& t)
		{
			if (auto known_bound = dynamic_cast<const known_bound_array_type*>(&t); known_bound)
				return array_type_reference(*known_bound);
			else
				return array_type_reference(dynamic_cast<const unknown_bound_array_type&>(t));
		}

	public:
	 	constexpr array_type_reference(const object_type& t) noexcept
			: array_type_reference(create(t))
		{}

		constexpr bool has_name(PP::string_view name) const noexcept override final
		{
			return visit([name](const auto& array_type) { return array_type.has_name(name);	});
		}

		constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final
		{
			visit([&out](const auto& array_type) { array_type.print_name_prefix(out); });
		}

		constexpr void print_name_suffix(PP::simple_ostream& out) const noexcept override final
		{
			visit([&out](const auto& array_type) { array_type.print_name_suffix(out); });
		}

		constexpr cv_type<complete_object_type> remove_extent() const noexcept override final
		{
			return visit([](const auto& array_type)	{ return array_type.remove_extent(); });
		}

		constexpr convertor array_to_pointer_conversion() const noexcept override final
		{
			return visit([](const auto& array_type) { return array_type.array_to_pointer_conversion(); });
		}

		constexpr bool operator==(const type& other) const noexcept override final
		{
			return visit([&other](const auto& array_type) { return array_type == other; });
		}
	};
}
