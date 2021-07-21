#pragma once
#include "PP/view.hpp"

#include "maybe_static_member_function.h"
#include "named_function.h"

namespace PPreflection
{
///
/// @brief Represents a constructor.
///
///
class constructor : public detail::named_function<maybe_static_member_function>
{
public:
	///
	/// @brief Invokes the constructor.
	///
	/// @param arg_iterator Iterator pointing to the dynamic reference to the
	/// first argument.
	///
	virtual dynamic_object invoke_unsafe(
		PP::any_iterator<PP::iterator_category::ra, dynamic_reference>
			arg_iterator) const = 0;

	///
	/// @brief Returns whether this constructor is declared as @p explicit.
	///
	constexpr virtual bool is_explicit() const noexcept = 0;

	///
	/// @brief Returns whether this constructor is a converting constructor.
	///
	constexpr bool is_converting() const noexcept
	{
		return !is_explicit() && PP::view_count(parameter_types()) == 1;
	}

	constexpr PP::string_view get_name() const noexcept override final
	{
		return get_parent().get_name();
	}

private:
	inline dynamic_variable invoke_unsafe(
		PP::any_iterator<PP::iterator_category::ra, dynamic_reference>
			arg_iterator,
		void*) const override final;
};
}
