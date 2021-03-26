#pragma once
#include "types/pointer_type.h"
#include "types/pointer_to_member_type.h"

namespace PPreflection
{
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

		class element
		{
			std::variant<pointer, member_pointer, unknown_bound_array, known_bound_array, U> P;
			PP::cv_qualification cv;

			constexpr bool compatible_P(const element& target) const noexcept
			{
				bool same_index = P.index() == target.P.index();

				return std::visit(PP::overloaded
				(
					[&p = target.P](member_pointer mp_this)
					{
						return std::visit(PP::overloaded
						(
							[mp_this](member_pointer mp_target){ return *mp_this.Class == *mp_target.Class; },
							[](auto){ return false; }
						), p);
					},
					[&p = target.P](known_bound_array a_this)
					{
						return std::visit(PP::overloaded
						(
							[a_this](known_bound_array a_target){ return *a_this.extent == *a_target.extent; },
							[](unknown_bound_array){ return true; },
							[](auto){ return false; }
						), p);
					},
					[&p = target.P](U u_this)
					{
						return std::visit(PP::overloaded
						(
							[u_this](U u_target){ return *u_this.u == *u_target.u; },
							[](auto){ return false; }
						), p);
					},
					[same_index](auto){ return same_index; }
				), P);
			}
		};

	private:
		PP::simple_vector<element> elements;

		constexpr void register_elements(cv_type_ptr<pointable_type> t)
		{
			while (true)
			{
				const auto* pointer_ptr = dynamic_cast<const pointer_type*>(t.type_ptr);
				if (pointer_ptr)
				{
					elements.push_back(pointer{}, t.cv);
					t = pointer_ptr->remove_pointer().to_type_ptr();
					continue;
				}

				const auto* member_pointer_ptr = dynamic_cast<const pointer_to_member_type*>(t.type_ptr);
				if (member_pointer_ptr)
				{
					elements.push_back(member_pointer{&member_pointer_ptr->get_class_type()}, t.cv);
					t = member_pointer_ptr->get_member_type().to_type_ptr();
					continue;
				}

				const auto* unknown_bound_array_ptr = dynamic_cast<const unknown_bound_array_type*>(t.type_ptr);
				if (unknown_bound_array_ptr)
				{
					elements.push_back(unknown_bound_array{}, t.cv);
					t = unknown_bound_array_ptr->remove_extent().to_type_ptr();
					continue;
				}

				const auto* known_bound_array_ptr = dynamic_cast<const known_bound_array_type*>(t.type_ptr);
				if (known_bound_array_ptr)
				{
					elements.push_back(known_bound_array{known_bound_array_ptr->get_extent()}, t.cv);
					t = known_bound_array_ptr->remove_extent().to_type_ptr();
					continue;
				}

				break;
			}

			elements.push_back(U{t.type_ptr}, t.cv);
		}

	public:
		constexpr explicit cv_qualification_signature(const pointer_type& type)
			: elements(2)
			, U(nullptr)
		{
			register_elements(type.remove_pointer().to_type_ptr());			
		}
		constexpr explicit cv_qualification_signature(const pointer_to_member_type& type)
			: elements(2)
			, U(nullptr)
		{
			register_elements(type.get_member_type().to_type_ptr());
		}

		constexpr bool compatible(cv_qualification_signature target) const noexcept
		{
			if (elements.count() != target.elements.count())
				return false;

			for (auto [element_this, element_target] : PP::zip_view_pack(elements, target.elements))
			{
				if (!(element_target.cv >= element_this.cv))
					return false;
				
				if (!element_this.compatible_P(element_target))
					return false;
			}

			auto first_diff = PP::view_find(*PP::functor([]
				(const element& element_this, const element& element_target)
				{
					return
						element_target.cv > element_this.cv ||
						(element_this.P.index() != element_target.P.index())
				}), PP::zip_view_pack(elements, target.elements))[PP::value_1];

			for (auto i = target.elements.begin(); i != first_diff; ++i)
			{
				if (!cv_is_const(i->cv))
					return false;
			}

			return true;
		}
	};
}