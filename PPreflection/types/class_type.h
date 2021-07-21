#pragma once
#include "PP/any_view.hpp"

#include "../dynamic_reference.h"
#include "user_defined_type.h"

namespace PPreflection::detail
{
class initialization;
}

namespace PPreflection
{
class constructor;
class conversion_function;
class dynamic_object;
class member_function;
class non_union_class_type;
class static_member_function;

///
/// @brief Represents a class type.
///
class class_type : public user_defined_type
{
	friend detail::initialization;

public:
	///
	/// @brief Gets a view of constructors.
	///
	constexpr virtual PP::any_view<PP::iterator_category::ra,
	                               const constructor&>
	get_constructors() const noexcept = 0;

	///
	/// @brief Gets a view of member functions.
	///
	constexpr virtual PP::any_view<PP::iterator_category::ra,
	                               const member_function&>
	get_member_functions() const noexcept = 0;

	///
	/// @brief Gets a view of conversion functions.
	///
	constexpr virtual PP::any_view<PP::iterator_category::ra,
	                               const conversion_function&>
	get_conversion_functions() const noexcept = 0;

	///
	/// @brief Gets a view of static member functions.
	///
	constexpr virtual PP::any_view<PP::iterator_category::ra,
	                               const static_member_function&>
	get_static_member_functions() const noexcept = 0;

	///
	/// @brief Gets a view of nested user defined types.
	///
	constexpr virtual PP::any_view<PP::iterator_category::ra,
	                               const user_defined_type&>
	get_nested_types() const noexcept = 0;

	///
	/// @brief Upcasts to a non-union class descriptor.
	///
	/// @retval nullptr This is a union type.
	///
	constexpr virtual const non_union_class_type* as_non_union_class()
		const noexcept = 0;

	///
	/// @brief Pushes member functions into @p i_out.
	///
	constexpr void get_member_functions(
		PP::string_view name,
		PP::concepts::iterator auto i_out) const noexcept;

	///
	/// @brief Pushes static member functions into @p i_out.
	///
	constexpr void get_static_member_functions(
		PP::string_view name,
		PP::concepts::iterator auto i_out) const noexcept;

	///
	/// @brief Pushes nested user defined types into @p i_out.
	///
	constexpr const user_defined_type* get_nested_type(
		PP::string_view name) const noexcept;

private:
	inline dynamic_object copy_initialize_same_or_derived(
		dynamic_reference arg) const noexcept;

	constexpr void get_conversion_functions_inherited(
		PP::concepts::iterator auto i_out) const noexcept;

	constexpr detail::standard_conversion_sequence
	make_standard_conversion_sequence_impl(
		const non_array_object_type& target) const noexcept override final;
};
}
