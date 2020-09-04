#pragma once
#include "type.h"

namespace detail
{
	template <typename T>
	class basic_type : public type
	{
	protected:
		constexpr void print_name_prefix(simple_ostream& out) const noexcept override final;
		constexpr void print_name_suffix(simple_ostream& out) const noexcept override final;
	public:
		constexpr bool has_name(std::string_view name) const noexcept override final;

		constexpr bool is_const() const noexcept override final;
		constexpr bool is_volatile() const noexcept override final;
		constexpr ref_qualifier get_ref_qualifier() const noexcept override final;

		constexpr std::size_t size() const noexcept override final;

		void destroy(void* ptr) const noexcept override final;

		constexpr pointer_view<const cref_t<type>> get_direct_bases() const noexcept override;

		constexpr const type& remove_cv() const noexcept override final;
		constexpr const type& remove_const() const noexcept override final;
		constexpr const type& remove_reference() const noexcept override final;
		constexpr const type& remove_pointer() const noexcept override final;

		constexpr const type& member_pointer_type() const noexcept override final;
		constexpr const type& member_pointer_class() const noexcept override final;

		constexpr const type& add_const() const noexcept override final;
		constexpr const type& add_volatile() const noexcept override final;
		constexpr const type& add_lreference() const noexcept override final;
		constexpr const type& add_rreference() const noexcept override final;

		constexpr std::size_t get_extent() const noexcept override final;
		constexpr const type& remove_extent() const noexcept override final;

		constexpr cv_qualifier get_function_cv_qualifier() const noexcept override final;
		constexpr ref_qualifier get_function_ref_qualifier() const noexcept override final;

		constexpr bool is_void() const noexcept override final;

		constexpr compound_category get_category() const noexcept override final;

		constexpr pointer_view<const cref_t<type>> parameter_types() const noexcept override final;
		constexpr const type& return_type() const noexcept override final;
		constexpr std::size_t get_id() const noexcept override final;
		constexpr virtual const namespace_t* get_namespace() const noexcept override;

		constexpr pointer_view<const cref_t<overloaded_member_function>> get_member_functions() const noexcept override;
		constexpr const overloaded_constructor* get_constructors() const noexcept override;
	};
}
