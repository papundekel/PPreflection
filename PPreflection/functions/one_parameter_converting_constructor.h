#pragma once
#include "../types/parameter_type_reference.h"
#include "constructor.h"

namespace PPreflection
{
///
/// @brief Represents a converting constructor with one parameter.
///
///
class one_parameter_converting_constructor : public constructor
{
public:
	///
	/// @brief Invokes the constructor.
	///
	/// @param arg A dynamic reference to the argument.
	///
	virtual dynamic_object invoke_unsafe(dynamic_reference arg) const = 0;

	///
	/// @brief Gets the type of the parameter.
	///
	constexpr virtual parameter_type_reference get_parameter_type()
		const noexcept = 0;

	constexpr bool is_explicit() const noexcept override final
	{
		return false;
	}

private:
	dynamic_object invoke_unsafe(
		PP::any_iterator<PP::iterator_category::ra, dynamic_reference>
			arg_iterator) const override final
	{
		return invoke_unsafe(*arg_iterator);
	}
};
}
