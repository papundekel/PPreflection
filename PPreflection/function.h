#pragma once
#include <type_traits>
#include "descriptor.h"
#include "pointer_view.h"
#include "dynamic_object.h"
#include "../PP/PP/transform_view.hpp"
#include "../PP/PP/id.hpp"
#include "../PP/PP/any_iterator.hpp"
#include "invoke.h"

class type;
class dynamic_reference;
class member_function;
class overloaded_function;

class function : public descriptor
{
	friend class overloaded_function;

protected:
	constexpr virtual dynamic_object invoke_unsafe(PP::any_iterator<const dynamic_reference&> arg_iterator) const noexcept = 0;

	constexpr virtual bool can_invoke(PP::any_view<const type&> argument_types) const noexcept;

	template <typename... Parameters>
	struct invoke_helper_t
	{
		class x
		{
			template <typename F, std::size_t... I>
			static constexpr decltype(auto) helper(F&& f, any_iterator<const dynamic_reference&> arg_iterator, std::index_sequence<I...>) noexcept;

		public:
			template <typename F>
			static constexpr decltype(auto) value_f(F&& f, any_iterator<const dynamic_reference&> arg_iterator) noexcept;
		};

		using type = x;
	};

	template <typename ParameterTypes, typename F>
	static constexpr decltype(auto) invoke_helper_helper(F&& f, PP::any_iterator<const dynamic_reference&> arg_iterator) noexcept
	{
		return ::invoke<get_type<apply_pack_types<function::invoke_helper_t, ParameterTypes>>>(std::forward<F>(f), arg_iterator);
	}

	template <typename ReturnType, typename F>
	static constexpr dynamic_object invoke_helper_helper_helper(F&& f) noexcept
	{
		if constexpr (std::is_void_v<ReturnType>)
		{
			std::forward<F>(f)();
			return dynamic_object::create_void();
		}
		else
			return dynamic_object(reflect<ReturnType, type>(),
				[&f](void* ptr)
				{
					if constexpr (std::is_reference_v<ReturnType>)
					{
						auto&& x = std::forward<F>(f)();
						new (ptr) std::remove_reference_t<ReturnType>*(&x);
					}
					else
						new (ptr) ReturnType(std::forward<F>(f)());
				});
	}

	template <typename ReturnType, typename ParameterTypes, typename F>
	static constexpr dynamic_object invoke_helper(F&& f, any_iterator<const dynamic_reference&> arg_iterator) noexcept
	{
		return invoke_helper_helper_helper<ReturnType>(
			[&f, arg_iterator]() -> decltype(auto)
			{
				return invoke_helper_helper<ParameterTypes>(std::forward<F>(f), arg_iterator);
			});
	}
	template <typename ReturnType, typename F>
	static constexpr dynamic_object invoke_helper(F&& f) noexcept
	{
		return invoke_helper_helper_helper<ReturnType>(std::forward<F>(f));
	}

	constexpr void print_name_basic(PP::simple_ostream& out) const noexcept;
	constexpr void print_noexcept(PP::simple_ostream& out) const noexcept;

public:
	constexpr virtual const descriptor& get_parent() const noexcept = 0;

private:
	constexpr const descriptor* get_parent_implementation() const noexcept override final
	{
		return &get_parent();
	}

	constexpr void print_name_before_parent(simple_ostream& out) const noexcept override;
	constexpr void print_name_after_parent(simple_ostream& out) const noexcept override;

public:
	constexpr bool has_name(std::string_view name) const noexcept override;

	constexpr virtual const overloaded_function& get_overloaded_function() const noexcept = 0;

	constexpr virtual const type& return_type() const noexcept = 0;

	constexpr virtual bool is_noexcept() const noexcept = 0;

	constexpr dynamic_object invoke(pointer_view<const dynamic_reference> args = {}) const;

	constexpr virtual any_view<const type&> parameter_types() const noexcept = 0;
};
