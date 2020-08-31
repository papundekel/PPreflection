#pragma once
#include <typeindex>
#include <array>
#include "descriptor.h"
#include "cref_t.h"
#include "pointer_view.hpp"
#include "type_pack.h"
#include "sizeof_many.h"
#include "cv_qualifier.h"
#include "ref_qualifier.h"
#include "apply_pack.h"

class namespace_t;
class overloaded_member_function;
class member_like_function;
template <typename Function>
class overloaded_member_like_function;
class function;
class conversion_function;
class dynamic_object;

namespace detail
{
	template <typename T>
	class basic_type;
}

class type : public descriptor
{
	template <typename T>
	friend class detail::basic_type;

	friend class dynamic_reference;
	friend class dynamic_object;

public:
	enum compound_category
	{
		basic, //fundamental, class, enum
		reference,
		pointer,
		pointer_to_member,
		function,
		array,
	};

	constexpr bool can_pointer_like_initialize_inner(const type& ref_type) const noexcept;

protected:
	constexpr virtual void print_name_first(simple_ostream& out) const noexcept = 0;
	constexpr virtual void print_name_second(simple_ostream& out) const noexcept = 0;

public:
	constexpr void print_name(simple_ostream& out) const noexcept override final;

	constexpr virtual ref_qualifier get_ref_qualifier() const noexcept = 0;
	constexpr virtual bool is_const() const noexcept = 0;
	constexpr virtual bool is_volatile() const noexcept = 0;
	constexpr virtual std::size_t size() const noexcept = 0;
	virtual void destroy(void* ptr) const noexcept = 0;
	constexpr virtual pointer_view<const cref_t<type>> get_direct_bases() const noexcept = 0;

	constexpr virtual const namespace_t* get_namespace() const noexcept = 0;

	constexpr virtual const type& add_lreference() const noexcept = 0;
	constexpr virtual const type& add_rreference() const noexcept = 0;
	constexpr virtual const type& add_const() const noexcept = 0;
	constexpr virtual const type& add_volatile() const noexcept = 0;
	constexpr virtual const type& remove_const() const noexcept = 0;

	constexpr virtual const type& remove_cv() const noexcept = 0;

	constexpr virtual const type& remove_reference() const noexcept = 0;

	constexpr virtual const type& remove_pointer() const noexcept = 0;

	constexpr virtual const type& member_pointer_type() const noexcept = 0;
	constexpr virtual const type& member_pointer_class() const noexcept = 0;

	constexpr virtual std::size_t get_extent() const noexcept = 0;
	constexpr virtual const type& remove_extent() const noexcept = 0;

	constexpr virtual pointer_view<const cref_t<type>> parameter_types() const noexcept = 0;
	constexpr virtual const type& return_type() const noexcept = 0;
	constexpr virtual cv_qualifier get_function_cv_qualifier() const noexcept = 0;
	constexpr virtual ref_qualifier get_function_ref_qualifier() const noexcept = 0;

	constexpr virtual bool is_void() const noexcept = 0;

	constexpr virtual compound_category get_category() const noexcept = 0;



	virtual std::size_t get_id() const noexcept = 0;

	constexpr cv_qualifier get_cv_qualifier() const noexcept;
	constexpr bool is_pointer_like() const noexcept;
	constexpr bool is_derived_from(const type& base) const noexcept;
	constexpr bool can_initialize(const type& to) const noexcept;
	constexpr bool is_reference() const noexcept;

	template <bool rvalue = false>
	constexpr const type& add_reference() const noexcept;

	template <bool rvalue>
	constexpr const type& make_reference() const noexcept;

	constexpr bool cv_at_most(const type& other) const noexcept;

	constexpr bool L1(const type&) const noexcept;
	constexpr const conversion_function* L2(const type&) const noexcept;

	constexpr bool can_reference_initialize_no_user_conversion(const type& ref_type) const noexcept;
	constexpr bool can_reference_initialize(const type& ref_type) const noexcept;

	constexpr virtual pointer_view<const cref_t<overloaded_member_function>> get_member_functions() const noexcept = 0;
	constexpr const overloaded_member_function* get_member_function(std::string_view name) const noexcept;

	constexpr virtual const overloaded_member_like_function<member_like_function>* get_constructors() const noexcept = 0;

	friend constexpr bool operator==(const type& a, const type& b) noexcept;

	constexpr dynamic_object create_instance(pointer_view<const dynamic_reference> args = {}) const;
};
