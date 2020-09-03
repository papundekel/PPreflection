#pragma once
#include "overloaded_constructor.h"
#include "basic_overloaded_function.h"
#include "constructor_info.h"
#include "map_pack.h"

namespace detail
{
	template <typename Class, typename Constructors>
	using basic_overloaded_constructor_helper = basic_overloaded_function<
		Class,
		map_pack_types<make_full_info<Class>::template make, Constructors>,
		overloaded_constructor>;

	template <typename Class, typename Constructors>
	class basic_overloaded_constructor final : public basic_overloaded_constructor_helper<Class, Constructors>
	{
		using MappedConstructors = basic_overloaded_constructor_helper<Class, Constructors>::Functions;

	public:
		constexpr void print_name(simple_ostream& out) const noexcept override final
		{
			auto class_name = descriptor::reflect_name<Class>();
			out.write(class_name);
			out.write("::");
			out.write(class_name);
		}
		constexpr bool has_name(std::string_view name) const noexcept override final
		{
			std::string_view class_name = descriptor::reflect_name<Class>();
			if (name.starts_with(class_name) && name.substr(class_name.length(), 2) == "::")
			{
				name = name.substr(class_name.length() + 2);
				return name == class_name;
			}

			return false;
		}
		constexpr pointer_view<const cref_t<constructor>> get_constructor_overloads() const noexcept override final
		{
			return reflect_many<MappedConstructors, constructor>();
		}

		constexpr const type& get_enclosing_class() const noexcept override final
		{
			return reflect<Class, type>();
		}
	};
}
