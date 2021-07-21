#pragma once
#include <iosfwd>

#include "PP/get_type.hpp"
#include "PP/string_view.hpp"
#include "PP/view.hpp"

namespace PP
{
class ostream;
}

namespace PPreflection::detail
{
template <typename, typename>
class basic_named_descriptor;
}

namespace PPreflection
{
using namespace PP::literals;

class parent_descriptor;

///
/// @brief Base class for all descriptors.
///
class descriptor
{
	template <typename, typename>
	friend class detail::basic_named_descriptor;
	friend class class_type;
	friend class Namespace;
	friend class parent_descriptor;
	friend class class_or_namespace;

public:
	///
	/// @brief Gets the parent entity descriptor.
	///
	/// @retval parent_descriptor_none_tag The entity doesn't have a
	/// parent.
	///
	constexpr virtual parent_descriptor get_parent(
		void* = nullptr) const noexcept = 0;

	///
	/// @brief Prints the whole name of the entity.
	///
	/// @param out The stream to output to.
	///
	constexpr void print_name(PP::ostream& out) const noexcept;

	///
	/// @brief Name check.
	///
	/// @retval false if the functions doesn't have the name @p name.
	///
	constexpr virtual bool has_name(PP::string_view name) const noexcept = 0;

private:
	constexpr virtual void print_name_before_parent(
		PP::ostream& out) const noexcept = 0;

	constexpr virtual void print_name_after_parent(
		PP::ostream& out) const noexcept = 0;

	static constexpr auto get_descriptor(
		PP::string_view name,
		PP::concepts::view auto&& descriptors) noexcept
		-> decltype(&PP::declval(PP::view_type_base(PP_DECLTYPE(descriptors))))
	{
		for (const auto& d : PP_F(descriptors))
			if (d.has_name(name))
				return &d;

		return nullptr;
	}

	static constexpr void get_descriptors(
		PP::string_view name,
		PP::concepts::view auto&& descriptors,
		PP::concepts::iterator auto i_out) noexcept
	{
		for (const auto& d : PP_F(descriptors))
			if (d.has_name(name))
				*i_out++ = d;
	}

	static constexpr PP::string_view reflect_name(
		PP::concepts::type auto t) noexcept;
};

std::ostream& operator<<(std::ostream& out, const descriptor& d);
}
