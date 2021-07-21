#pragma once
#include "PP/any_iterator.hpp"
#include "PP/any_view.hpp"
#include "PP/view_equal.hpp"

#include "descriptor.h"
#include "dynamic_reference.h"
#include "named_descriptor.h"

namespace PPreflection
{
class dynamic_variable;
class user_defined_type;
class namespace_function;

///
/// @brief Represents a namespace.
///
class Namespace : public named_descriptor<descriptor>
{
	constexpr parent_descriptor get_parent(void*) const noexcept override final;

public:
	///
	/// @brief Gets the parent namespace.
	///
	constexpr virtual const Namespace& get_parent() const noexcept = 0;

	///
	/// @brief Gets a view of nested namespaces.
	///
	constexpr virtual PP::any_view<PP::iterator_category::ra, const Namespace&>
	get_namespaces() const noexcept = 0;

	///
	/// @brief Gets a view of nested user defined types.
	///
	constexpr virtual PP::any_view<PP::iterator_category::ra,
	                               const user_defined_type&>
	get_types() const noexcept = 0;

	///
	/// @brief Gets a view of namespace functions.
	///
	constexpr virtual PP::any_view<PP::iterator_category::ra,
	                               const namespace_function&>
	get_functions() const noexcept = 0;

private:
	constexpr void print_name_before_parent(
		PP::ostream&) const noexcept override final
	{}
	constexpr void print_name_after_parent(
		PP::ostream& out) const noexcept override final
	{
		out.write(get_name());
	}

public:
	///
	/// @brief Gets a nested namespace descriptor with name @p name.
	///
	constexpr const Namespace* get_namespace(
		PP::string_view name) const noexcept;

	///
	/// @brief Gets a nested user defined type descriptor with name @p name.
	///
	constexpr const user_defined_type* get_type(
		PP::string_view name) const noexcept;

	///
	/// @brief Invokes a namespace function from this namespace with name @p
	/// function_name.
	///
	inline dynamic_variable invoke_qualified(
		PP::string_view function_name,
		PP::concepts::view auto&& arguments) const;

	///
	/// @see invoke_qualified().
	///
	inline dynamic_variable invoke_qualified(
		PP::string_view function_name,
		const std::initializer_list<dynamic_reference>& arguments) const;

private:
	inline dynamic_variable invoke_qualified_impl(
		PP::string_view function_name,
		PP::concepts::view auto&& arguments) const;
};
}
