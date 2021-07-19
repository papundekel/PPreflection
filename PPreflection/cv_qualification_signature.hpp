#pragma once
#include <compare>

#include "PP/simple_view.hpp"
#include "PP/small_optimized_vector.hpp"

#include "types/arithmetic_type_strong.h"
#include "types/class_type.h"
#include "types/known_bound_array_type.h"
#include "types/pointer_to_member_type.h"
#include "types/pointer_type.h"
#include "types/unknown_bound_array_type.h"

namespace PPreflection
{
	static constexpr auto equality_to_partial_ordering(const auto& a,
	                                                   const auto& b) noexcept
	{
		return a == b ? std::partial_ordering::equivalent
		              : std::partial_ordering::unordered;
	}

	static constexpr auto combine(std::partial_ordering a,
	                              std::partial_ordering b) noexcept
	{
		if (a == std::partial_ordering::unordered ||
		    b == std::partial_ordering::unordered)
			return std::partial_ordering::unordered;
		else if (a == b || b == std::partial_ordering::equivalent)
			return a;
		else if (a == std::partial_ordering::equivalent)
			return b;
		else
			return std::partial_ordering::unordered;
	}

	class cv_qualification_signature
	{
		struct pointer
		{};
		struct member_pointer
		{
			const class_type* Class;
		};
		struct unknown_bound_array
		{};
		struct known_bound_array
		{
			PP::size_t extent;
		};
		struct U
		{
			const pointable_type* u;
		};

		struct element
		{
			std::variant<pointer,
			             member_pointer,
			             unknown_bound_array,
			             known_bound_array,
			             U>
				P;
			PP::cv_qualifier cv;

			constexpr std::partial_ordering operator<=>(
				const element& other) const noexcept
			{
				auto compare_cv = other.cv <=> cv;
				if (compare_cv == std::partial_ordering::unordered)
					return std::partial_ordering::unordered;

				return combine(
					compare_cv,
					std::visit(
						PP::overloaded(
							[](member_pointer mp_this, member_pointer mp_target)
							{
								return equality_to_partial_ordering(
									*mp_this.Class,
									*mp_target.Class);
							},
							[](known_bound_array a_this,
				               known_bound_array a_target)
							{
								return equality_to_partial_ordering(
									a_this.extent,
									a_target.extent);
							},
							[](U u_this, U u_target)
							{
								return equality_to_partial_ordering(
									*u_this.u,
									*u_target.u);
							},
							[](pointer, pointer)
							{
								return std::partial_ordering::equivalent;
							},
							[](known_bound_array, unknown_bound_array)
							{
								return std::partial_ordering::greater;
							},
							[](unknown_bound_array, known_bound_array)
							{
								return std::partial_ordering::less;
							},
							[](unknown_bound_array, unknown_bound_array)
							{
								return std::partial_ordering::equivalent;
							},
							[](auto, auto)
							{
								return std::partial_ordering::unordered;
							}),
						P,
						other.P));
			}
		};

	private:
		PP::small_optimized_vector<element, 4> elements;

	public:
		constexpr explicit cv_qualification_signature(const pointer_type& type)
			: elements()
		{
			register_elements(type);
		}
		constexpr explicit cv_qualification_signature(
			const pointer_to_member_type& type)
			: elements()
		{
			register_elements(type);
		}
		constexpr explicit cv_qualification_signature(
			const non_array_object_type& type)
			: elements()
		{
			if (const auto* p = dynamic_cast<const pointer_type*>(&type); p)
				register_elements(*p);
			else if (const auto* p =
			             dynamic_cast<const pointer_to_member_type*>(&type);
			         p)
				register_elements(*p);
		}

		constexpr std::partial_ordering operator<=>(
			cv_qualification_signature other) const noexcept
		{
			if (elements.count() != other.elements.count())
				return std::partial_ordering::unordered;

			auto difference = std::partial_ordering::equivalent;
			PP::size_t index_first_difference = 0;

			{
				PP::size_t i = 0;

				for (auto [element_this, element_other] :
				     PP::zip_view_pack(elements, other.elements))
				{
					auto compare_element = element_this <=> element_other;

					if (compare_element == std::partial_ordering::unordered)
					{
						return std::partial_ordering::unordered;
					}
					else if (compare_element !=
					         std::partial_ordering::equivalent)
					{
						if (difference == std::partial_ordering::equivalent)
						{
							difference = compare_element;
							index_first_difference = i;
						}
						else if (difference != compare_element)
							return std::partial_ordering::unordered;
					}

					++i;
				}
			}

			if (difference == std::partial_ordering::equivalent)
				return std::partial_ordering::equivalent;

			auto make_view = [index_first_difference](const auto& elements)
			{
				return PP::simple_view(elements.begin(),
				                       elements.begin() +
				                           index_first_difference);
			};

			for (auto& element :
			     make_view(difference == std::partial_ordering::less
			                   ? elements
			                   : other.elements))
			{
				if (!PP::cv_is_const(element.cv))
					return std::partial_ordering::unordered;
			}

			return difference;
		}

	private:
		constexpr void register_elements(const pointer_to_member_type& t)
		{
			register_elements_implementation(t.get_member_type().to_type_ptr());
		}
		constexpr void register_elements(const pointer_type& t)
		{
			register_elements_implementation(t.remove_pointer().to_type_ptr());
		}

		constexpr void register_elements_implementation(
			cv_type_ptr<pointable_type> t)
		{
			while (true)
			{
				const auto* pointer_ptr =
					dynamic_cast<const pointer_type*>(t.type_ptr);
				if (pointer_ptr)
				{
					elements.push_back(pointer{}, t.cv);
					t = pointer_ptr->remove_pointer().to_type_ptr();
					continue;
				}

				const auto* member_pointer_ptr =
					dynamic_cast<const pointer_to_member_type*>(t.type_ptr);
				if (member_pointer_ptr)
				{
					elements.push_back(
						member_pointer{&member_pointer_ptr->get_class_type()},
						t.cv);
					t = member_pointer_ptr->get_member_type().to_type_ptr();
					continue;
				}

				const auto* unknown_bound_array_ptr =
					dynamic_cast<const unknown_bound_array_type*>(t.type_ptr);
				if (unknown_bound_array_ptr)
				{
					elements.push_back(unknown_bound_array{}, t.cv);
					t = unknown_bound_array_ptr->remove_extent().to_type_ptr();
					continue;
				}

				const auto* known_bound_array_ptr =
					dynamic_cast<const known_bound_array_type*>(t.type_ptr);
				if (known_bound_array_ptr)
				{
					elements.push_back(
						known_bound_array{known_bound_array_ptr->get_extent()},
						t.cv);
					t = known_bound_array_ptr->remove_extent().to_type_ptr();
					continue;
				}

				break;
			}

			elements.push_back(U{t.type_ptr}, t.cv);
		}
	};
}
