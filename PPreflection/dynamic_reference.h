#pragma once
#include "PP/concepts/same_except_cvref.hpp"
#include "PP/get_type.hpp"
#include "PP/reinterpret_cast.hpp"

#include "types/dynamic_reference_type.h"

namespace PPreflection
{
class dynamic_variable;
class dynamic_object;

///
/// @brief A weakly typed reference to an object or function.
///
class dynamic_reference
{
	friend class dynamic_object;

	union
	{
		void* ptr_object;
		void (*ptr_function)();
	};

	cv_type_ptr<referencable_type> referenced_type_cv;
	int is_lvalue : 1, is_function : 1;

public:
	///
	/// @brief Copy constructor. Creates a dynamic reference refercing the
	/// same object/function as @p other.
	///
	dynamic_reference(const dynamic_reference& other) = default;

	///
	/// @brief Constructs the dynamic reference. References the
	/// object/function referenced by @p r.
	///
	constexpr dynamic_reference(auto&& r) noexcept requires
		PP::concepts::different_except_cvref<decltype(r), dynamic_reference> &&
		PP::concepts::different_except_cvref<decltype(r), dynamic_object> &&
		PP::concepts::different_except_cvref<decltype(r), dynamic_variable>;

	// clang-format off
	private:
		constexpr dynamic_reference(const volatile void* ptr,
		                            const reference_type& t) noexcept
			: dynamic_reference(PP::placeholder, const_cast<void*>(ptr), t)
		{}
	// clang-format on

	template <typename Return, typename... Parameters>
	constexpr dynamic_reference(Return (*ptr)(Parameters...),
	                            const reference_type& t) noexcept
		: dynamic_reference(PP::placeholder, (void (*)())ptr, t)
	{}

	template <typename T>
	constexpr dynamic_reference(PP::placeholder_t,
	                            T* ptr,
	                            const reference_type& t) noexcept
		: ptr_object(nullptr)
		, referenced_type_cv(&t.remove_reference())
		, is_lvalue(t.is_lvalue())
		, is_function(PP::concepts::function<T>)
	{
		if constexpr (PP::concepts::function<T>)
			ptr_function = ptr;
		else
			ptr_object = ptr;
	}

public:
	///
	/// @brief Copy assignment. Changes the referenced
	/// object/function.
	///
	dynamic_reference& operator=(const dynamic_reference&) = default;

	///
	/// @brief Gets the @ref reference_type of this dynamic reference.
	///
	/// @return The type descriptor.
	///
	constexpr auto get_type() const noexcept
	{
		return detail::dynamic_reference_type(*referenced_type_cv, is_lvalue);
	}

	///
	/// @brief Casts the referenced object/pointer to a strong type.
	///
	/// @return If @p t references type @p T, returns by @p T&&.
	///
	inline auto cast_unsafe(PP::concepts::type auto t) const noexcept
		-> PP_GT(t) &&;

	///
	/// @brief Visits the dynamic reference with a unary functor. The
	/// dispatch is based on cv a ref qualifiers of this reference.
	///
	/// @return The result of the call to @p f.
	///
	inline decltype(auto) visit(PP::concepts::type auto t, auto&& f) const;

	///
	/// @brief Visits the dynamic reference with a unary functor. Assumes
	/// that the reference references a pointer. The dispatch is based on
	/// the cv qualifiers of the pointer.
	///
	/// @return The result of the call to @p f.
	///
	inline decltype(auto) visit_ptr(PP::concepts::type auto t, auto&& f) const;

	///
	/// @brief Get a pointer to the referenced object.
	///
	/// @return A pointer to the referenced object.
	/// @retval nullptr The dynamic reference references a function.
	///
	constexpr void* get_void_ptr() const;

	///
	/// @brief Creates a new dynamic reference with different cv and ref
	/// qualifiers.
	///
	/// @return A new dynamic reference.
	///
	constexpr dynamic_reference with_cv_ref(PP::cv_qualifier cv,
	                                        bool is_lvalue) const noexcept
	{
		auto copy = *this;
		copy.referenced_type_cv.cv = cv;
		copy.is_lvalue = is_lvalue;
		return copy;
	}

private:
	constexpr auto* reinterpret(PP::concepts::type auto t) const
	{
		if (is_function)
			return PP::reinterpret__cast(t, ptr_function);
		else
			return PP::reinterpret__cast(t, ptr_object);
	}
};
}
