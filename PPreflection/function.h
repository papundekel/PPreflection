#pragma once
#include "descriptor.h"
#include "simple_range.h"
#include "cref_t.h"
#include "dynamic_wrap.h"
#include <type_traits>

class type;
class dynamic_ptr;
class member_function;

class function : public descriptor
{
	template <typename T>
	friend class overloaded_function;

protected:
	constexpr virtual void invoke_implementation(void* result, const dynamic_ptr* args) const noexcept = 0;
	constexpr virtual bool can_invoke(simple_range<const dynamic_ptr> args) const noexcept;

	constexpr dynamic_wrap invoke_unsafe(simple_range<const dynamic_ptr> args) const noexcept;

	template <typename... Parameters>
	struct invoke_helper_t
	{
		class x
		{
			template <typename F, std::size_t... I>
			static constexpr decltype(auto) helper(F&& f, const dynamic_ptr* args, std::index_sequence<I...>) noexcept;

		public:
			template <typename F>
			constexpr decltype(auto) operator()(F&& f, const dynamic_ptr* args) const noexcept;

		};

		static constexpr x value_f() noexcept;
	};

public:
	constexpr virtual const type& return_type() const noexcept = 0;
	constexpr virtual simple_range<const cref_t<type>> parameter_types() const noexcept = 0;

	constexpr virtual bool is_noexcept() const noexcept = 0;

	constexpr dynamic_wrap invoke(simple_range<const dynamic_ptr> args = {}) const;
};
