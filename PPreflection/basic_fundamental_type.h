#pragma once
#include "basic_type.h"

namespace detail
{
	template <typename T>
	class basic_fundamental_type : public basic_type<T>
	{
		class basic_overloaded_fundamental_constructor final : public overloaded_constructor
		{
			class basic_fundamental_default_constructor final : public basic_constructor_base<T, type_pack<>, constructor>
			{
			protected:
				constexpr dynamic_object invoke_unsafe(any_iterator<const dynamic_reference&>) const noexcept override final
				{
					return dynamic_object::create<T>();
				}

			public:
				constexpr bool is_explicit() const noexcept override final
				{
					return false;
				}
			};

			class basic_fundamental_copy_constructor final : public basic_constructor_base<T, type_pack<const T&>, one_parameter_converting_constructor>
			{
			protected:
				constexpr dynamic_object invoke_unsafe_one_parameter(dynamic_reference arg) const noexcept override final
				{
					return dynamic_object::create<T>(arg.cast_unsafe<const T&>());
				}

			public:
				constexpr const type& get_parameter_type() const noexcept override final
				{
					return reflect<const T&, type>();
				}
			};

			static constexpr auto default_constructor = basic_fundamental_default_constructor{};
			static constexpr auto copy_constructor = basic_fundamental_copy_constructor{};

			static constexpr std::array<cref_t<function>, 2> functions_overloads = { default_constructor, copy_constructor };
			static constexpr std::array<cref_t<constructor>, 2> constructor_overloads = { default_constructor, copy_constructor };
			static constexpr std::array<cref_t<one_parameter_converting_constructor>, 1> one_parameter_converting_constructor_overloads = { copy_constructor };

		public:
			constexpr any_view<const function&> get_function_overloads() const noexcept override final
			{
				return functions_overloads;
			}
			constexpr any_view<const constructor&> get_constructor_overloads() const noexcept override final
			{
				return constructor_overloads;
			}
			constexpr any_view<const one_parameter_converting_constructor&> get_one_parameter_converting_constructor_overloads() const noexcept override final
			{
				return one_parameter_converting_constructor_overloads;
			}

			constexpr const type& get_enclosing_class() const noexcept override final
			{
				return reflect<T, type>();
			}
		};

		// didn't think this would work
		template <typename U>
		template <typename V>
		friend class detail::reflector<U>::reflect;

		static constexpr auto constructors = basic_overloaded_fundamental_constructor{};

	public:
		constexpr const namespace_t* get_namespace() const noexcept override final
		{
			return &reflect<namespace_t::global, namespace_t>();
		}
		constexpr const overloaded_constructor* get_constructors() const noexcept override final
		{
			return &constructors;
		}
	};
}
