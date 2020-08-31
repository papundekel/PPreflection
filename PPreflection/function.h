#pragma once
#include <type_traits>
#include "descriptor.h"
#include "pointer_view.hpp"
#include "cref_t.h"
#include "dynamic_object.h"
#include "../Papo/PP/transform_view.hpp"
#include "../Papo/PP/id.hpp"

class type;
class dynamic_reference;
class member_function;

class function : public descriptor
{
	template <typename T>
	friend class overloaded_function;

protected:
	constexpr virtual void invoke_implementation(void* result, const dynamic_reference* args) const noexcept = 0;
	constexpr virtual bool can_invoke(pointer_view<const dynamic_reference> args) const noexcept;

	constexpr dynamic_object invoke_unsafe(pointer_view<const dynamic_reference> args) const noexcept;

	template <typename... Parameters>
	struct invoke_helper_t
	{
		class x
		{
			template <typename F, std::size_t... I>
			static constexpr decltype(auto) helper(F&& f, const dynamic_reference* args, std::index_sequence<I...>) noexcept;

		public:
			template <typename F>
			constexpr decltype(auto) operator()(F&& f, const dynamic_reference* args) const noexcept;

		};

		static constexpr x value_f() noexcept;
	};

	constexpr virtual pointer_view<const cref_t<type>> parameter_types_implementation() const noexcept = 0;

public:
	constexpr PP::view auto parameter_types() const noexcept
	{
		return parameter_types_implementation() | PP::transform(PP::id<const type&>);
	}
	constexpr virtual const type& return_type() const noexcept = 0;

	constexpr virtual bool is_noexcept() const noexcept = 0;

	constexpr dynamic_object invoke(pointer_view<const dynamic_reference> args = {}) const;
};
